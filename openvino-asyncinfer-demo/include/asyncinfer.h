#ifndef ASYNCINFER_H
#define ASYNCINFER_H

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


class AsyncInfer{
public:
    AsyncInfer();
    ~AsyncInfer();
    //初始化
    bool init(int GPU_mode, int async_mode, std::string model_path,
                double score_threshold);
    //同步推理
    bool syncinference(cv::Mat &frame);
    //异步推理
    bool asyncinference(cv::Mat &next_frame); 
    //图片预处理
    bool pre_img(cv::Mat &frame, ov::Tensor &input_tensor);
    //主过程
    bool preocess(cv::Mat &frame);

    float prossibility;
    int number;
    ov::Tensor curr_input_tensor;
    ov::InferRequest curr_request;

private:
    
    //图像处理区 这个和模型参数有关系！
    int img_width = 28;
    int img_height = 28;

    //推理区
    std::string model_path;
    float score_threshold;
    int GPU_mode;
    int async_mode;
    ov::Core core;
    ov::CompiledModel compiled_model;//编译模型
    ov::InferRequest next_request;
    ov::Tensor next_input_tensor;
    ov::Tensor curr_output_tensor;

};

#endif // ASYNCINFER_H