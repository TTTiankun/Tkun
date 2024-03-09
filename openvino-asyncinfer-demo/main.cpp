#include"asyncinfer.h"

#include<iostream>

#include<opencv2/opencv.hpp>
#include<openvino/openvino.hpp>

//图像区
cv::Mat img1 = cv::imread("/home/jason/Desktop/1.jpg");
cv::Mat img2 = cv::imread("/home/jason/Desktop/2.jpg");
cv::Mat img3;

//文件区
std::string model_path = "/home/jason/Desktop/perception/model/number/best.onnx";

//推理设置区
int GPU_mode = 1;
int async_mode = 1;
double score_threshold = 0.5;
std::chrono::high_resolution_clock::time_point start;
bool condition;

int main(){

    //创建异步推理对象
    AsyncInfer asyncinfer;

    //初始化
    asyncinfer.init(GPU_mode, async_mode, model_path, score_threshold);

    if(async_mode == 0){
        while(1){
            start = std::chrono::high_resolution_clock::now();
            asyncinfer.syncinference(img1);
            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "duration: " <<duration.count() << "us" << std::endl;
            std::cout << "result: " <<asyncinfer.number  << " prob: " << asyncinfer.prossibility << std::endl;

            cv::Mat image_temp = img1;
            img1 = img2;
            img2 = image_temp;
            }
            
        }else{
            
            asyncinfer.pre_img(img1, asyncinfer.curr_input_tensor);
            asyncinfer.curr_request.start_async();//开始异步推理

            while(1){
                start = std::chrono::high_resolution_clock::now();
                condition = asyncinfer.asyncinference(img2);
                if(condition == false){
                    break;
                }
                std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                std::cout << "duration: " <<duration.count() << "us" << std::endl;
                std::cout << "result: " <<asyncinfer.number  << " prob: " << asyncinfer.prossibility << std::endl;

                cv::Mat image_temp = img1;
                img1 = img2;
                img2 = image_temp;
            }
        }    
    return 0;
}