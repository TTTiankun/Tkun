#示例
cars = ['bmw','audi','toyota','subaru']
for car in cars:
    if car == 'bmw': #检查是否是bmw 字符串是否相等
        print(car.upper())
    else:
        print(car.title())

#条件测试
car = 'Audi'
print(car == 'audi')

#比较数字
age = 18
print(age == 18)
print(age != 18) #检查是否不等于
print(age > 18) #检查是否大于
print(age < 18) #检查是否小于
print(age >= 18) #检查是否大于等于
print(age <= 18) #检查是否小于等于

#检查多个条件
age_0 = 22
age_1 = 18
print(age_0 >= 21 and age_1 >= 21) #and检查多个条件是否都为True
print(age_0 >= 21 or age_1 >= 21) #or检查多个条件是否有一个为True

#检查特定值是否包含在列表中!!!
print('This is a condition judgement:')
print('bmw' in cars) #检查特定值是否包含在列表中
print ('bmw' not in cars )#检查特定值是否不包含在列表中

#布尔表达式
game_active = True #布尔表达式通常用于记录条件，如游戏是否正在运行，或用户是否可以编辑网站的特定内容
#True和False的首字母必须大写 True: 1 False: 0

#if语句
#最简单的if语句
age_3 = 19
if (age_3 >= 18):
    print('You are old enough to vote!')

#if-else语句
age_4 = 17
if (age_4 >= 18):
    print('You are old enough to vote!')
else:
    print('Sorry, you are too young to vote!')

#if-elif-else结构
age_5 = 12
if (age_5 < 4):
    print('Your admission cost is $0.')
elif (age_5 < 14):
    print('Your admission cost is $5.')
elif(age_5 < 18):
    print('Your admission cost is $8.') #可以不断地添加elif代码块
else:
    print('Your admission cost is $10.') #else代码块是必须的，只要不满足前面的条件测试，其中的代码就会执行
                                         #但是在得知输入值满足所以条件的时候可以省略else代码块!!!

#测试多个条件
requested_toppings = ['mushrooms','extra cheese']
if ('mushrooms' in requested_toppings):
    print('Adding mushrooms.')
if ('pepperoni' in requested_toppings):
    print('Adding pepperoni.')
if ('extra cheese' in requested_toppings):
    print('Adding extra cheese.')
print('\nFinished making your pizza!')
#这种情况下不适用elif-else结构，因为python在满足了一个条件后，就会忽略后面的条件，即使后面的条件是True

#使用if语句处理列表
#检查特殊元素
requested_toppings = ['mushrooms','green peppers','extra cheese']
for requested_topping in requested_toppings:
    if (requested_topping == 'green peppers'):
        print('Sorry, we are out of green peppers right now.')
    else:
        print('Adding ' + requested_topping + '.')

print('\nFinished making your pizza!')

#确定列表不是空的
requested_toppings = []
if (requested_toppings): #列表为空时，if语句的条件测试将返回False
    for requested_topping in requested_toppings:
        print('Adding ' + requested_topping + '.')
    print('\nFinished making your pizza!')
else:
    print('Are you sure you want a plain pizza?')
    
#使用多个列表
available_toppings = ['mushrooms','olives','green peppers','pepperoni','pineapple','extra cheese']
requested_toppings = ['mushrooms','french fries','extra cheese']
for requested_topping in requested_toppings:
    if (requested_topping in available_toppings):
        print('Adding ' + requested_topping + '.')
    else:
        print("Sorry, we don't have " + requested_topping + '.')
print('\nFinished making your pizza!')
