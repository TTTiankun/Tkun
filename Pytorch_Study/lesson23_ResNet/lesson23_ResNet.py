#残差网络
#残差块是的很深的网络训练变得更加容易
#甚至可以训练1000层的网络
# 在传统的深度神经网络中，随着网络层次的增加，训练难度也会增加，这主要是因为梯度消失和梯度爆炸问题。而残差网络通过引入残差块，使得深层网络的训练变得更加容易。

# 残差块的主要思想是学习输入和输出之间的残差映射，而不是直接学习输入和输出的映射。
# 具体来说，如果我们假设输入为x，期望的输出为H(x)，那么在传统的网络中，我们直接学习H(x)；
# 而在残差网络中，我们学习的是残差F(x)=H(x)-x，然后通过x+F(x)来得到最终的输出。

from torch.nn import functional as F
from torch import nn
import torch
from d2l import torch as d2l

#定义残差块
class Residual(nn.Module):
    def __init__(self, input_channels, num_channels, use_1x1conv=False, strides=1): 
        super().__init__()
        self.conv1 = nn.Conv2d(input_channels, num_channels, kernel_size=3, padding=1, stride=strides) # 第一个卷积层
        self.conv2 = nn.Conv2d(num_channels, num_channels, kernel_size=3, padding=1) # 第二个卷积层
        if use_1x1conv:
            self.conv3 = nn.Conv2d(input_channels, num_channels, kernel_size=1, stride=strides) # 1x1卷积层
        else:
            self.conv3 = None
        self.bn1 = nn.BatchNorm2d(num_channels) # 第一个批量归一化层
        self.bn2 = nn.BatchNorm2d(num_channels) # 第二个批量归一化层
    def forward(self, X):
        Y = F.relu(self.bn1(self.conv1(X))) # 第一个卷积层+批量归一化层+激活函数
        Y = self.bn2(self.conv2(Y)) # 第二个卷积层+批量归一化层
        if self.conv3:
            X = self.conv3(X) # 1x1卷积层
        Y += X
        return F.relu(Y)

#测试残差块
blk = Residual(3, 3)
X = torch.rand(4, 3, 6, 6) # 4个样本，通道数为3，高和宽为6
Y = blk(X)
print(Y.shape) 

#增加输出通道数的同时减半输出的高和宽
blk = Residual(3, 6, use_1x1conv=True, strides=2)
print(blk(X).shape)

#ResNet模型
bl = nn.Sequential(
    nn.Conv2d(1, 64, kernel_size=7, stride=2, padding=3), # 第一层卷积层
    nn.BatchNorm2d(64), # 批量归一化层
    nn.ReLU(), # 激活函数
    nn.MaxPool2d(kernel_size=3, stride=2, padding=1)) # 最大池化层

def resnet_block(input_channels, num_channels, num_residuals, first_block=False): 
    blk = []
    for i in range(num_residuals):
        if i == 0 and not first_block: # 第一个残差块且不是第一个模块
            blk.append(Residual(input_channels, num_channels, use_1x1conv=True, strides=2)) # 第一个残差块
        else:
            blk.append(Residual(num_channels, num_channels)) # 其他残差块
    return blk

#添加所有的残差块
b2 = resnet_block(64, 64, 2, first_block=True) # 第一个模块 通道数为64，残差块数为2
b3 = resnet_block(64, 128, 2) # 第二个模块 通道数为128，残差块数为2
b4 = resnet_block(128, 256, 2) # 第三个模块 通道数为256，残差块数为2
b5 = resnet_block(256, 512, 2) # 第四个模块 通道数为512，残差块数为2

#将所有的模块添加到ResNet中
net = nn.Sequential(
    *bl, *b2, *b3, *b4, *b5, 
    nn.AdaptiveAvgPool2d((1, 1)), # 全局平均池化层
    nn.Flatten(), 
    nn.Linear(512, 10)) # 全连接层 输出为10 

#测试ResNet
X = torch.rand(size=(1, 1, 224, 224)) # 1个样本，通道数为1，高和宽为224
for layer in net:
    X = layer(X) # 逐层计算输出
    print(layer.__class__.__name__,'output shape:\t', X.shape) # 打印每一层的输出形状

#训练
#训练
lr, num_epochs, batch_size = 0.05, 5, 256 #学习率，迭代周期数，批量大小
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