from ultralytics import YOLO
from PIL import Image

path = 'test_openvino_model/best.pt'

# 导入openvino模型
model = YOLO(path)

# 导出检测结果
results = model('test_openvino_model/test.png')

#导出图片
im1 = Image.open('test_openvino_model/test.png')
results = model.predict(source=im1, save=True) 