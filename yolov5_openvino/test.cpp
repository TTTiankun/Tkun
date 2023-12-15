#include <fstream>                   //C++ 文件操作
#include <iostream>                  //C++ input & output stream
#include <sstream>                   //C++ String stream, 读写内存中的string对象
#include <opencv2/opencv.hpp>        //OpenCV 头文件
#include <openvino/openvino.hpp>     //OpenVINO >=2023.1
 
using namespace std;
using namespace ov;
using namespace cv;
 

// COCO数据集的标签，可以根据自己的实际情况修改标签。
vector<string> class_names = { "person", "bicycle", "car", "motorbike", "aeroplane", "bus", "train", "truck", "boat", "traffic light","fire hydrant",
"stop sign", "parking meter", "bench", "bird", "cat", "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe","backpack", "umbrella",
"handbag", "tie", "suitcase", "frisbee", "skis", "snowboard", "sports ball", "kite", "baseball bat", "baseball glove","skateboard", "surfboard",
"tennis racket", "bottle", "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple", "sandwich", "orange","broccoli", "carrot",
"hot dog", "pizza", "donut", "cake", "chair", "sofa", "pottedplant", "bed", "diningtable", "toilet", "tvmonitor", "laptop", "mouse","remote",
"keyboard", "cell phone", "microwave", "oven", "toaster", "sink", "refrigerator", "book", "clock", "vase", "scissors", "teddy bear", "hair drier", "toothbrush" };
 
//OpenVINO IR模型文件路径（修改为自己的yolov5s.xml路径）
string ir_filename = "../yolov5s.xml"; // 指定OpenVINO IR 模型文件的路径

