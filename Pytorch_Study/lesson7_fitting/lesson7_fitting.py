#看一下模型选择,欠拟合和过拟合的现象
import numpy as np #导入numpy库 用于科学计算
import math
import torch
from torch import nn
from d2l import torch as d2l

max_degree = 20 #最大的多项式次数
n_train, n_test = 100, 100 #训练和测试数据集大小
true_w = np.zeros(max_degree) #初始化权重 zeros函数返回一个给定形状和类型的用0填充的数组
true_w[0:4] = np.array([5, 1.2, -3.4, 5.6]) #前四个权重赋值

#使用多项式来生成数据集
features = np.random.normal(size=(n_train + n_test, 1)) #生成服从正态分布的随机数
np.random.shuffle(features) #打乱顺序
poly_features = np.power(features, np.arange(max_degree).reshape(1, -1)) #生成多项式 特征的每一列都是前一列的max_degree次方
                                                                         #多项式的次数从0到max_degree-1 共有max_degree项
for i in range(max_degree): #归一化
    poly_features[:, i] /= math.gamma(i + 1) #gamma函数
#生成标签
labels = np.dot(poly_features, true_w) #矩阵乘法 生成标签 
labels += np.random.normal(scale=0.1, size=labels.shape) #加上噪声 服从正态分布

true_w, features, poly_features, labels = [torch.tensor(x, dtype=torch.float32)
                                             for x in [true_w, features, poly_features, labels]] #转换成tensor 
#打印一下
print(features[:2], poly_features[:2, :], labels[:2]) #打印前两个样本的特征 前两个样本的多项式 前两个样本的标签
#标签就是需要预测的目标变量 比如人名对应的性别
#特征就是用来预测目标变量的变量 比如身高体重等
#多项式是通过对特征进行变换得到的 方便后面引入非线性关系 更好的拟合数据
#比如身高体重的平方 体重的平方等

def accuracy(y_hat,y): #定义一个函数 用来计算准确率 ！！！找出来整个样本中预测正确的样本的数量 然后除以样本的总数 就是准确率
    if len(y_hat.shape)>1 and y_hat.shape[1]>1: #如果y_hat的维度大于1 并且y_hat的第二维的长度大于1
        y_hat = y_hat.argmax(axis=1) #将y_hat中每一行中最大元素的索引作为预测的类别
    cmp = y_hat.type(y.dtype) == y #将y_hat转换为y的数据类型 并且和y进行比较
    return float(cmp.type(y.dtype).sum()) #将cmp转换为y的数据类型 并且求和

def evaluate_loss(net, data_iter, loss): #计算损失
 metric = d2l.Accumulator(2) #计算损失和样本数量
 for X, y in data_iter:
     out = net(X) #计算预测值
     y = y.reshape(out.shape) #将y的形状变成out的形状
     l = loss(out, y) #计算损失
     metric.add(l.sum(), l.numel())
 return metric[0] / metric[1] #返回损失

def train_epoch(net,train_iter,loss,updater): #定义一个函数 用来训练模型
    if isinstance(net,torch.nn.Module): #如果net是torch.nn.Module的实例
        net.train() #将net设置为训练模式
    metric = d2l.Accumulator(3) #定义一个累加器 用来存储三个量 分别是训练损失的总和 样本数量和准确率
    for X,y in train_iter: #对数据集train_iter中的每个样本
        y_hat = net(X) #计算预测值
        l = loss(y_hat,y) #计算损失值
        if isinstance(updater,torch.optim.Optimizer): #如果updater是torch.optim.Optimizer的实例
            updater.zero_grad() #梯度清零
            l.backward() #反向传播
            updater.step() #更新参数
            metric.add(float(l)*len(y),accuracy(y_hat,y),y.size().numel()) #计算损失值的总和 准确率和样本数量 并且添加到累加器中
        else: #如果updater不是torch.optim.Optimizer的实例
            l.sum().backward() #计算损失值的和的梯度
            updater(X.shape[0]) #更新参数
            metric.add(float(l.sum()),accuracy(y_hat,y),y.numel()) #计算损失值的总和 准确率和样本数量 并且添加到累加器中
    return metric[0]/metric[2],metric[1]/metric[2] #返回训练损失的平均值和准确率


#定义训练函数
def train(train_features,test_features,train_labels,test_labels,num_epochs=400):
    loss = nn.MSELoss() #损失函数
    input_shape = train_features.shape[-1] #输入形状
    #不设置偏置bias=True
    net = nn.Sequential(nn.Linear(input_shape,1,bias=False)) #线性回归模型
    batch_size = min(10,train_labels.shape[0]) #批量大小
    train_iter = d2l.load_array((train_features,train_labels.reshape(-1,1)),batch_size) #训练数据集
    test_iter = d2l.load_array((test_features,test_labels.reshape(-1,1)),batch_size,is_train=False) #测试数据集
    trainer = torch.optim.SGD(net.parameters(),lr=0.01) #优化器 使用随机梯度下降
    animator = d2l.Animator(xlabel='epoch',ylabel='loss',yscale='log',xlim=[1,num_epochs],ylim=[1e-3,1e2],legend=['train','test']) #动画
    for epoch in range(num_epochs): #训练
        train_epoch(net,train_iter,loss,trainer)
        print('epoch:',epoch+1,'train_loss:',evaluate_loss(net,train_iter,loss),
              'test_loss:',evaluate_loss(net,test_iter,loss)) #打印训练损失
    print('weight:',net[0].weight.data.numpy()) #打印权重


print('正常拟合')
#三阶多项式函数拟合（正常）
train(poly_features[:n_train, :4], poly_features[n_train:, :4],
        labels[:n_train], labels[n_train:]) 
#输入数据：训练数据集的前4个特征和测试数据集的前4个特征 数据和模型是匹配的 都是线性的
print('欠拟合')
#线性函数拟合 样本不足（欠拟合）
train(poly_features[:n_train, :2], poly_features[n_train:, :2],
        labels[:n_train], labels[n_train:])
#输入数据：训练数据集的前2个特征和测试数据集的前2个特征 数据和模型不匹配 模型是线性的 但是数据是非线性的
print('过拟合')
#训练样本不足（过拟合）
train(poly_features[:n_train, :], poly_features[n_train:, :],
        labels[:n_train], labels[n_train:])
#输入数据：训练数据集的所有特征和测试数据集的所有特征 数据和模型是匹配的 都是非线性的 但是训练数据集太少了 太关注噪声了