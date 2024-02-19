#数据增强
#增加一个已经存在的数据集，增加数据集的多样性
#特点：在线生成且随机
#常用的数据增强方法：
#1.翻转
#2.旋转
#3.缩放
#4.裁剪
#5.平移
#6.亮度调整
#7.对比度调整
#8.噪声
#9.模糊
#10.颜色变换
#11.通道变换
#12.仿射变换
#13.透视变换

#展示 烂了烂了 会读代码就行！
import torch
import torchvision
from torch import nn
from d2l import torch as d2l

d2l.set_figsize()
img = d2l.Image.open('lesson24_data_augmentation/test.png')
d2l.plt.imshow(img)