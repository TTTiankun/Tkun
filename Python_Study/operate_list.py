#利用循环打印列表
cars=['audi','bmw','subaru','toyota']
for car in cars:
    print(car)
#car是一个临时变量，用来存储列表中的每个值，循环结束后，这个变量将不再可用

#在for循环中执行更多的操作
cars=['audi','bmw','subaru','toyota']
for car in cars:
    print(car.title() + ', is a good car.')
    print('I like ' + car.title() + '.\n')
print('I really like cars.') #在for循环后面，没有缩进的代码都只执行一次，而不会重复执行
#不要忘记缩进！！！也不要进行不必要的缩进！！！不要忘记for循环后的冒号！！！

#创建数值列表
#使用函数range()
#打印数列
for value in range(1,5): #打印1-4 不包含5
    print(value)
    
#创建数字列表
num_list=list(range(1,5)) #创建数字列表
print(num_list)
#使用函数range()时，还可指定步长
even_numbers=list(range(2,11,2)) #创建1-10的偶数列表 每一次加2
print(even_numbers)

#其他用法
#创建一个列表，其中包含前10个整数（即1~10）的平方
squares=[]
for value in range(1,11):
    square = value**2
    squares.append(square)
print(squares)

print('\n''\n''\n')

#对数字列表执行简单的统计计算
digits=[1,2,3,4,5,6,7,8,9,0]
print(min(digits)) #最小值
print(max(digits)) #最大值
print(sum(digits)) #总和

#列表解析
#使用列表解析生成前面的平方数列表
squares_p=[value**2 for value in range(1,11)] #列表名=[for循环变量名 表达式 for循环]
print(squares_p)

#使用列表的一部分
#切片
print(squares_p[0:3]) #打印列表中的前三个元素  0:3表示从索引0开始，到索引3结束，但不包含索引3
#其他情况
print(squares_p[:5]) #如果没有指定第一个索引，python将自动从列表开头开始
print(squares_p[3:]) #如果没有指定第二个索引，python将自动到列表末尾结束
print(squares_p[-3:]) #打印列表中的后三个元素

#遍历切片
print('Here are the first three squares in my list:')
for square in squares_p[0:3]:
    print(square)

#复制列表
squares_s=squares_p[:] #复制列表
print(squares_s)
#如果不使用切片，而只是将squares_s=squares_p，这两个变量将指向同一个列表，这样就无法独立地修改其中任何一个列表了

