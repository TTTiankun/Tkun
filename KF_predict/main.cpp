#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <chrono>
#include <opencv2/videoio.hpp>
#include<eigen3/Eigen/Dense>

#include"solvepnp.h"
#include"find_rectangle.h"
#include"KF_test.h"

//这个滤波器是基于相机坐标系进行观测的，真实准确，但是测试起来效果不是很好
//因为涉及到相机坐标系和图像坐标系的转换
//创建一个捕捉视频的对象
cv::VideoCapture capture;

int main(){
    //创建对象
    Find_rectangle tk_rectangle;
    Solvepnp pnp;
    KalmanFilter kf;

    
    //打开摄像机
    capture.open(0);
    if(!capture.isOpened()){
        std::cout << "can not open camera" << std::endl;
        return -1;
    }
    tk_rectangle.find_init();
    while(1){
        auto start = std::chrono::system_clock::now();
        //读取图像到对象之中
        capture >> tk_rectangle.img;
        if(tk_rectangle.img.empty()){
            std::cout << "can not read img" << std::endl;
            break;
        }
        
        //处理图像
        tk_rectangle.make_mask();
        tk_rectangle.getcontours(tk_rectangle.mask);
        
        //计算处理帧率（这个功能实现不了待解决！）通过获取时间差来计算
        auto stop = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        double fps = 0;
        if(duration.count()>0){
             double fps = 1.0 / (duration.count()/1000);
        }
         
        //显示处理帧率和处理后的图像
        cv::putText(tk_rectangle.img, "FPS: " + std::to_string(fps), cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 0), 5);
        cv::imshow("image", tk_rectangle.img);
        
        //按下ESC退出
        char c = cv::waitKey(1);
        if(c == 27)
            break;
    }

}