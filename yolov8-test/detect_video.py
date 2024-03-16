from ultralytics import YOLO
#视频要放到模型文件夹里面
path = 'yolov9-new.pt'
path_video = 'test01.mp4'

# 导入openvino模型
model = YOLO(path)

# 追踪视频
results = model.track(source=path_video, show=True,save=True)