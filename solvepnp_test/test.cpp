#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <chrono>

using namespace std;
using namespace cv;
using namespace std::chrono;


VideoCapture capture;
Mat imgHSV, mask, img;
int hmin = 0, smin = 68, vmin = 171;
int hmax = 255, smax = 255, vmax = 255;
vector<Point2d> image;

//定义空间的物体点
vector<Point3d> object{
    {0, 0, 0},  // 左上
    {8, 0, 0},  // 右上
    {8, 8, 0},  // 右下
    {0, 8, 0},  // 左下
};



void info(){
    namedWindow("MAX", (200, 200));//设置一个条，可以调整遮罩
    createTrackbar("MINHue", "MAX", &hmin, 255);//给出控制栏名称，最小值的地址，还有最大值
    createTrackbar("MAXHue", "MAX", &hmax, 255);
    createTrackbar("Sat MIN", "MAX", &smin, 255);
    createTrackbar("Sat MAX", "MAX", &smax, 255);
    createTrackbar("Val MIN", "MAX", &vmin, 255);
    createTrackbar("Val MAX", "MAX", &vmax, 255);

}


// 排序比较函数，根据点相对于中心点的角度进行排序 顺序：左上，右上，右下，左下
bool comparePoints(const Point2f& a, const Point2f& b, const Point2f& center) {
    double angleA = atan2(a.y - center.y, a.x - center.x);
    double angleB = atan2(b.y - center.y, b.x - center.x);
    return angleA < angleB;
}

void getContours(Mat imgDil) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for (int i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);

        // 确保image是空的
        image.clear();

        if (area > 3000) {
            vector<vector<Point>> conPoly(contours.size());
            vector<Point> approxCurve;
            approxPolyDP(contours[i], approxCurve, 5.0, true);

            if (approxCurve.size() >= 4 && isContourConvex(approxCurve)) {
                // 将点按照从上到下，从左到右的顺序排列
                Point2f center(0, 0);
                //遍历所有点，然后取所有点的平均值，从而得到中心点
                for (const Point2f& point : approxCurve) {
                    center += point;
                }
                center *= 1.0 / approxCurve.size();
                
                sort(approxCurve.begin(), approxCurve.end(), [center](const Point2f& a, const Point2f& b) {
                    return comparePoints(a, b, center);
                });
                drawContours(img, contours, i, Scalar(255, 0, 255), 2);
                //cout<<approxCurve<<endl<<endl;
                // 如果标识只有四个点才开始进行接下来的操作
                if (approxCurve.size() >= 4) {
                    // 将四个点填入到image中
                    for (int j = 0; j < 4; j++) {
                        image.push_back(approxCurve[j]);
                    }

                    // 设置相机内参矩阵和畸变矩阵
                    Mat cameraMatrix = (cv::Mat_<double>(3, 3) << 1005.675897404832, 0, 641.0094449691178,
                                        0, 1004.999296938872, 348.9746795510874,
                                        0, 0, 1);

                    Mat distCoeffs = (cv::Mat_<double>(1, 5) << 0.07238068299789543, 1.673940715500982, 0.00064587667724675,
                                      -0.005597460826507149, -20.04641042377211);

                    // 定义旋转向量和平移向量
                    Mat rvec = Mat::zeros(3, 1, CV_64F);
                    Mat tvec = Mat::zeros(3, 1, CV_64F);

                    // 使用 solvePnP 计算旋转向量和平移向量
                    solvePnP(object, image, cameraMatrix, distCoeffs, rvec, tvec, false, cv::SOLVEPNP_IPPE);
                    //使用IPPE算法求解,避免在接近零度的时候出现解算出错的问题！

                    if (1) {
                        // 计算平移向量的模
                        double distance = norm(tvec);
                        // if(distance>10)
                        cout << "Distance to the object: " << distance << endl;
                    } else {
                        cout << "Error in solvePnP" << endl;
                    }
                }
            }
        }
    }
}

    

void findcolor(Mat img) {
    Mat imgHSV;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    //vector<vector<int>> mycolor{{0, 18, 247, 255, 255, 255}};  // 遮罩识别参数

    for (int i = 0; i < 6; i++) {
        //  Scalar lower(mycolor[i][0], mycolor[i][1], mycolor[i][2]);
        //  Scalar upper(mycolor[i][3], mycolor[i][4], mycolor[i][5]);
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        
        inRange(imgHSV, lower, upper, mask);
        imshow("mask", mask);
        
    }
}

void test01() {
    capture.open(0);
    info();
    while (1) {
        auto start = system_clock::now();//开始时间
        capture>>img;
        findcolor(img);
        getContours(mask);
        auto stop = high_resolution_clock::now();//结束时间
        auto duration = duration_cast<microseconds>(stop - start);//计算持续时间差
        double fps = 1.0 / (duration.count() / 1e6); // 计算帧率
        putText(img, "FPS: " + to_string(fps), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 5);
        imshow("image", img);
        char c = waitKey(1);
        if(c == 27)
            break;
    }
}

int main() {
    test01();
    return 0;
    
}

/*
Tips:
在OpenCV中，轮廓的层次(hierarchy)是一个用于描述轮廓之间关系的概念。每个轮廓都有一个与之对应的层次信息，这个信息是一个包含四个元素的数组，分别表示下一个轮廓、上一个轮廓、第一个子轮廓和父轮廓的索引。

这四个元素的具体含义如下：

- 下一个轮廓：在同一层级中，当前轮廓的下一个轮廓的索引。如果没有下一个轮廓，该值为-1。
- 上一个轮廓：在同一层级中，当前轮廓的上一个轮廓的索引。如果没有上一个轮廓，该值为-1。
- 第一个子轮廓：当前轮廓的第一个子轮廓的索引。如果没有子轮廓，该值为-1。
- 父轮廓：当前轮廓的父轮廓的索引。如果没有父轮廓，该值为-1。

这种层次结构可以帮助我们理解图像中轮廓的嵌套关系，例如，我们可以通过层次信息来找出所有的内部轮廓（即有父轮廓的轮廓）。

这两行代码是在设置用于存储图像轮廓信息的数据结构。

1. `vector<vector<Point>> contours;`：这行代码定义了一个二维向量`contours`，用于存储图像中每个轮廓的点集。内部的`vector<Point>`表示一个轮廓，它是由一系列的点`Point`组成的。外部的`vector`则用于存储所有的轮廓。

2. `vector<Vec4i> hierarchy;`：这行代码定义了一个向量`hierarchy`，用于存储轮廓之间的层次关系。`Vec4i`是一个包含4个整数的向量，对于每个轮廓`contours[i]`，`hierarchy[i]`就是一个`Vec4i`类型的向量，它包含了与`contours[i]`有关的层次信息，具体来说，`hierarchy[i][0]`表示下一个和`contours[i]`处于同一层次的轮廓的索引，`hierarchy[i][1]`表示上一个和`contours[i]`处于同一层次的轮廓的索引，`hierarchy[i][2]`表示`contours[i]`的第一个子轮廓的索引，`hierarchy[i][3]`表示`contours[i]`的父轮廓的索引。

这样设置的目的是为了在OpenCV中使用`findContours`函数找到并存储图像中的所有轮廓及其层次关系。



*/
