#从零开始实现SSD

import torch
import torch.nn as nn
import torch.nn.functional as F
import cv2
import numpy as np
from d2l import torch as d2l

#创建一个目标分类器
def cls_predictor(num_inputs, num_anchors, num_classes):
    return nn.Conv2d(num_inputs, num_anchors * (num_classes + 1), kernel_size=3, padding=1) #输出通道数是锚框数乘以（类别数加一）
                                                                                            #核大小是3*3 填充是1

#创建一个边界框预测器
def bbox_predictor(num_inputs, num_anchors):
    return nn.Conv2d(num_inputs, num_anchors * 4, kernel_size=3, padding=1) #输出通道数是锚框数乘以4 4是因为每个锚框的偏移量有4个 两个坐标两个宽高 
                                                                            #核大小是3*3 填充是1

#连接多尺度的预测
def forward(x, block):
    return block(x) #输入x经过block后输出

#测试代码
# Y1 = forward(torch.zeros((2, 8, 20, 20)), cls_predictor(8, 5, 10)) #输入通道数是8 锚框数是5 类别数是10
# Y2 = forward(torch.zeros((2, 16, 10, 10)), cls_predictor(16, 3, 10)) #输入通道数是16 锚框数是3 类别数是10
# print(Y1.shape, Y2.shape) #输出的形状

#flatten操作（扁平化） flatten操作将输入的形状变成（批量大小，通道数，高，宽）的形状 flatten操作不改变批量大小 
def flatten_pred(pred):
    return pred.permute(0, 2, 3, 1).reshape(pred.shape[0], -1) #permute操作将通道数放到最后 
                                                                #reshape操作将输入的形状变成（批量大小，通道数*高*宽）的形状

#concat操作（连接） concat操作将多个输入在某个维度上连结
def concat_preds(preds):
    return torch.cat([flatten_pred(p) for p in preds], dim=1) #将多个输入在通道数这个维度上连结

#测试代码
# print(concat_preds([Y1, Y2]).shape) #输出的形状

#定义一个模块化的块 (高和宽减半块) 原理：两个卷积层和一个最大池化层
def down_sample_blk(in_channels, out_channels):
    blk = [] #定义一个空列表
    for _ in range(2): 
        blk.append(nn.Conv2d(in_channels, out_channels, kernel_size=3, padding=1)) #添加一个卷积层
        blk.append(nn.BatchNorm2d(out_channels)) #添加一个批量归一化层 
        blk.append(nn.ReLU()) #添加一个激活函数
        in_channels = out_channels #输出通道数是下一个块的输入通道数
    blk.append(nn.MaxPool2d(2)) #添加一个最大池化层
    return nn.Sequential(*blk) #返回一个块

#测试代码
# print(down_sample_blk(3, 10)) #输出的块
# print(forward(torch.zeros((2, 3, 20, 20)),down_sample_blk(3,10)).shape) #输入的形状 经过块后输出的形状 

#基本网络块
def base_net():
    blk = [] #定义一个空列表
    num_filters = [3, 16, 32, 64] #通道数 高宽会减少8倍
    for i in range(len(num_filters) - 1): #遍历通道数
        blk.append(down_sample_blk(num_filters[i], num_filters[i + 1])) #添加一个块
    return nn.Sequential(*blk) #返回一个块

#测试代码
# print(base_net()) #输出的块
# print(forward(torch.zeros((2, 3, 256, 256)), base_net()).shape) #输入的形状 经过块后输出的形状

#完整的单发多框检测模型由五个模块组成
def get_blk(i):
    if i == 0: #第一个模块
        blk = base_net() #基本网络块
    elif i == 1: #第二个模块
        blk = down_sample_blk(64, 128) #高和宽减半块
    elif i == 4: #第五个模块
        blk = nn.AdaptiveMaxPool2d((1, 1)) #自适应最大池化层
    else: #其他模块
        blk = down_sample_blk(128, 128) #高和宽减半块
    return blk

#为每个模块定义一个前向传播函数
def blk_forward(X, blk, size, ratio, cls_predictor, bbox_predictor):
    Y = blk(X) #输入X经过blk后输出Y
    anchors = d2l.multibox_prior(Y, sizes=size, ratios=ratio) #生成锚框 
    cls_preds = cls_predictor(Y) #预测类别
    bbox_preds = bbox_predictor(Y) #预测边界框
    return (Y, anchors, cls_preds, bbox_preds) #返回Y锚框类别预测和边界框预测

#超参数
sizes = [[0.2, 0.272],
          [0.37, 0.447], 
          [0.54, 0.619],
          [0.71, 0.79], 
          [0.88, 0.961]] #锚框的尺寸在不断增大 尺寸含义：相对于锚框中心点的宽和高的比例

ratios = [[1, 2, 0.5]] * 5 #锚框的宽高比 5个模块每个模块有3个锚框的宽高比
num_anchors = len(sizes[0]) + len(ratios[0]) - 1 #锚框的数量

