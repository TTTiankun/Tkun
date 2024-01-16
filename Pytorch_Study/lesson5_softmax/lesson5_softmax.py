#softmax模型的实现
from itertools import accumulate #累加器 
import torch
from IPython import display
from d2l import torch as d2l

#读取数据
batch_size = 256 #每次读取的样本数量
train_iter, test_iter = d2l.load_data_fashion_mnist(batch_size) #读取数据

#对数据进行预处理 处理成向量
num_inputs = 784 #输入向量的长度 28*28=784
num_outputs = 10 #输出向量的维度 10个类别

#权重设置
W = torch.normal(0,0.01,size=(num_inputs,num_outputs),requires_grad=True) #大小为num_inputs*num_outputs的权重矩阵 服从均值为0 标准差为0.01的正态分布 并且要求计算梯度
B = torch.zeros(num_outputs,requires_grad=True) #维度为num_outputs的偏置向量 由0组成 并且要求计算梯度

#实现softmax运算
def softmax(X): #定义softmax函数
    X_exp = torch.exp(X) #对X中的每个元素求指数 也就是e的X次方
    partition = X_exp.sum(1,keepdim=True) #对X_exp中的每一行求和 并且保持维度 
    return X_exp/partition #返回softmax函数的值 也就是每个元素除以所在行的和 保持维度不变（广播机制）

def net(X): #定义softmax回归模型
    return softmax(torch.matmul(X.reshape((-1,W.shape[0])),W)+B) #返回softmax函数的值
    #X.reshape((-1,W.shape[0]))表示将X变换为一个2维的矩阵 第一维的长度为256(-1代表该维度大小由数据总和大小决定 在这个模型中就是步长) W.shape[0]为W的第一维的长度 也就是784
    #然后再对X和W进行矩阵乘法 然后再加上偏置向量B 然后再通过softmax函数

#定义损失函数（交叉熵） 所得到的返回值是一个向量 ！！！两个维度都大于0 表示样本0的交叉熵损失和样本1的交叉熵损失
def cross_entropy(y_hat,y): #定义交叉熵损失函数
    return -torch.log(y_hat[range(len(y_hat)),y]) #返回交叉熵损失函数的值

def accuracy(y_hat,y): #定义一个函数 用来计算准确率 ！！！找出来整个样本中预测正确的样本的数量 然后除以样本的总数 就是准确率
    if len(y_hat.shape)>1 and y_hat.shape[1]>1: #如果y_hat的维度大于1 并且y_hat的第二维的长度大于1
        y_hat = y_hat.argmax(axis=1) #将y_hat中每一行中最大元素的索引作为预测的类别
    cmp = y_hat.type(y.dtype) == y #将y_hat转换为y的数据类型 并且和y进行比较
    return float(cmp.type(y.dtype).sum()) #将cmp转换为y的数据类型 并且求和

#评估模型net在数据集data_iter上的准确率
def evaluate_accuracy(net,data_iter): #定义一个函数 用来评估模型net在数据集data_iter上的准确率
    if isinstance(net,torch.nn.Module): #如果net是torch.nn.Module的实例
        net.eval() #将net设置为评估模式
    metric = Accumulator(2) #定义一个累加器 用来存储两个量 分别是正确预测的样本数量和总样本数量
    for X,y in data_iter: #对数据集data_iter中的每个样本
        metric.add(accuracy(net(X),y),y.numel()) #计算准确率 并且将准确率和样本的总数添加到累加器中
    return metric[0]/metric[1] #返回正确预测的样本数量除以总样本数量 就是准确率

#做一个累加器的类
class Accumulator: #定义一个累加器的类
    def __init__(self,n):
        self.data = [0.0]*n
    
    def add(self,*args): #定义一个函数 用来将参数args中的每个元素和self.data中的每个元素相加
        self.data = [a+float(b) for a,b in zip(self.data,args)]
    
    def reset(self): #定义一个函数 用来将self.data中的每个元素清零
        self.data = [0.0]*len(self.data)
    
    def __getitem__(self,idx): #定义一个函数 用来返回self.data中索引为idx的元素
        return self.data[idx]

#训练的过程
def train_epoch(net,train_iter,loss,updater): #定义一个函数 用来训练模型
    if isinstance(net,torch.nn.Module): #如果net是torch.nn.Module的实例
        net.train() #将net设置为训练模式
    metric = Accumulator(3) #定义一个累加器 用来存储三个量 分别是训练损失的总和 样本数量和准确率
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

#训练函数
def train(net,train_iter,test_iter,loss,num_epochs,updater): #定义一个函数 用来训练模型
    for epoch in range(num_epochs):
        for epoch_S in range(1): #对于每个迭代周期
            train_metrics = train_epoch(net,train_iter,loss,updater) #训练模型
            test_acc = evaluate_accuracy(net,test_iter) #评估模型
        train_loss,train_acc = train_metrics #将训练损失的平均值和准确率分别赋值给train_loss和train_acc
        print(f'epoch {epoch+1},loss {train_loss:.3f},train acc {train_acc:.3f},test acc {test_acc:.3f}')
        #打印迭代周期的数量 训练损失的平均值 训练准确率 测试准确率

#利用小批量随机梯度下降来优化模型的损失函数
lr = 0.1 #学习率
def updater(batch_size): #定义一个函数 用来更新参数
    return d2l.sgd([W,B],lr,batch_size) #返回小批量随机梯度下降所需要的参数

#训练
#超参数
num_epochs = 10 #迭代周期的数量
train(net,train_iter,test_iter,cross_entropy,num_epochs,updater) #训练模型