// @brief 对网络的输入为图片数据的节点进行赋值，实现图片数据输入网络
// @param input_tensor 输入节点的tensor
// @param inpt_image 输入图片数据
void fill_tensor_data_image(ov::Tensor& input_tensor, const cv::Mat& input_image) {
	// 获取输入节点要求的输入图片数据的大小
	ov::Shape tensor_shape = input_tensor.get_shape();
	const size_t width = tensor_shape[3]; // 要求输入图片数据的宽度
	const size_t height = tensor_shape[2]; // 要求输入图片数据的高度
	const size_t channels = tensor_shape[1]; // 要求输入图片数据的维度
	// 读取节点数据内存指针
	float* input_tensor_data = input_tensor.data<float>();
	// 将图片数据填充到网络中
	// 原有图片数据为 H、W、C 格式，输入要求的为 C、H、W 格式
	for (size_t c = 0; c < channels; c++) {
		for (size_t h = 0; h < height; h++) {
			for (size_t w = 0; w < width; w++) {
				input_tensor_data[c * width * height + h * width + w] = input_image.at<cv::Vec<float, 3>>(h, w)[c];
			}
		}
	}
}
 
 
int main(int argc, char** argv) {

 
  
    //1、创建推理核心
    Core core; // 创建OpenVINO核心对象
    CompiledModel compiled_model =
        core.compile_model(ir_filename, "GPU"); // 编译OpenVINO模型
    InferRequest infer_request =
       compiled_model.create_infer_request(); // 创建推理请求对象

    //2、 预处理输入数据 - 格式化操作
	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened()) {
		cout << "Exit!webcam fails to open!" << endl;
		return -1;
	}
  
    // 3、获取输入节点tensor
    Tensor input_image_tensor =
        infer_request.get_tensor("images");          // 获取输入图像张量
    int input_h = input_image_tensor.get_shape()[2]; // 获取输入图像的高度
    int input_w = input_image_tensor.get_shape()[3]; // 获取输入图像的宽度

    cout << "input_h:" << input_h << "; input_w:" << input_w
        << endl; // 输出输入图像的高度和宽度
    cout << "input_image_tensor's element type:"
        << input_image_tensor.get_element_type()
        << endl; // 输出输入图像张量的元素类型
    cout << "input_image_tensor's shape:" << input_image_tensor.get_shape()
        << endl; // 输出输入图像张量的形状
 
    // 4、获取输出节点tensor
	Tensor output_tensor = infer_request.get_tensor("output0"); // 获取输出张量
    int out_rows = output_tensor.get_shape()[1]; // 获取输出张量的行数
     int out_cols = output_tensor.get_shape()[2]; // 获取输出张量的列数

    cout << "out_cols:" << out_cols << "; out_rows:" << out_rows
        << endl; // 输出输出张量的列数和行数
	
 
	//连续采集处理循环
	while (true) {

 
		Mat frame;
		cap >> frame;
 
		int64 start = cv::getTickCount(); // 获取开始时间
        int w = frame.cols;               // 获取图像帧的宽度
        int h = frame.rows;               // 获取图像帧的高度
        int _max = std::max(h, w);        // 获取宽度和高度的最大值
        cv::Mat image =
            cv::Mat::zeros(cv::Size(_max, _max), CV_8UC3); // 创建一个全零图像
        cv::Rect roi(0, 0, w, h); // 创建感兴趣区域
        frame.copyTo(image(roi)); // 将图像帧复制到全零图像的感兴趣区域

        float x_factor = static_cast<float>(image.cols) /
                        static_cast<float>(input_w); // 计算宽度缩放因子
        float y_factor = static_cast<float>(image.rows) /
                        static_cast<float>(input_h); // 计算高度缩放因子

        cv::Mat blob_image; // 创建用于推理的图像
        resize(image, blob_image, cv::Size(input_w, input_h)); // 调整图像大小
        blob_image.convertTo(blob_image, CV_32F); // 转换图像数据类型为32位浮点数
        blob_image = blob_image / 255.0; // 归一化图像数据

        fill_tensor_data_image(input_image_tensor,
                             blob_image); // 将图像数据填充到输入张量中

        infer_request.infer(); // 进行推理

        const ov::Tensor &output_tensor =
            infer_request.get_tensor("output0"); // 获取输出张量

        cv::Mat det_output(out_rows, out_cols, CV_32F,
                            (float *)output_tensor.data()); // 创建输出检测结果图像

        std::vector<cv::Rect> boxes;    // 创建用于存储边界框的向量
        std::vector<int> classIds;      // 创建用于存储类别标签的向量
        std::vector<float> confidences; // 创建用于存储置信度的向量

        for (int i = 0; i < det_output.rows; i++) {
            float confidence = det_output.at<float>(i, 4); // 获取置信度值
            if (confidence < 0.4) {
            continue; // 如果置信度低于0.4，继续下一次循环
            }

        cv::Mat classes_scores =
            det_output.row(i).colRange(5, 7); // 获取类别分数
        cv::Point classIdPoint;               // 创建类别标签点
        double score;
        minMaxLoc(classes_scores, 0, &score, 0,
                  &classIdPoint); // 获取类别标签和分数

        if (score > 0.5)
        {

            float cx = det_output.at<float>(i, 0); // 获取边界框中心x坐标
            float cy = det_output.at<float>(i, 1); // 获取边界框中心y坐标
            float ow = det_output.at<float>(i, 2); // 获取边界框宽度
            float oh = det_output.at<float>(i, 3); // 获取边界框高度
            int x = static_cast<int>((cx - 0.5 * ow) *
                                    x_factor); // 计算边界框左上角x坐标
            int y = static_cast<int>((cy - 0.5 * oh) *
                                    y_factor); // 计算边界框左上角y坐标
            int width = static_cast<int>(ow * x_factor);  // 计算边界框宽度
            int height = static_cast<int>(oh * y_factor); // 计算边界框高度
            cv::Rect box;                                 // 创建边界框
            box.x = x;
            box.y = y;
            box.width = width;
            box.height = height;

            boxes.push_back(box);               // 将边界框添加到向量中
            classIds.push_back(classIdPoint.x); // 将类别标签添加到向量中
            confidences.push_back(score);       // 将置信度添加到向量中
        }
      }

        std::vector<int> indexes; // 创建用于存储边界框索引的向量
         cv::dnn::NMSBoxes(boxes, confidences, 0.25, 0.45,
                            indexes); // 使用非极大值抑制获取最终的边界框索引
		for (size_t i = 0; i < indexes.size(); i++) 
        {
			int index = indexes[i];
			int idx = classIds[index];
			cv::rectangle(frame, boxes[index], cv::Scalar(0, 0, 255), 2, 8);
			cv::rectangle(frame, cv::Point(boxes[index].tl().x, boxes[index].tl().y - 20),
				cv::Point(boxes[index].br().x, boxes[index].tl().y), cv::Scalar(0, 255, 255), -1);
			cv::putText(frame, class_names[idx], cv::Point(boxes[index].tl().x, boxes[index].tl().y - 10), cv::FONT_HERSHEY_SIMPLEX, .5, cv::Scalar(0, 0, 0));
		}
 
		// 计算FPS render it
		float t = (cv::getTickCount() - start) / static_cast<float>(cv::getTickFrequency());
		cout << "Infer time(ms): " << t * 1000 << "ms; Detections: " << indexes.size() << endl;
		putText(frame, cv::format("FPS: %.2f", 1.0 / t), cv::Point(20, 40), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(255, 0, 0), 2, 8);
		cv::imshow("YOLOv5 + OpenVINO 2023.1 C++ Test", frame);
 
		char c = cv::waitKey(1);
		if (c == 27) { // ESC 设置退出程序
			break;
		}
	}
 
	cv::waitKey(0);
	cv::destroyAllWindows();
 
	return 0;
}