#创建一个简单类
class Dog():
    def __init__(self,name,age): #在初始化的时候，必须要有self参数
        self.name = name
        self.age = age
        
    def sit(self):
        print(self.name.title() + " is now sitting.") #小狗蹲下
        
    def roll_over(self):
        print(self.name.title() + " rolled over!") #小狗打滚


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
