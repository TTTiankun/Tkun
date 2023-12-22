#include"KF_test.h"
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>

void KalmanFilter::KalmanFilter_init(){
    x=Eigen::MatrixXd::Zero(6,1);//观测向量
    P=Eigen::MatrixXd::Zero(6,6);//误差协方差矩阵

    dt=100;//时间间隔
    A=Eigen::MatrixXd::Zero(6,6);//状态转移矩阵
    A<<1,0,0,dt,0,0,
       0,1,0,0,dt,0,
       0,0,1,0,0,dt,
       0,0,0,1,0,0,
       0,0,0,0,1,0,
       0,0,0,0,0,1;//状态转移矩阵

    H=Eigen::MatrixXd::Zero(6,6);//测量矩阵
    H<<1,0,0,0,0,0,
       0,1,0,0,0,0,
       0,0,1,0,0,0,
       0,0,0,1,0,0,
       0,0,0,0,1,0,
       0,0,0,0,0,1;//测量矩阵

    Q=Eigen::MatrixXd::Zero(6,6);//过程噪声协方差矩阵
    sigma_a=0.05;//加速度噪声标准差
    Q<<sigma_a*sigma_a*dt*dt,0,0,0,0,0,
       0,sigma_a*sigma_a*dt*dt,0,0,0,0,
       0,0,sigma_a*sigma_a*dt*dt,0,0,0,
       0,0,0,sigma_a*sigma_a,0,0,
       0,0,0,0,sigma_a*sigma_a,0,
       0,0,0,0,0,sigma_a*sigma_a;//过程噪声协方差矩阵

    R=Eigen::MatrixXd::Zero(6,6);//测量噪声协方差矩阵
    sigma_noise=0.1;//噪声标准差
    R<<sigma_noise*sigma_noise,0,0,0,0,0,
         0,sigma_noise*sigma_noise,0,0,0,0,
         0,0,sigma_noise*sigma_noise,0,0,0,
         0,0,0,sigma_noise*sigma_noise,0,0,
         0,0,0,0,sigma_noise*sigma_noise,0,
         0,0,0,0,0,sigma_noise*sigma_noise;//测量噪声协方差矩阵
       
}

void KalmanFilter::predict(){
    x=A*x;//预测状态向量
    P=A*P*A.transpose()+Q;//预测误差协方差矩阵
}

void KalmanFilter::update(const Eigen::VectorXd &z){
    y=z-H*x;//计算残差（测量值与预测值的差异） 
    S=H*P*H.transpose()+R;//计算残差的协方差矩阵
    K=P*H.transpose()*S.inverse();//计算卡尔曼增益
    
    x=x+K*y;//更新状态向量
    P=(Eigen::MatrixXd::Identity(6,6)-K*H)*P;//更新误差协方差矩阵
}

void KalmanFilter::show_predict(const Eigen::VectorXd &p,const Eigen::VectorXd &m,const cv::Mat &img){
    p_center = p;//预测中心点
    m_center = m;//测量中心点
    
    //没有用的调试遗留物，可以看看为什么下面两个圆画不出来！
    // std::cout << "predict_center: " << std::endl<<p_center << std::endl;
    // std::cout << "measure_center: " << std::endl<<m_center << std::endl;
    // cv::circle(img, cv::Point(p_center(0), p_center(1)), 5, cv::Scalar(0, 0, 255), -1);
    // cv::circle(img, cv::Point(cvRound(m_center.at<double>(0, 0)), cvRound(m_center.at<double>(1, 0))), 5, cv::Scalar(0, 255, 0), -1);
}
