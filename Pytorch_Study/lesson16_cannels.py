#图像的通道
#常见的RGB通道为三通道

#多通道输入 每一个通道都有一个卷积核，结果是每个通道的卷积结果相加
#每个输出通道可以识别特定的模式

#1*1卷积层
#1*1卷积层的主要作用是改变通道数，不改变高和宽 
#不识别空间模式，只进行通道融合

#实现2d多输入通道的互相关运算
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

#多输入通道的互相关运算
def corr2d_multi_in(X, K):
    #对X和K的第0维（通道维）遍历，然后将它们的结果相加
    return sum(corr2d(x, k) for x, k in zip(X, K)) # 逐个相加 逐个相乘后求和 zip函数将X和K的第0维打包成元组

#测试
X = torch.tensor([[[0, 1, 2], [3, 4, 5], [6, 7, 8]], [[1, 2, 3], [4, 5, 6], [7, 8, 9]]]) # 输入 2个3行3列的张量
K = torch.tensor([[[0, 1], [2, 3]], [[1, 2], [3, 4]]]) # 核 2个2行2列的张量
print(corr2d_multi_in(X, K)) # 输出

#多通道输入的互相关运算
def corr2d_multi_in_out(X, K):
    #对K的第0维遍历，每次同输入X做互相关运算。所有结果使用stack函数合并在一起
    return torch.stack([corr2d_multi_in(X, k) for k in K], 0) # 逐个相加 逐个相乘后求和 逐个相加
    #stack函数将多个张量合并在一起

#测试
K = torch.stack([K, K + 1, K + 2], 0) # 核 3个2行2列的张量 逐个相加
print(K) # 输出
print(K.shape) # 输出
print(corr2d_multi_in_out(X, K)) # 输出