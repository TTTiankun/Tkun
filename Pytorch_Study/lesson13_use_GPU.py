#显示计算设备
import torch
from torch import nn

print(torch.cpu.is_available()) #判断是否有CPU

print(torch.cuda.is_available()) #判断是否有GPU
print(torch.cuda.device_count()) #显示GPU数量
print(torch.cuda.current_device()) #显示当前GPU的索引号
print(torch.cuda.get_device_name(0)) #显示GPU_0的名字

#如果存在，返回GPU；否则返回CPU
def try_gpu(i=0): #定义一个函数
    if torch.cuda.device_count() >= i + 1: #判断是否有GPU
        return torch.device(f'cuda:{i}') #返回GPU
    return torch.device('cpu') #返回CPU

print(try_gpu()) #展示GPU

#返回所有的GPU
def try_all_gpus(): #定义一个函数
    devices = [torch.device(f'cuda:{i}') for i in range(torch.cuda.device_count())] #返回所有的GPU
    return devices if devices else [torch.device('cpu')] #返回所有的GPU

print(try_all_gpus()) #展示所有的GPU

#查看张量所在的设备
X = torch.tensor([1, 2, 3]) #定义一个张量
print(X) #查看张量所在的设备

#存储在GPU上
Z = torch.zeros(2, 3, device=try_gpu()) #定义一个张量 可以通过device指定存储设备
print(Z) #展示张量

#要在两个设备之间移动数据，我们只需要调用张量的cuda或to函数 例如：X.cuda()或X.to(device)
#要在同一设备上才能发生计算
Y = X.to('cuda') + Z #将X移动到GPU上，然后进行加法运算
print(Y) #展示张量

#将网络放在GPU上
net = nn.Sequential(nn.Linear(3, 1)) #定义一个网络
net = net.to(device=try_gpu()) #将网络放在GPU上
net(X)
print(net(X)) #展示网络

#显示全连接层的设备
print(net[0].weight.data.device)