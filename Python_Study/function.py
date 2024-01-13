#示例
def greet_user():
    """显示简单的问候语"""
    print("Hello!")

greet_user()

#向函数传递信息
def greet_user(username): #username是形参
    """显示简单的问候语"""
    print("Hello, " + username.title() + "!")

username = input("Please enter your name: ")
greet_user(username) #username是实参

#实参与形参
#实参是调用函数时传递给函数的信息
#形参是函数完成其工作所需的一项信息
#上面的例子中，username是一个形参，因为它是函数完成其工作所需的信息之一
#在Python之中，对于不可变变量（例如整形和浮点型）传递进去的是值，而不是变量本身
#但是对于可变变量（例如列表和字典）传递进去的是变量的引用，而不是值
#下面的例子可以看出来
def add_numbers(a, b):
    a +=1
    b +=1   
a = 1
b = 2
add_numbers(a, b)
print(a)
print(b)
#这里也涉及到了函数重载的问题，在使用相同的函数名时，Python会自动识别出传入的参数类型，从而调用相应的函数
def add_numbers(numbers):
    numbers[0] +=1
    numbers[1] +=1
num_list = [1, 2]
add_numbers(num_list)
print(num_list[0])
print(num_list[1])

#返回值
#函数并非总是直接显示输出，相反，它可以处理一些数据，并返回一个或一组值
#简单的返回值
def get_formatted_name(first_name, last_name):
    """返回整洁的姓名"""
    full_name = first_name + ' ' + last_name
    return full_name.title() #return语句将值返回到函数调用行
musician = get_formatted_name('jimi', 'hendrix')
print(musician)

#让实参变成可选的
#有时候需要让实参变成可选的，这样使用函数的人就只需在必要时才提供额外的信息
#下面的例子中，我们让middle_name变成可选的，如果用户提供了middle_name，就将其包含到返回的字符串中
#否则，将只返回first_name和last_name
def get_formatted_name(first_name, last_name, middle_name = ''):
    """返回整洁的姓名"""
    if (middle_name):
        full_name = first_name + ' ' + middle_name + ' ' + last_name
    else:
        full_name = first_name + ' ' + last_name 
    return full_name.title()
musician = get_formatted_name('jimi', 'hendrix')
print(musician)
musician = get_formatted_name('john', 'hooker', 'lee')
print(musician)

#返回字典
#函数可返回任何类型的值，包括列表和字典等较复杂的数据结构
#下面的例子中，我们将存储在函数中的信息封装到一个字典中返回
def build_person(first_name, last_name):
    """返回一个字典，其中包含有关一个人的信息"""
    person = {'first': first_name, 'last': last_name}
    return person
musician = build_person('jimi', 'hendrix')
print(musician)

#传递列表
#可以向函数传递列表，这样函数就能直接访问其内容
#下面的例子中，我们将列表传递给一个名为show_magicians()的函数，这个函数打印列表中每个魔术师的名字
def show_magicians(magicians):
    """打印列表中每个魔术师的名字"""
    for magician in magicians:
        print(magician)
magicians = ['alice', 'david', 'carolina']
show_magicians(magicians)
#修改列表
#下面的例子中，我们将列表传递给一个名为make_great()的函数，这个函数将魔术师的名字都加上了“the Great”
def make_great(magicians):
    """在每个魔术师的名字中都加上the Great"""
    for i in range(len(magicians)):
        magicians[i] = 'the Great ' + magicians[i]
make_great(magicians)
show_magicians(magicians)
#禁止函数修改列表
#有时候需要禁止函数修改列表，可以向函数传递列表的副本而不是原件，这样函数所做的任何修改都只影响副本，而丝毫不影响原件
#下面的例子中，我们在函数调用中将列表名magicians[:]创建magicians_copy副本，并将副本存储到形参magicians中
#函数对列表所做的任何修改都只影响副本，而不影响原件
print('\n')
magicians = ['alice', 'david', 'carolina']
magicicans_copy = magicians[:]
make_great(magicicans_copy)
show_magicians(magicians)
show_magicians(magicicans_copy)

#传递任意数量的实参
#有时候，你预先不知道函数需要接受多少个实参，好在Python允许函数从调用语句中收集任意数量的实参
#下面的例子中，形参前面的*号让Python创建一个名为toppings的空元组，并将收到的所有值都封装到这个元组中
def make_pizza(*toppings):
    """打印顾客点的所有配料"""
    print(toppings)
make_pizza('pepperoni')
make_pizza('mushrooms', 'green peppers', 'extra cheese')

#结合使用位置实参和任意数量实参
#如果要让函数接受不同类型的实参，必须在函数定义中将接纳任意数量实参的形参放在最后
#Python先匹配位置实参和关键字实参，再将余下的实参都收集到最后一个形参中
#下面的例子中，Python将收到的第一个值存储在形参topping中，并将其他所有值都存储在元组toppings中
def make_pizza(size, *toppings):
    """打印顾客点的所有配料"""
    print('\nMaking a ' + str(size) + '-inch pizza with the following toppings:')
    for topping in toppings:
        print('- ' + topping)
make_pizza(16,'pepperoni')
make_pizza(20,'mushrooms', 'green peppers', 'extra cheese')

#使用任意数量的关键字实参
#有时候，需要接受任意数量的实参，但预先不知道传递给函数的会是什么样的信息
#下面的例子中，函数build_profile()接受名和姓，同时还接受任意数量的关键字实参
#我们将收到的所有关键字都封装到字典user_info中
def build_profile(first, last, **user_info):
    """创建一个字典，其中包含我们知道的有关用户的一切"""
    profile = {}
    profile['first_name'] = first
    profile['last_name'] = last 
    for key, value in user_info.items():
        profile[key] = value
    return profile
user_profile = build_profile('albert', 'einstein', location = 'princeton', field = 'physics',job = 'scientist')

#将函数存储在模块中
#函数的优点之一是，使用它们可将代码块与主程序分离
#通过给函数指定描述性名称，可让主程序容易理解得多
#你还可以更进一步，将函数存储在被称为模块的独立文件中，再将模块导入到主程序中
#import语句允许在当前运行的程序文件中使用模块中的代码
#下面的例子将在pizza.py和make_pizza.py中演示
