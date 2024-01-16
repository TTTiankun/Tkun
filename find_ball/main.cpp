#include<iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include"detect_min_ball.h"

//定义相关的变量
cv::Mat img;
std::string path = "/home/jason/Desktop/find_ball/test1.png";
std::string path_video = "/home/jason/Desktop/find_ball/test.avi";

int main(){
    detect_ball ball;
    // img = cv::imread(path);
    cv::VideoCapture capture;
    capture.open(path_video);
    // capture.read(img);
    // cv::Mat img_temp = img;

    // ball.pre_process(img_temp, img_temp);
    // ball.pre_detect(img_temp, img_temp);
    // ball.detect(img_temp, img_temp);
    // ball.show_detect(img, img);
    // cv::resize(img, img, cv::Size(img.cols*0.5, 
    //                                             img.rows*0.5));
    // cv::imshow("img", img);
    // cv::waitKey(0);

    while(1){
        capture.read(img);
        cv::Mat img_temp = img;
        ball.pre_process(img_temp, img_temp);
        ball.pre_detect(img_temp, img_temp);
        ball.detect(img_temp, img_temp);
        ball.show_detect(img, img);
        cv::resize(img, img, cv::Size(img.cols*0.5, 
                                                img.rows*0.5));
        cv::imshow("img", img);
        cv::waitKey(30);
    }
}