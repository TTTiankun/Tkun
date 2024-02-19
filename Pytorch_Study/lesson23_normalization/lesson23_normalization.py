#批量归一化
#固定小批量中的均值和方差，然后学习出适合的偏移和缩放参数
#批量归一化层通常在卷积层或全连接层之后、激活函数之前使用
#批量归一化层的输出可以是任意的
#批量归一化可以加速收敛速度，提升学习率的大小，但不改变模型的精度

import torch
from torch import nn
from d2l import torch as d2l

#定义归一化层
def batch_norm(X, gamma, beta, moving_mean, moving_var, eps, momentum):
    # 通过autograd来判断当前模式是训练模式还是预测模式
    if not torch.is_grad_enabled():
        # 如果是在预测模式下，直接使用传入的移动平均所得的均值和方差
        X_hat = (X - moving_mean) / torch.sqrt(moving_var + eps)
    else:
        assert len(X.shape) in (2, 4) # X的形状为二维或四维
        if len(X.shape) == 2:
            # 使用全连接层的情况，计算特征维上的均值和方差
            mean = X.mean(dim=0)
            var = ((X - mean) ** 2).mean(dim=0)
        else:
            # 使用二维卷积层的情况，计算通道维上（axis=1）的均值和方差。这里我们需要保持X的形状以便后面可以做广播运算
            mean = X.mean(dim=(0, 2, 3), keepdim=True)
            var = ((X - mean) ** 2).mean(dim=(0, 2, 3), keepdim=True)
        # 训练模式下用当前的均值和方差做标准化
        X_hat = (X - mean) / torch.sqrt(var + eps)
        # 更新移动平均的均值和方差
        moving_mean = momentum * moving_mean + (1.0 - momentum) * mean 
        moving_var = momentum * moving_var + (1.0 - momentum) * var
    Y = gamma * X_hat + beta  # 拉伸和偏移
    return Y, moving_mean, moving_var # 返回Y和移动平均的均值和方差

#定义批量归一化层
class BatchNorm(nn.Module):
    def __init__(self, num_features, num_dims):
        super().__init__()
        if num_dims == 2:
            shape = (1, num_features)
        else:
            shape = (1, num_features, 1, 1)
        # 参与求梯度和迭代的拉伸和偏移参数，分别初始化成0和1
        self.gamma = nn.Parameter(torch.ones(shape))
        self.beta = nn.Parameter(torch.zeros(shape))
        # 不参与求梯度和迭代的变量，全在内存上初始化成0
        self.moving_mean = torch.zeros(shape)
        self.moving_var = torch.zeros(shape)
    def forward(self, X):
        if self.moving_mean.device != X.device:
            self.moving_mean = self.moving_mean.to(X.device)
            self.moving_var = self.moving_var.to(X.device)
        # 保存更新过的moving_mean和moving_var
        Y, self.moving_mean, self.moving_var = batch_norm(
            X, self.gamma, self.beta, self.moving_mean,
            self.moving_var, eps=1e-5, momentum=0.9) # 这里的momentum是0.9
        return Y
    

#将批量归一化层和LeNet模型结合起来

net = nn.Sequential(
    nn.Conv2d(1, 6, kernel_size=5), BatchNorm(6, num_dims=4), nn.Sigmoid(),
    nn.MaxPool2d(kernel_size=2, stride=2),
    nn.Conv2d(6, 16, kernel_size=5), BatchNorm(16, num_dims=4), nn.Sigmoid(),
    nn.MaxPool2d(kernel_size=2, stride=2), nn.Flatten(),
    nn.Linear(16*4*4, 120), BatchNorm(120, num_dims=2), nn.Sigmoid(),
    nn.Linear(120, 84), BatchNorm(84, num_dims=2), nn.Sigmoid(),
    nn.Linear(84, 10))

#这个不太行，超显存了 内存也不够！
#训练模型
lr, num_epochs, batch_size = 1.0, 5, 32 #学习率，迭代周期数，批量大小
train_iter, test_iter = d2l.load_data_fashion_mnist(batch_size)

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
# device = try_gpu() # GPU
device = torch.device('cpu')
net = net.to(device) # 网络
train(net, train_iter, test_iter, num_epochs, lr, device) # 训练