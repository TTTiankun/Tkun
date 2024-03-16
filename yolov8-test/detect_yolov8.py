from ultralytics import YOLO
from PIL import Image

path = 'breast.pt'

# 导入openvino模型
model = YOLO(path)

# 导出检测结果
results = model('31.png')

# 导出图片
im1 = Image.open("31.png")
results = model.predict(source=im1, save=True) 