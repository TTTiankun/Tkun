#include"yolov8pose.h"
#include"yolov8.h"

#include<iostream>

#include<opencv2/opencv.hpp>
#include<openvino/openvino.hpp>
#include<chrono>

//全局变量区
cv::VideoCapture cap;
cv::Mat img;

// std::vector<int> class_ids;
// std::vector<cv::Rect> boxes;
// std::vector<int> class_scores;
// std::vector<cv::Point> keypoints;

//文件区
std::string model_path_pose = "/home/jason/Desktop/test-speed/openvino/yolov8n-pose.onnx";
std::string model_path = "/home/jason/Desktop/test-speed/openvino/yolov8n.onnx";
std::string video_path1 = "/home/jason/Desktop/repository/test.mp4";
std::string video_path2 = "/home/jason/Desktop/repository/1.avi";


//推理设置区
int GPU_model = 1;
double score_threshold = 0.5;
double NMS_threshold = 0.25;
std::vector<cv::Scalar> colors = { cv::Scalar(255, 0, 0), cv::Scalar(255, 0, 255), cv::Scalar(170, 0, 255), cv::Scalar(255, 0, 85),
                                   cv::Scalar(255, 0, 170), cv::Scalar(85, 255, 0), cv::Scalar(255, 170, 0), cv::Scalar(0, 255, 0),
                                   cv::Scalar(255, 255, 0), cv::Scalar(0, 255, 85), cv::Scalar(170, 255, 0), cv::Scalar(0, 85, 255),
                                   cv::Scalar(0, 255, 170), cv::Scalar(0, 0, 255), cv::Scalar(0, 255, 255), cv::Scalar(85, 0, 255),
                                   cv::Scalar(0, 170, 255)};

std::vector<std::string> class_names_pose = {"person"};

std::vector<std::string> class_names = {
    "person", "bicycle", "car", "motorcycle", "airplane", "bus", "train", "truck", "boat", "traffic light",
    "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat", "dog", "horse", "sheep", "cow",
    "elephant", "bear", "zebra", "giraffe", "backpack", "umbrella", "handbag", "tie", "suitcase", "frisbee",
    "skis", "snowboard", "sports ball", "kite", "baseball bat", "baseball glove", "skateboard", "surfboard",
    "tennis racket", "bottle", "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple",
    "sandwich", "orange", "broccoli", "carrot", "hot dog", "pizza", "donut", "cake", "chair", "couch",
    "potted plant", "bed", "dining table", "toilet", "tv", "laptop", "mouse", "remote", "keyboard", "cell phone",
    "microwave", "oven", "toaster", "sink", "refrigerator", "book", "clock", "vase", "scissors", "teddy bear",
    "hair drier", "toothbrush" };

void Yolov8_pose(){
    cap.open(video_path1);
    
    class Yolov8pose yolo_pose;
    yolo_pose.init(GPU_model, model_path_pose, score_threshold, 
                NMS_threshold, colors, class_names_pose);
    
    while(1){
        cap>>img;
        if(img.empty()){
            std::cout << "img is empty" << std::endl;
            break;
        }
        
        auto start = std::chrono::high_resolution_clock::now();
        
        yolo_pose.process(img);

        //推理用时计算
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "Inference time: " << duration.count() << "ms" << std::endl;

        //视频帧率计算
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << (1000.0/duration.count());
        std::string fps = stream.str();

        //推理时间和帧率显示
        cv::putText(img, "FPS:" + fps, cv::Point(10,15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,255), 1);
        cv::putText(img, "Inference time:" + std::to_string(duration.count()) + "ms", cv::Point(10,35), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,255), 1);
        
        yolo_pose.show(img);

        cv::imshow("img",img);
        cv::waitKey(1);
    }
}

void Yolov8(){
    cap.open(video_path1);
    
    class Yolov8 yolo;
    yolo.init(GPU_model, model_path, score_threshold, 
                NMS_threshold, colors, class_names);
    
    while(1){
        cap>>img;
        if(img.empty()){
            std::cout << "img is empty" << std::endl;
            break;
        }
        
        auto start = std::chrono::high_resolution_clock::now();
        
        yolo.process(img);

        //推理用时计算
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "Inference time: " << duration.count() << "ms" << std::endl;

        //视频帧率计算
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << (1000.0/duration.count());
        std::string fps = stream.str();

        //推理时间和帧率显示
        cv::putText(img, "FPS:" + fps, cv::Point(10,15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,255), 1);
        cv::putText(img, "Inference time:" + std::to_string(duration.count()) + "ms", cv::Point(10,35), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,255), 1);
        
        yolo.show(img);

        cv::imshow("img",img);
        cv::waitKey(1);
    }  
}

int main(){
    Yolov8_pose();
}