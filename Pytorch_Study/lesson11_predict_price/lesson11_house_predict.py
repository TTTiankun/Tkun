import numpy as np
import pandas as pd # 读取数据
import torch
from torch import nn
from d2l import torch as d2l
import os # 读取文件
import hashlib # 加密
import requests # 请求
import zipfile # 压缩
import tarfile # 压缩

DATA_HUB = dict()#字典
DATA_URL = 'http://d2l-data.s3-accelerate.amazonaws.com/'#数据集的地址

#下载数据集
def download(name,cache_dir=os.path.join('..','data')):#数据集的名字 数据集的缓存地址
    assert name in DATA_HUB, f"{name} does not exist in {DATA_HUB}."#断言name在DATA_HUB中
    url, sha1_hash = DATA_HUB[name]#获取数据集的地址和SHA-1校验码
    os.makedirs(cache_dir, exist_ok=True)#创建缓存目录
    fname = os.path.join(cache_dir, url.split('/')[-1])#获取文件名
    if os.path.exists(fname):#如果文件存在
        sha1 = hashlib.sha1()#获取SHA-1对象
        with open(fname, 'rb') as f:#打开文件
            while True:#循环
                data = f.read(1048576)#读取文件
                if not data:#如果没有数据
                    break#退出循环
                sha1.update(data)#更新SHA-1对象
        if sha1.hexdigest() == sha1_hash:#如果SHA-1校验码正确
            return fname#返回文件名
    print(f'Downloading {fname} from {url}...')#打印下载信息
    d2l.download(url, fname)#下载数据集
    return fname#返回文件名

#下载数据集
DATA_HUB['kaggle_house_train'] = (DATA_URL + 'kaggle_house_pred_train.csv',#训练数据集
                                  '585e9cc93e70b39160e7921475f9bcd7d31219ce')#数据集的SHA-1校验码


DATA_HUB['kaggle_house_test'] = (DATA_URL + 'kaggle_house_pred_test.csv',#测试数据集
                                'fa19780a7b011d9b009e8bff8e99922a8ee2eb90')#数据集的SHA-1校验码

#用于下载数据集现在就注释掉吧
# download('kaggle_house_train')#下载训练数据集
# download('kaggle_house_test')#下载测试数据集

train_data = pd.read_csv("lesson11_predict_price/data/kaggle_house_pred_train.csv")#读取训练数据
test_data = pd.read_csv("lesson11_predict_price/data/kaggle_house_pred_test.csv")#读取测试数据

#1460个样本 80个特征 1个标签 这个是训练数据 标签是房价
#1459个样本 80个特征 这个是测试数据 没有标签

#显示样本的前4个特征和后2个特征以及标签
print(train_data.iloc[0:4,[0,1,2,3,-3,-2,-1]])#iloc函数是通过行号来取行数据的 默认从0开始这行代码是使用 pandas 库的 DataFrame 对象的 `iloc` 方法来选择数据。


#  `0:4`：选择第0行到第3行（不包括第4行）的数据，即选择前4行的数据。
#  `[0,1,2,3,-3,-2,-1]`：选择第0列、第1列、第2列、第3列以及倒数第3列、倒数第2列和倒数第1列的数据。


#去除ID列

all_features = pd.concat((train_data.iloc[:, 1:-1], test_data.iloc[:, 1:]))#将训练数据和测试数据的特征合并起来

#将缺失的数值替换为均值 通过将特征重新放缩到零均值和单位方差来标准化数据，从而使其平均值为0，方差为1
numeric_features = all_features.dtypes[all_features.dtypes != 'object'].index#选出数值特征
all_features[numeric_features] = all_features[numeric_features].apply(
    lambda x: (x - x.mean()) / (x.std()))#将缺失的数值替换为均值
#lambda函数是一种匿名函数，即没有函数名的函数，它允许快速定义单行函数，类似于C语言中的宏，可以用在任何需要函数的地方。
#缺失值替换公式：(x - x.mean()) / (x.std()) 意思是用x的均值除以x的标准差替换
all_features[numeric_features] = all_features[numeric_features].fillna(0)#将缺失的数值替换为0

