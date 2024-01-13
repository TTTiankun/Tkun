#变量的命名规则 和c++差不多
#变量名必须是大小写英文、数字和_的组合，且不能用数字开头

#字符串
#字符串是以单引号'或双引号"括起来的任意文本
first_name = 'Michael'
last_name = 'Jordan'
print(first_name)
print(last_name)
#一些常见用法
#修改大小写
print(first_name.title())
#全部大写
print(first_name.upper())
#全部小写
print(first_name.lower())
#合并字符串
print(first_name + ' ' + last_name)
#使用制表符或换行符来添加空白
print('\t' + first_name) #\t是制表符
print('\n' + first_name) #\n是换行符
#删除空白
favorite_language = ' python '
print(favorite_language.rstrip()) #删除末尾空白
print(favorite_language.lstrip()) #删除开头空白
print(favorite_language.strip()) #删除两端空白
#在要使用单引号的时候，可以使用双引号括起来

#类似于C++的字符串，Python的字符串也可以通过索引值获取单个字符
First_word = first_name[0]
print('This is the first word from First name:' + ' ' + First_word)


#数字
#整数
age = 24
print(age)
message = 'Happy ' + str(age) + 'th Birthday!' #str()函数将非字符串值表示为字符串
print(message)
#浮点数
money = 0.1 + 0.2
print(money) #0.30000000000000004 原因是计算机无法精确表示无限循环小数 解决：使用函数round()让python将浮点数转换为小数点后指定位数的数字
print(round(money, 2)) #0.3 2表示保留小数点后两位
#Python将带小数点的数字都称为浮点数

#常见运算
#加减乘除
print('\n')
print(2 + 3)
print(3 - 2)
print(2 * 3)
print(3 / 2)
#乘方
print(3 ** 2)
#取模
print(3 % 2)

#Python之禅
print('\n')
import this