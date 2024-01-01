#!/bin/bash/

# 1. 常规
docker run -d #希望容器在后台运行
docker run -it #希望容器在后台运行，并且打开容器的shell
docker --name TK #给容器命名
docker run -p 8080:80 #将容器的80端口映射到主机的8080端口
#为什么要映射端口？因为容器的端口是随机的，我们需要将容器的端口映射到主机的端口，这样我们才能访问到容器的服务

docker run -e TZ="Asia/Shanghai" #设置容器的时区
docker run -e TK_ROOT_PASSWORD="123456" #设置容器的root密码
TK #镜像的名字

# 2. 进阶
#常见命令
docker pull #拉取镜像
docker images #查看本地镜像
#images的参数
#-a 查看所有镜像
#-q 只显示镜像的id

docker rmi #删除镜像
docker build #构建镜像
docker save #保存镜像
docker load #加载镜像
docker push #推送镜像
docker run #运行容器
docker stop #停止容器
docker start #启动容器 (已经停止的容器) 和 docker run 有区别！！！
docker ps #查看容器的运行状态

docker ps --format"{{.ID}}\t{{.Names}}\t{{.Image}}\t{{.Status}}\t{{.Ports}}" #格式化输出 常用！
#意思是输出容器的id、容器的名字、容器的镜像、容器的状态、容器的端口

docker rm #删除容器 注意和rmi区分！！！
docker exec #进入容器
#exec的参数
#-i 保持标准输入打开
#-t 分配一个伪终端
#-d 分配一个守护进程
#-u 指定用户
#-it 交互式进入容器

docker logs #查看容器的日志
#logs的参数
# -f 跟踪日志输出

#例子：利用Nginx容器部署静态资源
docker run -d -p 80:80 -v html:/usr/share/nginx/html --name nginx nginx
# -d 后台运行 -p 端口映射 -v 数据卷挂载 --name 容器命名 镜像名字
#注意 一个端口只能映射到一个容器上，否则会报错！！！
#切换到root用户
sudo -u root bash
#如何查看当前用户
cat /etc/passwd | cut -d: -f1

#进入指定的卷
cd /var/lib/docker/volumes/html/_data

#查看目录下的文件
ls

#开始写入文件，修改静态资源，也可以上传文件在这个目录下
echo "hello world" > index.html
nano index.html

#在网络中，我们可以通过容器的ip地址访问容器的服务
#但是容器的ip地址是随机的，我们可以通过容器的名字访问容器的服务

#查看容器的ip地址
docker inspect nginx | grep IPAddress

#数据卷
#简介：数据卷是一个可供一个或多个容器使用的特殊目录，它绕过了UFS，可以提供很多有用的特性： 是容器内目录和宿主机内目录映射的桥梁
#数据卷可以在容器之间共享和重用
#对数据卷的修改会立马生效
#对数据卷的更新，不会影响镜像
#卷会一直存在，直到没有容器使用

docker volume #管理数据卷
#--help 查看帮助
#ls 列出数据卷
#prune 清理数据卷
#inspect [数据卷] 查看数据卷的详细信息



docker inspect #查看容器的详细信息

#本地目录挂在
#将本地的目录挂在到容器的目录下
#将本地的目录挂在到容器的目录下，可以实现容器和主机的文件共享

docker run -d -p 80:80 -v ./html:/usr/share/nginx/html --name nginx nginx
#意思是将当前目录下的html目录挂在到容器的/usr/share/nginx/html目录下
#注意： ./html 是相对路径，相对于当前目录 如果不加 ./ 或者 / 会被识别为数据卷
#在网络中访问的方法 示例：172.17.0.2/index.html(后面加上文件名或者目录名)


#创建一个镜像的步骤
#1. 创建一个Dockerfile文件
#2. 编写Dockerfile文件
#3. 构建镜像
#4. 运行镜像

#1.准备一个linux的运行环境
#2.安装JRE并配置环境变量
#3.拷贝jar包到linux环境
#4.编写运行脚本

#Dockerfile的常见指令
#FROM 指定基础镜像
#MAINTAINER 指定作者
#RUN 执行命令
#ENV 指定环境变量
#COPY 拷贝文件
#ADD 添加文件
#WORKDIR 指定工作目录
#EXPOSE 指定端口
#CMD 指定容器启动时执行的命令
#ENTRYPOINT 指定容器启动时执行的命令

#Ubuntu 22.04 基础镜像实例
#指定基础镜像
FROM ubuntu:22.04
#指定作者
MAINTAINER TK
#配置环境变量，JDK的安装目录，容器内的时区
ENV JAVA_HOME = /usr/local/jdk
#拷贝JDK和Java项目的包
COPY jdk-8u291-linux-x64.tar.gz /usr/local/
COPY demo.jar /usr/local/
#安装JDK
RUN tar -zxvf /usr/local/jdk-8u291-linux-x64.tar.gz -C /usr/local/
cmd /usr/local/jdk1.8.0_291 /usr/local/jdk
#配置环境变量
ENV PATH $JAVA_HOME/bin:$PATH
ENE JAVA_HOME /usr/local/jdk
#设置时区
ENV TZ="Asia/Shanghai"
#设置工作目录
WORKDIR /usr/local/
#暴露端口
EXPOSE 8080
#启动项目
ENTRYPOINT ["java","-jar","demo.jar"]

#构建自定义镜像
#过程命令
docker build -t demo:1.0 .
#-t 指定镜像的名字
#demo:1.0 镜像的名字和版本号
#.  Dockerfile所在的目录

#如何配置Java镜像的文件夹
#运行命令
#准备一个文件夹
mkdir demo
#进入文件夹
cd demo
#创建Dockerfile文件
touch Dockerfile
#创建jar包
touch demo.jar
#创建JDK安装包
touch jdk-8u291-linux-x64.tar.gz
#创建镜像
docker build -t demo:1.0 .
#意思是在当前目录下创建一个镜像，镜像的名字是demo，版本号是1.0
#运行镜像
docker run -d -p 8080:8080 demo:1.0

#网络
#网络的作用：容器之间的通信
#网络的类型：桥接网络、主机网络、无网络
#桥接网络：默认的网络类型，容器之间可以互相通信，容器和主机之间可以通信
#主机网络：容器和主机之间可以通信，容器之间不能通信
#无网络：容器和主机之间不能通信，容器之间也不能通信

#网络的常见命令
#docker network ls #查看网络
#docker network create #创建网络
#docker network inspect #查看网络的详细信息
#docker network connect #连接网络
#docker network disconnect #断开网络
#docker network rm #删除网络
#docker network prune #清理未使用的网络

#如何建立两个容器之间的通信
#1. 创建一个桥接网络
docker network create --driver bridge my-bridge
#含义是创建一个桥接网络，网络的名字是my-bridge --driver bridge 指定网络的类型是桥接网络
#2. 连接容器到网络
docker network connect my-bridge nginx
#意思是将nginx容器连接到my-bridge网络上
#3.再连接一个容器到网络
docker network connect my-bridge nginx2
#意思是将nginx2容器连接到my-bridge网络上
#4.在创建一个容器时，连接到网络
docker run -d -p 8080:80 --name nginx3 --network my-bridge nginx
#意思是创建一个容器，容器的名字是nginx3，容器的端口是8080，容器的网络是my-bridge，容器的镜像是nginx
#进入容器
docker exec -it nginx3 bash
#退出容器
exit