#处理字符串类型的数据
#将离散数值转换为指示特征 单独热编码
all_features = pd.get_dummies(all_features, dummy_na=True)#将离散数值转换为指示特征 单独热编码
all_features = all_features.astype('float32')
print(all_features.iloc[0:4,[0,1,2,3,-3,-2,-1]])
#现在数据量来到2919个样本 330个特征

#获取numpy格式的数据
n_train = train_data.shape[0]#训练数据的样本数 意思是获取训练数据的行数
train_features = torch.tensor(all_features[:n_train].values, dtype=torch.float32)#训练数据的特征
test_features = torch.tensor(all_features[n_train:].values, dtype=torch.float32)#测试数据的特征
train_labels = torch.tensor(train_data.SalePrice.values.reshape(-1, 1), dtype=torch.float32)#训练数据的标签

#定义模型
loss = nn.MSELoss()#损失函数 使用均方误差损失函数
in_features = train_features.shape[1]#输入特征数

#获取网络
def get_net():
    net = nn.Sequential(nn.Linear(in_features, 1))#获取网络 使用线性回归 一个线性层 一个输出
    return net

def log_rmse(net, features, labels): #计算均方根误差
    # 将小于1的值设成1，使得取对数时数值更稳定
    clipped_preds = torch.clamp(net(features), 1, float('inf'))#将小于1的值设成1，使得取对数时数值更稳定
    #net(features)是预测值 1是最小值 float('inf')是最大值（正无穷）
    rmse = torch.sqrt(loss(clipped_preds.log(), labels.log()))#计算均方根误差 使用均方误差损失函数 
    return rmse.item()#返回均方根误差

#定义训练函数 使用Adam优化算法 优点：1.相对于SGD收敛更快 2.相对于SGD更容易找到全局最优点 3.相对于SGD对参数的初始化不敏感
def train(net, train_features, train_labels, test_features, test_labels,
          num_epochs, learning_rate, weight_decay, batch_size):#网络 训练数据的特征 训练数据的标签 测试数据的特征 测试数据的标签 迭代次数 学习率 权重衰减 批量大小
    train_ls, test_ls = [], []#训练损失 测试损失
    dataset = torch.utils.data.TensorDataset(train_features, train_labels)#训练数据集
    train_iter = torch.utils.data.DataLoader(dataset, batch_size, shuffle=True)#训练数据迭代器
    #shuffle=True表示打乱数据
    #batch_size是批量大小
    optimizer = torch.optim.Adam(params=net.parameters(), lr=learning_rate, weight_decay=weight_decay)#优化器 使用Adam优化算法
    net = net.float()#将网络的数据类型转换为float
    for epoch in range(num_epochs):#迭代次数
        for X, y in train_iter:#训练数据迭代器
            l = loss(net(X.float()), y.float())#计算损失 使用均方误差损失函数
            optimizer.zero_grad()#梯度清零
            l.backward()#反向传播
            optimizer.step()#更新参数
        train_loss = log_rmse(net, train_features, train_labels)
        train_ls.append(log_rmse(net, train_features, train_labels))#计算均方根误差
        if test_labels is not None:#如果测试数据的标签不为空
            test_loss = log_rmse(net, test_features, test_labels)
            test_ls.append(log_rmse(net, test_features, test_labels))#计算均方根误差
            print(f'Epoch {epoch + 1}/{num_epochs}, Train RMSE: {train_loss}, Test RMSE: {test_loss}')
        else:
            print(f'Epoch {epoch + 1}/{num_epochs}, Train RMSE: {train_loss}')
    return train_ls, test_ls#返回训练损失和测试损失


            

