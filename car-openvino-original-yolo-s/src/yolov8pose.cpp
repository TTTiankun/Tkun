#include"yolov8pose.h"

#include <cstddef>
#include<iostream>

#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <openvino/core/preprocess/input_model_info.hpp>
#include <openvino/core/preprocess/pre_post_process.hpp>
#include <openvino/core/type/element_type.hpp>
#include<openvino/openvino.hpp>
#include <openvino/runtime/intel_cpu/properties.hpp>//CPU插件属性头文件
#include <openvino/runtime/intel_gpu/properties.hpp>//GPU插件属性头文件
#include <string>

Yolov8pose::Yolov8pose(){
    std::cout<<"The image inference(pose) begin!"<<std::endl;
}
Yolov8pose::~Yolov8pose(){}

bool Yolov8pose::init(int GPU_mode, std::string model_path,
                double score_threshold, double NMS_threshold,
                 std::vector<cv::Scalar> color,std::vector<std::string> &class_names){
    this ->GPU_mode = GPU_mode;
    this ->model_path = model_path;
    this ->score_threshold = score_threshold;
    this ->NMS_threshold = NMS_threshold;
    this ->colors = color;
    this ->class_names = class_names;

    auto model = core.read_model(model_path);//读取模型

    //获取模型尺寸
    ov::Shape model_input_shape = model->input().get_shape();
    std::cout<<"model_input_shape: "<<model_input_shape<<std::endl;
    this->model_input_w = model_input_shape[3];
    this->model_input_h = model_input_shape[2];

    //创建预处理后处理器 该优化会影响推理结果，但去除优化后不会影响速度，怀疑是设置的输出输入格式不对
    ov::preprocess::PrePostProcessor ppp(model);

    // 输入设置
    // ov::preprocess::InputInfo &input = ppp.input();

    // input.tensor().set_layout("NHWC").set_element_type(ov::element::f32).set_shape({1, this->model_input_h, this->model_input_w, 3}).set_color_format(ov::preprocess::ColorFormat::BGR);
    // // 模型设置
    // input.model().set_layout("NCHW");
    // // 预处理设置
    // input.preprocess().convert_layout("NCHW").convert_color(ov::preprocess::ColorFormat::RGB);

    // if (this->GPU_mode == 1) {
    //     input.preprocess().convert_element_type(ov::element::f16);
    // } else {
    //     input.preprocess().convert_element_type(ov::element::f32);
    // }

    //设置模型缩放尺寸
    //input.preprocess().scale({255.0f, 255.0f, 255.0f});

    // // 输出设置
    ov::preprocess::OutputInfo &output = ppp.output();

    // ov::Shape model_output_shape = model->output().get_shape();
    // if (model_output_shape[1] > model_output_shape[2]) {
    //     this->model_output_w = model_output_shape[2];
    //     this->model_output_h = model_output_shape[1];
    // } else {
    //     this->model_output_w = model_output_shape[1];
    //     this->model_output_h = model_output_shape[2];
    //     output.tensor().set_layout("CWH");
    //     output.model().set_layout("CHW");
    //     output.postprocess().convert_layout("CHW");
    // }

    // output.tensor().set_element_type(ov::element::f32);
    // output.postprocess().convert_element_type(ov::element::f32);
    
    //可省去的代码
    //因为GPU用f16,所以这里要转换为f32输出
    // if (this->GPU_mode == 1) {
    //     output.postprocess().convert_element_type(ov::element::f32);
    // }

    //构建模型
    model = ppp.build();
    
    //CPU初始化设置
    if(this->GPU_mode == 0){
        std::cout<<"The CPU(yolo) mode is setting!"<<std::endl;
        auto cpu_properties = core.get_property("CPU", ov::supported_properties);//储存CPU设置
        for (auto &&property: cpu_properties) {
            if (property != ov::supported_properties.name()) {
                if (property.is_mutable()) {
                    if (property == "AFFINITY") {
                        core.set_property("CPU", ov::affinity(ov::Affinity::HYBRID_AWARE));
                        continue;
                    }
                    if (property == "INFERENCE_NUM_THREADS") {
                        core.set_property("CPU", ov::inference_num_threads(32));
                        continue;
                    }
                    if (property == "INFERENCE_PRECISION_HINT") {
                        core.set_property("CPU", ov::hint::inference_precision(ov::element::f32));
                        continue;
                    }
                    if (property == "PERFORMANCE_HINT") {
                        core.set_property("CPU", ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY));
                        continue;
                    }
                    if (property == "NUM_STREAMS") {
                        core.set_property("CPU", ov::streams::num(ov::streams::NUMA));
                        continue;
                    }
                    if (property == "PERF_COUNT") {
                        core.set_property("CPU", ov::enable_profiling(false));
                        continue;
                    }
                }
            }
        }
    }
    /*CPU设置
    * ov::affinity(ov::Affinity::HYBRID_AWARE)//设置核心与线程的关系,0:禁用线程相关性:NONE;1,将线程固定到核心，最适合静态基准测试:CODE;
    *               2,将线程固定到NUMA节点，最适合实际情况:NUMA;3,让运行时锁定内核类型，例如，对于延迟任务，更喜欢“大”内核:HYBRID_AWARE
    * ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY)//设置性能模式为低延迟:LATENCY;默认:UNDEFINED
    * ov::hint::inference_precision(ov::element::f32)//设置推理精度，cpu只能是f32
    * ov::enable_profiling(false)//允许解析数据,耗时较长,不知道有什么用,设置为false关掉
    * ov::streams::num(ov::steams::AUTO)//创建最少的流以提高性能
    * ov::streams::num(ov::streams::NUMA)//推理实例数按计算资源平均分配
    * ov::inference_num_threads(16)//设置推理实例的线程并发数为32个,设置太满同时有大型程序允许会卡顿,会卡得厉害,
    */
    
    //GPU初始化设置
    if(this->GPU_mode == 1){
        std::cout<<"The GPU(yolo) mode is setting!"<<std::endl;
        auto gpu_properties = core.get_property("GPU", ov::supported_properties);//储存GPU设置
        for (auto &&property: gpu_properties) {
            if (property != ov::supported_properties.name()) {
                if (property.is_mutable()) {
                    if (property == "INFERENCE_PRECISION_HINT") {
                        core.set_property("GPU", ov::hint::inference_precision(ov::element::f16));
                        continue;
                    }
                    if (property == "PERFORMANCE_HINT") {
                        core.set_property("GPU", ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY));
                        continue;
                    }
                    if (property == "MODEL_PRIORITY") {
                        core.set_property("GPU", ov::hint::model_priority(ov::hint::Priority::HIGH));
                        continue;
                    }
                    if (property == "GPU_HOST_TASK_PRIORITY") {
                        core.set_property("GPU", ov::intel_gpu::hint::host_task_priority(ov::hint::Priority::HIGH));
                        continue;
                    }
                    if (property == "CACHE_DIR") 
                    {
                        core.set_property("GPU", ov::cache_dir("../Save_Buffer_Dir"));
                        continue;  
                    }                  
                    if (property == "GPU_QUEUE_PRIORITY") {
                        core.set_property("GPU", ov::intel_gpu::hint::queue_priority(ov::hint::Priority::HIGH));
                        continue;
                    }
                    if (property == "GPU_QUEUE_THROTTLE") {
                        core.set_property("GPU", ov::intel_gpu::hint::queue_throttle(ov::intel_gpu::hint::ThrottleLevel::HIGH));
                        continue;
                    }
                    if (property == "PERF_COUNT") {
                        core.set_property("GPU", ov::enable_profiling(false));
                        continue;
                    }
                    if (property == "COMPILATION_NUM_THREADS") {
                        core.set_property("GPU", ov::compilation_num_threads(16));
                        continue;
                    }
                }
            }
        }
    }
    /*GPU模式设置
    * ,ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY)//设置性能模式为低延迟:LATENCY;默认:UNDEFINED
    * ,ov::hint::model_priority(ov::hint::Priority::MEDIUM)//设置模型优先级为高:HIGH;中:MEDIUM(默认);低:LOW
    * ,ov::hint::inference_precision(ov::element::f32)//设置推理精度，cpu只能是f32
    * ,ov::enable_profiling(true))//允许解析数据,耗时较长,不知道有什么用???
    * ,ov::compilation_num_threads(16)//设置编译实例的线并发数为16
    * ,ov::intel_gpu::hint::host_task_priority(ov::hint::Priority::HIGH)//设置GPU插件使用的TBB关联的cpu核心类型为大核(如果可用):HIGH;任意可用核心:MEDIUM(默认);小核(如果可用):LOW
    * ,ov::intel_gpu::hint::queue_priority(ov::hint::Priority::HIGH)//设置OpenCL队列优先级为高:HIGH;中:MEDIUM(默认);低:LOW
    * ,ov::intel_gpu::hint::queue_throttle(ov::intel_gpu::hint::ThrottleLevel::HIGH)//设置OpenCL节流阀，控制的能耗为高:HIGH;中:MEDIUM(默认);低:LOW
    */

    //获取可执行模型
    if (this->GPU_mode == 0) {// CPU模式
        compiled_model = core.compile_model(model, "CPU");
    } else if (this->GPU_mode == 1) {// GPU模式
        compiled_model = core.compile_model(model, "GPU", ov::hint::inference_precision(ov::element::f16));
    }
    
    this->infer_request=compiled_model.create_infer_request();//创建推理请求
    this->input_tensor = infer_request.get_input_tensor();
    this-> output_tensor = infer_request.get_output_tensor();

    std::cout<<"The image inference(pose) init success!"<<std::endl;
    cv::waitKey(1000);
    return true;
}


