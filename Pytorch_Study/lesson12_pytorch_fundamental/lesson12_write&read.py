#保存训练结果和读取数据集

import torch
import torch.nn as nn
import torch.nn.functional as F

X = torch.arange(4) #定义一个4维向量
print(X) #展示这个向量
torch.save(X, 'lesson12_pytorch_fundamental/X-file') #保存这个向量 保存在X-file文件中 保存的是tensor 放在当前目录

#读取数据集
X2 = torch.load('lesson12_pytorch_fundamental/X-file') #读取X-file文件
print(X2) #展示读取的结果

#储存一个张量然后把他们读回内存
Y = torch.zeros(4) #定义一个4维张量
print(Y) #展示这个张量
torch.save([X, Y], 'lesson12_pytorch_fundamental/XY-file') #保存这个张量
XY_list = torch.load('lesson12_pytorch_fundamental/XY-file') #读取这个张量
print(XY_list) #展示读取的结果

#将字符串映射到张量的字典
mydict = {'X': X, 'Y': Y} #定义一个字典
print(mydict) #展示这个字典
torch.save(mydict, 'lesson12_pytorch_fundamental/XY-dict') #保存这个字典
mydict2 = torch.load('lesson12_pytorch_fundamental/XY-dict') #读取这个字典
print(mydict2) #展示读取的结果

#加载和保存模型参数 
class MLP(nn.Module): #定义一个多层感知机
    def __init__(self):
        super().__init__()
        self.hidden = nn.Linear(20, 256) #定义一个线性层 输入维度为20 输出维度为256
        self.output = nn.Linear(256, 10) #定义一个线性层 输入维度为256 输出维度为10

    def forward(self, x):
        return self.output(F.relu(self.hidden(x))) #返回线性层的结果
    
net = MLP() #实例化一个多层感知机
X = torch.randn(size=(2, 20)) #定义一个2*20的张量
Y = net(X) #将张量输入到多层感知机中

#保存多层感知机的参数 保存这个字典 也可以储存在net.params文件中
torch.save(net.state_dict(), 'lesson12_pytorch_fundamental/net.pt') #保存多层感知机的参数

#读取多层感知机的参数
clone = MLP() #实例化一个多层感知机
clone.load_state_dict(torch.load('lesson12_pytorch_fundamental/net.pt')) #读取多层感知机的参数
print(clone.eval()) #评估多层感知机的参数

#判断两个多层感知机的参数是否相同
Y_clone = clone(X) #将张量输入到多层感知机中
print(Y_clone == Y) #判断两个多层感知机的参数是否相同

