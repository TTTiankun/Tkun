#创建一个简单类
class Dog():
    def __init__(self,name,age): #在初始化的时候，必须要有self参数
        self.name = name
        self.age = age
        
    def sit(self):
        print(self.name.title() + " is now sitting.") #小狗蹲下
        
    def roll_over(self):
        print(self.name.title() + " rolled over!") #小狗打滚

dog_01 = Dog('willie',6)
dog_02 = Dog('lucy',3)
print("My dog's name is " + dog_01.name.title() + ".")
print("My dog is " + str(dog_01.age) + " years old.")
dog_01.sit()
dog_01.roll_over()

#可以在初始化的时候，给属性指定默认值
class Car():
    def __init__(self,make,model,year):
        self.make = make
        self.model = model
        self.year = year
        self.fuel = 95
        self._productor = 'China' #在Python之中没有私有属性，但是可以通过在属性前面加上两个下划线，让Python将属性设置为私有的
    def get_fuel_type(self):
        print(self.fuel)
    
    def get_descriptive_name(self):
        long_name = str(self.year) + ' ' + self.make + ' ' +self.model
        return long_name.title()
    
    def get_productor(self):
        print(self.productor)
    
    def change_productor(self,productor):
        self.productor = productor

car_01 = Car('audi','a4',2016)
# car_01._productor = 'Japan' 这两行代码会出现错误，因为productor是私有属性
# car_01.get_productor()
car_01.change_productor('Japan')
car_01.get_productor() #这样就可以修改私有属性了 因为是调用对象内的函数，所以可以修改私有属性

class distance():
    def _init_(self,distance):
        self.distance = distance
    
    def get_distance(self):
        print(self.distance)

#继承
#写一个电动汽车的类 Car是父类，ElectricCar是子类
class ElectricCar(Car):
    def __init__(self,make,model,year):
        super().__init__(make,model,year) #super()函数是一个特殊函数，帮助Python将父类和子类关联起来
        self.battery_size = 70
        self.distance = distance() #将类作为对象的属性
        
    
    def describe_battery(self):
        print("This car has a " + str(self.battery_size) + "-kWh battery.")
        
    def get_fuel_type(self):
        print("This car doesn't need a fuel tank!") #重写父类的方法
    
    def get_distance_pro(self):
        print("This car can run " + str(self.distance.distance) + "km!")
    
ecar_01 = ElectricCar('tesla','model s',2016)
ecar_01.describe_battery()
ecar_01.change_productor('USA')
ecar_01.get_productor() #继承父类的方法

#后期可以将实物用代码模拟出来，能够有更好的编程效率

#导入类
#接下来的代码将会在home.py和car.py中展现

#Python标准库
#Python标准库是一组模块，安装的Python都包含它
#下面的代码演示了如何使用标准库中的模块
from collections import OrderedDict

favouite_languages = OrderedDict() #创建一个空的有序字典 顺序是按照添加的顺序
favouite_languages['jen'] = 'python'
favouite_languages['sarah'] = 'c'
favouite_languages['edward'] = 'ruby'
favouite_languages['phil'] = 'python'
                                                      
for name,language in favouite_languages.items():
    print(name.title() + "'s favourite language is " + language.title() + ".")

favouite_languages_01 = {} #创建一个空的无序字典 好吧 没什么区别
favouite_languages_01['jen'] = 'python'
favouite_languages_01['sarah'] = 'c'
favouite_languages_01['edward'] = 'ruby'
favouite_languages_01['phil'] = 'python'

for name,language in favouite_languages_01.items():
    print(name.title() + "'s favourite language is " + language.title() + ".")
    





