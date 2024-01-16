# 基本的for循环 读取序列中的每个元素
fruits = ['apple', 'banana', 'cherry']
for fruit in fruits:
    print(fruit)

# 使用range函数的for循环 生成一个整数序列
#range(start, stop, step) 从start开始到stop结束，每次增加step
for i in range(1, 6, 2):
    print(i)

# 带有enumerate函数的for循环 和函数一起作用 这种用法中一定要在函数中存在yield关键字，
# 同时指定返回值的对应关系，而且函数中也要有for循环，相对于将一个for循环中的东西封装成一个函数，然后把其结果返回

languages = ['Python', 'Java', 'C++']
for index, language in enumerate(languages):
    print(f"Index: {index}, Language: {language}")

def my_enumerate(iterable, start=0):
    """
    自定义实现的enumerate函数
    """
    i = start
    for item in iterable:
        yield i, item # yield关键字用于返回一个生成器 生成器是一个特殊的迭代器 
        i += 1
