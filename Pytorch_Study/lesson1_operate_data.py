import torch
x = torch.arange(1,9) # 生成一个从3到4的一维张量
print(x)

a = x.shape # 查看张量的形状
print(a)

b = x.numel() # 查看张量的元素个数
print(b)

x = x.reshape(2,4) # 改变张量的形状 折叠成2行4列的张量
print(x)

y = torch.zeros(2,3,4) # 生成一个全0的张量 2个3行4列的张量
print(y)

z = torch.ones(2,3,4) # 生成一个全1的张量 2个3行4列的张量
print(z)

w = torch.rand(2,3,4) # 生成一个随机数的张量(小数) 2个3行4列的张量print(w)

v = torch.tensor([1,2,3,4]) # 生成一个张量
print(v)

#可以进行一些运算
#可以进行逻辑判断
print(z == w) # 逐个元素进行判断相等

#广播机制
#张量的形状不一样，但是可以进行运算
t = x + v # 2个3行4列的张量 + 1个4列的张量
print(t)

#元素的访问
print(t[1,3]) # 访问第2行第4列的元素
print(t[0:2])  # 访问第1行到第2行的元素

#元素的修改
t[1,3] = 100 # 修改第2行第4列的元素
print(t)
t[0:2,1:2] = 200 # 修改第1行到第2行的第2列的元素
print(t)

#运行一些操作会到时新结果的内存重新分配
before = id(t) # 查看t的内存地址
print(before)
t = t + x # t + 1 会重新分配内存
print(id(t)) # 查看t的内存地址

#执行原地操作 可以创建新的张量防止内存重新分配
z = torch.zeros_like(t) # 生成一个和t一样的全0的张量
print(id(z)) # 查看z的内存地址
z[:] = t + x # 原地操作
print(id(z)) # 查看z的内存地址

#将张量转换成numpy数组
e = t.numpy() # 将张量转换成numpy数组
print(e)
print(type(e),type(t)) # 查看类型
#将numpy数组转换成张量
import numpy as np
f = np.ones((2,3))
print(f)
g = torch.from_numpy(f) # 将numpy数组转换成张量
print(g)
#将张量转换成标量
h = torch.tensor(1.0)
print(h)
i = h.item() # 将张量转换成标量
print(i)
h = int(h) # 将张量转换成整数
print(h)
i = float(i) # 将标量转换成小数
print(i)
