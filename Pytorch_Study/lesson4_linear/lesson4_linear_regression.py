#线性回归
#线性回归是一个基本的机器学习算法
#线性回归的模型是一个线性模型 也就是说模型的预测值是输入特征的线性函数

#线性回归的基本要素
#1.模型
#2.损失函数
#3.优化算法

#权重的本质就是机器学习中的对于特征的参数，通过参数根据特征得到预测结果
#例如：y = w1*x1 + w2*x2 + w3*x3 + b 其中w1,w2,w3就是权重

#线性回归的简单实现
import random
import torch
from d2l import torch as d2l

#创造数据集

def synthetic_data(w,b,num_examples):
    """生成y = Xw + b + 噪声"""
    X = torch.normal(0,1,(num_examples,len(w))) # 生成一个从0到1的一维张量 并且改变数据类型为float32 折叠成num_examples行len(w)列的张量
    y = torch.matmul(X,w) + b # 矩阵乘法
    y += torch.normal(0,0.01,y.shape) # 加上噪声 均值为0 方差为0.01
    return X,y.reshape((-1,1)) # 返回X和y 且y的形状为(-1,1) -1表示自动计算 1表示1列

true_w = torch.tensor([2,-3.4]) #W的真实值
true_b = 4.2 #B的真实值
features,labels = synthetic_data(true_w,true_b,1000) #生成1000个样本 且每个样本有2个特征 2个特征的真实值为true_w 且每个样本的标签为true_b + 噪声
print('features:',features[0],'\nlabel:',labels[0]) #打印第一个样本

#这个是在jupyter notebook中运行的 这个地方没办法展示
# d2l.set_figsize() #设置图像大小
# d2l.plt.scatter(features[:,(1)].detach().numpy(),labels.detach().numpy(),1) #画散点图

def data_iter(batch_size,features,labels):
    """读取小批量数据"""
    num_examples = len(features) #样本数量
    indices = list(range(num_examples)) #生成一个从0到num_examples-1的列表 batch_size表示每次读取的样本数量
    random.shuffle(indices) #打乱数据
    for i in range(0,num_examples,batch_size):
        batch_indices = torch.tensor(indices[i:min(i+batch_size,num_examples)]) #生成一个从i到i+batch_size的张量 但是不超过num_examples 也就是说最后一个batch_size可能不足batch_size
        yield features[batch_indices],labels[batch_indices] #返回一个生成器

#通过这种方式模拟读取数据的过程
batch_size_test = 10 #每次读取的样本数量为10
for X,y in data_iter(batch_size_test,features,labels): #每次从数据集中读取batch_size个样本
    print(X,'\n',y)
    break

#定义模型
def linreg(X,w,b):
    """线性回归模型""" #Xw + b
    return torch.matmul(X,w) + b #矩阵乘法 Xw + b

#定义损失函数
#损失指的是预测值和真实值之间的差距 用来衡量模型的好坏 或者模型的训练进度
def squared_loss(y_hat,y):
    """均方损失""" # (y_hat - y)^2 / 2
    return (y_hat - y.reshape(y_hat.shape))**2 / 2 #返回均方损失 也就是(y_hat - y)^2 / 2 也就是平方损失

#定义优化算法
def sgd(params,lr,batch_size):
    """小批量随机梯度下降"""
    with torch.no_grad(): #不计算梯度 也就是不会记录梯度
        for param in params: #遍历参数 也就是w和b
            param -= lr * param.grad / batch_size #更新参数  lr表示学习率 也就是步长
            param.grad.zero_() #梯度清零 这样子下一次计算梯度的时候就不会和上一次的梯度相关了

print('--------------------------------------------------------------------')

#训练模型
#定义超参数
lr = 0.03 #学习率
num_epochs = 100 #迭代次数
net = linreg #模型
loss = squared_loss #损失函数
batch_size = 10 #每次读取的样本数量
#初始化模型参数
w = torch.normal(0,0.01,size=(2,1),requires_grad=True) #初始化w 从0到0.01的正态分布 2行1列 并且需要计算梯度 
b = torch.zeros(1,requires_grad=True) #初始化b 1行1列 并且需要计算梯度


for epoch in range(num_epochs): #迭代num_epoch3次
    for X,y in data_iter(batch_size,features,labels): #每次从数据集中读取batch_size个样本
        l = loss(net(X,w,b),y) #计算损失 把X，w，b传入模型net中计算预测值 然后和y比较计算损失
        
        #因为l是一个长度为batch_size的向量 所以我们对l取和 然后再反向传播
        l.sum().backward() #计算梯度 也就是对l求导 
        sgd([w,b],lr,batch_size) #更新参数
    with torch.no_grad(): #不计算梯度 评价一下训练的进度
        train_l = loss(net(features,w,b),labels) #计算训练集的损失 
        print(f'epoch {epoch + 1},loss {float(train_l.mean()):f}') #打印损失 对训练集的损失取均值

print('--------------------------------------------------------------------')
print(f'w的估计值：{w}\nb的估计值：{b}')
print(f'w的估计误差：{true_w - w.reshape(true_w.shape)}')
print(f'b的估计误差：{true_b - b}')