bool Yolov8pose::process(cv::Mat &source,std::vector<Object> &detected_armors,
                std::vector<Object> &detected_robots){
    pre_img(source);
    inference();
    extract();
    cv::dnn::NMSBoxes(boxes, class_scores, score_threshold, NMS_threshold, indices);
    find_result(detected_armors, detected_robots);
    return true;
}

cv::Mat Yolov8pose::letterbox(cv::Mat &source){
    col = source.cols;
    row = source.rows;
    max = MAX(col, row);
    cv::Mat result = cv::Mat::zeros(max, max, CV_8UC3);
    source.copyTo(result(cv::Rect(0, 0, col, row)));
    return result;
}

bool Yolov8pose::pre_img(cv::Mat &frame){
    letterbox_img = letterbox(frame);
    scale = letterbox_img.size[0] / 640.0;
    blob = cv::dnn::blobFromImage(letterbox_img, 1.0 / 255.0, cv::Size(640, 640), cv::Scalar(), true);
    return true;
}

bool Yolov8pose::inference(){
    
    input_port = compiled_model.input();//获取输入端口
    //获取输入张量
    input_tensor = ov::Tensor (input_port.get_element_type(), input_port.get_shape(), blob.ptr(0));
    //测试
    //std::cout << "input_tensor_type: " << input_port.get_element_type()<< std::endl;

    infer_request.set_input_tensor(input_tensor);//获取推理请求
    infer_request.infer();//推理
    output_tensor = infer_request.get_output_tensor(0);//获取输出张量
    output_shape = output_tensor.get_shape();//获取输出形状
    //测试
    //std::cout << "output_shape: " << output_shape << std::endl;
    
    output_data = output_tensor.data<float>();//获取输出数据

    return true;
}

