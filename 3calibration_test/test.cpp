#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>

int main() {
    
    cv::Size boardSize(11, 8);//棋盘格内角点数，自己仔细数一数！！！！！
    std::vector<std::vector<cv::Point3f>> objectPoints;
    std::vector<std::vector<cv::Point2f>> imagePoints;
    std::vector<cv::Point3f> obj;
    for (int i = 0; i < boardSize.height; ++i) {
        for (int j = 0; j < boardSize.width; ++j) {
            obj.push_back(cv::Point3f(j, i, 0));
        }
    }
    cv::VideoCapture capture(0);//调整输入设备
    if (!capture.isOpened()) {
        std::cerr << "Error opening camera." << std::endl;
        return -1;
    }
   cv::Mat frame;
int successImages = 0;
int remainingImages = 30;  // 初始剩余图像数量

while (successImages < 30) {
    capture >> frame;
    cv::Mat gray, mask;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    std::vector<cv::Point2f> corners;
    bool found = cv::findChessboardCorners(gray, boardSize, corners);

    if (found) {
        cv::cornerSubPix(gray, corners, cv::Size(15, 15), cv::Size(-1, -1),
                         cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.05));
        
        cv::drawChessboardCorners(frame, boardSize, corners, found);

        // 按下K键就可以截图
        int key = cv::waitKey(1);
        if (key == 'k' || key == 'K') {
            
            objectPoints.push_back(obj);
            imagePoints.push_back(corners);
            successImages++;
            remainingImages = std::max(0, remainingImages - 1);

            //保存相关图片
            //cv::imwrite("image_" + std::to_string(successImages) + ".png", frame);
        }
    }

    // 显示计数
    cv::putText(frame, "Remian_image: " + std::to_string(remainingImages), cv::Point(10, 30),
                cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255), 2);

    cv::imshow("Calibration", frame);

    // 按下ESC键就可以退出
    int key = cv::waitKey(1);
    if (key == 27)
        break;
}

    
    cv::Mat cameraMatrix, distCoeffs;
    std::vector<cv::Mat> rvecs, tvecs;
    cv::calibrateCamera(objectPoints, imagePoints, frame.size(), cameraMatrix, distCoeffs, rvecs, tvecs);
    // 将相机矩阵和畸变系数保存到文本文件
    std::ofstream outputFile("calibration_results.txt");
    if (outputFile.is_open()) {
        outputFile << "Camera Matrix:\n" << cameraMatrix << "\n\n";
        outputFile << "Distortion Coefficients:\n" << distCoeffs << "\n\n";
        outputFile.close();
        std::cout << "结果已经保存！\n";
    } else {
        std::cerr << "打开写入文件失败！！！\n";
    }
    
    std::cout << "Camera Matrix:\n" << cameraMatrix << "\n\n";
    std::cout << "Distortion Coefficients:\n" << distCoeffs << "\n\n";
    capture.release();

    return 0;
}