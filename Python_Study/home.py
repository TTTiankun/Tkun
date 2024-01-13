from car import Car #从car.py中导入Car类 导入单个类
# from car import * #导入所有的类
Car_01 = Car('audi','a4',2016)
Car_01.get_fuel_type()

from car import Dog,ElectricCar #从car.py中导入多个类 #若一个类作为另一个类的属性，那么只需要导入含有属性的类就行
my_dog = Dog('willie',6)
my_dog.sit()
Ecar_01 = ElectricCar('tesla','model s',2016)
Ecar_01.distance.distance = 100
Ecar_01.get_distance_pro()
Ecar_01.distance.get_distance()