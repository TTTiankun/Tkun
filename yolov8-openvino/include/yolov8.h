#ifndef YOLOV8_H
#define YOLOV8_H
//openvino&opencv
#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>
#include <openvino/core/node.hpp>
#include <openvino/core/node_output.hpp>
#include <openvino/core/shape.hpp>
#include <openvino/openvino.hpp>
#include <openvino/runtime/infer_request.hpp>
#include <openvino/runtime/intel_cpu/properties.hpp>//CPU插件属性头文件
#include <openvino/runtime/intel_gpu/properties.hpp>//GPU插件属性头文件
//c++
#include<vector>
#include<string>
#include<iostream>

class Yolov8{
public:
    Yolov8();
    ~Yolov8();

    bool init(int GPU_model, std::string model_path,
                double score_threshold, double NMS_threshold,
                 std::vector<cv::Scalar> color,std::vector<std::string> &class_names);//初始化
    bool process(cv::Mat &source);//总过程
    bool pre_img(cv::Mat &frame);//图像预处理
    cv::Mat letterbox(cv::Mat &source);//图像转化器
    bool inference();//推理
    void extract();//结果提取
    void show(cv::Mat &source);//显示结果

private:
    //推理参数区
    int GPU_model;//是否使用GPU
    std::string model_path;//模型路径
    ov::Core core;//openvino核心
    ov::InferRequest infer_request;//推理请求
    ov::CompiledModel compiled_model;//编译模型
    ov::Tensor input_tensor;//输入张量
    ov::Tensor output_tensor;//输出张量
    cv::Mat blob;//输入图像四维张量
    ov::Output<const ov::Node> input_port;//输入端口
    float *output_data;//输出数据
    ov::Shape output_shape;//输出向量形状
    cv::Mat output_buffer;//输出缓存区
    cv::Mat classes_scores;//类别置信度

    //后处理单元
    double score_threshold;//置信度阈值
    double NMS_threshold;//NMS阈值

    //图像处理区
    cv::Mat letterbox_img;
    float scale;
    int col;//列
    int row;//行
    int max;//最大值

    //结果区
    std::vector<int> class_ids;
    std::vector<cv::Rect> boxes;
    std::vector<float> class_scores;
    std::vector<std::vector<float>>obj_keypoints;
    std::vector<cv::Scalar> colors;
    std::vector<std::string> class_names;
    std::vector<int> indices;

};


#endif // YOLOV8_H