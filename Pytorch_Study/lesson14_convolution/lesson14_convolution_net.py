import torch
from torch import nn
import numpy as np

#计算二维互相关运算
def corr2d(X, K):
    h, w = K.shape
    Y = torch.zeros((X.shape[0] - h + 1, X.shape[1] - w + 1)) # 输出的形状
    for i in range(Y.shape[0]): 
        for j in range(Y.shape[1]): 
            Y[i, j] = (X[i: i + h, j: j + w] * K).sum() # 逐元素相乘后求和
    return Y

#测试
X = torch.tensor([[0, 1, 2], [3, 4, 5], [6, 7, 8]]) # 输入 1个3行3列的张量
K = torch.tensor([[0, 1], [2, 3]]) # 核 2行2列的张量
Y = corr2d(X, K) # 互相关运算
print(Y)

#定义一个二维卷积层
class Conv2D(nn.Module):
    def __init__(self, kernel_size):
        super(Conv2D, self).__init__() # 继承父类
        self.weight = nn.Parameter(torch.randn(kernel_size)) # 核矩阵
        self.bias = nn.Parameter(torch.randn(1)) # 偏移

    def forward(self, x):
        return corr2d(x, self.weight) + self.bias # 互相关运算加上偏移
    
#应用 对黑白边缘进行检测 1表示黑色 0表示白色
X = torch.ones(6, 8) # 输入 1个6行8列的张量
X[:, 2:6] = 0 # 1个6行8列的张量中间4列为0
print(X)

K = torch.tensor([[1, -1]]) # 核 1行2列的张量 为了检测黑白边缘
Y = corr2d(X, K) # 互相关运算
print(Y) # 输出 1表示从白到黑 -1表示从黑到白

#卷积核只能检测垂直的边缘 因为卷积核只有1行2列 是一个水平的卷积核
#如果想检测水平的边缘 需要将卷积核旋转90度
#例子
A = torch.transpose(X, 0, 1) # 旋转90度
print(A)
Y = corr2d(A, K) # 互相关运算
print(Y) # 输出 1表示从白到黑 -1表示从黑到白 无法输出

#定义一个学习的卷积核 这是一个四维的卷积
conv2d = nn.Conv2d(1, 1, kernel_size=(1, 2), bias=False) # 输入通道数 输出通道数 核大小 偏移=False

C = torch.ones(1,1,6,8) # 输入 1个1行6列8列的张量 1个通道 1个批量 6行8列
D = torch.ones(1,1,6,7) # 核 1个1行6列7列的张量 1个通道 1个批量 6行7列
#在卷积神经网络中，输入通常比卷积核大。这是因为卷积运算的目的是在输入的各个区域上滑动卷积核，以生成输出的特征图。

#在你的代码中，输入 `C` 的形状为 `(1,1,6,8)`，而卷积核 `D` 的形状为 `(1,1,6,7)`。
#这意味着卷积核可以在输入的宽度方向上滑动2个位置（从第1列滑动到第2列，然后从第2列滑动到第3列），
#在高度方向上只能在同一位置。这样，卷积运算就能在输入的各个区域上应用卷积核，生成输出的特征图。

#如果输入和卷积核的大小相同，那么卷积运算就只能在输入的一个位置上应用卷积核，这将大大限制卷积神经网络的能力。

#学习代码 迭代10次
optimizer = torch.optim.SGD(conv2d.parameters(), lr=0.01) # 创建优化器

for i in range(10):
    Y_hat = conv2d(C) # 卷积运算
    l = (Y_hat - D) ** 2 # 损失函数
    conv2d.zero_grad() # 梯度清零
    l.sum().backward() # 反向传播 求梯度 要现将l求和变成一个标量才可以反向传播
    optimizer.step() # 更新权重
    if (i + 1) % 2 == 0:
        print('batch %d, loss %.3f' % (i + 1, l.sum())) # 输出批次 损失

#卷积公式
#输出的高度和宽度可以通过以下公式计算：
#输出高度 = 输入高度 - 卷积核高度 + 1
#输出宽度 = 输入宽度 - 卷积核宽度 + 1
#在本例中，输出高度 = 6 - 1 + 1 = 6，输出宽度 = 8 - 2 + 1 = 7。
#因此，卷积的输出形状为 (1, 6, 7)。

#存在矩阵
#1 2 3
#4 5 6
#7 8 9
        
#卷积核
#1 2
#3 4
        
#输出
#1*1+2*2+4*3+5*4 = 1+4+12+20 = 37
#2*1+3*2+5*3+6*4 = 2+6+15+24 = 47
#4*1+5*2+7*3+8*4 = 4+10+21+32 = 67
#5*1+6*2+8*3+9*4 = 5+12+24+36 = 77

#输出
#37 47
#67 77