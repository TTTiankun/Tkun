# 导入 pizza 模块中的全部函数
#import pizza
#使用这种方式导入模块后，调用函数时就需要使用模块名和函数名的组合pizza.make_pizza()
#例子
# pizza.make_pizza(16,'pepperoni')

# 导入 pizza 模块中的全部函数（慎用，可能导致命名空间冲突）
#from pizza import *

# 从 pizza 模块中导入 make_pizza 函数
from pizza import make_pizza
# 从 pizza 模块中导入 build_profile 函数并指定别名 bp ！！！利用as给函数指定别名！！！
from pizza import build_profile as bp
make_pizza(16,'pepperoni') #用这种方式导入就可以直接调用函数了
make_pizza(20,'mushrooms', 'green peppers', 'extra cheese')
User = bp('albert', 'einstein', location = 'princeton', field = 'physics',job = 'scientist')
print(User)


#导入的模块必须和主程序位于同一个目录下，或者在sys.path包含的目录中
#sys.path是一个列表，包含解释器查找模块的位置
#下面的例子中，我们将模块存储在pizza.py所在的目录中，因此只需指定pizza就可以导入这个模块
#如果将这个文件存储在其他地方，需要将pizza.py所在的目录添加到sys.path中
# import sys
# sys.path.append('pizza.py所在的目录')
# import sys

# # 查看当前的sys.path
# print(sys.path)

# # 添加一个目录到sys.path（这仅在当前运行时生效，不会永久改变路径）
# sys.path.append("/path/to/your/directory")

# # 使用新的sys.path导入模块
# from your_module import some_function




#使用相对路径导入
#如果导入的模块位于导入模块的同级目录下，可以使用相对路径
#下面的例子中，模块pizza.py位于文件夹pizzaria中，因此主程序中的import语句如下所示
# from pizzaria import pizza
# from pizzaria.pizza import make_pizza

#使用绝对路径导入
# 完整的包路径
# from my_package import other_module
# from my_package.subpackage import some_function


