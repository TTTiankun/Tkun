import os # 导入os模块

#os.chdir('C:\\Users\\Administrator\\Desktop\\Python\\Python数据分析与挖掘实战\\第2周\\第2课\\data') # 切换路径
os.makedirs('data',exist_ok=True) # 创建文件夹
with open('./data/1.txt','w') as f: # 创建文件
    f.write('NumRooms,Alley,Price,SquareFeet,Neighborhood\n') # 列名
    f.write('NA,Pave,NA,1416,NridgHt\n') # 数据 表示一个数据样本
    f.write('2,NA,NA,948,OldTown\n') # 数据
    f.write('3,NA,178100,1717,StoneBr\n') # 数据

# 读取数据
import pandas as pd # 导入pandas模块
read = pd.read_csv('./data/1.txt') # 读取数据
print(read) # 打印数据

#注意数据类型 下面代码因为数据类型不一致会报错
# #处理缺失值
# #删除缺失值
# read_del = pd.read_csv('./data/1.txt') # 读取数据
# read_del = read_del.dropna(axis=0) # 删除缺失值
# #设置字符串的缺失值
# read_str = pd.read_csv('./data/1.txt') # 读取数据
# read_str = pd.get_dummies(read_str,dummy_na=True)# 设置字符串的缺失值
# print(read_str) # 打印数据
# print('\n')
#给缺失值取平均
# read_pro = pd.read_csv('./data/1.txt') # 读取数据
# read_pro = read_pro.fillna(read_pro.mean()) # 给缺失值取平均