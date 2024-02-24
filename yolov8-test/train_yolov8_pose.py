from ultralytics import YOLO

#创造模型结构文件
model = YOLO('yolov8-pose.yaml')

#导入模型权重
model = YOLO('yolov8n-pose.pt')

#训练模型
results = model.train(data='cars-pose.yaml', epochs=500,device='0',
                      optimizer='auto', optimize = True,imgsz=640, 
                      batch=32,lr0 = 0.01, lrf = 0.003)
#Changeable parameters：data, epochs, device, optimize, imgsz, batch_size, lr0, lrf
#可调整参数: 数据集, 训练轮数, 训练设备, 优化器, 图片大小, 批大小, 初始学习率, 最终学习率


#测试模型
metrics = model.val()

#导出模型
model.export(format='onnx')
model.export(format='openvino')
