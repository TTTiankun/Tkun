#include <chrono>
#include <cmath>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <openvino/core/shape.hpp>
#include <openvino/openvino.hpp>
#include <openvino/opsets/opset1.hpp>
#include <openvino/runtime/infer_request.hpp>
#include <openvino/runtime/intel_cpu/properties.hpp>
#include <openvino/runtime/intel_gpu/properties.hpp>
#include <openvino/runtime/tensor.hpp>

using namespace std;
using namespace cv;


std::string xml_path = "/home/jason/Desktop/perception/model/number/best.onnx";


ov::Core core;
ov::CompiledModel compiled_model;
ov::InferRequest curr_request;
ov::InferRequest next_request;


int main(){
     std::cout << "openvino numdetector init " << xml_path << std::endl;

    int gpu_mode = 0;

    int img_width=28;
    int img_height=28;

    auto model = core.read_model(xml_path);

    ov::preprocess::PrePostProcessor ppp(model);
    ov::preprocess::InputInfo &input = ppp.input(0);
    input.tensor()
            .set_layout("NHWC")
            .set_element_type(ov::element::u8)
            .set_shape({1, img_height, img_width, 1});
    input.model().set_layout("NCHW");
    input.preprocess().convert_layout("NCHW");
    if (gpu_mode == 1) {
        input.preprocess().convert_element_type(ov::element::f16);
    } else {
        input.preprocess().convert_element_type(ov::element::f32);
    }

    input.preprocess().scale(255.0f);
    ov::preprocess::OutputInfo &output = ppp.output(0);
    output.postprocess().convert_element_type(ov::element::f32);
    model = ppp.build();

    if (gpu_mode == 0) {
        // CPU设置
        auto cpu_properties = core.get_property("CPU", ov::supported_properties);
        for (auto &&property: cpu_properties) {
            if (property != ov::supported_properties.name()) {
                if (property.is_mutable()) {
                    if (property == "AFFINITY") {
                        core.set_property("CPU", ov::affinity(ov::Affinity::NUMA));
                        continue;
                    }
                    if (property == "INFERENCE_NUM_THREADS") {
                        core.set_property("CPU", ov::inference_num_threads(16));
                        continue;
                    }
                    if (property == "INFERENCE_PRECISION_HINT") {
                        core.set_property("CPU",
                                          ov::hint::inference_precision(ov::element::f32));
                        continue;
                    }
                    if (property == "PERFORMANCE_HINT") {
                        core.set_property("CPU", ov::hint::performance_mode(
                                                         ov::hint::PerformanceMode::LATENCY));
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
    }

    //     获取可执行网络
    if (gpu_mode == 0) {// CPU模式
        compiled_model = core.compile_model(
                model, "CPU",
                ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY));
    } 

    std::cout<<"init is over!"<<std::endl;

        /*
     * 可以设置环境变量OPENVINO_HETERO_VISUALIZE=1获得操作和图的注释，来针对性设置子图和操作所用设备,
     * 注释文件位于cmake-build-debug/bin/中,命令行使用 xdot *.dot读取
     */
    

    curr_request = compiled_model.create_infer_request();
    next_request = compiled_model.create_infer_request();
    
    cv::Mat image_curr = cv::imread("/home/jason/Desktop/1.jpg");
    cv::Mat image_next = cv::imread("/home/jason/Desktop/2.jpg");

    
    resize(image_curr, image_curr, Size(img_width, img_height));

    ov::Tensor curr_input_tensor = curr_request.get_input_tensor();
    auto in_data = curr_input_tensor.data<uint8_t>();
    Mat data_mat_curr(img_height, img_width, CV_8UC1, in_data);
    cv::cvtColor(image_curr, data_mat_curr, cv::COLOR_BGR2GRAY);
    cv::threshold(data_mat_curr, data_mat_curr, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::imshow("image", data_mat_curr);
    //cv::waitKey(0);
    curr_request.start_async();

    next_request.wait();

    std::cout << "start!" << std::endl;

    while(1){
        
        // cv::Mat image_curr = cv::imread("/home/jason/Desktop/1.jpg");
    

    
        // resize(image_curr, image_curr, Size(img_width, img_height));

        // ov::Tensor curr_input_tensor = curr_request.get_input_tensor();
        // auto in_data_curr = curr_input_tensor.data<uint8_t>();
        // Mat data_mat_curr(img_height, img_width, CV_8UC1, in_data);
        // cv::cvtColor(image_curr, data_mat_curr, cv::COLOR_BGR2GRAY);
        // cv::threshold(data_mat_curr, data_mat_curr, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        // cv::imshow("image", data_mat_curr);
        // //cv::waitKey(0);


        
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();


        resize(image_next, image_next, Size(img_width, img_height));


        
        ov::Tensor next_input_tensor = next_request.get_input_tensor();

        

        auto in_data = next_input_tensor.data<uint8_t>();
        Mat data_mat_next(img_height, img_width, CV_8UC1, in_data);
        cv::cvtColor(image_next, data_mat_next, cv::COLOR_BGR2GRAY);
        cv::threshold(data_mat_next, data_mat_next, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        
        cv::imshow("image", data_mat_next);
        // cv::waitKey(0);

        next_request.start_async();

        // std::cout<<"start!again"<<std::endl;

        curr_request.wait();

        ov::Tensor curr_output_tensor = curr_request.get_output_tensor();
        auto out_data = curr_output_tensor.data<float>();
        // ov::Shape shape = curr_output_tensor.get_shape();
        // std::cout << "shape: " << shape << std::endl;

        int max = 0;
        float prob = 0.0;
        for (int i = 0; i < 11; i++) {
            if (out_data[i] > prob) {
                prob = out_data[i];
                max = i;    
            }
        }
         
        std::cout << "max: " << max << " prob: " << prob << std::endl;
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "duration: " <<duration.count() << "us" << std::endl;

        // cv::waitKey(0);

        ov::InferRequest temp = curr_request;
        curr_request = next_request;
        next_request = temp;
        cv::Mat image_temp = image_curr;
        image_curr = image_next;
        image_next = image_temp;
    
    }
    
    
  






}


