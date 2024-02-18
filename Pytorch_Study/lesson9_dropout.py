#丢弃法
#一个好的模型需要对数据输入的扰动有足够的鲁棒性，而不是对数据过于敏感
#方法：1.丢弃法（dropout）：在训练模型时，丢弃法通过随机删除神经网络的一些单元（神经元）来实现
#      2.正则化：通过惩罚模型参数的大小来降低模型的复杂度
#      3.数据增强：使用有噪音的数据

#无偏差的加入噪音
#我们希望加了噪音的数据集的期望和原来的数据集是相等的

#丢弃法扰动
#丢弃法的主要思想是通过在神经网络中引入噪声，来改变网络的学习行为
#通常作用在隐藏的全连接层的输出上
#丢弃法的实现：在每次迭代中，随机将一些元素置为0
#丢弃法的工作原理：1.丢弃法只在训练模型时使用
#                2.当使用丢弃法时，批量大小需要设置的大一些
#                3.丢弃法的实现：将上一层输出乘以一个丢弃向量，丢弃向量中的元素取值为0或1，0表示丢弃，1表示保留
#                4.丢弃的概率是控制模型复杂度的超参数

#正则项只在训练中使用：他们影响模型参数的更新
#在推理过程中，丢弃发直接返回输入

#实现
import torch
from torch import nn
from d2l import torch as d2l

#定义丢弃法
def dropout_layer(x,dropout):
    assert 0 <= dropout <= 1 #断言dropout的值在0到1之间
    if dropout==1: #如果dropout=1
        return torch.zeros_like(x) #返回一个和x形状相同的全0张量
    if dropout==0: #如果dropout=0
        return x
    mask=(torch.rand(x.shape)<1-dropout).float() #创建一个和x形状相同的张量，其中元素值为0或1，概率为1-dropout
    return mask*x/(1-dropout) #返回一个和x形状相同的张量，其中元素值为0或x/(1-dropout)

#测试丢弃法
x=torch.arange(16,dtype=torch.float32).reshape((2,8)) #创建一个张量
print(x) #打印张量
print(dropout_layer(x,0)) #测试丢弃法
print(dropout_layer(x,0.5)) #测试丢弃法
print(dropout_layer(x,1)) #测试丢弃法

#定义具有两个隐藏层的多层感知机 每一个隐藏层包含256个单元
#定义模型参数
num_inputs,num_outputs,num_hiddens1,num_hiddens2=784,10,256,256 #输入数 输出数 第一个隐藏层的神经元个数 第二个隐藏层的神经元个数

class Net(nn.Module):
    def __init__(self,num_inputs,num_outputs,num_hiddens1,num_hiddens2,is_training=True):
        super(Net,self).__init__() #uper(Net,self)表示调用父类的构造函数
        self.num_inputs=num_inputs #输入数
        self.training=is_training #是否训练
        self.lin1=nn.Linear(num_inputs,num_hiddens1) #第一个全连接层
        self.lin2=nn.Linear(num_hiddens1,num_hiddens2) #第二个全连接层
        self.lin3=nn.Linear(num_hiddens2,num_outputs) #输出层
        self.relu=nn.ReLU() #激活函数 使用ReLU
    def forward(self,X):
        H1=self.relu(self.lin1(X.reshape((-1,self.num_inputs)))) #第一个全连接层
        if self.training==True: #如果是训练
            H1=dropout_layer(H1,0) #第一个全连接层的输出使用丢弃法
        H2=self.relu(self.lin2(H1)) #第二个全连接层
        if self.training==True: #如果是训练
            H2=dropout_layer(H2,0) #第二个全连接层的输出使用丢弃法
        out=self.lin3(H2) #第三个全连接层 输出层
        return out
    
net = Net(num_inputs,num_outputs,num_hiddens1,num_hiddens2) #创建一个网络

#训练和测试模型
#设置超参数
num_epochs,lr,batch_size=10,0.5,256 #迭代次数 学习率 批量大小
loss=nn.CrossEntropyLoss() #损失函数 使用交叉熵损失函数
train_iter,test_iter=d2l.load_data_fashion_mnist(batch_size) #训练集迭代器 测试集迭代器
trainer = torch.optim.SGD(net.parameters(),lr=lr) #优化器 使用随机梯度下降优化

def train(net,train_iter,test_iter,loss,num_epochs,trainer):
    for epoch in range(num_epochs): #迭代
        net.train() #训练模式
        train_l,train_acc,n=0.0,0.0,0 #训练损失 训练准确率 训练样本数
        with torch.enable_grad():
            for X,y in train_iter: #训练集迭代器
                y_hat=net(X) #预测值
                l=loss(y_hat,y) #损失函数
                trainer.zero_grad() #梯度清零
                l.backward() #反向传播
                trainer.step() #更新参数
                train_l+=l.item() #累加损失函数
            with torch.no_grad():
                for X,y in test_iter:
                    y_hat=net(X) #预测值
                    train_acc+=(y_hat.argmax(dim=1)==y).float().sum().item() #累加准确率 y_hat.argmax(dim=1)==y表示预测值和真实值相等
                    n+=y.shape[0] #累加样本数
                    print(f'epoch {epoch+1}, loss {train_l/n}, train_acc {train_acc/n}')

train(net,train_iter,test_iter,loss,num_epochs,trainer) #训练