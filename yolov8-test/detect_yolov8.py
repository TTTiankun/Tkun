from ultralytics import YOLO
from PIL import Image

path = 'yolov8n_openvino_model/'

# 导入openvino模型
model = YOLO(path)

# 导出检测结果
results = model('bus.jpg')

# 导出图片
im1 = Image.open("bus.jpg")
results = model.predict(source=im1, save=True) 