void Yolov8pose::extract(){
        
        output_buffer = cv::Mat(output_shape[1], output_shape[2], CV_32F, output_data);//获取输出缓冲区
        cv::transpose(output_buffer, output_buffer);//转置
        
        //如果是TDT-POSE 将会有14个通道 box[cx, cy, w, h] + Score_class1 + Score_class2 + [4,2] keypoints
        for (int i = 0; i < output_buffer.rows; i++) {
        float class_score1 = output_buffer.at<float>(i, 4);
        float class_score2 = output_buffer.at<float>(i, 5);
        maxscore = std::max(class_score1, class_score2);

        if (maxscore > score_threshold) {
            
            float cx = output_buffer.at<float>(i, 0);
            float cy = output_buffer.at<float>(i, 1);
            float w = output_buffer.at<float>(i, 2);
            float h = output_buffer.at<float>(i, 3);
            // 获取框框
            int left = int((cx - 0.5 * w) * scale);
            int top = int((cy - 0.5 * h) * scale);
            int width = int(w * scale);
            int height = int(h * scale);
            // 获取关键点
            std::vector<float> keypoints;
            cv::Mat kpts = output_buffer.row(i).colRange(5, 14);
            for (int i = 0; i < 17; i++) {                
                float x = kpts.at<float>(0, i * 3 + 0) * scale;
                float y = kpts.at<float>(0, i * 3 + 1) * scale;
                float s = kpts.at<float>(0, i * 3 + 2);
                keypoints.push_back(x);
                keypoints.push_back(y);
                keypoints.push_back(s);
            }

            class_scores.push_back(maxscore);
            if(class_score1 > class_score2)
                class_ids.push_back(0);
            else
                class_ids.push_back(1);

            boxes.push_back(cv::Rect(left, top, width, height));
            obj_keypoints.push_back(keypoints);
        }
    }
}

