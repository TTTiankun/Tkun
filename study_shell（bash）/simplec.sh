#!/bin/bash

#常用的一些Linux命令

#ls命令
#ls 显示文件或目录
#用法：ls [选项] [文件或目录]
#ls -l 显示文件的详细信息
#ls -a 显示所有文件，包括隐藏文件

#cd命令
#cd 切换目录
#用法：cd [目录]
#cd ~ 返回用户主目录
#cd - 返回上次所在的目录
#cd .. 返回上一级目录
#cd . 返回当前目录

#pwd命令
#pwd 显示当前所在的目录
#用法：pwd [选项]
#pwd -P 显示出确切的路径，而不是使用符号链接
#pwd -L 如果当前目录是一个符号链接，则显示符号链接所指向的目录
#pwd -W 显示当前工作的目录，而不是完整的路径

#mkdir命令
#mkdir 创建目录
#用法：mkdir [选项] [目录]
#mkdir -p 创建多级目录

#touch命令
#touch 创建空文件
#用法：touch [选项] [文件]
#touch -t 修改文件的时间戳
#touch -a 修改文件的访问时间
#touch -m 修改文件的修改时间

#cat命令
#cat 查看文件内容
#用法：cat [选项] [文件]
#cat -n 查看文件内容并显示行号
#cat -b 查看文件内容并显示行号，不显示空行
#cat -s 查看文件内容，多个空行合并为一行
#cat -A 查看文件内容，显示特殊字符
#cat -T 查看文件内容，显示制表符
#cat -E 查看文件内容，显示结尾的$

#more命令
#more 分页显示文件内容
#用法：more [选项] [文件]
#more -d 分页显示文件内容，显示百分比
#more -c 分页显示文件内容，显示行数
#more -f 分页显示文件内容，显示文件名和行数
#more -p 分页显示文件内容，显示文件名和百分比
#more -s 分页显示文件内容，合并多个空行为一行
#more -u 分页显示文件内容，显示特殊字符
#more -l 分页显示文件内容，忽略换行符
#more -num 分页显示文件内容，每页显示num行

#cp命令
#cp 复制文件
#用法：cp [选项] [源文件] [目标文件]
#cp -r 复制目录
#cp -p 复制文件，保留文件属性
#cp -d 复制文件，如果是链接文件则复制链接属性
#cp -a 复制文件，保留文件属性，如果是链接文件则复制链接属性

#mv命令
#mv 移动文件
#用法：mv [选项] [源文件] [目标文件]
#mv -f 移动文件，不提示
#mv -i 移动文件，提示
#mv -u 移动文件，目标文件不存在或源文件比目标文件新才移动
#mv -n 移动文件，目标文件不存在才移动
#mv -b 移动文件，如果目标文件存在则备份
#mv -S 移动文件，如果目标文件存在则备份，备份文件的后缀为S
#mv -T 移动文件，如果目标文件是目录则移动到目标目录，否则移动并重命名

#rm命令
#rm 删除文件
#用法：rm [选项] [文件]
#rm -f 删除文件，不提示
#rm -i 删除文件，提示
#rm -r 删除目录
#rm -rf 删除目录，不提示
#rm -ri 删除目录，提示

#which命令
#which 查找命令的绝对路径
#用法：which [选项] [命令]
#which -a 查找所有命令的绝对路径

#find命令
#find 查找文件
#用法：find [路径] [选项] [表达式]
#!!!!!!
#find *test 查找当前目录下以test结尾的文件
#find test* 查找当前目录下以test开头的文件
#find *test* 查找当前目录下包含test的文件
#!!!!!!
#find -name 查找文件，按照文件名查找
#find -iname 查找文件，按照文件名查找，忽略大小写
#find -user 查找文件，按照文件属主查找
#find -nouser 查找文件，查找无属主的文件
#find -group 查找文件，按照文件属组查找

#grep命令
#grep 查找文件内容
#用法：grep [选项] [表达式] [文件]
#示例：grep "hello world" test.txt 查找test.txt文件中包含hello world的行
#grep -c 查找文件内容，显示匹配的行数
#grep -n 查找文件内容，显示匹配的行数和行号
#grep -v 查找文件内容，显示不匹配的行
#grep -i 查找文件内容，忽略大小写
#grep -r 查找文件内容，递归查找
#grep -w 查找文件内容，匹配整个单词
#grep -l 查找文件内容，显示匹配的文件名

