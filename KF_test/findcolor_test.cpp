//调参用的文件

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


Mat imgHSV, mask;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 0, smax = 0, vmax = 0;



Mat img;

void test01()
{

    namedWindow("MAX", (200, 200));//设置一个条，可以调整遮罩
    createTrackbar("MINHue", "MAX", &hmin, 255);//给出控制栏名称，最小值的地址，还有最大值
    createTrackbar("MAXHue", "MAX", &hmax, 255);
    createTrackbar("Sat MIN", "MAX", &smin, 255);
    createTrackbar("Sat MAX", "MAX", &smax, 255);
    createTrackbar("Val MIN", "MAX", &vmin, 255);
    createTrackbar("Val MAX", "MAX", &vmax, 255);

    VideoCapture capture;
    capture.open(0);

    while (1)
    {
        
        capture.read(img);

        cvtColor(img, imgHSV, COLOR_BGR2HSV);//将图片由BRG格式变为HSV格式
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);

        inRange(imgHSV, lower, upper, mask);//设置一个遮罩，第一个是原图形的名称，前两个值表示的是颜色范围，最后一个表示图像改变后的名称
        cout << hmin << "," << smin << "," << vmin << "," << hmax << "," << smax << "," << vmax << endl;
        
        
        imshow("image", img);
        waitKey(1);

        imshow("mask", mask);
        waitKey(1);
        
    }


}


int main()
{
    test01();
}