void Yolov8pose::find_result(std::vector<Object> &detected_armors,
                std::vector<Object> &detected_robots){
    for (size_t i = 0; i < indices.size(); i++) {
        int idx = indices[i];
        int class_id = class_ids[idx];
        if(class_id == 0){
            //装甲板
            detected_armors.push_back(Object{boxes[idx], obj_keypoints[idx], class_scores[idx]});
        }else{
            //机器人
            detected_robots.push_back(Object{boxes[idx], obj_keypoints[idx], class_scores[idx]});
        }
    }
    //清空相关容器
    indices.clear();
    class_ids.clear();
    class_scores.clear();
    boxes.clear();
}

void Yolov8pose::show_result(cv::Mat &source, std::vector<Object> &detected_armors,
                std::vector<Object> &detected_robots){
    for(size_t i = 0; i < detected_armors.size(); i++){
        cv::Rect show_rect = detected_armors[i].rect;
        cv::rectangle(source, show_rect, cv::Scalar(0, 255, 0), 2);
        std::string label = class_names[0] + ":" + std::to_string(class_scores[detected_armors[i].object_score]).substr(0, 4);
        cv::Size textSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, 0);
        cv::Rect textBox(detected_armors[i].rect.tl().x, detected_armors[i].rect.tl().y - 15, textSize.width, textSize.height+5);
        cv::rectangle(source, textBox, colors[0], cv::FILLED);
        cv::putText(source, label, cv::Point(detected_armors[i].rect.tl().x, detected_armors[i].rect.tl().y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255));
        cv::putText(source, std::to_string(detected_armors[i].armor_id), cv::Point(detected_armors[i].rect.tl().x + 10, detected_armors[i].rect.tl().y + 20), cv::FONT_HERSHEY_COMPLEX, 0.8, cv::Scalar(255, 155, 55));
    }

    for(size_t i = 0; i < detected_robots.size(); i++){
        cv::Rect show_rect = detected_robots[i].rect;
        cv::rectangle(source, show_rect, cv::Scalar(0, 255, 0), 2);
        std::string label = class_names[1] + ":" + std::to_string(class_scores[detected_robots[i].object_score]).substr(0, 4);
        cv::Size textSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, 0);
        cv::Rect textBox(detected_robots[i].rect.tl().x, detected_robots[i].rect.tl().y - 15, textSize.width, textSize.height+5);
        cv::rectangle(source, textBox, colors[0], cv::FILLED);
        cv::putText(source, label, cv::Point(detected_robots[i].rect.tl().x, detected_robots[i].rect.tl().y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255));
    }
}