#示例
message = input('Tell me something, and I will repeat it back to you: ')
print(message)

#使用int()来获取数值输入 强制类型转换
age = input('How old are you? ')
age = int(age) #只有这样才可以将age转换为整数 不然age是字符串！！！
if(age <= 18): #age >= 18是一个条件测试，如果age大于等于18，python返回True，否则返回False
    print('Too Small!!!') 