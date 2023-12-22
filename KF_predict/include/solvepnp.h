#ifndef SOLVEPNP_H
#define SOLVEPNP_H

#include<iostream>
#include <opencv2/core/types.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/calib3d/calib3d.hpp>
#include<eigen3/Eigen/Dense>

class Solvepnp{
public:

    void solve_init();
    
    void get_centerPoints(std::vector<cv::Point2f>& approxCurve, cv::Point2f& centerPoint);

    void solvepnp(std::vector<cv::Point3d> objectPoints, std::vector<cv::Point2d> imagePoints, cv::Mat CamerMatrix, cv::Mat distCoeffs, cv::Mat rvec, cv::Mat tvec);

    bool comparePoints(const cv::Point2f& a, const cv::Point2f& b, const cv::Point2f& center);

    void reference(const int& x,const int& y,const int& z,const cv::Mat& CamerMatrix);

    void reference_back(const Eigen::VectorXd predict,const Eigen::VectorXd measure,const cv::Mat& img);

    std::vector<cv::Point2d> imagePoints;//定义图像中的点
    cv::Point2f centerPoint;//定义四边形的中心点
  
    std::vector<cv::Point3d> objectPoints;//定义空间物体的点
    //相机内参
    cv::Mat CamerMatrix;
    //相机畸变参数
    cv::Mat distCoeffs;
    //定义旋转向量和平移向量
    cv::Mat rvec;
    cv::Mat tvec;

    //最终相机坐标系下的坐标
    Eigen::VectorXd camera_result;
    
    //定义Z方向距离    
    double distance;
private:
    //获取速度的变量
    bool initialized = false;//是否为第一次
    Eigen::VectorXd camera_v;//CV测量位置
    Eigen::VectorXd pre_center = Eigen::RowVectorXd::Zero(3);//上一次的中心点
    Eigen::VectorXd velocity;//Eigin测量速度
    double dtt=6;//时间间隔
};

#endif