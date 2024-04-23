from ultralytics import YOLO

#创造模型结构文件并导入权重
model = YOLO('yolov8n.yaml').load('yolov8n.pt')     


#训练模型
results = model.train(data='stomach.yaml', epochs=30,device='0',
                      optimizer='auto', optimize = True,imgsz=640, 
                      batch=32,lr0 = 0.01, lrf = 0.001)
#Changeable parameters：data, epochs, device, optimize, imgsz, batch_size, lr0, lrf
#可调整参数: 数据集, 训练轮数, 训练设备, 优化器, 图片大小, 批大小, 初始学习率, 最终学习率


#测试模型
results = model.val()

# #导出模型
# success_onnx = model.export(format='onnx')
# success_openvino = model.export(format='openvino')
