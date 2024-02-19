#微调
#微调通过使用大数据上得到的与训练好的模型相似的模型来初始化模型参数，从而得到更好的模型。
#微调的方法是：先在大数据集上训练一个模型，然后将这个模型的参数作为要微调的模型的初始参数，然后在小数据集上训练这个模型。
#微调通常速度更快、精度更高

#展示

import os
import torch
import torchvision
from torch import nn
from d2l import torch as d2l
from torch.utils.data import DataLoader
import torch.optim as optim
from torchvision import transforms


#导入数据集
d2l.DATA_HUB['hotdog'] = (d2l.DATA_URL + 'hotdog.zip',
                            'fba480ffa8aa7e0febbb511d181409f899b9baa5')
#下载数据集
data_dir = d2l.download_extract('hotdog')

#数据增强
train_imgs = torchvision.datasets.ImageFolder(
    os.path.join(data_dir, 'train')) #训练集 图片文件夹 里面有hotdog和not_hotdog两个文件夹 分别存放着热狗和非热狗的图片 

test_imgs = torchvision.datasets.ImageFolder(
    os.path.join(data_dir, 'test')) #测试集 图片文件夹 里面有hotdog和not_hotdog两个文件夹 分别存放着热狗和非热狗的图片

#数据增强
normalize = torchvision.transforms.Normalize(
    [0.485, 0.456, 0.406], [0.229, 0.224, 0.225]) #归一化 三个通道的均值和方差 

#训练集数据增强
train_augs = torchvision.transforms.Compose([
    torchvision.transforms.RandomResizedCrop(224), #随机裁剪
    torchvision.transforms.RandomHorizontalFlip(), #随机水平翻转
    torchvision.transforms.ToTensor(), #转换为张量
    normalize]) #归一化

#测试集数据增强
test_augs = torchvision.transforms.Compose([
    torchvision.transforms.Resize(256), #调整大小
    torchvision.transforms.CenterCrop(224), #中心裁剪
    torchvision.transforms.ToTensor(), #转换为张量
    normalize]) #归一化

#定义和初始化模型
pretrained_net = torchvision.models.resnet18(pretrained=True) #使用resnet18模型 预训练好的模型参数 pretrained=True意思是使用预训练好的模型参数
pretrained_net.fc = nn.Linear(512, 2) #将全连接层的输出改为2

#定义
finetune_net = torchvision.models.resnet18(pretrained=True) #使用resnet18模型 预训练好的模型参数 pretrained=True意思是使用预训练好的模型参数
finetune_net.fc = nn.Linear(finetune_net.fc.in_features,2) #替换掉全连接层 从而满足新的数据集的输出 比如热狗和非热狗两类
nn.init.xavier_uniform_(finetune_net.fc.weight) #初始化全连接层的权重

# 微调
def train_fine_tuning(net, learning_rate, batch_size=256, num_epochs=20, param_group=True):
    # 加载训练集和测试集
    train_iter = DataLoader(
        torchvision.datasets.ImageFolder(os.path.join(data_dir, 'train'),
                                         transform=train_augs),
        batch_size=batch_size, shuffle=True)
    test_iter = DataLoader(
        torchvision.datasets.ImageFolder(os.path.join(data_dir, 'test'),
                                         transform=test_augs),
        batch_size=batch_size)

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

train_fine_tuning(finetune_net, 5e-5) #微调