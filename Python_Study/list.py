#列表
bicycle = ['trek','cannondale','redline','specialized']
print(bicycle)

#访问列表元素
print(bicycle[0]) #索引从0开始

#修改列表元素
bicycle[0] = 'ducati'
print(bicycle)

#在列表中添加元素
bicycle.append('speed500') #在列表末尾添加元素
print(bicycle)

#在列表中插入元素
bicycle.insert(1,'honda') #在列表中插入元素
print(bicycle)

#在列表中删除元素
del bicycle[1] #删除列表中的元素
print(bicycle)

#使用方法pop()删除元素
popped_bicycle = bicycle.pop() #删除列表末尾的元素，并让你能够接着使用它
print(bicycle)
print(popped_bicycle)
#弹出列表中任何位置处的元素
first_owned = bicycle.pop(0) #弹出列表中任何位置处的元素
print('The first bicycle I owned was a ' + first_owned.title() + '.')
#根据值删除元素
bicycle.remove('redline') #根据值删除元素
print(bicycle)
print('\n')
#注意：remove()只删除第一个指定的值。如果要删除的值可能在列表中出现多次，就需要使用循环来判断是否删除了所有这样的值

#判断列表中是否包含特定的值
bicycle = ['trek','cannondale','redline','specialized']
print('trek' in bicycle) #判断列表中是否包含特定的值
print('ducati' in bicycle)
print('\n')

#组织列表
#使用方法sort()对列表进行永久性排序
cars = ['bmw','audi','toyota','subaru']
cars.sort() #按字母顺序排序
print(cars)
cars.sort(reverse=True) #按字母顺序相反的顺序排序   reverse=True是按字母顺序相反的顺序排序
print(cars)

#使用函数sorted()对列表进行临时排序
cars = ['bmw','audi','toyota','subaru']
print(sorted(cars)) #按字母顺序排序
print(cars)
print('\n')

#倒着打印列表
cars = ['bmw','audi','toyota','subaru']
cars.reverse() #永久性修改列表元素的排列顺序
print(cars)

#确定列表的长度
cars = ['bmw','audi','toyota','subaru']
print(len(cars)) #确定列表的长度
print('\n')
