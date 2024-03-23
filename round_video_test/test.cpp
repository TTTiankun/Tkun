#include <opencv2/opencv.hpp>

int main() {
    // 打开输入视频
    cv::VideoCapture cap("../test.mp4");
    if (!cap.isOpened()) {
        std::cout << "无法打开输入视频" << std::endl;
        return -1;
    }

    // 获取视频的宽度和高度
    int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    // 创建一个VideoWriter对象
    cv::VideoWriter video("../output.mp4", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, cv::Size(frame_height, frame_width));

    cv::Mat src;

    while (true) {
        cap >> src;

        // 如果视频结束，跳出循环
        if (src.empty()) {
            break;
        }

        // 旋转图像
        cv::Mat dst;
        cv::rotate(src, dst, cv::ROTATE_90_CLOCKWISE);
        cv::rotate(dst, dst, cv::ROTATE_90_CLOCKWISE);
        cv::rotate(dst, dst, cv::ROTATE_90_CLOCKWISE);

        // 写入输出视频
        video.write(dst);
    }

    // 释放资源
    cap.release();
    video.release();

    return 0;
}