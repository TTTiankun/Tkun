#include <iostream>
#include <opencv2/highgui.hpp>
#include <openvino/core/type/element_type.hpp>
#include <openvino/runtime/compiled_model.hpp>
#include <string>
#include <vector>
#include <algorithm>

#include <openvino/openvino.hpp> //openvino header file
#include <opencv2/opencv.hpp>    //opencv header file
#include <openvino/opsets/opset1.hpp>
#include <openvino/runtime/compiled_model.hpp>
#include <openvino/runtime/core.hpp>
#include <openvino/runtime/infer_request.hpp>
#include <openvino/runtime/intel_cpu/properties.hpp>
#include <openvino/runtime/intel_gpu/properties.hpp>
#include <openvino/runtime/tensor.hpp>

int GPU_mode = 0; // 0: CPU mode; 1: GPU mode
std::string model_path = "/home/jason/Desktop/test-speed/openvino/yolov8-cls-int.onnx"; // Model path

using namespace cv;
using namespace dnn;

// Keep the ratio before resize
Mat letterbox(const cv::Mat& source)
{
    int col = source.cols;
    int row = source.rows;
    int _max = MAX(col, row);
    Mat result = Mat::zeros(_max, _max, CV_8UC3);
    source.copyTo(result(Rect(0, 0, col, row)));
    return result;
}

int main(int argc, char* argv[])
{
    // -------- Step 1. Initialize OpenVINO Runtime Core --------
    ov::Core core;

    auto model = core.read_model(model_path);

    // -------- Step 2. Compile the Model --------
    ov::preprocess::PrePostProcessor ppp(model);
    
    //设置输入
    // ov::preprocess::InputInfo &input = ppp.input(0);
    // // input.tensor()
    // //         .set_layout("NHWC")
    // //         // .set_element_type(ov::element::f16)
    // //         .set_shape({1, 32, 32, 3});
    
    // input.model().set_layout("NCHW");
    // input.preprocess().convert_layout("NCHW");
    
    // //只有GPU才可以使用fp16
    // if (GPU_mode == 1) {
    //     input.preprocess().convert_element_type(ov::element::f16);
    // } else {
    //     input.preprocess().convert_element_type(ov::element::f32);
    // }

    // //模型缩放
    // input.preprocess().scale(255.0f);
    
    // //设置输出
    // ov::preprocess::OutputInfo &output = ppp.output(0);
    // output.postprocess().convert_element_type(ov::element::f32);
    
    //构建模型
    model = ppp.build();

    //CPU初始化设置
    if(GPU_mode == 0){
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
    if(GPU_mode == 1){
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
    ov::CompiledModel compiled_model;
    //获取可执行模型
    if (GPU_mode == 0) {// CPU模式
        compiled_model = core.compile_model(model, "CPU");
    } else if (GPU_mode == 1) {// GPU模式
        compiled_model = core.compile_model(model, "GPU", ov::hint::inference_precision(ov::element::f16));
    }
    
    ov::InferRequest curr_request=compiled_model.create_infer_request();//创建推理请求
    ov::InferRequest next_request=compiled_model.create_infer_request();//创建推理请求




    std::cout<<"The asyncinference init success!"<<std::endl;
    cv::waitKey(1000);

    // -------- Step 3. Create an Inference Request --------
    ov::InferRequest infer_request = compiled_model.create_infer_request();

    // -------- Step 4.Read a picture file and do the preprocess --------
    Mat img1 = cv::imread("../1.jpg"); 
    Mat img2 = cv::imread("../2.jpg");
    Mat img3 = cv::imread("../3.jpg");
    Mat img4 = cv::imread("../4.jpg");
    Mat img5 = cv::imread("../5.jpg");
    
    std::vector<cv::Mat> img;
    img.push_back(img1);
    img.push_back(img2);
    img.push_back(img3);
    img.push_back(img4);
    img.push_back(img5);

    int num = 5;
    int curr_num = 1;

    Mat letterbox_img = letterbox(img[0]);

    Mat blob = blobFromImage(letterbox_img, 1.0 / 255.0, Size(32, 32), Scalar(), true);
    auto input_port = compiled_model.input();
    ov::Tensor input_tensor_curr(input_port.get_element_type(), input_port.get_shape(), blob.ptr(0));
    curr_request.set_input_tensor(input_tensor_curr);

    while(1){
        if(num > 1){
            curr_request.start_async();
        }

        for(int i=1;i<=num;i++){
            auto start = std::chrono::high_resolution_clock::now();

            if(curr_num == num){
                try{
                    curr_request.wait();
                }catch(const std::exception& e){
                    throw std::runtime_error("BUSY");
                }
                try{
                    next_request.wait();
                }catch(const std::exception& e){
                    throw std::runtime_error("BUSY");
                }

                curr_request.infer();

                auto curr_output = curr_request.get_output_tensor(0);
                auto outdata = curr_output.data<float>();

                int max = 0;
                float prob = 0;
                for (int i = 0; i < 9; i++) {
                    if (outdata[i] > prob) {
                        max = i+1;
                        prob = outdata[i];
                    }
                }
                std::cout << "The result of " << max << " is " << prob << std::endl;
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "The time of is " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us" << std::endl;
                std::cout<<"The end of the program"<<std::endl;
                curr_num = 1;
                cv::waitKey(1000);
            }else {
                
                Mat letterbox_img = letterbox(img[i]);
                // imshow("letterbox_img", letterbox_img);
                // waitKey(1000);
                Mat blob = blobFromImage(letterbox_img, 1.0 / 255.0, Size(32, 32), Scalar(), true);
                auto input_port = compiled_model.input();
                ov::Tensor input_tensor_next(input_port.get_element_type(), input_port.get_shape(), blob.ptr(0));
                next_request.set_input_tensor(input_tensor_next);   
                
                next_request.start_async();

                try{
                    curr_request.wait();
                }catch(const std::exception& e){
                    throw std::runtime_error("BUSY");
                }

                auto curr_output = curr_request.get_output_tensor(0);
                auto outdata = curr_output.data<float>();

                int max = 0;
                float prob = 0;
                for (int i = 0; i < 9; i++) {
                    if (outdata[i] > prob) {
                        max = i+1;
                        prob = outdata[i];
                    }
                }

                std::cout << "The result of " << max << " is " << prob << std::endl;
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "The time of is " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us" << std::endl;
                std::cout<<curr_num + 1<<std::endl;
                curr_num++;

                std::swap(curr_request, next_request);

            }
        }

    }
    return 0;
}
