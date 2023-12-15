#include<opencv2/opencv.hpp>
#include <iostream>

using namespace std;

cv::Mat imgHSV, mask,img;


void getContours(cv::Mat imgDil){ //进行边缘检测的函数
    vector<vector<cv::Point>>contours;//vector容器储存这个
    vector<cv::Vec4i>hierarchy;
    string objectType;
    cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);//返现边缘

    cv::Point poll;

    for (int i = 0; i < contours.size(); i++)
    {
        double area = contourArea(contours[i]);//将area由contours容器之中赋值

        vector<vector<cv::Point>>conPoly(contours.size());//创建另外一个容器进行储存，这个一定要写声明容器！！！！
        vector<cv::Rect>boundRect(contours.size());



        if (area > 3000)
        {
            double peri = arcLength(contours[i], 1);//设置选取的精度
            cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, 1);//将最后设置为true，我们绘制的图形是闭合图形，第二个是绘制的精度
            //drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);//绘制线条
            cv::Rect rect = cv::boundingRect(conPoly[i]);//建立数组获取中心点坐标

            cv::rectangle(img,rect,cv::Scalar(0,255,255),2);//绘制矩形（图像，矩形，颜色，粗细
            int x = rect.width / 2;
            int y = rect.height / 2;
            
            poll = cv::Point(rect.x + x, rect.y + y);

            circle(img, poll, 10, cv::Scalar(0, 0, 255), 3);
            circle(img, poll, 70, cv::Scalar(0, 255, 145), 3);
            
            
            cout << poll << endl;
           
        }
    }

}


vector<vector<int>>mycolor{{0, 129, 0, 70, 255, 255}//遮罩识别参数
};

void findcolor(cv::Mat img){
    cv::Mat imgHSV;
    cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);//将图片由BRG格式变为HSV格式

    for (int i = 0; i < mycolor.size(); i++)
    {
        cv::Scalar lower(mycolor[i][0], mycolor[i][1], mycolor[i][2]);//获取识别颜色的范围值，HSV格式
        cv::Scalar upper(mycolor[i][3], mycolor[i][4], mycolor[i][5]);
        cv::Mat mask;//每次都要刷新遮罩
        inRange(imgHSV, lower, upper, mask);
        cv::imshow("mask", mask);//每次都要重新命名遮罩
        getContours(mask);//导入出现遮罩的函数

    }

}

void test01(){

    cv::VideoCapture capture;
    capture.open(0);
    void info_kf();
    
    while (1)
    {
        capture.read(img);
        findcolor(img);//导入查找颜色的函数
        cv::imshow("image", img);
        cv::waitKey(1);
    }
}


int main()
{
    test01();
}