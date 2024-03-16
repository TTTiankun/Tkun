from ultralytics import YOLO

#导入训练模型
model = YOLO('yolov8-cls-28.pt')

#设置图片路径
img_path = "/home/jason/Desktop/yolov8-test/test_station.jpg"
img1 = img_path
results = model.predict(source=img1, save=True) 