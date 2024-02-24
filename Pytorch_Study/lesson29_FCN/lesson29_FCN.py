#FCN 全连接卷积神经网络
#FCN是用深度神经网络来做语义分割的奠基性工具

#FCN的网络结构
#FCN的网络结构是由卷积层和反卷积层组成的，卷积层用来提取特征，反卷积层用来将特征图恢复到原图大小
#
#FCN的网络结构如下：
#1.输入图像
#2.卷积层
#3.转置卷积层
#4.输出图像

#将CNN最后的全连接层用转置卷积层替代

#实现
import torch
from torch import nn
from d2l import torch as d2l
from torch.nn import functional as F
import torchvision
from torch.utils.data import DataLoader
import os
import torch.optim as optim

#先获取一个预训练的模型
#获取resnet18模型 这里就是微调一下模型罢了
pretrained_net = torchvision.models.resnet18(pretrained=True)
#print(list(pretrained_net.children())[-3:]) #获取模型的最后三层

#创建一个全卷积网络
net = nn.Sequential(*list(pretrained_net.children())[:-2]) #创建一个全卷积网络

#测试代码
X = torch.rand(size=(1, 3, 320, 480)) #输入的形状
print(net(X).shape) #输出的形状

#定义一个1*1卷积层 使用：Pascal VOC2012数据集(21类) 将要素地图的高宽增加32倍
num_classes = 21 #类别数
net.add_module('final_conv', nn.Conv2d(512, num_classes, kernel_size=1)) #添加一个1*1卷积层

net.add_module('transpose_conv', nn.ConvTranspose2d(num_classes, num_classes, 
                                                    kernel_size=64, padding=16, stride=32)) #添加一个转置卷积层

#初始化转置卷积层
def bilinear_kernel(in_channels, out_channels, kernel_size):
    factor = (kernel_size + 1) // 2 #因子
    if kernel_size % 2 == 1: #如果是奇数
        center = factor - 1 #中心
    else: #如果是偶数
        center = factor - 0.5 #中心
    og = (torch.arange(kernel_size).reshape(-1, 1), torch.arange(kernel_size).reshape(1, -1)) #原始网格
    filt = (1 - torch.abs(og[0] - center) / factor) * (1 - torch.abs(og[1] - center) / factor) #滤波器 
    weight = torch.zeros((in_channels, out_channels, kernel_size, kernel_size)) #权重
    weight[range(in_channels), range(out_channels), :, :] = filt #权重
    return weight #返回权重


#废弃
# #双线性插值的上采样实验
# conv_trans = nn.ConvTranspose2d(3, 3, kernel_size=4, padding=1, stride=2, bias=False) #定义一个转置卷积层

# conv_trans.weight.data.copy_(bilinear_kernel(3, 3, 4)) #初始化转置卷积层
# img = torchvision.io.read_image('lesson24_data_augmentation/test.png').unsqueeze(0) / 255 #读取图像

# X = img.unsqueeze(0) #输入的形状
# Y = conv_trans(X) #输出的形状

# out_img = Y[0].permute(1, 2, 0) #输出的形状

# d2l.set_figsize()
# print('input image shape:', img.squeeze(0).shape) #输入的形状
# d2l.plt.imshow(img.squeeze(0)) #显示图像
# print('output image shape:', out_img.shape) #输出的形状
# d2l.plt.imshow(out_img.detach()) #显示图像

#读取数据
batch_size, crop_size = 32, (320, 480) #批量大小和裁剪大小


#训练函数
def train(net, learning_rate, batch_size=256, num_epochs=20, param_group=True):
    # 加载训练集和测试集
    train_iter, test_iter = d2l.load_data_voc(batch_size, crop_size) #读取数据

    # 确定使用的设备（GPU或CPU）
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    net.to(device)

    # 定义损失函数和优化器
    loss_fn = nn.CrossEntropyLoss()
    optimizer = optim.SGD(net.parameters(), lr=learning_rate, momentum=0.9)

    # 循环训练多个epoch
    for epoch in range(num_epochs):
        net.train()  # 将模型设置为训练模式
        running_loss = 0.0
        correct = 0
        total = 0

        # 遍历训练集
        for inputs, labels in train_iter:
            inputs, labels = inputs.to(device), labels.to(device)

            optimizer.zero_grad()  # 梯度清零

            outputs = net(inputs)  # 前向传播
            loss = loss_fn(outputs, labels)  # 计算损失
            loss.backward()  # 反向传播
            optimizer.step()  # 更新权重

            running_loss += loss.item()

            # 计算训练集准确率
            _, predicted = outputs.max(1)
            total += labels.size(0)
            correct += predicted.eq(labels).sum().item()

        # 计算平均训练损失和准确率
        train_loss = running_loss / len(train_iter)
        train_acc = correct / total

        # 打印训练情况
        print(f"Epoch [{epoch + 1}/{num_epochs}], Train Loss: {train_loss:.4f}, Train Acc: {100 * train_acc:.2f}%")

    print('Finished Training')

#训练
train(net, 0.1) #训练