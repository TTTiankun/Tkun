一些关于书写Shell的基本规则

代码规范
#！/bin/bash 注释：告知系统当前这个脚本使用的是shell解释器

Shell的相关指令

文件名命名规范
文件名.sh 备注：.sh是Linux系统下bash shell的默认后缀

使用流程
1.创建.sh文件  使用touch/nano 命令创建.sh文件
2.编写shell代码
3.执行shell脚本  脚本必须要有执行权限 -x 

打开执行权限命令：
chmod +x test.sh


在运行脚本的时候一定要写成 test.sh 
它和其他二进制程序一样 如果只写成test.sh Linux系统会去PATH（环境变量）中宣召
这个时候只有usr/bin等在PATH之中