# GoogLeNet是一种深度卷积神经网络（Deep Convolutional Neural Network），由Google的研究人员在2014年提出，该模型在ImageNet大规模视觉识别挑战赛（ILSVRC）上取得了优秀的成绩。

# GoogLeNet的主要优点：

# 1. **深度**：GoogLeNet的网络深度达到了22层，比之前的网络模型深度大大提高，这使得模型能够学习到更复杂的特征表示。

# 2. **计算效率**：GoogLeNet引入了Inception模块，通过合理的网络结构设计，大大减少了计算量。

# 3. **无全连接层**：GoogLeNet去掉了全连接层，大大减少了模型的参数数量，降低了过拟合的风险。

# 4. **辅助分类器**：GoogLeNet在网络中引入了两个辅助分类器，用于进行中间层的监督，提高了网络的训练速度和性能。

# GoogLeNet的简介：

# GoogLeNet是一种深度学习模型，主要用于图像识别。它的设计灵感来源于LeNet，但在结构上做了很多创新，如引入了Inception模块，去掉了全连接层，添加了辅助分类器等。
#这些创新使得GoogLeNet在处理图像识别任务时，既能保持高精度，又能有效控制计算量和模型大小。

# GoogLeNet的网络结构：
# GoogLeNet的网络结构非常复杂，主要由Inception模块组成。Inception模块是GoogLeNet的核心，它是一种网络结构模块，能够有效地提取图像的特征表示。

#代码实现

import torch
from torch import nn
from torch.nn import functional as F
from d2l import torch as d2l

# 定义Inception模块
class Inception(nn.Module):
    # c1 - c4为每条线路里的层的输出通道数
    def __init__(self, in_channels, c1, c2, c3, c4, **kwargs):
        super(Inception, self).__init__(**kwargs)
        # 线路1，单1 x 1卷积层
        self.p1_1 = nn.Conv2d(in_channels, c1, kernel_size=1)
        # 线路2，1 x 1卷积层后接3 x 3卷积层
        self.p2_1 = nn.Conv2d(in_channels, c2[0], kernel_size=1)
        self.p2_2 = nn.Conv2d(c2[0], c2[1], kernel_size=3, padding=1)
        # 线路3，1 x 1卷积层后接5 x 5卷积层
        self.p3_1 = nn.Conv2d(in_channels, c3[0], kernel_size=1)
        self.p3_2 = nn.Conv2d(c3[0], c3[1], kernel_size=5, padding=2)
        # 线路4，3 x 3最大池化层后接1 x 1卷积层
        self.p4_1 = nn.MaxPool2d(kernel_size=3, stride=1, padding=1)
        self.p4_2 = nn.Conv2d(in_channels, c4, kernel_size=1)

    def forward(self, x):
        p1 = F.relu(self.p1_1(x)) # 线路1
        p2 = F.relu(self.p2_2(F.relu(self.p2_1(x)))) # 线路2
        p3 = F.relu(self.p3_2(F.relu(self.p3_1(x)))) # 线路3
        p4 = F.relu(self.p4_2(self.p4_1(x))) # 线路4
        # 在通道维上连结输出
        return torch.cat((p1, p2, p3, p4), dim=1) 

# GoogLeNet模型

# GoogLeNet跟VGG一样，先定义数个卷积块，再定义数个全连接层块。卷积块里的卷积层通常使用较小的卷积核，全连接块则使用全局平均池化层对每个通道中所有元素求平均并直接用于分类。

#block1 简单卷积块 
b1 = nn.Sequential(nn.Conv2d(1, 64, kernel_size=7, stride=2, padding=3),
                   nn.ReLU(), nn.MaxPool2d(kernel_size=3, stride=2, padding=1))

#block2 2个堆叠的卷积块 
b2 = nn.Sequential(nn.Conv2d(64, 64, kernel_size=1), nn.ReLU(),
                   nn.Conv2d(64, 192, kernel_size=3, padding=1), nn.ReLU(),
                   nn.MaxPool2d(kernel_size=3, stride=2, padding=1))

#block3 4个堆叠的Inception块
b3 = nn.Sequential(Inception(192, 64, (96, 128), (16, 32), 32),
                   Inception(256, 128, (128, 192), (32, 96), 64),
                   nn.MaxPool2d(kernel_size=3, stride=2, padding=1))

#block4 5个堆叠的Inception块
b4 = nn.Sequential(Inception(480, 192, (96, 208), (16, 48), 64),
                   Inception(512, 160, (112, 224), (24, 64), 64),
                   Inception(512, 128, (128, 256), (24, 64), 64),
                   Inception(512, 112, (144, 288), (32, 64), 64),
                   Inception(528, 256, (160, 320), (32, 128), 128),
                   nn.MaxPool2d(kernel_size=3, stride=2, padding=1))

#block5 2个堆叠的Inception块
b5 = nn.Sequential(Inception(832, 256, (160, 320), (32, 128), 128),
                   Inception(832, 384, (192, 384), (48, 128), 128),
                   nn.AdaptiveAvgPool2d((1, 1)), nn.Flatten())

#网络
net = nn.Sequential(b1, b2, b3, b4, b5, nn.Linear(1024, 10))

#测试
# GoogLeNet模型的计算复杂，而且不如VGG那样便于修改通道数。为了使Fashion-MNIST上的训练短小精悍，我们将输入的高和宽从224降到96。下面演示各个block的输出的形状变化。
X = torch.rand(size=(1, 1, 96, 96))
for layer in net:
    X = layer(X)
    print(layer.__class__.__name__,'output shape:\t',X.shape)

#训练
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