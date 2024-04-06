#ifndef YOLOV8_H
#define YOLOV8_H

#include <opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
#include <openvino/opsets/opset1.hpp>
#include<openvino/core/core.hpp>    
#include <openvino/runtime/intel_cpu/properties.hpp>
#include <openvino/runtime/intel_gpu/properties.hpp>
#include<openvino/openvino.hpp>
#include <openvino/runtime/tensor.hpp>

using namespace std;
using namespace cv;


class YOLOv8
{
public:
    YOLOv8();
    ~YOLOv8();

    struct Object
    {
        Rect_<float> rect;
        float confidence;
        vector<float> points;
        int class_id;
    };

    bool init(string xml_path,double cof_threshold,double nms_area_threshold,int gpu_mode);

    void process_frame(Mat &image, vector<Object> &station, vector<Object> &angle);


private:
       
        void boxes_extract(float *output_data, int cof_threshold, vector<Rect> &boxes, vector<float> &cof, vector<int> &ids);



        ov::Core core;
        ov::CompiledModel compiled_model;
        ov::InferRequest infer_request;
        ov::Tensor input_tensor;
        ov::Tensor output_tensor;

        //参数区
        string xml_path;            //OpenVINO模型xml文件路径
        double cof_threshold;       //置信度阈值,计算方法是框置信度乘以物品种类置信度
        double nms_area_threshold;  //nms最小重叠面积阈值
        int gpu_mode=0;
        int model_input_w,model_input_h;
        int model_output_w,model_output_h;

        int top;
        int right;
        int left;
        int bottom;
        double f;

};

#endif // YOLOV8_H