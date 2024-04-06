#include"yolov8.h"
#include <opencv2/dnn/dnn.hpp>

YOLOv8::YOLOv8(){}
YOLOv8::~YOLOv8(){}

bool YOLOv8::init(string xml_path, double cof_threshold, double nms_area_threshold, int use_gpu) {
    this->gpu_mode = use_gpu;

    this->xml_path = xml_path;
    this->cof_threshold = cof_threshold;
    this->nms_area_threshold = nms_area_threshold;

    auto model = core.read_model(xml_path);
    ov::Shape model_input_shape = model->input().get_shape();
    this->model_input_w = model_input_shape[3];
    this->model_input_h = model_input_shape[2];

    ov::preprocess::PrePostProcessor ppp(model);

    // 输入设置
    ov::preprocess::InputInfo &input = ppp.input();

    input.tensor().set_layout("NHWC").set_element_type(ov::element::u8).set_shape({1, this->model_input_h, this->model_input_w, 3}).set_color_format(ov::preprocess::ColorFormat::BGR);
    // 模型设置
    input.model().set_layout("NCHW");
    // 预处理设置
    input.preprocess().convert_layout("NCHW").convert_color(ov::preprocess::ColorFormat::RGB);

    if (this->gpu_mode == 1) {
        input.preprocess().convert_element_type(ov::element::f16);
    } else {
        input.preprocess().convert_element_type(ov::element::f32);
    }

    input.preprocess().scale({255.0f, 255.0f, 255.0f});

    // 输出设置
    ov::preprocess::OutputInfo &output = ppp.output();

    ov::Shape model_output_shape = model->output().get_shape();
    if (model_output_shape[1] > model_output_shape[2]) {
        this->model_output_w = model_output_shape[2];
        this->model_output_h = model_output_shape[1];
    } else {
        this->model_output_w = model_output_shape[1];
        this->model_output_h = model_output_shape[2];
        output.tensor().set_layout("CWH");
        output.model().set_layout("CHW");
        output.postprocess().convert_layout("CHW");
    }

    output.tensor().set_element_type(ov::element::f32);
    if (this->gpu_mode == 1) {
        output.postprocess().convert_element_type(ov::element::f32);
    }

    model = ppp.build();

    if (this->gpu_mode == 0 || this->gpu_mode == 2 || this->gpu_mode == 3) {
        // CPU设置
        auto cpu_properties = core.get_property("CPU", ov::supported_properties);
        for (auto &&property: cpu_properties) {
            if (property != ov::supported_properties.name()) {
                if (property.is_mutable()) {
                    if (property == "AFFINITY") {
                        core.set_property("CPU", ov::affinity(ov::Affinity::HYBRID_AWARE));
                        continue;
                    }
                    if (property == "INFERENCE_NUM_THREADS") {
                        core.set_property("CPU", ov::inference_num_threads(16));
                        continue;
                    }
                    if (property == "INFERENCE_PRECISION_HINT") {
                        core.set_property("CPU", ov::hint::inference_precision(ov::element::f32));
                        continue;
                    }
                    if (property == "PERFORMANCE_HINT") {
                        core.set_property("CPU", ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY));
                        continue;
                    }
                    if (property == "NUM_STREAMS") {
                        core.set_property("CPU", ov::streams::num(ov::streams::NUMA));
                        continue;
                    }
                    if (property == "PERF_COUNT") {
                        core.set_property("CPU", ov::enable_profiling(false));
                        continue;
                    }
                }
            }
        }
        /*CPU设置
         * ov::affinity(ov::Affinity::HYBRID_AWARE)//设置核心与线程的关系,0:禁用线程相关性:NONE;1,将线程固定到核心，最适合静态基准测试:CODE;
         *               2,将线程固定到NUMA节点，最适合实际情况:NUMA;3,让运行时锁定内核类型，例如，对于延迟任务，更喜欢“大”内核:HYBRID_AWARE
         * ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY)//设置性能模式为低延迟:LATENCY;默认:UNDEFINED
         * ov::hint::inference_precision(ov::element::f32)//设置推理精度，cpu只能是f32
         * ov::enable_profiling(false)//允许解析数据,耗时较长,不知道有什么用,设置为false关掉
         * ov::streams::num(12)//设置推理实例并发数为5个
         * ov::streams::num(ov::steams::AUTO)//创建最少的流以提高性能
         * ov::streams::num(ov::streams::NUMA)//推理实例数按计算资源平均分配
         * ov::inference_num_threads(16)//设置推理实例的线程并发数为16个,设置太满同时有大型程序允许会卡顿,会卡得厉害,
         * ov::intel_cpu::denormals_optimization(true)//非正规优化，耗时较长，有些情况能加速，大部分情况效果不明显
         */
    }

    if (this->gpu_mode == 1 || this->gpu_mode == 2 || this->gpu_mode == 3) {
        // GPU设置
        auto gpu_properties = core.get_property("GPU", ov::supported_properties);
        for (auto &&property: gpu_properties) {
            if (property != ov::supported_properties.name()) {
                if (property.is_mutable()) {
                    if (property == "INFERENCE_PRECISION_HINT") {
                        core.set_property("GPU", ov::hint::inference_precision(ov::element::f16));
                        continue;
                    }
                    if (property == "PERFORMANCE_HINT") {
                        core.set_property("GPU", ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY));
                        continue;
                    }
                    if (property == "MODEL_PRIORITY") {
                        core.set_property("GPU", ov::hint::model_priority(ov::hint::Priority::HIGH));
                        continue;
                    }
                    if (property == "CACHE_DIR") {
                        core.set_property("GPU", ov::cache_dir("~/Detector_Cache"));
                        continue;
                    }
                    if (property == "GPU_HOST_TASK_PRIORITY") {
                        core.set_property("GPU", ov::intel_gpu::hint::host_task_priority(ov::hint::Priority::HIGH));
                        continue;
                    }
                    if (property == "GPU_QUEUE_PRIORITY") {
                        core.set_property("GPU", ov::intel_gpu::hint::queue_priority(ov::hint::Priority::HIGH));
                        continue;
                    }
                    if (property == "GPU_QUEUE_THROTTLE") {
                        core.set_property("GPU", ov::intel_gpu::hint::queue_throttle(ov::intel_gpu::hint::ThrottleLevel::HIGH));
                        continue;
                    }
                    if (property == "PERF_COUNT") {
                        core.set_property("GPU", ov::enable_profiling(false));
                        continue;
                    }
                    if (property == "COMPILATION_NUM_THREADS") {
                        core.set_property("GPU", ov::compilation_num_threads(16));
                        continue;
                    }
                }
            }
        }
        /*GPU模式设置
         * ,ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY)//设置性能模式为低延迟:LATENCY;默认:UNDEFINED
         * ,ov::hint::model_priority(ov::hint::Priority::MEDIUM)//设置模型优先级为高:HIGH;中:MEDIUM(默认);低:LOW
         * ,ov::hint::inference_precision(ov::element::f32)//设置推理精度，cpu只能是f32
         * ,ov::enable_profiling(true))//允许解析数据,耗时较长,不知道有什么用
         * ,ov::compilation_num_threads(16)//设置编译实例的线并发数为16
         * ,ov::cache_dir("../../Cache")//设置缓存路径
         * ,ov::intel_gpu::hint::host_task_priority(ov::hint::Priority::HIGH)//设置GPU插件使用的TBB关联的cpu核心类型为大核(如果可用):HIGH;任意可用核心:MEDIUM(默认);小核(如果可用):LOW
         * ,ov::intel_gpu::hint::queue_priority(ov::hint::Priority::HIGH)//设置OpenCL队列优先级为高:HIGH;中:MEDIUM(默认);低:LOW
         * ,ov::intel_gpu::hint::queue_throttle(ov::intel_gpu::hint::ThrottleLevel::HIGH)//设置OpenCL节流阀，控制的能耗为高:HIGH;中:MEDIUM(默认);低:LOW
         */
    }
    /*
    cout<<"设备参数"<<endl;
    std::vector<std::string> availableDevices = core.get_available_devices();
    for (auto&& device : availableDevices) {
        cout << device << endl;

        // Query supported properties and print all of them
        cout<< "\tSUPPORTED_PROPERTIES: " << endl;
        auto supported_properties = core.get_property(device, ov::supported_properties);
        for (auto&& property : supported_properties) {
            if (property != ov::supported_properties.name()) {
                cout << "\t\t" << (property.is_mutable() ? "Mutable: " : "Immutable: ") << property << " : "
                     << flush;

                if (core.get_property(device, property).empty()) {
                    cout << "EMPTY VALUE" << endl;
                } else {
                    std::string stringValue=core.get_property(device, property).as<std::string>();
                    cout << (stringValue.empty() ? "\"\"" : stringValue) << endl;
                }
            }
        }

        cout << endl;
    }
    */

    //     获取可执行网络
    if (this->gpu_mode == 0) {// CPU模式
        compiled_model = core.compile_model(model, "CPU");
    } else if (this->gpu_mode == 1) {// GPU模式
        compiled_model = core.compile_model(model, "GPU", ov::hint::inference_precision(ov::element::f16));
    } else if (this->gpu_mode == 2) {
        compiled_model = core.compile_model(model, "AUTO:GPU,CPU", ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY));
        auto supported_properties = compiled_model.get_property(ov::hint::performance_mode);
        cout << supported_properties << endl;
    } else if (this->gpu_mode == 3) {// 异构模式,待完善，优化耗时估计较长

        /*//可手动设置操作或子图使用的设备，例子如下
         * {
            // This example demonstrates how to perform default affinity initialization and then
            // correct affinity manually for some layers
            const std::string device = "HETERO:GPU,CPU";

            // query_model result contains mapping of supported operations to devices
            auto supported_ops = core.query_model(model, device);

            // update default affinities manually for specific operations
            supported_ops["operation_name"] = "CPU";

            // set affinities to a model
            for (auto &&node : model->get_ops()) {
             auto &affinity = supported_ops[node->get_friendly_name()];
             // Store affinity mapping using op runtime information
             node->get_rt_info()["affinity"] = affinity;
            }

            // load model with manually set affinities
            auto compiled_model = core.compile_model(model, device);
            }
         */
        compiled_model = core.compile_model(model, "HETERO:GPU,CPU", ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY));
        auto supported_properties = compiled_model.get_property(ov::hint::performance_mode);
        cout << supported_properties << endl;
        /*
         * 可以设置环境变量OPENVINO_HETERO_VISUALIZE=1获得操作和图的注释，来针对性设置子图和操作所用设备,
         * 注释文件位于cmake-build-debug/bin/中,命令行使用 xdot *.dot读取
         */
    }

    infer_request = compiled_model.create_infer_request();
    input_tensor = infer_request.get_input_tensor();
    output_tensor = infer_request.get_output_tensor();
    cout<<"模型初始化完成"<<endl;

    return true;
}

