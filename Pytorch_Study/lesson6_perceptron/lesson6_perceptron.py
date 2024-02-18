#感知机的实现

import torch
from torch import nn
from d2l import torch as d2l


batch_size = 256 #设置批量大小
train_iter, test_iter = d2l.load_data_fashion_mnist(batch_size) #加载数据集 并且设置批量大小

#设置输出输入参数
num_inputs = 784 #输入的图像大小为28*28 向量长度为784
num_outputs = 10 #输出参数 10个类别
num_hiddens = 256 #隐藏层参数

W1 = nn.Parameter(torch.randn(num_inputs,num_hiddens,requires_grad=True)*0.01) #设置输入层参数
#randn函数返回一个张量，包含了从标准正态分布(均值为0，方差为 1，即高斯白噪声)中抽取的一组随机数，形状由可变参数sizes定义。

b1 = nn.Parameter(torch.zeros(num_hiddens,requires_grad=True)) #设置偏置参数 256个
# zeros函数返回一个张量，包含了从标准正态分布(均值为0，方差为 1，即高斯白噪声)中抽取的一组随机数，形状由可变参数sizes定义。

W2 = nn.Parameter(torch.randn(num_hiddens,num_outputs,requires_grad=True)*0.01) #设置输出层参数
#randn函数返回一个张量，包含了从标准正态分布(均值为0，方差为 1，即高斯白噪声)中抽取的一组随机数，形状由可变参数sizes定义。

b2 = nn.Parameter(torch.zeros(num_outputs,requires_grad=True)) #设置偏置参数 10个

#定义激活函数(ReLU)
def relu(X):
    a = torch.zeros_like(X) #生成一个和X形状相同的全0张量
    return torch.max(X,a) #返回X和a中的最大值

#定义网络
def net(X):
    X = X.reshape((-1,num_inputs)) #将X转换为2维张量
    H1 = relu(X @W1+b1) #计算隐藏层 也就是第一层 也就是第一次分割 
    H2 = (H1 @W2+b2) #计算隐藏层 也就是第二层 也就是第二次分割
    return H2 #计算输出层 也就是第二层 也就是第二次分割

loss = nn.CrossEntropyLoss() #定义损失函数

num_epochs, lr = 10, 0.1 #设置迭代周期和学习率
updater = torch.optim.SGD([W1,b1,W2,b2],lr=lr) #设置优化器 使用随机梯度下降算法 更新参数

def train(net, train_iter, test_iter, loss, num_epochs, updater):
    for epoch in range(num_epochs): #对于每个迭代周期
       total_loss, total_acc, total_count = 0.0, 0.0, 0 #定义损失函数、准确率、样本总数
       for X, y in train_iter:
            updater.zero_grad()  # 梯度清零 也就是将梯度设置为0
            y_hat = net(X)  # 前向传播 也就是计算预测值
            l = loss(y_hat, y)  # 计算损失 也就是计算预测值和真实值之间的差
            l.backward()  # 反向传播 也就是计算梯度
            updater.step()  # 更新参数 也就是更新权重和偏置
            total_loss += l.item() * y.shape[0]
            total_acc += (y_hat.argmax(dim=1) == y).sum().item() #计算准确率
            total_count += y.shape[0] #计算样本总数
        
       train_loss = total_loss / total_count #计算损失函数
       train_acc = total_acc / total_count #计算准确率
        

       test_loss, test_acc, test_count = 0.0, 0.0, 0 #定义损失函数、准确率、样本总数
       with torch.no_grad(): #不计算梯度
            for X, y in test_iter:
                y_hat = net(X) # 前向传播 也就是计算预测值
                l = loss(y_hat, y) # 计算损失 也就是计算预测值和真实值之间的差
                test_loss += l.item() * y.shape[0] #计算损失函数
                test_acc += (y_hat.argmax(dim=1) == y).sum().item() #计算准确率
                test_count += y.shape[0] #计算样本总数
        
       test_loss = test_loss / test_count #计算损失函数
       test_acc = test_acc / test_count #计算准确率
        
       print(f'Epoch {epoch + 1}, '
              f'Train loss {train_loss:.4f}, Train acc {train_acc:.4f}, '
              f'Test loss {test_loss:.4f}, Test acc {test_acc:.4f}')

# 调用训练函数
train(net, train_iter, test_iter, loss, num_epochs, updater)