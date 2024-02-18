#线性回归的简洁实现
import numpy as np
import torch
from torch.utils import data #导入data模块
from d2l import torch as d2l #导入d2l模块
from torch import nn #导入nn模块 神经网络模块

#设置真实值
true_w = torch.tensor([2,-3.4]) #W的真实值
true_b = 4.2 #B的真实值
features,labels = d2l.synthetic_data(true_w,true_b,1000) #生成1000个样本 且每个样本有2个特征 2个特征的真实值为true_w 且每个样本的标签为true_b + 噪声

#读取数据集
def load_array(data_arrays,batch_size,is_train=True): #data_arrays表示数据集 batch_size表示每次读取的样本数量 is_train表示是否为训练集
    """构造一个PyTorch数据迭代器"""
    dataset = data.TensorDataset(*data_arrays) #将数据和标签组合
    return data.DataLoader(dataset,batch_size,shuffle=is_train) #返回一个数据迭代器

#定义模型
net = nn.Sequential(nn.Linear(2,1)) #定义一个线性回归模型 2表示输入特征数量 1表示输出特征数量
#初始化模型参数
net[0].weight.data.normal_(0,0.01) #初始化w 从0到0.01的正态分布
net[0].bias.data.fill_(0) #初始化b 0
#定义损失函数
loss = nn.MSELoss() #均方损失
#定义优化算法
trainer = torch.optim.SGD(net.parameters(),lr=0.03) #小批量随机梯度下降 优化算法为SGD 学习率为0.03 net.parameters()表示优化net中的所有参数

#训练模型
#定义超参数
num_epochs = 10 #迭代次数
batch_size = 10 #每次读取的样本数量

for epoch in range(num_epochs): #迭代num_epochs次
    for X,y in load_array((features,labels),batch_size): #每次从数据集中读取batch_size个样本
        l = loss(net(X),y.reshape(-1,1)) #计算损失
        trainer.zero_grad() #梯度清零
        l.backward() #反向传播
        trainer.step() #更新参数
    l = loss(net(features),labels.reshape(-1,1)) #计算损失
    print(f'epoch {epoch + 1},loss {l:f}') #打印损失

#打印结果
w = net[0].weight.data #打印w
print(w)
b = net[0].bias.data #打印b
print(b)
print('w的估计误差:',true_w - w.reshape(true_w.shape)) #打印w的估计误差
print('b的估计误差:',true_b - b) #打印b的估计误差