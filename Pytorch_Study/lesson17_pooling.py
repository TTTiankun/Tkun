#最大池化层
#返回滑动窗口中的最大值

#池化层与卷积层类似，都具有滑动窗口的特性，但是池化层不需要卷积层的参数，只需要滑动窗口中的最大值或者平均值即可。
#都有填充和步幅

#最大池化层：表示每个窗口最强的模式信号
#平均池化层：表示每个窗口的平均信号

#池化层可以进行边缘检测，可以检测图像的边缘特征

#实现最大池化层

import torch
from torch import nn
import numpy as np

def pool2d(X, pool_size, mode):
    p_h, p_w = pool_size # 池化层的高度和宽度
    Y = torch.zeros(X.shape[0] - p_h + 1, X.shape[1] - p_w + 1) # 输出的形状 逐个相加 逐个相乘后求和
    for i in range(Y.shape[0]): 
        for j in range(Y.shape[1]): 
            if mode == 'max': # 最大池化层 
                Y[i, j] = X[i: i + p_h, j: j + p_w].max() # 最大值 
                
# - `X[i: i + p_h, j: j + p_w]` 是从输入张量 `X` 中选取一个子区域。这个子区域的位置由 `i` 和 `j` 决定，大小由 `p_h` 和 `p_w` 决定。这个子区域就是池化窗口。

# - `.max()` 是在这个池化窗口上执行最大池化操作。它会返回池化窗口中的最大值。就是找到这个窗口覆盖数字的最大值

# - `Y[i, j] =` 是将这个最大值赋值给输出张量 `Y` 的对应位置。

            elif mode == 'avg': # 平均池化层
                Y[i, j] = X[i: i + p_h, j: j + p_w].mean() # 平均值
    return Y

#测试
X = torch.tensor([[0, 1, 2], [3, 4, 5], [6, 7, 8]],dtype=torch.float) # 输入 3行3列的张量 注意：求和mean时需要转换为浮点数
print(pool2d(X, (2, 2),'max')) # 输出
print(pool2d(X, (2, 2), 'avg')) # 输出

#池化层的填充和步幅
Y = torch.arange(16, dtype=torch.float).view(1, 1, 4, 4) # 输入 1个1行4列4列的张量
print(Y)

#使用深度学习框架中内置的二维最大池化层
pool2d = nn.MaxPool2d(3) # 最大池化层 3*3的池化窗口
print(pool2d(Y)) # 输出

#填充和步幅
pool2d = nn.MaxPool2d(3, padding=1, stride=2) # 最大池化层 3*3的池化窗口 填充 步幅
print(pool2d(Y)) # 输出

#池化层的输出通道数和输入通道数相同
#池化层的输出通道数和输入通道数相同，因为池化层的作用是对输入数据的每个通道进行池化，而不是改变通道数。
#多输入通道的池化层
X = torch.cat((Y, Y + 1), 1) # 输入 1个1行4列4列的张量 1个1行4列4列的张量
print(X)

pool2d = nn.MaxPool2d(3, padding=1, stride=2) # 最大池化层 3*3的池化窗口 填充 步幅
print(pool2d(X)) # 输出
#输出通道数为输入通道数的一半