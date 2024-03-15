#include"yolov8pose.h"
#include"numberdetector.h"

#include<iostream>

#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<openvino/openvino.hpp>
#include<chrono>
#include <openvino/runtime/tensor.hpp>
#include <vector>

//全局变量区
cv::VideoCapture cap;
cv::Mat img;

//文件区
std::string model_yolo_path = "/home/jason/Desktop/test-speed/openvino/best.onnx";
std::string model_number_path = "/home/jason/Desktop/T-DT-Vision-2024/model/number/best.onnx";
std::string test_video_path = "/home/jason/Desktop/repository/1.avi";

//推理设置区
int GPU_yolo_mode = 0;
int GPU_number_mode = 0;

double score_threshold = 0.5;
double NMS_threshold = 0.25;

//颜色区
std::vector<std::string> class_names = {"armor","car"};
std::vector<cv::Scalar> points_colors = { cv::Scalar(255, 0, 0), cv::Scalar(255, 0, 255),cv::Scalar(0, 0, 255),cv::Scalar(0, 255, 255)};

void final(){

}

int main(){
    cap.open(test_video_path);

    //创建推理对象
    class Yolov8pose yolo;
    class Numberdetector number;

    std::vector<Yolov8pose::Object> detected_armors;
    std::vector<Yolov8pose::Object> detected_robots;

    //初始化
    yolo.init(GPU_yolo_mode,model_yolo_path,
                score_threshold,NMS_threshold,points_colors,class_names);
    number.init(GPU_number_mode,model_number_path,score_threshold);

    while(1){
        cap >> img;
        if(img.empty()){
            std::cout << "img is empty" << std::endl;
            break;
        }
        //全局计时
        auto start_all = std::chrono::high_resolution_clock::now();
        //YOLO部分
        auto start_yolo = std::chrono::high_resolution_clock::now();
        yolo.process(img,detected_armors,detected_robots);
        auto end_yolo = std::chrono::high_resolution_clock::now();
        auto duration_yolo = std::chrono::duration_cast<std::chrono::milliseconds>(end_yolo - start_yolo);
        std::cout << "YOLO inference time: " << duration_yolo.count() << "ms" << std::endl;

        //检测是否有目标
        if(detected_armors.size() == 0){
            std::cout << "No armor detected" << std::endl;
            //展示结果
            //视频帧率计算
            auto end_all = std::chrono::high_resolution_clock::now();
            auto duration_all = std::chrono::duration_cast<std::chrono::milliseconds>(end_all - start_all);
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << (1000.0/duration_all.count());
            std::string fps = stream.str();

            //推理时间和帧率显示
            cv::putText(img, "FPS:" + fps, cv::Point(10,15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,255), 1);
            cv::putText(img, "Inference time:" + std::to_string(duration_all.count()) + "ms", cv::Point(10,35), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,255), 1);
        
            cv::imshow("Window", img);
            cv::waitKey(1);
            std::cout<<std::endl;//换行
        }else{
            if(detected_robots.size() == 0){
            std::cout << "No robot detected" << std::endl;
            }
            //数字识别部分
            number.cut_img(img,detected_armors);
            auto start_number = std::chrono::high_resolution_clock::now();
            for(int i = 0;i<detected_armors.size();i++){
                // cv::imshow("number",detected_armors[i].number_image);
                // cv::waitKey(1);
                number.syncinference(detected_armors[i].number_image);
                detected_armors[i].armor_id = number.number;
                detected_armors[i].number_score = number.prossibility;
                std::cout << "The number is: " << number.number << " The prossibility is: " << number.prossibility << std::endl;
            }
                auto end_number = std::chrono::high_resolution_clock::now();
                auto duration_number = std::chrono::duration_cast<std::chrono::microseconds>(end_number - start_number);
                std::cout << "Number inference time: " << duration_number.count() << "us" << std::endl;

            //展示结果
            //视频帧率计算
            auto end_all = std::chrono::high_resolution_clock::now();
            auto duration_all = std::chrono::duration_cast<std::chrono::milliseconds>(end_all - start_all);
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << (1000.0/duration_all.count());
            std::string fps = stream.str();

            //推理时间和帧率显示
            cv::putText(img, "FPS:" + fps, cv::Point(10,15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,255), 1);
            cv::putText(img, "Inference time:" + std::to_string(duration_all.count()) + "ms", cv::Point(10,35), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,255), 1);
        
            yolo.show_result(img,detected_armors,detected_robots);

            cv::imshow("Window", img);
            cv::waitKey(1);
            detected_armors.clear();
            detected_robots.clear();
            std::cout<<std::endl;//换行
        }
    }
    return 0;
}