#include <iostream>
#include <opencv2/opencv.hpp>

int main(){
    // 指定文件夹路径
    std::string folderPath = "/home/jason/Desktop/capture_test/";//指定保存文件夹路径
    //std::string videoPath = "/Desktop/1.mp4";//指定视频路径
    
    // 设置截图的数量上限
    int maxScreenshots = 5;
    int currentScreenshot = 0;

    cv::VideoCapture capture(0);  // 打开默认摄像头

    if (!capture.isOpened()) {
        std::cerr << "Error: Unable to open the camera or video.\n";
        return -1;
    }

    while (currentScreenshot < maxScreenshots) {
        cv::Mat frame;
        capture >> frame;

        // 检查是否成功读取图像
        if (frame.empty()) {
            std::cerr << "Error: Unable to read the frame.\n";
            break;
        }

        // 显示还能截图的数量
        int remainingScreenshots = maxScreenshots - currentScreenshot;
        cv::putText(frame, "Remaining Screenshots: " + std::to_string(remainingScreenshots),
                    cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255), 2);

        // 显示图像
        cv::imshow("Capture Test", frame);

        // 检查是否按下 'K' 键
        int key = cv::waitKey(1);
        if (key == 'K' || key == 'k') {
            // 递增截图计数
            currentScreenshot++;

            // 创建文件名并保存图像
            std::string filePath = folderPath + "Photo_" + std::to_string(currentScreenshot) + ".png";
            cv::imwrite(filePath, frame);
            std::cout << "Screenshot saved to: " << filePath << "\n";
        }

        // 按下 ESC 键退出
        if (key == 27) {
            break;
        }
    }

    // 释放摄像头
    capture.release();

    return 0;
}
