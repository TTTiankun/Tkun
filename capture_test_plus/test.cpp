/*
version:2.0
author:Jason
date:2024-3-11
description: 更新了截图的区域
*/



#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

int main(){
    // 指定文件夹路径
    std::string folderPath = "/home/jason/Desktop/rx_datasets/";//指定保存文件夹路径
    std::string videoPath = "/home/jason/Desktop/test02.mp4";//指定视频路径
    
    // 设置截图的数量上限
    int maxScreenshots = 40;
    int currentScreenshot = 0;

    cv::VideoCapture capture(videoPath);  // 打开默认摄像头

    if (!capture.isOpened()) {
        std::cerr << "Error: Unable to open the camera or video.\n";
        return -1;
    }

    while (currentScreenshot < maxScreenshots) {
        cv::Mat frame;
        capture >> frame;

        // 检查是否成功读取图像
        if (frame.empty()) {
            std::cerr << "Error: Unable to read the frame.\n";
            break;
        }

        //视频区域截取
        cv::Rect cut = cv::Rect(frame.size().width-frame.size().width*0.42,frame.size().height-frame.size().height*0.85,frame.size().width*0.42,frame.size().height*0.80);
        cv::Mat cut_img = frame(cut);

        // 显示图像
        cv::Mat temp;

        cv::resize(cut_img, temp, cv::Size(frame.size().height*0.3, frame.size().width*0.3));
        cv::imshow("Capture Test", temp);
        
        // 检查是否按下 'K' 键
        int key = cv::waitKey(60);
        if (key == 'K' || key == 'k') {

            // 显示还能截图的数量
            int remainingScreenshots = maxScreenshots - currentScreenshot;
            // 递增截图计数
            currentScreenshot++;

            // 创建文件名并保存图像
            std::string filePath = folderPath + std::to_string(currentScreenshot) + ".png";
            cv::imwrite(filePath, cut_img);
            std::cout << "Screenshot saved to: " << filePath << "\n";
            std::cout<<"Remaining screenshots: "<<remainingScreenshots<<"\n";
        }

        // 按下 ESC 键退出
        if (key == 27) {
            break;
        }
    }

    // 释放摄像头
    capture.release();

    return 0;
}
