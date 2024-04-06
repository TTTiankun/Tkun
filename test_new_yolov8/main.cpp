#include"yolov8.h"

#include<iostream>
#include<opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <vector>

std::string model_path = "/home/jason/Desktop/test-speed/openvino/station.onnx";
std::string video_path = "/home/jason/Desktop/repository/b2.avi";  
cv::VideoCapture cap;

int main(){
    cap.open(video_path);
    if(!cap.isOpened()){
        std::cout << "Error: Video file not found" << std::endl;
        return -1;
    }
    cv::Mat frame;    
    class YOLOv8 yolo;
    yolo.init(model_path,0.5,0.5,1);
    while(1){
        cap >> frame;

        auto time_start = std::chrono::high_resolution_clock::now();
        std::vector<YOLOv8::Object> station;
        std::vector<YOLOv8::Object> angle;
        yolo.process_frame(frame,station,angle);
        auto time_end = std::chrono::high_resolution_clock::now();
        std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count() << "ms" << std::endl;
        for(auto &object:station){
            cv::rectangle(frame,object.rect,cv::Scalar(0,255,0),2);
            cv::putText(frame,"station",cv::Point(object.rect.x,object.rect.y),cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar(0,255,0),2);
        }
        for(auto &angle:angle){
            cv::rectangle(frame,angle.rect,cv::Scalar(0,0,255),2);
            cv::putText(frame,"angle",cv::Point(angle.rect.x,angle.rect.y),cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar(0,0,255),2);
        }
        //cv::imshow("YOLOv8",frame);
        cv::waitKey(1);
    }
    


}