#include"detect_min_ball.h"
#include<iostream>
#include <opencv2/core/base.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<eigen3/Eigen/Dense>

detect_ball::detect_ball(){
}

detect_ball::~detect_ball(){
}
//对图像进行预处理
void detect_ball::pre_process(cv::Mat &input, cv::Mat &output){
    //对图像进行缩放
    std::vector<cv::Point2f>centers;
    cv::resize(input, input, cv::Size(input.cols*size_factor, 
                                                        input.rows*size_factor));
    //找到图像的中心
    x = input.cols; 
    y = input.rows;
    int center[2] = {x/2, y/2};

    //裁剪图像
    int width = x*0.5;
    ROI_X = (int)center[0] - x/10;
    ROI_Y = (int)center[1]- y/10;
    int height = y - ROI_Y - 1;
    //调试程序，笑死了，把长宽搞反了！
    // std::cout<<ROI_Y<<std::endl;
    // std::cout<<y<<std::endl;
    // std::cout<<height<<std::endl;
    // std::cout<<input.size()<<std::endl;
    
    cv::Rect ROI(ROI_X, ROI_Y, width, height);
    output = input(ROI);//输出图片

}
//HSV二值化准备识别
void detect_ball::pre_detect(cv::Mat &input, cv::Mat &output){
    //处理图像
    cv::Mat imgHSV, mask;
    cv::cvtColor(input, imgHSV, cv::COLOR_BGR2HSV);
   
    //HSV颜色范围
    cv::Scalar lower(49,48,85);
    cv::Scalar upper(70,158,255);

    //设置遮罩
    cv::inRange(imgHSV, lower, upper, mask);
    // cv::imshow("mask", mask);
    output = mask;
  
}
//识别球
void detect_ball::detect(cv::Mat &input, cv::Mat &output){
    //创建变量
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    
    //查找轮廓并绘制结果
    cv::findContours(input, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, cv::Point());
    for(int i = 0;i<contours.size();i++){
        double area = cv::contourArea(contours[i]);
        double r = sqrt(area/3.1415926);
        if(area>20){
            cv::Point2f center;
            float rad;
            cv::minEnclosingCircle(contours[i], center, rad);
            rad = (int)rad;
            centers.push_back(center);
            radius.push_back(rad);
            //调试代码
            // cv::circle(input, center, rad, cv::Scalar(0, 100, 100), 1);
            // cv::putText(input_s, "ball", center, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255,255,255), 20);
        }
    }
    output = input;
    //展示结果（调试）
    // cv::imshow("output", output);
}

void detect_ball::show_detect(cv::Mat &input, cv::Mat &output){
    for(int i = 0;i<centers.size();i++){
        cv::Point2f center = centers[i]/size_factor;
        center = (center + cv::Point2f(ROI_X/size_factor, ROI_Y/size_factor));
        int rad = radius[i]/size_factor; 
        cv::circle(output, center, rad, cv::Scalar(0, 255,0), 10);
        // 添加文字
        std::string text = "Circle " + std::to_string(i + 1);
        cv::putText(output, text, center + cv::Point2f(rad + 10, 0),
                    cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(255, 0, 0), 4);
     
    }
    centers.clear();
    radius.clear();
}