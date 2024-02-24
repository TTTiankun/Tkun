#转置卷积
# 转置卷积，也被称为反卷积或者部分人称之为反向卷积，主要用于扩大特征图的尺寸。
# 在深度学习中，它常常被用于卷积神经网络的上采样部分，例如在生成对抗网络（GANs）和全卷积网络（FCNs）中。
# 这种操作可以帮助我们从低分辨率的特征图恢复到高分辨率的图像，
# 从而实现图像的生成或者分割等任务。

#实现
import torch
from torch import nn
from d2l import torch as d2l

#定义一个转置卷积层(基础实现)
def trans_conv(X,K):
    h, w = K.shape
    Y = torch.zeros((X.shape[0] + h - 1, X.shape[1] + w - 1)) #定义一个全0的张量 
    for i in range(X.shape[0]): #遍历高
        for j in range(X.shape[1]): #遍历宽
            Y[i:i + h, j:j + w] += X[i, j] * K #将X的元素与K的元素相乘后加到Y上
    return Y

X = torch.tensor([[0.0, 1.0], [2.0, 3.0]])
K = torch.tensor([[0.0, 1.0], [2.0,3.0]])
print(trans_conv(X, K))

#定义一个转置卷积层(高级实现)
def trans_conv_plus():
    X = torch.tensor([[0.0, 1.0], [2.0, 3.0]])
    K = torch.tensor([[0.0, 1.0], [2.0,3.0]])
    X = X.reshape(1, 1, 2, 2)
    K = K.reshape(1, 1, 2, 2)
    tconv = nn.ConvTranspose2d(1, 1, kernel_size=2, bias=False) #定义一个转置卷积层 1个输入通道数 1个输出通道数 卷积核大小是2*2 没有偏差 
    tconv.weight.data = K
    print(tconv(X))

#2*2的输入经过2*2的转置卷积层输出是3*3的张量
trans_conv_plus()

#填充 步幅 多通道
X = X.reshape(1, 1, 2, 2)
K = K.reshape(1, 1, 2, 2)
#步幅决定了输出的高和宽
tconv = nn.ConvTranspose2d(1, 1, kernel_size=2, padding=1, stride=3, bias=False) #定义一个转置卷积层 1个输入通道数 1个输出通道数 卷积核大小是2*2 填充是1 步幅是3 没有偏差
tconv.weight.data = K
print(tconv(X))

#与矩阵变换的联系
A = torch.arange(9.0).reshape(3, 3) #定义一个3*3的张量
K = torch.tensor([[0.0, 1.0], [2.0, 3.0]]) #定义一个2*2的张量
Y = d2l.corr2d(A, K) #定义一个二维相关运算
print(Y)

#转置卷积类似于矩阵变换的转置
#转置卷积的核数组K与二维相关运算的核数组K的转置进行了对应
def kernel2matrix(K):
    k, W = torch.zeros(5), torch.zeros((4, 9))
    k[:2], k[3:5] = K[0, :], K[1, :]
    W[0, :5], W[1, 1:6], W[2, 3:8], W[3, 4:] = k, k, k, k
    return W

W = kernel2matrix(K)
print(W) #输出的矩阵



