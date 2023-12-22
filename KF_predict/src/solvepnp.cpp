#include"solvepnp.h"
#include <opencv2/calib3d.hpp>


void Solvepnp::solve_init(){
    
    objectPoints = {//定义空间物体的点
    {0, 0, 0},  // 左上
    {8, 0, 0},  // 右上
    {8, 8, 0},  // 右下
    {0, 8, 0},  // 左下
    };
    
    //相机内参
    CamerMatrix= (cv::Mat_<double>(3, 3) << 1005.675897404832, 0, 641.0094449691178,
                                        0, 1004.999296938872, 348.9746795510874,
                                        0, 0, 1);
    //相机畸变参数
    distCoeffs= (cv::Mat_<double>(1, 5) << 0.07238068299789543, 1.673940715500982, 0.00064587667724675,
                                      -0.005597460826507149, -20.04641042377211);
    //定义旋转向量和平移向量
    rvec = cv::Mat::zeros(3, 1, CV_64F);
    tvec = cv::Mat::zeros(3, 1, CV_64F);

    //定义Z方向距离
    distance = 0;
  
}

bool Solvepnp::comparePoints(const cv::Point2f& a, const cv::Point2f& b, const cv::Point2f& center){
    double angleA = atan2(a.y - center.y, a.x - center.x);
    double angleB = atan2(b.y - center.y, b.x - center.x);
    return angleA < angleB;
}

void Solvepnp::get_centerPoints(std::vector<cv::Point2f>& approxCurve, cv::Point2f& centerPoint){
    for (int i = 0; i < approxCurve.size(); i++){
        centerPoint += approxCurve[i];
    }
    centerPoint *= (1. / approxCurve.size());
}

void Solvepnp::solvepnp(std::vector<cv::Point3d> objectPoints, std::vector<cv::Point2d> imagePoints, cv::Mat CamerMatrix, cv::Mat distCoeffs, cv::Mat rvec, cv::Mat tvec){
    
    // std::cout << "imagePoints: " << imagePoints.size() << std::endl;
    // std::cout << "objectPoints: " << objectPoints.size() << std::endl;
    cv::solvePnP(objectPoints, imagePoints, CamerMatrix, distCoeffs, rvec, tvec, false, cv::SOLVEPNP_IPPE);
    if(1){
        distance = norm(tvec);
        
        //std::cout << "Distance to the object: " << distance << std::endl;
    }
    else{
        std::cout << "solvePnp failed!" << std::endl;
    }
}


void Solvepnp::reference(const int& x,const int& y,const int& z,const cv::Mat& CamerMatrix){
    // 计算相机坐标系下的坐标
    cv::Mat img_coords = (cv::Mat_<double>(3, 1) << x, y, 1);
    cv::Mat invCamerMatrix = CamerMatrix.inv();  // 计算相机内参矩阵的逆矩阵
    cv::Mat camera_r = invCamerMatrix * img_coords * z;
    
    camera_result.resize(6,1);
    camera_v.resize(3,1);
    
    camera_v<<camera_r.at<double>(0, 0), camera_r.at<double>(1, 0), camera_r.at<double>(2, 0);
    camera_result << camera_r.at<double>(0, 0), camera_r.at<double>(1, 0), camera_r.at<double>(2, 0),0,0,0;
    
    //camera_r.at<double>(0, 0)是Opencv访问矩阵元素的一种方式，表示访问第一行第一列的元素，然后返回double类型
    
}

void Solvepnp::reference_back(const Eigen::VectorXd predict,const Eigen::VectorXd measure,const cv::Mat& img){
    // 计算相机坐标系下的坐标
    cv::Mat predict_point = (cv::Mat_<double>(1,3)<<predict(0),predict(1),predict(2));
    cv::Mat measure_point = (cv::Mat_<double>(1,3)<<measure(0),measure(1),measure(2));
    cv::Mat image_predict = CamerMatrix * predict_point.t();
    image_predict = image_predict / image_predict.at<double>(2, 0);
    cv::Mat image_measure = CamerMatrix * measure_point.t();
    image_measure = image_measure / image_measure.at<double>(2, 0);

    std::cout << "predict_point: " << std::endl<<predict_point << std::endl;
    std::cout << "measure_point: " << std::endl<<measure_point << std::endl;

    cv::circle(img, cv::Point(cvRound(image_predict.at<double>(0, 0)), cvRound(image_predict.at<double>(0, 1))), 2, cv::Scalar(0, 255, 255), -1);
    //cv::circle(img, cv::Point(cvRound(image_measure.at<double>(0, 0)), cvRound(image_measure.at<double>(0, 1))), 2, cv::Scalar(0, 0, 0), -1);

}


