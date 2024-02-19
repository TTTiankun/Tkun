#NIN

#NIN块
#一个卷积层连接着两个充当全连接层的1x1卷积层

#NIN架构
#无全连接层 交替使用NIN块和步幅为2的最大池化 逐步减小高宽和增大通道数
#最后使用全局平均池化层得到输出 其输入通道数是类别数

import torch
from torch import nn
from d2l import torch as d2l

#设置NIN块
def nin_block(in_channels, out_channels, kernel_size, stride, padding):
    return nn.Sequential(
        nn.Conv2d(in_channels, out_channels, kernel_size, stride, padding), # 卷积层
        nn.ReLU(), # 激活函数
        nn.Conv2d(out_channels, out_channels, kernel_size=1), # 1x1卷积层
        nn.ReLU(), # 激活函数
        nn.Conv2d(out_channels, out_channels, kernel_size=1), # 1x1卷积层
        nn.ReLU() # 激活函数
    )

#NIN模型
#NIN使用卷积窗口形状分别为11x11, 5x5, 3x3的卷积层, 和输出通道数分别为96, 256, 384的NIN块
#之后使用步幅为2, 窗口形状为3x3的最大池化层
#再使用两个输出通道数为384的NIN块
#最后使用步幅为2, 窗口形状为3x3的最大池化层
#最后使用输出通道数为10的NIN块, 然后使用全局平均池化层得到输出

#网络设置
net = nn.Sequential(
    nin_block(1, 96, kernel_size=11, stride=4, padding=0), # 输入通道数1 11x11卷积层 步幅4 无填充
    nn.MaxPool2d(3, stride=2), # 池化层
    nin_block(96, 256, kernel_size=5, stride=1, padding=2), # 输入通道数96 5x5卷积层 有填充
    nn.MaxPool2d(3, stride=2), # 池化层
    nin_block(256, 384, kernel_size=3, stride=1, padding=1), # 输入通道数256 3x3卷积层 有填充
    nn.MaxPool2d(3, stride=2), # 池化层
    nn.Dropout(0.5), # 随机丢弃 丢弃概率0.5
    nin_block(384, 10, kernel_size=3, stride=1, padding=1), # 输入通道数384 3x3卷积层 有填充
    nn.AdaptiveAvgPool2d((1, 1)), # 全局平均池化层
    nn.Flatten() # 展平
)

#测试 查看每个块的输出形状
X = torch.rand(size=(1, 1, 224, 224))
for layer in net:
    X = layer(X)
    print(layer.__class__.__name__, 'output shape:\t', X.shape)

#训练
lr, num_epochs, batch_size = 0.1, 5, 128 #学习率，迭代周期数，批量大小
train_iter, test_iter = d2l.load_data_fashion_mnist(batch_size, resize=224) #加载数据集

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
    return metric[0] / metric[1] # 准确度

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
device = try_gpu() # GPU
net = net.to(device) # 网络
train(net, train_iter, test_iter, num_epochs, lr, device) # 训练