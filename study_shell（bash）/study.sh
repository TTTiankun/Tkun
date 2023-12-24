#！/bin/bash

#变量的定义与使用

#定义变量 变量先定义后使用

#命名规则：字母数字下划线，不能以数字开头，不能使用bash关键字

str="hello world"
echo $str
#输出结果：hello world

#关于单双引号的区别
#单引号：原样输出，不会进行变量替换，不会进行转义
#双引号：会进行变量替换，会进行转义
#注意：双引号中的$()会进行命令替换，单引号中的$()会原样输出
date=`date` #命令替换 在esc下面的那个键
echo $date
#输出结果：eg ： 2019年 08月 22日 星期四 10:49:02 CST

#变量的只读属性
a=10
readonly a
a=20
echo $a
#输出结果：只读变量，不可修改

#接受用户输入
#read -p "提示信息" -t 5 -n 6 -s 变量名

read -p '请输入需要创建的文本的文件路径' filepath
sudo touch $filepath
echo '文件创建成功'
ls -l $filepath

# 条件判断语句
if [ -e "$filepath" ]; then #注意：if和[之间要有空格，]和;之间要有空格 -e是判断文件是否存在
    echo "文件存在"
elif [ -d "$filepath" ]; then #-d是判断目录是否存在
    echo "文本窜在"
else
    echo "文件不存在"
fi

#算数运算符
# + - * / % **
# +是加，-是减，*是乘，/是除，%是取余，**是乘方
#注意：乘号*前面必须加反斜杠\转义
#注意：算数运算符两边必须要有空格
a=10
b=20
val=`expr $a + $b` #注意：表达式和运算符之间要有空格 expr是表达式的意思
echo "a + b : $val"

#关系运算符
# -eq -ne -gt -lt -ge -le 
#-eq是等于，-ne是不等于，-gt是大于，-lt是小于，-ge是大于等于，-le是小于等于
#注意：关系运算符两边必须要有空格
a=10
b=20
if [ $a -eq $b ]
then
   echo "$a -eq $b : a 等于 b"
else
   echo "$a -eq $b: a 不等于 b"
fi #fi是if的倒过来 用来结束if语句的

#逻辑运算符
# ! -o -a
# !是非，-o是或，-a是与
#注意：逻辑运算符两边必须要有空格
a=10
b=20
if [ $a != $b ]
then
   echo "$a != $b : a 不等于 b"
else
   echo "$a != $b: a 等于 b"
fi

#字符串运算符
# = != -z -n str
# =是判断两个字符串是否相等，!=是判断两个字符串是否不等，-z是判断字符串长度是否为0，-n是判断字符串长度是否不为0，str是判断字符串是否为空
#注意：字符串运算符两边必须要有空格
a="abc"
b="efg"
if [ $a = $b ]
then
   echo "$a = $b : a 等于 b" #注意：echo后面的内容要用双引号括起来
else
   echo "$a = $b: a 不等于 b"
fi

#文件测试运算符
# -e -r -w -x -s -d -f -c -b
# -e是判断文件是否存在，-r是判断文件是否可读，-w是判断文件是否可写，-x是判断文件是否可执行，-s是判断文件是否为空（文件大小是否大于0），-d是判断文件是否为目录，-f是判断文件是否为普通文件，-c是判断文件是否为字符设备文件，-b是判断文件是否为块设备文件
#注意：文件测试运算符两边必须要有空格
file="/Users/zhengzhongsheng/Desktop/Shell/ShellStudy/study.sh"
if [ -r $file ]
then
   echo "文件可读"
else
   echo "文件不可读"
fi



