import torch
A = torch.arange(20).reshape(5,4)
print(A)
#转置
print(A.T)
#对于对称矩阵来说，转置不会改变矩阵
#矩阵的加法
B = torch.arange(20,dtype=torch.float32).reshape(5,4) # 生成一个从0到19的一维张量 并且改变数据类型为float32 折叠成5行4列的张量
C = B.clone() # 克隆B
print(C)
print(C+B)

#矩阵的数量乘法
print(2*B)

#矩阵的点乘
print(B*B)

#计算矩阵元素的和
print(B.sum())
#计算矩阵的均值
print(B.mean())
#计算矩阵的标准差
print(B.std())
#计算矩阵的最大值
print(B.max())
#计算矩阵的最小值
print(B.min())
#计算某个轴的和
print(B.sum(axis=0)) # 按列求和
print(B.sum(axis=1)) # 按行求和
print(B.sum(axis=[0,1])) # 按列求和 再按行求和
print(B.sum(axis=1,keepdim=True)) # 按列求和 保持维度
#累计求和
print(B.cumsum(axis=0)) # 按列累计求和

#矩阵的点积
x = torch.arange(4,dtype=torch.float32) # 生成一个从0到3的一维张量 并且改变数据类型为float32
y = torch.ones_like(x) # 生成一个和x一样的全1的张量
print(torch.dot(x,y)) # 矩阵的点积

#矩阵的范数
print(torch.norm(B)) # 矩阵的范数

#自动求导
x.requires_grad_(True) # 设置自动求导 等价于x = torch.arange(4,dtype=torch.float32,requires_grad=True)
print(x)

y = 2*torch.dot(x,x) # 计算y
print(y)

y = x.sum() 
y.backward() # 反向传播
print(x.grad) # 输出梯度

# 在数学和计算机科学中，梯度（Gradient）是一个向量，表示一个多变量函数在某一点的局部导数或变化率。梯度是一个矢量，其方向指向函数值增长最快的方向，而大小表示增长的速率。

# 对于一个具有多个输入变量的函数 f(x1,x2,…,xn)f(x1​,x2​,…,xn​)，其梯度由各个偏导数组成。

# 梯度的性质：

#     方向性： 梯度的方向指向函数值增长最快的方向。如果你站在某一点，并沿着梯度的方向移动，函数值将以最快的速度增加。
#     大小： 梯度的大小表示函数值增长的速率。梯度的大小越大，表示函数在该点的变化越剧烈。

# 梯度在优化问题中扮演着重要的角色，特别是在机器学习中。在机器学习中，通过梯度下降算法，可以沿着梯度的负方向逐步调整模型参数，以最小化（或最大化）目标函数。梯度下降是一种迭代优化算法，通过沿着梯度的反方向更新参数，逐渐接近目标的最优解。

# 总的来说，梯度是一个用来表示多变量函数变化率的重要概念，广泛应用于数学、物理、工程和计算机科学等领域。