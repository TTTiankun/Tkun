import torch
from torch import nn 

net = nn.Sequential(nn.Linear(4, 8), nn.ReLU(), nn.Linear(8, 1)) #定义一个线性层网络，双线性层
X = torch.rand(size=(2, 4)) #定义一个随机输入
print(net(X)) #输出结果

print(net[2].state_dict()) #输出第二层的参数
# OrderedDict([('weight', tensor([[ 0.0708,  0.1764,  0.1848,  0.1145,  0.0599, -0.2996,  0.2673, -0.2456]])), ('bias', tensor([0.2601]))])

print(type(net[2].bias)) #输出第二层的偏置类型
# <class 'torch.nn.parameter.Parameter'>

print(net[2].bias) #输出第二层的偏置

# Parameter containing:
def block1():
    return nn.Sequential(nn.Linear(4, 8), nn.ReLU(), nn.Linear(8, 4), nn.ReLU())

#block2会嵌套四个block1
def block2():
    net = nn.Sequential()
    for i in range(4):
        net.add_module(f'block{i}', block1()) #嵌套block1
    return net

rgnet = nn.Sequential(block2(), nn.Linear(4, 1)) #嵌套block2
print(rgnet(X)) #输出结果

print(rgnet) #输出网络结构

def init_normal(m):
    if type(m) == nn.Linear: #如果是线性层
        nn.init.normal_(m.weight, mean=0, std=0.01) #初始化权重
        nn.init.zeros_(m.bias) #初始化偏置

net.apply(init_normal) #对网络进行初始化 相当于网络中的每一层都通过init_normal进行初始化
print(net[0].weight.data[0], net[0].bias.data[0]) #输出第一层的权重和偏置

#自定义初始化
def my_init(m):
    if type(m) == nn.Linear:
        print("Init", *[(name, param.shape) for name, param in m.named_parameters()][0]) #输出每一层的参数
        nn.init.uniform_(m.weight, -10, 10) #初始化权重 从-10到10
        nn.init.zeros_(m.bias) #初始化偏置 为0

net.apply(my_init) #对网络进行初始化 相当于网络中的每一层都通过my_init进行初始化
print(net[0].weight.data[0], net[0].bias.data[0]) #输出第一层的权重和偏置

#手动定义初始化
net[0].weight.data[:] += 1 #手动定义权重 全部加1
net[0].weight.data[0, 0] = 42 #手动定义权重 第一行第一列为42
net[0].bias.data[:] = 0 #手动定义偏置 全部为0
print(net[0].weight.data[0], net[0].bias.data[0]) #输出第一层的权重和偏置

#参数绑定
shared = nn.Linear(8, 8) #定义一个线性层
net = nn.Sequential(nn.Linear(4, 8), nn.ReLU(), shared, nn.ReLU(), shared, nn.ReLU(), nn.Linear(8, 1)) #定义一个网络
#第二个和第三个线性层共享参数 通过shared进行绑定

net(X)#设置网络
print(net[2].weight.data[0] == net[4].weight.data[0]) #输出第二个和第三个线性层的权重是否相等
net[2].weight.data[0, 0] = 100 #修改第二个线性层的权重
print(net[2].weight.data[0] == net[4].weight.data[0]) #输出第二个和第三个线性层的权重是否相等