#wc命令
#wc 统计文件的行数、单词数、字节数
#用法：wc [选项] [文件]
#wc -l 统计文件的行数
#wc -w 统计文件的单词数
#wc -c 统计文件的字节数
#wc -m 统计文件的字符数
#wc -L 统计文件的最长行的长度

#管道符
#| 管道符，将前一个命令的输出作为后一个命令的输入
#用法：命令1 | 命令2
#ls -l | grep test* 查找当前目录下以test开头的文件

#echo命令
#echo 输出内容
#用法：echo [选项] [内容]
#echo -e 输出内容，支持转义字符
#echo -n 输出内容，不换行

#printf命令
#printf 输出内容
#用法：printf [格式] [内容]
#printf "%s\n" "hello world"

#tail命令
#tail 查看文件的最后几行
#用法：tail [选项] [文件]
#tail -n 查看文件的最后几行
#tail -f 查看文件的最后几行，实时更新

#重定向符
#> 重定向符，将命令的输出重定向到文件中
#用法：命令 > 文件
#echo "hello world" > test.txt 将hello world写入到test.txt文件中
#>> 重定向符，将命令的输出追加到文件中
#用法：命令 >> 文件
#echo "hello world" >> test.txt 将hello world追加到test.txt文件中
#< 重定向符，将文件的内容作为命令的输入
#用法：命令 < 文件
#cat < test.txt 将test.txt文件的内容作为cat命令的输入
#<< 重定向符，将命令的输入作为文件的内容
#用法：命令 << 文件
#cat << test.txt 将cat命令的输入作为test.txt文件的内容

#chmod命令
#chmod 修改文件的权限
#用法：chmod [选项] [权限] [文件]
#chmod u+x 修改文件的权限，给文件的属主增加可执行权限
#chmod u-x 修改文件的权限，给文件的属主删除可执行权限
#chmod u=r 修改文件的权限，给文件的属主设置只读权限
#chmod u=rw 修改文件的权限，给文件的属主设置读写权限
#chmod u=rwx 修改文件的权限，给文件的属主设置读写可执行权限
#chmod u=rwx,g=r 修改文件的权限，给文件的属主设置读写可执行权限，给文件的属组设置只读权限
#chmod u=rwx,g=r,o=r 修改文件的权限，给文件的属主设置读写可执行权限，给文件的属组设置只读权限，给其他用户设置只读权限
#chmod 777 修改文件的权限，给文件的属主、属组、其他用户设置读写可执行权限
#chmod -R 777 修改文件的权限，给文件的属主、属组、其他用户设置读写可执行权限，递归修改
#字母权限：r=读，w=写，x=执行
#数字权限：r=4，w=2，x=1
#rwx=4+2+1=7
#rw-=4+2=6

#chown命令
#chown 修改文件的属主
#用法：chown [选项] [属主] [文件]
#chown root test.txt 将test.txt文件的属主修改为root

#快捷键
#ctrl+c 终止当前命令
#ctrl+d 退出当前终端
#ctrl+l 清屏
#ctrl+a 光标移动到行首
#ctrl+e 光标移动到行尾
#ctrl+u 删除光标之前的内容
#ctrl+k 删除光标之后的内容
#ctrl+r 搜索历史命令
#ctrl+z 将当前命令放到后台运行
#ctrl+s 暂停当前终端
#ctrl+q 恢复当前终端

#history命令
#history 查看历史命令
#用法：history [选项]
#history -c 清空历史命令

#系统环境配置程序

#apt命令
#apt 安装软件
#用法：apt [选项] [软件]
#apt install 安装软件
#apt remove 卸载软件
#apt update 更新软件源
#apt upgrade 更新软件
#apt search 搜索软件
#apt show 查看软件信息
#apt list 查看软件列表
#apt autoremove 自动删除不需要的软件包
#apt clean 清理软件缓存
#apt autoclean 自动清理软件缓存

