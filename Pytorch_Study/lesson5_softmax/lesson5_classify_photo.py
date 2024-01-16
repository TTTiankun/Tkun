import torch
import torchvision
from torch.utils import data #导入data模块 用来读取数据
from torchvision import transforms #导入transforms模块 用来对图像进行预处理
from d2l import torch as d2l #导入d2l模块 用来画图

#通过ToTensor实例将图像数据从PIL类型变换成32位浮点数格式
#并除以255使得所有像素的数值均在0到1之间
trans = transforms.ToTensor() #定义一个转换器 将图像转换为张量
mnist_train = torchvision.datasets.FashionMNIST(
    root='data',train = True, transform=trans,download=True) #下载训练集
mnist_test = torchvision.datasets.FashionMNIST(
    root='data',train=False,transform=trans,download=True) #下载测试集

print(len(mnist_train),len(mnist_test) )#打印训练集和测试集的长度

print(mnist_train[0][0].shape) #打印第一个样本的形状 也就是图像的形状 1个通道 28*28的图像

#读取数据
batch_size = 256 #每次读取的样本数量
def get_dataloader_workers(): #定义一个函数 用来计算读取数据的进程数量
    """使用4个进程来读取数据"""
    return 4 #返回4个进程
train_iter = data.DataLoader(mnist_train,batch_size,shuffle=True,num_workers=get_dataloader_workers()) #训练集的数据迭代器
# mnist_train表示数据集 batch_size表示每次兑取的样本数量 shuffle=True表示打乱数据 num_workers=get_dataloader_workers()表示使用4个进程来读取数据

timer = d2l.Timer() #定义一个计时器
for X,y in train_iter: #每次从数据集中读取batch_size个样本
    continue #不做任何事情
print(f'{timer.stop():.2f} sec') #打印读取数据所用的时间

#读取数据一般要比训练模型的时间长 因为读取数据的时候需要从磁盘中读取数据 而训练模型的时候只需要从内存中读取数据

#定义一个函数 用来读取数据 封装完成
def load_data_fashion_mnist(batch_size,resize=None): #batch_size表示每次读取的样本数量 resize=None表示不对图像进行尺寸变换
    trans = [transforms.ToTensor()] #定义一个列表 用来存储转换器
    if resize:
        trans.insert(0,transforms.Resize(resize)) #如果resize不为None 则在列表的第一个位置插入一个转换器 用来对图像进行尺寸变换
    trans = transforms.Compose(trans) #将列表转换为一个转换器
    mnist_train = torchvision.datasets.FashionMNIST(
    root='data',train = True, transform=trans,download=True) #下载训练集
    mnist_test = torchvision.datasets.FashionMNIST(
    root='data',train=False,transform=trans,download=True) #下载测试集
    
    return (data.DataLoader(mnist_train,batch_size,shuffle=True,num_workers=get_dataloader_workers()), #返回训练集的数据迭代器
            data.DataLoader(mnist_test,batch_size,shuffle=False,num_workers=get_dataloader_workers())) #返回测试集的数据迭代器