#ifndef FIND_RECTANGLE_H
#define FIND_RECTANGLE_H

#include<iostream>
#include <opencv2/core/types.hpp>
#include<opencv2/opencv.hpp>
#include<vector>

class Find_rectangle
{
public:
    
    void find_init();

    void getcontours(cv::Mat Mask);

    void make_mask();

    bool comparePoints(const cv::Point2f& a, const cv::Point2f& b, const cv::Point2f& center);

    cv::Mat img;
    cv::Mat mask, imgHSV;
    int hmin = 0, smin = 68, vmin = 171;
    int hmax = 255, smax = 255, vmax = 255;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<cv::Point2f> approxCurve;
    
};

#endif