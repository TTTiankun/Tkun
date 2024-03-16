from ultralytics import YOLO

path = 'car-0.5.pt'

model = YOLO(path)

#导出模型
model.export(format='onnx')
model.export(format='openvino')