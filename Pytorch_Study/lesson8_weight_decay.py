#权重衰退
#通过限制参数值的选择范围来控制模型容量

#运用均值范数
#硬性限制
#柔性限制

#参数更新法则
#计算梯度
#更新参数
#重复以上两个步骤

#这个时候权重可能会越来越小 因为在更新的时候会先让权重减去一个值
#正则化：通过在损失函数中加入刻画模型复杂度的指标，利用给w加权值，使得学出来的模型参数值较小，从而使得整个模型更加简单，这种方式叫做正则化
#权重衰退是最广泛的正则化技术之一

import torch
from torch import nn
from d2l import torch as d2l

#生成一个人工数据集
n_train,n_test,num_inputs=20,100,200 #训练集样本数 测试集样本数 特征数
true_w,true_b=torch.ones(num_inputs,1)*0.01,0.05 #真实权重和偏差 
#创建一个张量，将其中元素都设为1
#将张量乘以标量0.01，然后将偏差设为0.05

#生成数据集
train_data=d2l.synthetic_data(true_w,true_b,n_train) #训练集
test_data=d2l.synthetic_data(true_w,true_b,n_test) #测试集

train_iter=d2l.load_array(train_data,batch_size=1) #训练集迭代器
test_iter=d2l.load_array(test_data,batch_size=1,is_train=False) #测试集迭代器

#初始化模型参数
def init_params():
    w=torch.normal(0,1,size=(num_inputs,1),requires_grad=True) #初始化权重
    b=torch.zeros(1,requires_grad=True) #初始化偏差
    return [w,b] #返回一个列表 里面包含了权重和偏差

#定义L2范数惩罚项
def l2_penalty(w):
    return torch.sum(w.pow(2))/2 #返回L2范数惩罚项 公式：w的平方和除以2

#权重衰减的本质就是在每一次更新参数的时候都让权重减去一个值 ！！！这个值通过L2范数惩罚项*一个权重衰减超参数得到
#训练
def train(lambd):
    w,b=init_params() #初始化权重和偏差
    net,loss=lambda X:d2l.linreg(X,w,b),d2l.squared_loss #定义网络和损失函数
    num_epochs,lr=100,0.003 #迭代次数 学习率
    for epoch in range(num_epochs): #迭代
        for X,y in train_iter: #训练集迭代器
            with torch.enable_grad(): #计算梯度
                l=loss(net(X),y)+lambd*l2_penalty(w) # 损失函数+L2范数惩罚项 
            l.sum().backward() #反向传播
            d2l.sgd([w,b],lr,1) #更新参数 1是批量大小 用于计算梯度的和 优化算法是随机梯度下降
        if(epoch+1)%5==0: #每5次迭代
            with torch.no_grad():
                print(f'epoch {epoch+5}, loss_train {d2l.evaluate_loss(net,train_iter,loss)}, loss_test{d2l.evaluate_loss(net,test_iter,loss)}') #打印迭代次数和损失函数
    print("w的L2范数是：",torch.norm(w).item()) #打印w的L2范数 用item()函数将张量转换为标量

train(lambd=3) #训练
#当L2范数惩罚项的权重设为3时，w的L2范数比不使用权重衰减时的w的L2范数要小很多
#这是因为在使用权重衰减时，我们令损失函数不仅最小化训练误差，而且最小化权重的L2范数
#如果训练时不使用L2范数，那么肯呢个会出现过你和的情况

#反向传播（Backpropagation）是一种在神经网络中计算梯度的有效方法。它是深度学习中最常用的训练算法之一。

#反向传播的基本思想是通过链式法则（Chain Rule）将输出层的误差反向传播到隐藏层和输入层，从而计算出每个参数对损失函数的偏导数（即梯度）。然后，我们可以使用这些梯度来更新网络的参数，以最小化损失函数。

#简单实现 权重衰减

def train_breif(lambd):
    net = nn.Sequential(nn.Linear(num_inputs,1)) #定义网络 一个线性层
    for param in net.parameters(): #遍历网络中的参数
        param.data.normal_() #将参数初始化为正态分布
    loss = nn.MSELoss() #定义损失函数 使用均方损失
    num_epochs,lr = 100,0.003 #迭代次数 学习率 设置超参数
    trainer = torch.optim.SGD([{"params":net[0].weight,"weight_decay":lambd},
                               {"params":net[0].bias}],lr=lr) #优化器 
    #net[0].weight表示网络中的第一个层的权重 net[0].bias表示网络中的第一个层的偏差
    #weight_decay表示权重衰减的超参数 
    #lr表示学习率
    #意思是创建了一个SGD优化器 用来更新网络中的第一个层的权重和偏差 其中权重参数使用了L2正则化

    for epoch in range(num_epochs): #迭代
        for X,y in train_iter:
            with torch.enable_grad():
                trainer.zero_grad()
                l = loss(net(X),y)
            l.backward()
            trainer.step() #更新参数
        if(epoch+1)%5==0:
            with torch.no_grad():
                print(f'epoch {epoch+5}, loss_train {d2l.evaluate_loss(net,train_iter,loss)}, loss_test{d2l.evaluate_loss(net,test_iter,loss)}')
    print("w的L2范数是：",torch.norm(net[0].weight).item())#打印w的L2范数 用item()函数将张量转换为标量
train_breif(3) #训练