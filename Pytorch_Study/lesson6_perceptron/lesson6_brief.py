#简单实现 API
import torch
from torch import nn
from d2l import torch as d2l

#设置参数
batch_size = 256 #设置批量大小
train_iter, test_iter = d2l.load_data_fashion_mnist(batch_size) #加载数据集 并且设置批量大小


#设置网络
net = nn.Sequential(nn.Flatten(),nn.Linear(784,256),nn.ReLU(),nn.Linear(256,10)) 
#定义一个网络 也就是一个Sequential实例 使用Flatten层将每个图像展平为向量 然后是一个线性层 然后是一个ReLU层 然后是一个线性层
#线性层的输出个数是隐藏单元的个数 也就是256个 向量长度为784
#ReLU层用来对隐藏单元进行激活
#线性层的输出个数是输出单元的个数 也就是10个 向量长度为256

#设置权重函数
def init_weights(m):
    if type(m) == nn.Linear:
        nn.init.normal_(m.weight,std=0.01)

net.apply(init_weights) #对网络net中的每个层应用函数init_weights

#设置损失函数
loss = nn.CrossEntropyLoss() #定义损失函数

#设置优化器
updater = torch.optim.SGD(net.parameters(),lr=0.1) #设置优化器 使用随机梯度下降算法 更新参数

#训练模型
num_epochs = 10 #设置迭代周期
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
