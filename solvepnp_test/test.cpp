#include<opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
using namespace std;
using namespace cv;

Mat imgHSV, mask,img;

vector<Point2d>image;

//定义空间的物体点
vector<Point3d>object{
    {0,5,0},//左上
    {0,0,0},//左下
    {5,0,0},//右下
    {5,5,0},//右上
 
};


void getContours(Mat imgDil)//进行边缘检测的函数
{
    vector<vector<Point>>contours;//vector容器储存这个
    vector<Vec4i>hierarchy;
    string objectType;
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//返现边缘

     Point poll;

    for (int i = 0; i < contours.size(); i++)
    {
        double area = contourArea(contours[i]);//将area由contours容器之中赋值

        vector<vector<Point>>conPoly(contours.size());//创建另外一个容器进行储存，这个一定要写声明容器！！！！
        vector<Rect>boundRect(contours.size());



        if (area > 3000){
            double peri = arcLength(contours[i], 1);//设置选取的精度
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, 1);//将最后设置为true，我们绘制的图形是闭合图形，第二个是绘制的精度
            //drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);//绘制线条
            Rect rect = boundingRect(conPoly[i]);//建立数组获取中心点坐标

            rectangle(img,rect,Scalar(0,255,255),2);//绘制矩形（图像，矩形，颜色，粗细
            
            // 获取矩形的左上角和右下角坐标
            Point tl = rect.tl();  // 左上角
            Point br = rect.br();  // 右下角
            // 计算矩形的四个顶点坐标
            Point tr(rect.x + rect.width, rect.y);// 右上角
            Point bl(rect.x, rect.y + rect.height);// 左下角
            //确保每次循环前都清空了容器
            image.clear();
            
            image.push_back(tl);
            image.push_back(bl);
            image.push_back(tr);
            image.push_back(br);
            
            //设置相机内参矩阵
            Mat cameraMatrix = (cv::Mat_<double>(3, 3) << 
            1.7774091341308808e+03, 0., 7.1075979428865026e+02,
            0., 1.7754170626354828e+03, 5.3472407285624729e+02,
            0., 0., 1.
            );

            //设置相机畸变矩阵
            Mat distCoeffs = (cv::Mat_<double>(1, 5) <<
            -5.6313426428564950e-01, 1.8301501710641366e-01,
            1.9661478907901904e-03, 9.6259122849674621e-04,
            5.6883803390679100e-01
            );



            // 旋转矩阵和平移向量
            Mat rvec, tvec;

            // 使用 solvePnP 进行相机姿态估计
            bool success = solvePnP(object, image, cameraMatrix, distCoeffs, rvec, tvec);
            if(success){
                // 计算相机到物体的距离
                double distance = norm(tvec);

                // 输出距离
                cout << "Distance to the object: " << distance << endl;
            }
            else{
                cout<<"error"<<endl;
            }


            int x = rect.width / 2;
            int y = rect.height / 2;
            
            poll = Point(rect.x + x, rect.y + y);

            circle(img, poll, 10, Scalar(0, 0, 255), 3);
            circle(img, poll, 70, Scalar(0, 255, 145), 3);
            
            
            //cout << poll << endl;
           
        }
    }

}


vector<vector<int>>mycolor{{0, 129, 0, 70, 255, 255}};//遮罩识别参数

void findcolor(Mat img){
    Mat imgHSV;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);//将图片由BRG格式变为HSV格式

    for (int i = 0; i < mycolor.size(); i++)
    {
        Scalar lower(mycolor[i][0], mycolor[i][1], mycolor[i][2]);//获取识别颜色的范围值，HSV格式
        Scalar upper(mycolor[i][3], mycolor[i][4], mycolor[i][5]);
        Mat mask;//每次都要刷新遮罩
        inRange(imgHSV, lower, upper, mask);
        imshow("mask", mask);//每次都要重新命名遮罩
        getContours(mask);//导入出现遮罩的函数

    }

}

void test01(){

    VideoCapture capture;
    capture.open(0);
    
    
    while (1){
        capture.read(img);
        findcolor(img);//导入查找颜色的函数
        imshow("image", img);
        waitKey(1);
    }
}


int main(){
    test01();
}