#定义完整的模型
class TinySSD(nn.Module):
    def __init__(self, num_classes, **kwargs):
        super(TinySSD, self).__init__(**kwargs)
        self.num_classes = num_classes #类别数
        idx_to_in_channels = [64, 128, 128, 128, 128] #输入通道数
        for i in range(5): #遍历5个模块
            #添加一个模块
            setattr(self, f'blk_{i}', get_blk(i)) #添加一个模块
            setattr(self, f'cls_{i}', cls_predictor(idx_to_in_channels[i], num_anchors, num_classes)) #添加一个类别预测器
            setattr(self, f'bbox_{i}', bbox_predictor(idx_to_in_channels[i], num_anchors)) #添加一个边界框预测器

    def forward(self, X):
        anchors, cls_preds, bbox_preds = [None] * 5, [None] * 5, [None] * 5 #初始化锚框类别预测和边界框预测
        for i in range(5): #遍历5个模块
            #获取模块
            X, anchors[i], cls_preds[i], bbox_preds[i] = blk_forward(X, getattr(self, f'blk_{i}'), sizes[i], ratios[i], 
                                                                    getattr(self, f'cls_{i}'), getattr(self, f'bbox_{i}')) #获取模块
        
        anchors = torch.cat(anchors, dim=1) #在通道数这个维度上连结
        cls_preds = concat_preds(cls_preds) #连接类别预测
        cls_preds = cls_preds.reshape(cls_preds.shape[0], -1, self.num_classes + 1) #形状变换 
        bbox_preds = concat_preds(bbox_preds)

        #返回锚框类别预测和边界框预测
        return anchors, cls_preds, bbox_preds
    
#测试代码 创建一个模型实例 并使用它做前向计算
# net = TinySSD(num_classes=1) #类别数是1
# X = torch.zeros((32, 3, 256, 256)) #输入的形状
# anchors, cls_preds, bbox_preds = net(X) #输入X经过net后输出锚框类别预测和边界框预测

# print('output anchors:', anchors.shape) #输出的锚框的形状
# print('output class preds:', cls_preds.shape) #输出的类别预测的形状
# print('output bbox preds:', bbox_preds.shape) #输出的边界框预测的形状

#加载数据集
batch_size = 32 #批量大小
train_iter, _ = d2l.load_data_bananas(batch_size) #加载数据集

#初始化其参数和优化算法
device, net = d2l.try_gpu(), TinySSD(num_classes=1) #类别数是1
trainer = torch.optim.SGD(net.parameters(), lr=0.2, weight_decay=5e-4) #优化算法

#定义损失函数
cls_loss = nn.CrossEntropyLoss(reduction='none') #类别损失 
bbox_loss = nn.L1Loss(reduction='none') #边界框损失

#定义一个函数计算所有锚框的类别预测和边界框预测的损失
def calc_loss(cls_preds, cls_labels, bbox_preds, bbox_labels, bbox_masks):
    batch_size, num_classes = cls_preds.shape[0], cls_preds.shape[2] #批量大小 类别数
    cls = cls_loss(cls_preds.reshape(-1, num_classes), cls_labels.reshape(-1)).reshape(batch_size, -1).mean(dim=1) #类别损失
    bbox = bbox_loss(bbox_preds * bbox_masks, bbox_labels * bbox_masks).mean(dim=1) #边界框损失
    return cls + bbox #返回类别损失和边界框损失

#定义一个函数来计算分类预测的准确率
def cls_eval(cls_preds, cls_labels):
    return float((cls_preds.argmax(dim=-1).type(cls_labels.dtype) == cls_labels).sum()) #返回准确率

#定义一个函数来计算锚框预测的准确率
def bbox_eval(bbox_preds, bbox_labels, bbox_masks):
    return float((torch.abs((bbox_labels - bbox_preds) * bbox_masks)).sum()) #返回平均绝对误差 


#训练模型
net = net.to(device) #模型移动到device上
#超参数
num_epochs, timer = 20, d2l.Timer() #迭代周期 计时器
#训练函数
def trainer(net, train_iter, num_epochs, lr, device):
    net.train() #训练模式
    trainer = torch.optim.SGD(net.parameters(), lr=lr) #优化算法
    for epoch in range(num_epochs): #遍历迭代周期
        acc_sum, mae_sum, n, m = 0.0, 0.0, 0, 0 #准确率和平均绝对误差
        for features, target in train_iter: #遍历数据集
            timer.start() #计时开始
            trainer.zero_grad() #梯度清零
            X, Y = features.to(device), target.to(device) #数据移动到device上
            anchors, cls_preds, bbox_preds = net(X) #输入X经过net后输出锚框类别预测和边界框预测
            bbox_labels, bbox_masks, cls_labels = d2l.multibox_target(anchors, Y) #多框目标
            l = calc_loss(cls_preds, cls_labels, bbox_preds, bbox_labels, bbox_masks).mean() #计算损失
            l.backward() #反向传播
            trainer.step() #迭代优化算法
            acc_sum += cls_eval(cls_preds, cls_labels) #计算准确率
            n += cls_labels.numel() #计算元素个数
            mae_sum += bbox_eval(bbox_preds, bbox_labels, bbox_masks) #计算平均绝对误差
            m += bbox_labels.numel() #计算元素个数
        if (epoch + 1) % 1 == 0: #每1次迭代
            print('epoch %2d, class err %.2f, bbox mae %.2f, time %.1f sec' % (epoch + 1, 1 - acc_sum / n, mae_sum / m, timer.stop())) #输出迭代周期和准确率
    print(f'class err {1 - acc_sum / n:.2f}, bbox mae {mae_sum / m:.2f}') #输出准确率和平均绝对误
    print(f'{n / timer.stop():.1f} examples/sec on {str(device)}') #输出每秒处理的样本数

#训练
trainer(net, train_iter, num_epochs, lr=0.2, device=device) #训练模型

