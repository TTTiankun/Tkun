#填充
#在输入的四周加入一些额外的行和列，这样可以使得输入的图像更大，从而可以更好地进行卷积操作
#可以通过这种方式从而使输出图像与输入图像大小相同甚至更大！

#步幅
#步幅是指卷积核在图像上滑动的步长，步幅越大，输出图像的尺寸就会越小
#如果输入的高度和宽度不可以被步幅整除，那么就需要在输入的四周进行填充，或者进行往下取整操作

import torch
from torch import nn

#将二维互相关运算的计算过程封装在corr2d函数中
def comp_conv2d(conv2d, X):
    # (1, 1)代表批量大小和通道数 均为1
    X = X.view((1, 1) + X.shape) 
    Y = conv2d(X) 
    print(X.shape) #输出输入的形状
    return Y.view(Y.shape[2:]) 

#填充
#填充的行数和列数分别为1
conv2d = nn.Conv2d(1, 1, kernel_size=3, padding=1) # 输入通道数 输出通道数 核大小 填充 将输入的高度和宽度两侧分别填充1
X = torch.rand(8, 8) # 8行8列的张量
print(comp_conv2d(conv2d, X).shape) # 输出

#填充不同的高度和宽度
conv2d = nn.Conv2d(1, 1, kernel_size=(5, 3), padding=(2, 1)) # 输入通道数 输出通道数 核大小 填充 将输入的高度和宽度两侧分别填充2和1
print(comp_conv2d(conv2d, X).shape) # 输出 输出和输入的大小应该是一样的

#步幅
#步幅为2
conv2d = nn.Conv2d(1, 1, kernel_size=3, padding=1, stride=2) # 输入通道数 输出通道数 核大小 填充 步幅 将输入的高度和宽度两侧分别填充1 步幅为2
print(comp_conv2d(conv2d, X).shape) # 输出

#不同的高度和宽度的步幅
conv2d = nn.Conv2d(1, 1, kernel_size=(3, 5), padding=(0, 1), stride=(3, 4)) # 输入通道数 输出通道数 核大小 填充 步幅 将输入的高度和宽度两侧分别填充0和1 步幅为3和4
print(comp_conv2d(conv2d, X).shape) # 输出
print(comp_conv2d(conv2d, X)) # 输出