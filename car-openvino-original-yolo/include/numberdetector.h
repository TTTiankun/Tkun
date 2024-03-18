#ifndef NUMBERDETECTOR_H
#define NUMBERDETECTOR_H

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
#include <openvino/runtime/compiled_model.hpp>
#include <openvino/runtime/core.hpp>
#include <openvino/runtime/infer_request.hpp>
#include <openvino/runtime/intel_cpu/properties.hpp>
#include <openvino/runtime/intel_gpu/properties.hpp>
#include <openvino/runtime/tensor.hpp>
#include <vector>

#include"yolov8pose.h"


class Numberdetector{
public:
    Numberdetector();
    ~Numberdetector();
    //初始化
    bool init(int GPU_mode,std::string model_path,
                double score_threshold);

    //异步推理
    bool asyncinference(std::vector<Yolov8pose::Object> &detected_armors); 
    //图片预处理
    bool pre_img(cv::Mat &frame, ov::Tensor &input_tensor);
    //图片处理器
    cv::Mat letterbox(const cv::Mat &source);
    //图像裁剪
    void cut_img(cv::Mat &frame, std::vector<Yolov8pose::Object> &detected_armors);
    


private:
    
    //推理区
    std::string model_path;
    float score_threshold;
    int GPU_mode;
    ov::Core core;
    ov::CompiledModel compiled_model;//编译模型
    cv::Mat blob;//输入图像四维张量
    ov::Output<const ov::Node> input_port;//输入端口
    float *output_data;//输出数据
    float prossibility;
    int number;
    ov::Tensor curr_input_tensor;
    ov::InferRequest curr_request;
    ov::Tensor next_input_tensor;
    ov::Tensor curr_output_tensor;
    ov::InferRequest next_request;


    //图像预处理区
    cv::Mat letterbox_img;
    float scale;
    int col;//列
    int row;//行
    int max;

};

#endif // NUMBERDETECTOR_H