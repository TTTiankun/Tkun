# VGG（Visual Geometry Group）是一种深度卷积神经网络架构，由牛津大学的视觉几何组（Visual Geometry Group）提出，因此得名。
# VGG在2014年的ImageNet图像识别挑战赛中取得了优秀的成绩。

# VGG的主要特点是其结构简单，全部使用3x3的小型卷积核和2x2的最大池化核，通过堆叠这些小型卷积核和池化核来构建深度网络。
# VGG有多个版本，包括VGG16和VGG19，数字代表网络中的层数。

# VGG虽然在参数量和计算量上较大，但其结构简单、理解容易的特点使得它在图像识别和处理领域得到了广泛应用。 

#总结：
#VGG使用可重复使用的卷积层来构建网络，这些卷积层都是3x3的小型卷积核，这样可以减少参数量，同时提高网络的非线性表达能力。
#不同卷积块个数和超参数可以得到不同复杂度的变种

import torch
from torch import nn
from d2l import torch as d2l

#定义VGG块
def vgg_block(num_convs, in_channels, out_channels):
    layers = [] #存储VGG块的各个层
    for _ in range(num_convs): #堆叠卷积层
        layers.append(nn.Conv2d(in_channels, out_channels, kernel_size=3, padding=1)) #卷积层 输入通道数，输出通道数，卷积核大小，填充
        layers.append(nn.ReLU()) #激活函数
        in_channels = out_channels #下一个卷积层的输入通道数
    layers.append(nn.MaxPool2d(kernel_size=2, stride=2)) #最大池化层
    return nn.Sequential(*layers) #返回VGG块

conv_arch = ((1, 64), (1, 128), (2, 256), (2, 512), (2, 512)) #每个元组代表一个VGG块的卷积层个数和输出通道数

def vgg(conv_arch):
    conv_blks = [] #存储VGG块
    in_channels = 1 #输入通道数
    for (num_convs, out_channels) in conv_arch: #遍历每个VGG块
        conv_blks.append(vgg_block(num_convs, in_channels, out_channels)) #添加VGG块
        in_channels = out_channels #下一个VGG块的输入通道数
    return nn.Sequential(*conv_blks, nn.Flatten(), #展平
                         nn.Linear(out_channels * 7 * 7, 4096), nn.ReLU(), #全连接层
                         nn.Dropout(0.5), #丢弃层
                         nn.Linear(4096, 4096), nn.ReLU(), #全连接层
                         nn.Dropout(0.5), #丢弃层
                         nn.Linear(4096, 10)) #输出层

net = vgg(conv_arch) #实例化VGG网络

#测试 观察每一层的输出形状
#构造一个高度和宽度为224的单通道数据样本来观察每一层的输出形状
X = torch.randn(size=(1, 1, 224, 224))
for blk in net:
    X = blk(X)
    print(blk.__class__.__name__, 'output shape:\t', X.shape)

#由于VGG-11比AlexNet计算量更大，因此我们构建了一个通道数较少的网络
ratio = 4 #通道数减少的比例
small_conv_arch = [(pair[0], pair[1] // ratio) for pair in conv_arch] #通道数减少4倍
net = vgg(small_conv_arch) #实例化VGG网络

#训练
lr, num_epochs, batch_size = 0.05, 10, 128 #学习率，迭代周期数，批量大小
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

# 损失函数（loss function）的值大于1是完全可能的，这取决于你使用的损失函数和问题的性质。

# 在你的代码中，你使用的是交叉熵损失（CrossEntropyLoss）。交叉熵损失是用于多分类问题的一种常见损失函数，它的值可以是任意的正数，包括大于1的值。

# 交叉熵损失的计算公式为：

# ```
# CrossEntropyLoss = -Σ(y*log(y_hat))
# ```

# 其中，`y` 是真实标签的独热编码，`y_hat` 是模型的预测概率。当模型的预测概率与真实标签相差很大时，交叉熵损失就会很大。

# 例如，如果对于一个样本，真实标签是类别1，但模型预测类别1的概率只有0.1，那么这个样本的交叉熵损失就会大于1。

# 所以，如果你在训练初期看到损失大于1，这是正常的，因为模型还没有学习到足够的信息。随着训练的进行，你应该会看到损失逐渐下降。