#include "numberdetector.h"
#include"yolov8pose.h"

#include<iostream>

#include <opencv2/core/cvstd.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<openvino/openvino.hpp>
#include <openvino/runtime/infer_request.hpp>

Numberdetector::Numberdetector(){
    std::cout<<"number-inference begin!"<<std::endl;
}

Numberdetector::~Numberdetector(){}


bool Numberdetector::init(int GPU_mode, std::string model_path,
                double score_threshold){
    
    this->model_path = model_path;
    this->score_threshold = score_threshold;
    this->GPU_mode = GPU_mode;


    //创建模型
    auto model = core.read_model(model_path);
    
    //创建预处理处理器
    ov::preprocess::PrePostProcessor ppp(model);
    
    //设置输入
    ov::preprocess::InputInfo &input = ppp.input(0);
    input.tensor()
            .set_layout("NHWC")
            .set_element_type(ov::element::u8)
            .set_shape({1, img_height, img_width, 1});
    
    input.model().set_layout("NCHW");
    input.preprocess().convert_layout("NCHW");
    
    //只有GPU才可以使用fp16
    if (GPU_mode == 1) {
        input.preprocess().convert_element_type(ov::element::f16);
    } else {
        input.preprocess().convert_element_type(ov::element::f32);
    }

    //模型缩放
    input.preprocess().scale(255.0f);
    
    //设置输出
    ov::preprocess::OutputInfo &output = ppp.output(0);
    output.postprocess().convert_element_type(ov::element::f32);
    
    //构建模型
    model = ppp.build();

    //CPU初始化设置
    if(this->GPU_mode == 0){
        auto cpu_properties = core.get_property("CPU", ov::supported_properties);//储存CPU设置
        for (auto &&property: cpu_properties) {
            if (property != ov::supported_properties.name()) {
                if (property.is_mutable()) {
                    if (property == "AFFINITY") {
                        core.set_property("CPU", ov::affinity(ov::Affinity::HYBRID_AWARE));
                        continue;
                    }
                    if (property == "INFERENCE_NUM_THREADS") {
                        core.set_property("CPU", ov::inference_num_threads(16));
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
    * ov::streams::num(12)//设置推理实例并发数为5个
    * ov::streams::num(ov::steams::AUTO)//创建最少的流以提高性能
    * ov::streams::num(ov::streams::NUMA)//推理实例数按计算资源平均分配
    * ov::inference_num_threads(16)//设置推理实例的线程并发数为16个,设置太满同时有大型程序允许会卡顿,会卡得厉害,
    * ov::intel_cpu::denormals_optimization(true)//非正规优化，耗时较长，有些情况能加速，大部分情况效果不明显
    */
    
    //GPU初始化设置
    if(this->GPU_mode == 1){
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
    * ,ov::enable_profiling(true))//允许解析数据,耗时较长,不知道有什么用
    * ,ov::compilation_num_threads(16)//设置编译实例的线并发数为16
    * ,ov::cache_dir("../../Cache")//设置缓存路径
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
    
    this->curr_request=compiled_model.create_infer_request();//创建推理请求
    this->next_request=compiled_model.create_infer_request();//创建推理请求
    this->curr_input_tensor = this->curr_request.get_input_tensor();
    this->next_input_tensor = this->next_request.get_input_tensor();



    std::cout<<"The asyncinference init success!"<<std::endl;
    cv::waitKey(1000);
    return true;
}

bool Numberdetector::pre_img(cv::Mat &frame, ov::Tensor &input_tensor){
    if(frame.empty()){
        std::cout << "The frame is empty!" << std::endl;
        return false;
    }else{
        resize(frame, frame, cv::Size(img_width, img_height));//设置图片输入尺寸
        auto in_data = input_tensor.data<uint8_t>();//设置输入的数据类型
        cv::Mat data_mat(img_height, img_width, CV_8UC1, in_data);//设置输入的数据格式
        cv::cvtColor(frame, data_mat, cv::COLOR_BGR2GRAY);//转换为灰度图
        cv::imshow("number_image", frame);
        return true;
    }
}

    

void Numberdetector::cut_img(cv::Mat &frame, std::vector<Yolov8pose::Object> &detected_armors){
    for(int i = 0; detected_armors.size() > i;i++){
        cv::Rect rect = detected_armors[i].rect;
        int img_width = frame.size().width;
        int img_height = frame.size().height;
        if(rect.x < 0 || rect.y < 0 || rect.x + rect.width > img_width || rect.y + rect.height > img_height){
            std::cout << "The armor is out of the image!" << std::endl;
            continue;
        }
        cv::Mat number_image = frame(rect);
        if(number_image.empty()){
            std::cout << "The number_image is empty!" << std::endl;
            continue;
        }
         detected_armors[i].number_image = number_image;
    }
}

