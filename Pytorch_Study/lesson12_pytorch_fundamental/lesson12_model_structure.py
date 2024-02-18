#回顾多层感知机
import torch
from torch import nn
from torch.nn import functional as F

net1 = nn.Sequential(nn.Linear(20, 256), nn.ReLU(), nn.Linear(256, 10)) 
#这里的20是输入特征数 10是输出特征数 256是隐藏层的神经元个数 线性激活函数是ReLU

X = torch.rand(2, 20) #随机生成一个2行20列的矩阵
Y = torch.rand(2, 20) #随机生成一个2行20列的矩阵
print(net1(X)) #输出

#自定义模型 MLP 代表多层感知机
class MLP(nn.Module):
    def __init__(self):
        super().__init__() #调用父类的初始化函数
        self.hidden = nn.Linear(20, 256) #隐藏层
        self.out = nn.Linear(256, 10) #输出层
    
    def forward(self, X): #定义前向传播
        return self.out(F.relu(self.hidden(X))) #激活函数是ReLU
    
net2 = MLP()
print(net2(Y))

#顺序块 这里的Sequential类继承自Module类 
#可以将它看成是一个容器 它负责将传入的模块逐一添加到计算图中
#比如激活函数ReLU和全连接层Linear都是Module类的子类
class MySequential(nn.Module):
    def __init__(self, *args): #接收一系列的模块
        super().__init__()
        for block in args: #遍历每个模块
            self._modules[block] = block #将每个模块添加到模块字典中
    
    def forward(self, X): #定义前向传播
        for block in self._modules.values(): #遍历每个模块
            X = block(X) #将每个模块的输出作为下一个模块的输入
        return X

net3 = MySequential(nn.Linear(20, 256), nn.ReLU(), nn.Linear(256, 10))
#这里的20是输入特征数 10是输出特征数 256是隐藏层的神经元个数 线性激活函数是ReLU
print(net3(Y))

#全连接隐藏层 作用：将输入特征转换成隐藏特征 
class FixedHiddenMLP(nn.Module):
    def __init__(self):
        super().__init__()
        self.rand_weight = torch.rand((20, 20), requires_grad=False) #定义权重矩阵
        self.linear = nn.Linear(20, 20) #定义全连接层 使用线性回归
    
    #作用：将输入特征和隐藏特征相乘 然后使用ReLU激活函数
    def forward(self, X): #定义前向传播
        X = self.linear(X) #全连接层 
        X = F.relu(torch.mm(X, self.rand_weight) + 1) #ReLU激活函数
        X = self.linear(X) #全连接层
        while X.abs().sum() > 1: #当X的绝对值之和大于1时
            X /= 2 #将X除以2
        return X.sum() #返回X的和
    
net4 = FixedHiddenMLP()
print(net4(X))

#混合搭配各种组合块
class NestMLP(nn.Module):
    def __init__(self):
        super().__init__()
        self.net = nn.Sequential(nn.Linear(20, 256), nn.ReLU(),
                                 nn.Linear(256,128),nn.ReLU()) #定义一个Sequential类 
        #这上面定义里两个隐藏层 一个是256个神经元 一个是128个神经元
        
        self.linear = nn.Linear(128, 10) #定义一个全连接层
    def forward(self, X): #定义前向传播
        return self.linear(self.net(X)) #返回全连接层的输出
    
chimera = nn.Sequential(NestMLP(), nn.Linear(10, 1),nn.Linear(1,20),FixedHiddenMLP()) #定义一个Sequential类 chimera是嵌套的
#过程：先将输入特征转换成隐藏特征 然后将隐藏特征转换成输出特征 输出先被转化为（batch_size,1）再被转化为（batch_size,20），最后被FixedHiddenMLP转化为（batch_size,1）
print(chimera(X)) #输出