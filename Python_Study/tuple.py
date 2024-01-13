#元组
#元组看起来犹如列表，但使用圆括号而不是方括号来标识 但是元组是不可变的 列表是可以操作的
dimensions=(200,50)
print(dimensions)
print("Here are two dimensions in dimensions:")
print(dimensions[0])
print(dimensions[1])
#dimensions[0]=200 #报错 元组不可变

#遍历元组中的所有值
for dimension in dimensions:
    print(dimensions)

#修改元组变量 尽管不能修改元组的元素，但可以给存储元组的变量赋值
dimensions = (400,100) #本质上就是重新定义数组！！！
print("Modified dimensions:")
for dimension in dimensions:
    print(dimension)