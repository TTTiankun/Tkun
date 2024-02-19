#LeNet的实现

import torch
from torch import nn
from d2l import torch as d2l

#创建一个reshape层将原始输入大小28*28转换为LeNet所需的大小
class Reshape(torch.nn.Module):
    def forward(self, x):
        return x.view(-1, 1, 28, 28)

#LeNet网络
net = torch.nn.Sequential(Reshape(), # 重塑
                          nn.Conv2d(1, 6, kernel_size=5, padding=2), nn.Sigmoid(), # 卷积层
                            nn.AvgPool2d(kernel_size=2, stride=2), # 池化层
                            nn.Conv2d(6, 16, kernel_size=5), nn.Sigmoid(), # 卷积层
                            nn.AvgPool2d(kernel_size=2, stride=2), # 池化层
                            nn.Flatten(), # 展平
                            nn.Linear(16*5*5, 120), nn.Sigmoid(), # 全连接层
                            nn.Linear(120, 84), nn.Sigmoid(), # 全连接层
                            nn.Linear(84, 10)) # 全连接层

X = torch.rand(size=(1, 1, 28, 28), dtype=torch.float32) # 输入 1个1行28列28列的张量

#查看每一层的输出形状
for layer in net:
    X = layer(X)
    print(layer.__class__.__name__,'output shape:\t',X.shape)

#下载数据集
batch_size = 256
train_iter, test_iter = d2l.load_data_fashion_mnist(batch_size=batch_size) # 加载数据集

#使用GPU进行训练
def try_gpu():
    if torch.cuda.is_available():
        device = torch.device('cuda')
    else:
        device = torch.device('cpu')
    return device

#评估准确率
def evaluate_accuracy_gpu(net, data_iter, device=None): 
    if isinstance(net, torch.nn.Module): # 判断net是否是torch.nn.Module的实例
        net.eval() # 评估模式，关闭dropout
        if not device:
            device = next(iter(net.parameters())).device
    metric = d2l.Accumulator(2) # 正确预测数，预测总数
    for X, y in data_iter:
        if isinstance(X, list):
            X = [x.to(device) for x in X] # 将X的每一个元素转换为device
        else:
            X = X.to(device)
        y = y.to(device)
        metric.add(d2l.accuracy(net(X), y), y.numel()) # 正确预测数，预测总数
    return metric[0] / metric[1]

def train(net,train_iter,test_iter,num_epochs,lr,device):
    #初始化权重
    def init_weights(m):
        if type(m) == nn.Linear or type(m) == nn.Conv2d:
            nn.init.xavier_uniform_(m.weight) # xavier初始化
    net.apply(init_weights) # 初始化
    print('training on',device)
    net.to(device)
    optimizer = torch.optim.SGD(net.parameters(),lr=lr) # 随机梯度下降
    loss = nn.CrossEntropyLoss() # 交叉熵损失函数
    timer = d2l.Timer() # 计时器
    for epoch in range(num_epochs):
        metric = d2l.Accumulator(3) # 训练损失总和，训练准确度总和，样本数
        net.train() # 训练模式
        for i, (X, y) in enumerate(train_iter):
            timer.start()
            optimizer.zero_grad() # 梯度清零
            X, y = X.to(device), y.to(device)
            y_hat = net(X) # 预测
            l = loss(y_hat, y) # 计算损失
            l.backward() # 反向传播
            optimizer.step() # 更新参数
            with torch.no_grad():
                metric.add(l*X.shape[0],d2l.accuracy(y_hat,y),X.shape[0]) # 训练损失总和，训练准确度总和，样本数
            timer.stop()
            train_loss = metric[0]/metric[2]
            train_acc = metric[1]/metric[2]
            if (i+1) % 50 == 0:
                print(f'Epoch [{epoch+1}/{num_epochs}], loss {train_loss:.3f}, train acc {train_acc:.3f}') # 输出损失和准确度
                test_acc = evaluate_accuracy_gpu(net,test_iter) # 计算准确度
                print(f'test acc {test_acc:.3f}') # 输出准确度

    print(f'loss {train_loss:.3f}, train acc {train_acc:.3f}, 'f'test acc {test_acc:.3f}')
    print(f'{metric[2]*num_epochs/timer.sum():.1f} examples/sec 'f'on {str(device)}')
    print(f'{timer.sum()} seconds')

#训练测试
#设置超参数
lr, num_epochs = 0.9, 100 # 学习率 迭代次数
device = try_gpu() # GPU
net = net.to(device) # 网络
train(net, train_iter, test_iter, num_epochs, lr, device) # 训练