#dpkg命令
#dpkg 安装软件
#用法：dpkg [选项] [软件]
#dpkg -i 安装软件
#dpkg -r 卸载软件
#dpkg -l 查看软件列表
#dpkg -L 查看软件安装的位置
#dpkg -S 查看软件的安装位置
#dpkg -s 查看软件的详细信息

#pip命令
#pip 安装Python包
#用法：pip [选项] [包]
#pip install 安装Python包
#pip uninstall 卸载Python包
#pip search 搜索Python包
#pip show 查看Python包信息
#pip list 查看Python包列表
#pip freeze 查看Python包列表，包含版本号
#pip install -r 安装Python包，从文件中读取包名

#date命令
#date 显示当前时间
#用法：date [选项]
#date -s 设置当前时间
#date -d 显示指定时间
#date -r 显示指定文件的时间
#格式化输出
#date +%Y 显示当前年份
#date +%y 显示当前年份的后两位
#date +%m 显示当前月份
#date +%d 显示当前日期
#date +%H 显示当前小时
#date +%M 显示当前分钟
#date +%S 显示当前秒数
#date +%s 显示当前时间戳
#date +%A 显示当前星期
#date +%a 显示当前星期的缩写
#date +%B 显示当前月份
#date +%b 显示当前月份的缩写
#date +%j 显示当前年份的第几天
#date +%U 显示当前年份的第几周
#date +%W 显示当前年份的第几周
#date +%w 显示当前星期几
#date +%Z 显示当前时区
#date +%z 显示当前时区的偏移量
#date +%c 显示当前日期和时间
#date +%x 显示当前日期
#示例：date "+%Y-%m-%d %H:%M:%S" 输出结果：2020-01-01 00:00:00
#示例：date "+%Y-%m-%d %H:%M:%S" -d "1 days ago" 输出结果：2019-12-31 00:00:00

#ifconfig命令
#ifconfig 查看网络信息
#用法：ifconfig [选项] [网络设备]
#ifconfig -a 查看所有网络设备的信息
#ifconfig -s 查看所有网络设备的信息，简洁显示
#ifconfig 网络设备 up 启动网络设备
#ifconfig 网络设备 down 关闭网络设备
#ifconfig 网络设备 ip地址 修改网络设备的ip地址
#ifconfig 网络设备 netmask 子网掩码 修改网络设备的子网掩码
#ifconfig 网络设备 broadcast 广播地址 修改网络设备的广播地址
#ifconfig 网络设备 mtu 最大传输单元 修改网络设备的最大传输单元
#ifconfig 网络设备 hw ether mac地址 修改网络设备的mac地址
#ifconfig 网络设备 multicast 开启组播
#ifconfig 网络设备 -multicast 关闭组播

#ping命令
#ping 测试网络连通性
#用法：ping [选项] [主机名或ip地址]
#ping -c 次数 指定ping的次数
#ping -i 秒数 指定ping的间隔时间
#ping -w 秒数 指定ping的超时时间
#ping -s 字节数 指定ping的数据包大小

#wget命令
#wget 下载文件
#用法：wget [选项] [文件]
#示例：wget https://www.baidu.com
#wget -c 断点续传
#wget -b 后台下载
#wget -t 次数 指定下载次数
#wget -i 文件 指定下载地址文件

#netstat命令
#netstat 查看网络状态
#用法：netstat [选项]
#netstat -a 查看所有网络状态
#netstat -t 查看tcp网络状态
#netstat -u 查看udp网络状态
#netstat -l 查看监听状态
#netstat -anp 查看所有网络状态，显示进程信息

#curl命令
#curl 发送网络请求
#用法：curl [选项] [url]
#curl -I 发送HEAD请求
#curl -X 发送指定请求
#curl -d 发送POST请求
#curl -F 发送POST请求，上传文件
#curl -H 发送请求头
#curl -A 发送User-Agent
#curl -e 发送Referer
#curl -b 发送Cookie
#curl -c 发送Cookie
#curl -u 发送Basic认证
#curl -x 发送代理请求
#curl -s 发送静默请求
#curl -o 发送请求，保存到文件

