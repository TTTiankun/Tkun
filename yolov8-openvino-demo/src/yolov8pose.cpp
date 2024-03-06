#include"yolov8pose.h"

#include<iostream>

#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <openvino/core/type/element_type.hpp>
#include<openvino/openvino.hpp>

Yolov8pose::Yolov8pose(){
    std::cout<<"The image inference(pose) begin!"<<std::endl;
}
Yolov8pose::~Yolov8pose(){}

bool Yolov8pose::init(int GPU_model, std::string model_path,
                double score_threshold, double NMS_threshold,
                 std::vector<cv::Scalar> color,std::vector<std::string> &class_names){
    this ->GPU_model = GPU_model;
    this ->model_path = model_path;
    this ->score_threshold = score_threshold;
    this ->NMS_threshold = NMS_threshold;
    this ->colors = color;
    this ->class_names = class_names;

    if(GPU_model == 1){
        std::cout<<"使用GPU推理"<<std::endl;
        
        compiled_model=core.compile_model(model_path,"GPU",
                                    ov::hint::inference_precision(ov::element::f16),//使用GPU推理，使用fp16精度,加速百分之30左右
                                    ov::hint::model_priority(ov::hint::Priority::HIGH),//设置模型优先级为高 不影响推理速度
                                    ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY),//设置推理模式为低延迟模式，加速百分之5左右
                                    ov::compilation_num_threads(16),//设置编译线程数为16
                                    ov::intel_gpu::hint::host_task_priority(ov::hint::Priority::HIGH),//设置GPU插件使用的TBB关联的cpu核心类型为大核(如果可用):HIGH;任意可用核心:MEDIUM(默认);小核(如果可用):LOW
                                    ov::intel_gpu::hint::queue_priority(ov::hint::Priority::HIGH),//设置OpenCL队列优先级为高:HIGH;中:MEDIUM(默认);低:LOW
                                    ov::intel_gpu::hint::queue_throttle(ov::intel_gpu::hint::ThrottleLevel::HIGH),//设置OpenCL节流阀，控制的能耗为高:HIGH;中:MEDIUM(默认);低:LOW 
                                    ov::enable_profiling(false)//设置是否开启推理性能分析
                                    //TODO:更多的推理参数设置请参考openvino文档
                                    );
    }else{
        std::cout<<"使用CPU推理"<<std::endl;
        compiled_model=core.compile_model(model_path,"CPU",
                                    ov::hint::inference_precision(ov::element::f32),//使用CPU推理，使用fp32精度,因为不能使用fp16精度
                                    ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY),//设置推理模式为低延迟模式，加速百分之5左右
                                    ov::affinity(ov::Affinity::HYBRID_AWARE),//设置CPU推理使用的线程亲和性为混合感知
                                    ov::enable_profiling(false),//设置是否开启推理性能分析
                                    ov::streams::num(ov::streams::NUMA)//设置CPU推理使用的流数为NUMA
                                    //TODO:更多的推理参数设置请参考openvino文档
                                    );
    }

    this->infer_request=compiled_model.create_infer_request();//创建推理请求
    this->input_tensor = infer_request.get_input_tensor();
    this-> output_tensor = infer_request.get_output_tensor();

    return true;
}


bool Yolov8pose::process(cv::Mat &source){
    pre_img(source);
    inference();
    extract();
    cv::dnn::NMSBoxes(boxes, class_scores, score_threshold, NMS_threshold, indices);
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
        
        
        //如果是yolov8n-pose 将会有56个通道 box[cx, cy, w, h] + Score + [17,3] keypoints
        for (int i = 0; i < output_buffer.rows; i++) {
        float class_score = output_buffer.at<float>(i, 4);

        if (class_score > score_threshold) {
            
            class_scores.push_back(class_score);
            class_ids.push_back(0); 
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
            cv::Mat kpts = output_buffer.row(i).colRange(5, 56);
            for (int i = 0; i < 17; i++) {                
                float x = kpts.at<float>(0, i * 3 + 0) * scale;
                float y = kpts.at<float>(0, i * 3 + 1) * scale;
                float s = kpts.at<float>(0, i * 3 + 2);
                keypoints.push_back(x);
                keypoints.push_back(y);
                keypoints.push_back(s);
            }

            boxes.push_back(cv::Rect(left, top, width, height));
            obj_keypoints.push_back(keypoints);
        }
    }
}

void Yolov8pose::show(cv::Mat &source){
    for (size_t i = 0; i < indices.size(); i++) {
        int index = indices[i];
        //画框框
        cv::rectangle(source,boxes[index], cv::Scalar(0, 0, 255), 2, 8);
        std::string label = "Person:" + std::to_string(class_scores[index]).substr(0, 4);//提取长度为4的字符串
        cv::Size textSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, 0);
        cv::Rect textBox(boxes[index].tl().x, boxes[index].tl().y - 15, textSize.width, textSize.height+5);
        cv::rectangle(source, textBox, cv::Scalar(0, 0, 255), cv::FILLED);
        cv::putText(source, label, cv::Point(boxes[index].tl().x, boxes[index].tl().y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255));
        // 画点
        std::vector<float> object_keypoints = obj_keypoints[index];
        for (int i = 0; i < 4; i++) {
            int x = std::clamp(int(object_keypoints[i*3+0]), 0, source.cols);//将object_keypoints的值限制在0到source.cols之间
            int y = std::clamp(int(object_keypoints[i*3+1]), 0, source.rows);
            cv::circle(source, cv::Point(x, y), 5, colors[i], -1);            
        }
    }
    //清空相关的容器
    class_scores.clear();
    class_ids.clear();
    boxes.clear();
    obj_keypoints.clear();
    indices.clear();   
}