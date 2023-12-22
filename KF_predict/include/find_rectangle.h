#ifndef FIND_RECTANGLE_H
#define FIND_RECTANGLE_H

#include<iostream>
#include <opencv2/core/types.hpp>
#include<opencv2/opencv.hpp>
#include<vector>

class Find_rectangle
{
public:
    
    void find_init();//初始化

    void getcontours(cv::Mat Mask);//选取轮廓，同时进行后续的操作！核心代码

    void make_mask();//设置遮罩，可滑动条调节

    //设置一些变量
    cv::Mat img;
    cv::Mat mask, imgHSV;
    int hmin = 0, smin = 68, vmin = 171;
    int hmax = 255, smax = 255, vmax = 255;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<cv::Point2f> approxCurve;
    
};

#endif