void YOLOv8::boxes_extract(float *output_data, int cof_threshold, vector<Rect> &rects, vector<float> &rect_cofs, vector<int> &cls) {
    
    for (int i = 0; i < this->model_output_h * this->model_output_w; i += this->model_output_w) {

        //这里使用的是没有关键点的模型
        //输出的张量形态[h*w,w]
        //前四位分别是x,y,w,h
        double max_prob = 0;
        int idx = 0;
        int class_num = 2;
        int dias = 4;
        for (int t = 0; t < class_num; t++) {
            double tp = output_data[i + 4 + t];
            if (tp > max_prob) {
                max_prob = tp;
                idx = t;
            }
        }

        if (max_prob < cof_threshold)
            continue;

        double x = output_data[i + 0];
        double y = output_data[i + 1];
        double w = output_data[i + 2];
        double h = output_data[i + 3];

        cls.push_back(idx);
        rects.push_back(Rect(x - w / 2, y - h / 2, w, h));
        rect_cofs.push_back(max_prob);
    }
}


void YOLOv8::process_frame(Mat &image, vector<Object> &station, vector<Object> &angle) {
    if(image.empty()){
        cout<<"Error: Image is empty"<<endl;
    }
    
    int image_h = image.rows;
    int image_w = image.cols;
    double f_h = double(image_h) / double(this->model_input_h);
    double f_w = double(image_w) / double(this->model_input_w);
    int r_h, r_w;
    cv::Mat resize_image;
    // 变换尺寸兼载入数据
    if (f_h > f_w) {
        f = f_h;
        r_h = this->model_input_h;
        r_w = std::floor(image_w / f_h);
    } else {
        f = f_w;
        r_h = std::floor(image_h / f_w);
        r_w = this->model_input_w;
    }
    cv::resize(image, resize_image, cv::Size(r_w, r_h), 0, 0);

    int d_h = this->model_input_h - r_h;
    int d_w = this->model_input_w - r_w;
    top = std::floor(d_h / 2);
    left = std::floor(d_w / 2);
    bottom = d_h - top;
    right = d_w - left;

    auto input_data = input_tensor.data<uint8_t>();
    Mat data_mat(this->model_input_h, this->model_input_w, CV_8UC3, input_data);
    cv::copyMakeBorder(resize_image, data_mat, top, bottom, left, right, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0)); //给图像加上黑色的边框  

    infer_request.infer();

    output_tensor = infer_request.get_output_tensor();
    float *output_data = output_tensor.data<float>();
    // std::cout << "Inference done" << std::endl;
    
    
    vector<Rect> rects;
    vector<float> rect_cofs;
    vector<int> cls;
    

    boxes_extract(output_data, cof_threshold,rects,rect_cofs,cls);

    vector<int> final_id;
    dnn::NMSBoxes(rects, rect_cofs, cof_threshold, nms_area_threshold, final_id);

    for(auto id: final_id){
        
        Object result;
        result.class_id = cls[id];
        result.rect.x = (rects[id].x - left) * f;
        result.rect.y = (rects[id].y - top) * f;
        result.rect.width = (rects[id].width) * f;
        result.rect.height = (rects[id].height) * f;

        result.confidence = rect_cofs[id]; 

        if(result.rect.x<0 ||result.rect.x + result.rect.width>image.cols || result.rect.y<0 || result.rect.y + result.rect.height>image.rows){
            continue;
        }
        if(result.class_id == 0){
            station.push_back(result);
        }else if(result.class_id == 1){
            angle.push_back(result);
        }
    }  
}