#K折交叉验证
#获取训练数据的特征 训练数据的标签 验证数据的特征 验证数据的标签
def get_k_fold_data(k, i, X, y):#k折交叉验证 折数 第i折 训练数据的特征 训练数据的标签
    assert k > 1#断言k大于1
    fold_size = X.shape[0] // k#每一折的大小
    X_train, y_train = None, None#训练数据的特征 训练数据的标签
    for j in range(k):#迭代
        idx = slice(j * fold_size, (j + 1) * fold_size)#索引
        X_part, y_part = X[idx, :], y[idx]#训练数据的特征 训练数据的标签
        if j == i:#如果j等于i
            X_valid, y_valid = X_part, y_part#验证数据的特征 验证数据的标签 意思是将X_part和y_part赋值给X_valid和y_valid
        elif X_train is None:#如果训练数据的特征为空
            X_train, y_train = X_part, y_part#训练数据的特征 训练数据的标签
        else:#如果训练数据的特征不为空
            X_train = torch.cat((X_train, X_part), dim=0)#训练数据的特征 意思是将X_train和X_part在第0维度上（行）进行拼接
            y_train = torch.cat((y_train, y_part), dim=0)#训练数据的标签
    return X_train, y_train, X_valid, y_valid#返回训练数据的特征 训练数据的标签 验证数据的特征 验证数据的标签

#在K折交叉验证中我们训练K次并返回训练和验证的平均误差

#K折交叉验证核心步骤
def k_fold(k, X_train, y_train, num_epochs,
           learning_rate, weight_decay, batch_size):#k折交叉验证 折数 训练数据的特征 训练数据的标签 迭代次数 学习率 权重衰减 批量大小
    train_l_sum, valid_l_sum = 0, 0#训练损失和 验证损失和
    for i in range(k):#迭代
        data = get_k_fold_data(k, i, X_train, y_train)#获取训练数据的特征 训练数据的标签 验证数据的特征 验证数据的标签
        net = get_net()#获取网络
        train_ls, valid_ls = train(net, *data, num_epochs, learning_rate,
                                   weight_decay, batch_size)#训练损失 测试损失
        train_l_sum += train_ls[-1]#训练损失和
        valid_l_sum += valid_ls[-1]#验证损失和
        if i == 0:#如果i等于0
            print(f'fold {i + 1}, train log rmse {float(train_ls[-1]):f}, 'f'valid log rmse {float(valid_ls[-1]):f}')#打印训练损失和验证损失
    return train_l_sum / k, valid_l_sum / k#返回训练损失和验证损失

#RMSE 误差均方根
#这种参数用来评估回归模型预测效果的好坏 
#公式：sqrt(sum((y-y_hat)^2)/n) 即 y和y_hat的差的平方和的平均值的开方
#y是真实值 y_hat是预测值 n是样本个数
#RMSE越小，说明预测效果越好 缺点：容易受到异常值的影响

#模型选择
#使用K折交叉验证来选择模型设计并调节超参数
#我们通过网格搜索来找到良好的超参数的组合
#对于每组超参数，我们运行K折交叉验证5次并记录训练和验证的平均误差
#最后我们输出在K折交叉验证中平均训练和验证误差

#定义超参数
k, num_epochs, lr, weight_decay, batch_size = 20, 10000, 0.3, 0.1, 512#折数 迭代次数 学习率 权重衰减 批量大小

#训练并验证模型
def train_and_pred(train_features, test_features, train_labels, test_data,
                   num_epochs, lr, weight_decay, batch_size):#训练数据的特征 测试数据的特征 训练数据的标签 测试数据的标签 迭代次数 学习率 权重衰减 批量大小
    net = get_net()#获取网络
    train_ls, _ = train(net, train_features, train_labels, None, None,
                        num_epochs, lr, weight_decay, batch_size)#训练损失 测试损失
    print(f'train log rmse {float(train_ls[-1]):f}')#打印训练损失
    # Apply the network to the test set
    preds = net(test_features).detach().numpy()#预测值
    test_data['SalePrice'] = pd.Series(preds.reshape(1, -1)[0])#测试数据的标签
    submission = pd.concat([test_data['Id'], test_data['SalePrice']], axis=1)#将测试数据的ID和预测值拼接起来
    submission.to_csv('submission.csv', index=False)#将submission保存为csv文件 不保存索引

#训练并验证模型
train_and_pred(train_features, test_features, train_labels, test_data,
               num_epochs, lr, weight_decay, batch_size)#训练数据的特征 测试数据的特征 训练数据的标签 测试数据的标签 迭代次数 学习率 权重衰减 批量大小
