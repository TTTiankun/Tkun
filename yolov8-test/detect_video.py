from ultralytics import YOLO
#视频要放到模型文件夹里面
path = 'best_openvino_model/'
path_video = 'test.avi'

# 导入openvino模型
model = YOLO(path)

# 追踪视频
results = model.track(source=path, show=True,save=True)