from ultralytics import YOLO

path = 'next_model.pt'

model = YOLO(path)

#导出模型
model.export(format='onnx')
model.export(format='openvino')