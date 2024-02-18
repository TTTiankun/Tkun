#构造一个没有任何参数的自定义层
import torch
import torch.nn.functional as F
from torch import nn

class CenteredLayer(nn.Module):
    def __init__(self, **kwargs):
        super(CenteredLayer, self).__init__(**kwargs) #继承父类的属性
    
    def forward(self, x):
        return x - x.mean() #返回输入减去均值的结果

layer = CenteredLayer() #定义一个层
print(layer(torch.tensor([1, 2, 3, 4, 5], dtype=torch.float))) #设置输入
#意思是输入这个层，输入值减去均值之后返回

#将这个层作为一个子模块嵌套到更复杂的模型中
net = nn.Sequential(nn.Linear(8, 128), CenteredLayer()) #定义一个网络 有两层 第一层是线性层 第二层是自定义层
y = net(torch.rand(4, 8)) #设置输入
print(y.mean()) #输出均值

#参数绑定
class MyLinear(nn.Module):
    def __init__(self, in_units, units, **kwargs):
        super(MyLinear, self).__init__(**kwargs) #继承父类的属性
        self.weight = nn.Parameter(torch.randn(in_units, units)) #定义权重
        self.bias = nn.Parameter(torch.randn(units)) #定义偏置 
    def forward(self, x):
        linear = torch.matmul(x, self.weight.data) + self.bias.data #计算线性层 乘以权重加上偏置
        return F.relu(linear) #返回线性层的relu
    
dense = MyLinear(5, 3) #定义一个线性层 输入一个5维向量 输出一个3维向量
print(dense.weight) #输出权重

tensor1 = torch.rand(2, 5) #输入一个2*5的矩阵
print(tensor1) 
print(dense(tensor1)) #设置输入 

#使用自定义层构建模型
net = nn.Sequential(MyLinear(5, 8), MyLinear(8, 1)) #定义一个网络 有两层 第一层是线性层 第二层是线性层
print(net(tensor1)) #设置输入并展示输出