#ps命令
#ps 查看进程信息
#用法：ps [选项]
#ps -a 查看所有进程信息
#ps -u 查看指定用户的进程信息
#ps -x 查看后台进程信息
#ps -e 查看所有进程信息
#ps -f 查看全格式进程信息
#ps -l 查看长格式进程信息
#ps -aux 查看所有进程信息，显示详细信息
#ps -aux | grep 进程名 查看所有进程信息，显示详细信息，过滤进程名

#kill命令
#kill 终止进程
#用法：kill [选项] [进程号]
#kill -l 查看所有信号
#kill -9 终止进程，强制终止
#kill -15 终止进程，优雅终止

#top命令
#top 查看系统资源
#用法：top [选项]
#top -d 秒数 指定刷新时间
#top -n 次数 指定刷新次数
#top -p 进程号 指定进程号
#top -u 用户名 指定用户名
#top -i 指定忽略的进程号
#top -c 显示完整的命令
#top -b 以批处理模式运行
#top -H 显示线程信息
#top -M 显示内存信息

#iostat命令
#iostat 查看磁盘IO信息
#用法：iostat [选项] [秒数] [次数]
#iostat -a 查看所有信息
#iostat -x 查看扩展信息
#iostat -c 查看CPU信息
#iostat -d 查看磁盘信息
#iostat -m 查看内存信息
#iostat -n 查看网络信息
#iostat -p 查看进程信息
#iostat -t 查看时间信息

#sar命令
#sar 查看系统资源
#用法：sar [选项] [秒数] [次数]
#sar -u 查看CPU信息
#sar -d 查看磁盘信息
#sar -m 查看内存信息
#sar -n 查看网络信息
#sar -p 查看进程信息
#sar -t 查看时间信息

#zip命令
#zip 压缩文件
#用法：zip [选项] [压缩文件] [文件]
#示例：zip test.zip test.txt 将test.txt文件压缩为test.zip文件
#zip -r 压缩目录
#zip -m 压缩文件，压缩后删除源文件
#zip -d 压缩文件，删除压缩文件中的文件
#zip -u 压缩文件，更新压缩文件中的文件
#zip -c 压缩文件，显示压缩进度
#zip -q 压缩文件，静默压缩
#zip -l 压缩文件，显示压缩文件中的文件
#zip -v 压缩文件，显示压缩文件的详细信息
#zip -T 压缩文件，测试压缩文件的完整性
#zip -F 压缩文件，修复压缩文件
#zip -s 压缩文件，分割压缩文件
#zip -O 压缩文件，设置压缩文件的密码

#unzip命令
#unzip 解压文件
#用法：unzip [选项] [压缩文件]
#unzip -l 查看压缩文件中的文件
#unzip -v 查看压缩文件的详细信息
#unzip -t 测试压缩文件的完整性
#unzip -c 解压文件，显示解压进度
#unzip -q 解压文件，静默解压
#unzip -n 解压文件，不覆盖已存在的文件
#unzip -o 解压文件，覆盖已存在的文件
#unzip -d 解压文件，指定解压目录
#unzip -P 解压文件，解压加密的文件

#tar命令
#tar 归档文件
#用法：tar [选项] [归档文件] [文件]
#示例：tar -cvf test.tar test.txt 将test.txt文件归档为test.tar文件
#常见组合命令
#tar -zcvf test.tar.gz test.txt 将test.txt文件归档为test.tar.gz文件
#tar -cvf test.tar.bz2 test.txt 将test.txt文件归档为test.tar文件

#tar -c 归档文件，创建归档文件
#tar -x 归档文件，解压归档文件
#tar -t 归档文件，查看归档文件
#tar -r 归档文件，追加文件到归档文件
#tar -u 归档文件，更新归档文件
#tar -d 归档文件，删除归档文件中的文件
#tar -f 归档文件，指定归档文件
#tar -z 归档文件，使用gzip压缩
#tar -j 归档文件，使用bzip2压缩
#tar -v 归档文件，显示详细信息
#tar -l 归档文件，显示详细信息
#tar -k 归档文件，不覆盖已存在的文件
#tar -m 归档文件，保留文件的修改时间





