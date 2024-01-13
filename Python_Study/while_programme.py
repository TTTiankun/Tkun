#示例
current_number = 1
while current_number <= 5:
    print(current_number)
    current_number +=1 #注意：Python中没有++和--运算符
    
#可以通过文字判断退出循环
prompt = '\nTell me something, and I will repeat it back to you:'  #prompt为提示之意
prompt += '\nEnter "quit" to end the program.'
message = ''
while message != 'quit': #!=表示不等于
    message = input(prompt)
    if message != 'quit':
        print(message)
        
#使用bool类型判断状态
active = True #设置一个标志，用于判断整个程序是否处于活动状态
while active:
    message = input(prompt)
    if message == 'quit':
        active = False #active设置为False，程序将停止运行
    else:
        print(message)

#使用break退出循环
prompt = '\nPlease enter the name of a city you have visited:'
prompt += '\n(Enter "quit" when you are finished.)'

while (True):
    city = input(prompt)
    if city == 'quit':
        break
    else:
        print('I\'d love to go to ' + city.title() + '!') 
        
#在循环中使用continue
current_number = 0
while current_number < 10:
    current_number += 1
    if (current_number % 2 == 0): #如果current_number是偶数，就执行continue语句，让python忽略余下的代码，并返回到循环的开头
        continue
    print(current_number)

#一定要避免无限循环！！！注意判断的条件！！！
#例子：
# while True:
#     print('This is a infinite loop!!!')

#在列表之间移动元素
#首先创建一个待验证用户列表
unconfirmed_users = ['alice', 'brian', 'candace']
#和一个用于存储已验证用户的空列表
confirmed_users = []
#验证每个用户，直到没有未验证用户为止
while unconfirmed_users:
    current_user = unconfirmed_users.pop() #pop()方法删除列表末尾的元素，并返回这个元素
    print('Verifying user: ' + current_user.title())
    confirmed_users.append(current_user) #append()方法将元素添加到列表末尾
#显示所有已验证的用户
print('\nThe following users have been confirmed:')
for users in confirmed_users:
    print(users.title())

#删除包含特定值的所有列表元素
pets = ['dog', 'cat', 'dog', 'goldfish', 'cat', 'rabbit', 'cat']
#如果使用remove（）
pets.remove('cat') #只删除第一个指定的值
print(pets)
pets=['dog', 'cat', 'dog', 'goldfish', 'cat', 'rabbit', 'cat']
#如果使用循环
while 'cat' in pets:
    pets.remove('cat') #循环将不断运行，直到列表中不再包含值'cat'
print(pets)

#使用用户输入来填充字典
responses = {} #创建一个空字典
#设置一个标志，指出调查是否继续
polling_active = True
while polling_active:
    #提示输入被调查者的名字和回答
    name = input('\nWhat is your name?')
    response = input('Which mountain would you like to climb someday?')
    #将答案存储在字典中
    responses[name] = response
    #看看是否还有人要参与调查
    repeat = input('Would you like to let another person respond?(yes/no)')
    if repeat == 'no':
        polling_active = False
#调查结束，显示结果
print('\n--- Poll Results ---')
for name, response in responses.items():
    print(name + ' would like to climb ' + response + '.')

        