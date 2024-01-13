#简单的示例
alion_0 = {'color': 'green' ,'points': 5} #设置建-值对应关系

print(alion_0['color']) #通过键获取值
print(alion_0['points'])

#添加键-值对
alion_0['x_position'] = 0
alion_0['y_position'] = 25
print(alion_0)

#修改字典中的值
alion_0['color'] = 'yellow'
print("Now alion_0 change the color!")
print(alion_0['color'])

#删除键-值对
del alion_0['points']
print(alion_0)

#在字典中用类似对象的方式储存信息
favorite_languages = {
    'jen': 'python',
    'sarah': 'c',
    'edward': 'ruby',
    'phil': 'python'
    }
print("Sarah's favorite language is " + favorite_languages['sarah'].title() + ".")
print('\n')

#遍历字典
#遍历所有的键-值对
for key, value in favorite_languages.items(): #items()方法返回一个键-值对列表
    print("\nName: " + key)
    print("Favourite Laguage: " + value)

#遍历字典中的所有键
print('\nThese are all users here:')
for name in favorite_languages.keys(): #keys()方法返回一个键列表
    print(name.title())
    
#按顺序遍历字典中的所有键
print('\nThese are all users here:')
for name in sorted(favorite_languages.keys()): #sorted()方法返回一个按顺序排列的键列表
    print(name.title())

#遍历字典中的所有值
print('\nThese are all languages here:')
for language in set(favorite_languages.values()): #set()方法返回一个去重后的值列表
    print(language.title())

#使用set（）来排除重复项
print('\nThese are all languages here:')
for language in set(favorite_languages.values()): #set()方法返回一个去重后的值列表
    print(language.title())
    
#嵌套
#字典列表
alion_1 = {'color': 'green' ,'points': 5} #设置建-值对应关系
alion_2 = {'color': 'red' ,'points': 10}
alions = [alion_0, alion_1, alion_2] #将字典放在列表中
print(alions)

#遍历创建字典列表
alions = [] #创建一个空列表
for alion_number in range(30): #创建30个字典 也可以写成range(0,30)！！！
    new_alion = {'color': 'green' ,'points': 5, 'speed': 'slow'}
    alions.append(new_alion) #将字典添加到列表中
print(alions[0].keys()) #打印第一个字典的所有键值，这个时候字典列表中的字典都是一样的
print(len(alions)) #打印列表长度

#显示前五个字典
for alion in alions[0:5]: #遍历前五个字典
    print(alion)
    
#在字典中储存列表
#存储所点pizza的信息
pizza = {
    'crust': 'thick',
    'toppings': ['mushrooms', 'extra cheese']
    }
print("You ordered a " + pizza['crust'] + "-crust pizza " + "with the following toppings:")
for topping in pizza['toppings']:
    print("\t" + topping)

#在字典中储存字典
#存储所点用户的信息
users = {
    'aeinstein': {
        'first': 'albert',
        'last': 'einstein',
        'location': 'princeton'
        },
    'mcurie': {
        'first': 'marie',
        'last': 'curie',
        'location': 'paris'
        }
    }

print('Here are all users information:')
for username,user_info in users.items():
    print('\nUsername:'+ username)
    print('Full name:' + user_info['first'].title() + ' ' + user_info['last'].title())
    print('Location:' + user_info['location'].title())