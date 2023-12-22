#include"find_rectangle.h"
#include"solvepnp.h"
#include"KF_test.h"
#include <opencv2/imgproc.hpp>

void Find_rectangle::find_init(){
     cv::namedWindow("MAX");  // 创建窗口

    // 调整窗口大小
    cv::resizeWindow("MAX", 600, 200);
    
    cv::createTrackbar("MINHue", "MAX", &hmin, 255);
    cv::createTrackbar("MAXHue", "MAX", &hmax, 255);
    cv::createTrackbar("Sat MIN", "MAX", &smin, 255);
    cv::createTrackbar("Sat MAX", "MAX", &smax, 255);
    cv::createTrackbar("Val MIN", "MAX", &vmin, 255);
    cv::createTrackbar("Val MAX", "MAX", &vmax, 255);
}


void Find_rectangle::make_mask(){
    cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);//转换颜色空间

    for(int i=0;i<6;i++){
        cv::Scalar lower(hmin, smin, vmin);//设置最小值
        cv::Scalar upper(hmax, smax, vmax);//设置最大值

        cv::inRange(imgHSV, lower, upper, mask);//将图像转换为遮罩
        imshow("Mask",mask);
    }
}

void Find_rectangle::getcontours(cv::Mat Mask){
    Solvepnp pnp;
    KalmanFilter kf;
    
    pnp.solve_init();
    
    cv::findContours(Mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);//找到轮廓
    bool comparePoints(const cv::Point2f& a, const cv::Point2f& b, const cv::Point2f& center);
    for(int i=0;i<contours.size();i++){
        double area = cv::contourArea(contours[i]);

        pnp.imagePoints.clear();

        if (area>3000){
            cv::approxPolyDP(contours[i],approxCurve,5.0/*逼近精度，表示原始曲线和其近似多边形之间的最大距离*/,true);//对轮廓进行多边形拟合
            cv::drawContours(img, contours, i, cv::Scalar(255, 0, 255), 3);//画出轮廓
            if(approxCurve.size()>=4 && cv::isContourConvex(approxCurve)){
                pnp.get_centerPoints(approxCurve, pnp.centerPoint);
                cv::Point2f center = pnp.centerPoint;
                std::sort(approxCurve.begin(),approxCurve.end(),[center,&pnp](const cv::Point2f& a, const cv::Point2f& b){
                /*这段代码的功能是使用自定义比较函数 `comparePoints` 对 `approxCurve` 这个向量进行排序，比较函数使用了 `center` 作为参考点。*/
                    return pnp.comparePoints(a, b, center);
                });
                for (int i = 0; i < 4; i++){
                    pnp.imagePoints.push_back(approxCurve[i]);
                }
                pnp.solvepnp(pnp.objectPoints, pnp.imagePoints, pnp.CamerMatrix, pnp.distCoeffs, pnp.rvec, pnp.tvec);
                pnp.reference(pnp.centerPoint.x,pnp.centerPoint.y,pnp.tvec.at<double>(0,2), pnp.CamerMatrix);
                
                kf.KalmanFilter_init();
                kf.predict();
                kf.update(pnp.camera_result);
                kf.show_predict(kf.x,pnp.camera_result,img);
                pnp.reference_back(kf.x,pnp.camera_result,img);


            }
        }
    }
   

}