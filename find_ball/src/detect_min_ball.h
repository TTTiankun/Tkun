#include<iostream>
#include <opencv2/core/types.hpp>
#include<opencv2/opencv.hpp>
#include<eigen3/Eigen/Dense>
#include <vector>


class detect_ball{
public:
    detect_ball();
    ~detect_ball();
    void pre_process(cv::Mat &input, cv::Mat &output);
    void pre_detect(cv::Mat &input, cv::Mat &output);
    void detect(cv::Mat &input, cv::Mat &output);
    void show_detect(cv::Mat &input, cv::Mat &output);

private:
    double size_factor = 0.3;
    std::vector<cv::Point2f>centers;
    std::vector<int> radius;
    int index = 0;
    int x;
    int y;
    int ROI_X;
    int ROI_Y;
};