#ifndef KF_H
#define KF_H

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <iostream>
#include<opencv2/opencv.hpp>

class KalmanFilter{
public:
    
    void KalmanFilter_init();
    
    void predict();
    
    Eigen::VectorXd getstate();

    void update(const Eigen::VectorXd &z);

    void show_predict(const Eigen::VectorXd &p,const Eigen::VectorXd &m,const cv::Mat &img);

    Eigen::VectorXd getState();

    Eigen::VectorXd x;//状态向量
    Eigen::MatrixXd P;//误差协方差矩阵
    
    Eigen::MatrixXd A;//状态转移矩阵
    Eigen::MatrixXd H;//测量矩阵
    Eigen::MatrixXd R;//测量噪声协方差矩阵
    Eigen::MatrixXd Q;//过程噪声协方差矩阵

    Eigen::VectorXd y;//测量值
    Eigen::MatrixXd S;//测量噪声协方差矩阵
    Eigen::MatrixXd K;//卡尔曼增益
    Eigen::MatrixXd p_center;//预测中心点
    Eigen::MatrixXd m_center;//测量中心点
    
    double dt;//时间间隔
    double sigma_noise;//噪声标准差
    double sigma_a;//加速度噪声标准差

};



#endif