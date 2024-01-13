//C语言复习大纲！！！
#include<stdio.h>
#include<stdlib.h>//标准库的头文件
#include<stdbool.h>//布尔型的头文件
#include<math.h>//数学库的头文件
#include<string.h>//字符串的头文件

//数据类型
void data(){
    int a =10;//整型
    float b =20.0;//单精度浮点型
    double d = 30.0;//双精度浮点型
    char c = 'a';//字符型
    char str[10] = "hello";//字符串
    bool k = true;//布尔型

    printf("%d\n",a);
    printf("%f\n",b);
    printf("%lf\n",d);
    printf("%c\n",c);
    printf("%s\n",str); 
    printf("%d\n",k); 
}

//数据类型转换
void datachange(){
    //隐式转换
    //字符型转换为整型
    char c = 'a';
    int a;
    a = c;
    printf("%d\n",a);
    //浮点型转换为整型
    double d = 3.14;
    int b;
    b = d;
    printf("%d\n",b);

    //显示转换
    //整型转换为字符型
    int e = 65;
    char f;
    f = (char)e;//强制将整型转换为字符型
    printf("%c\n",f);

    //整型转换为浮点型
    int g = 65;
    float h;
    h = (float)g;//强制将整型转换为浮点型
    printf("%f\n",h);

    //ASCII码
    /* A = 65 a = 97 中间有32个字符
      ASCII 有128个字符
    */
}

//数据输出
void dataout(){
    int a = 10;
    float b = 20.0;
    double d = 30.0;
    char c = 'a';
    char str[10] = "hello";

    printf("%d\n",a);//最常规
    printf("%04d\n",a);//输出4位整型，不足4位前面补0 （只有整型可以这样用）
    printf("%f\n",b);//最常规
    printf("%15.2f\n",b);//保留两位小数
    printf("%.2f\n",d);//保留两位小数
    printf("%3c\n",c);//最常规
    printf("%s\n",str);//最常规
    printf("%10s\n",str);//输出10个字符，不足10个前面补空格
    printf("%5.3s\n",str);//输出3个字符(不包括结束符)，不足3个输出全部，从左到右
}

//数据输入
void datain(){
    int a;
    float b;
    double d;
    char c;
    char k;
    char str2[10];
    char str1[10];
    char str[10];

    scanf("%d",&a);//最常规
    scanf("%f",&b);//最常规
    scanf("%lf",&d);//最常规
    
    scanf("%c",&c);//最常规
    scanf("%s",str);//最常规 读取一个字符串 以空格为结束符

    gets(str2);//最常规 读取一行字符串 以换行符为结束符 如果同时输入字符和字符串，那么scanf只能用来输入字符，gets用来输入字符串
    //原因
    /*
    当你使用 %s 格式指示符时，scanf 函数会读取字符串，但它会在字符串的末尾停止，留下一个换行符（\n）在输入缓冲区中。
    这是因为在输入字符串时，通常会按下 Enter 键，而 Enter 键产生一个换行符。

    接着，在代码的下一行使用 %c 格式指示符尝试读取一个字符。
    然而，由于上一个 scanf("%s", s); 留下的换行符仍然在输入缓冲区中，%c 会读取这个换行符，而不是用户实际输入的字符。
    */
   

    printf("%d\n",a);
    printf("%f\n",b);
    printf("%lf\n",d);
    printf("%c\n",c);
    printf("%s\n",str);
    printf("%s\n",str2);
    
}

//运算符
void calculate(){
    int a = 10;
    int b = 20;
    int c = 0;
    c = a + b;//加法
    printf("%d\n",c);
    c = a - b;//减法
    printf("%d\n",c);
    c = a * b;//乘法
    printf("%d\n",c);
    c = a / b;//除法 如果两个整形运算产生小数，那么会向下取整
    printf("%d\n",c);
    c = a % b;//取余
    printf("%d\n",c);
    
    //比较 返回bool值
    c = a > b;
    printf("%d\n",c);
    c = a < b;
    printf("%d\n",c);
    c = a == b;
    printf("%d\n",c);
    c = a != b;
    printf("%d\n",c);
    c = a >= b;
    printf("%d\n",c);
    c = a <= b;
    printf("%d\n",c);
    c = a && b;
    printf("%d\n",c);
    c = a || b;
    printf("%d\n",c);
    c = !a;
 
}

//递增递减
void addsub(){
    int a = 10;
    int c = 10;
    int d = 20;
    int b = 20;
    printf("%d\n",a++);
    //printf("%d\n",a);
    printf("%d\n",++c);
    printf("%d\n",b--);
    printf("%d\n",--d);
}

//数学库
void mathex(){
    int a = 10;
    int b = 2;
    int c = 0;
    c = abs(a);//绝对值
    printf("%d\n",c);
    c = pow(a,b);//a的b次方
    printf("%d\n",c);
    c = sqrt(a);//a的平方根
    printf("%d\n",c);
    c = exp(a);//e的a次方
    printf("%d\n",c);
    c = exp2(a);//2的a次方
    c = log2(a);//以2为底a的对数
    printf("%d\n",c);
    c = rand();//随机数
    printf("%d\n",c);
    c = rand()%100;//随机数 (0-99取值范围)
    printf("%d\n",c);
}

//if语句
void ifex(){
    int a = 10;
    int b = 20;
    
    if(a<b){
        printf("a<b\n");
    }

    if(a<b){
        printf("a<b\n");
    }else{  
        printf("a>b\n");
    }

    if(a>b){
        printf("a>b\n");
    }else if(a<b){
        printf("a<b\n");
    }
}

//switch语句
void switchex(){
    int a = 1;
    switch(a){
        case 1:
            printf("a=1\n");
            break;//结尾必须有break
        case 2:
            printf("a=2\n");
            break;
        case 3:
            printf("a=3\n");
            break;
        
        default:
            printf("a=10\n");
            break;
    }
}

//while语句
void whileex(){
    int a = 10;
    int b = 10;
   //先判断后执行
    while(a<10){
        printf("a=%d\n",a);
        a++;
    }
    printf("\n\n\n");
    
    //先执行后判断
    do {
        printf("b=%d\n",b);
        b++;
    }while(b<10);
}

//for语句
void forex(){
    
    for(int i=0;i<10;i++){
        printf("i=%d\n",i);
    }

    printf("\n\n\n");
    
    for(int i=0;i<10;i++){
        for(;i<5;i++){
            printf("i=%d",i);
        }
        printf("i=%d\n",i);
    }

    //死循环
    // for(;;){
    //     printf("hello\n");
    // }
}

//break语句
void breakex(){
    for(int i=0;i<10;i++){
        if(i==5){
            break;
        }
        printf("i=%d\n",i);
    }

    printf("\n\n\n");

    for(int i=0;i<5;i++){
        for(int j=0;j<10;j++){
            if(j==5){
                break;
            }
            printf("j=%d\n",j);
        }
        printf("a=%d\n",i);
    }
}

//continue语句
void continueex(){
    for(int i=0;i<10;i++){
        if(i==5){
            continue;
        }
        printf("i=%d\n",i);
    }

    printf("\n\n\n");

    for(int i=0;i<5;i++){
        for(int j=0;j<10;j++){
            if(j==5){
                continue;
            }
            printf("j=%d\n",j);
        }
        printf("a=%d\n",i);
    }
}

//goto语句
void gotoex(){
    for(int i=0;i<10;i++){
        if(i==5){
            goto flag;
        }
        printf("i=%d\n",i);
    }

    flag:
    printf("hello\n");
}

//递归
int digui(int n){
    
    if(n==1){
        return 1;
        
    }else{
        return n*digui(n-1); 
    }
    
}

//数组
void arrayex(){
    int a[10];
    int b[10] = {1,2,3,4,5,6,7,8,9,10};
    int c[] = {1,2,3,4,5};

    int d[2][3]={
        {1,2,3},
        {4,5,6}
    };

    int e[2][3]={1,2,3,4,5,6};

    //输出数组
    for(int i=0;i<10;i++){
        printf("b[%d]=%d\n",i,b[i]);
    }

    printf("\n\n\n");

    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            printf("d[%d][%d]=%d\n",i,j,d[i][j]);
        }
    }

    printf("\n\n\n");

    //输入数组
    for(int i=0;i<10;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<10;i++){
        printf("a[%d]=%d\n",i,a[i]);
    }
}

//字符串数组
void string_array(){
    char s1[100]="hello";
    printf("%s\n",s1);

    char s2[]=" world";
    printf("%s\n",s2);
//字符串数组的拼接
    strcat(s1,s2);//字符串拼接（把后面的连接到前面）
    printf("%s\n",s1);
//字符串数组的复制
    char s3[100];
    strcpy(s3,s1);//字符串复制（把后面的复制到前面）
    printf("%s\n",s3);
//初始化字符串数组
    char s4[]={'h','e','l','l','o','\0'};
    printf("%s\n",s4);
//字符串数组的复制
    char s5[10];
    for(int i=0;i!='\0';i++){
        s5[i]=s1[i];
    }
    printf("%s\n",s5);
//获取字符串数组的长度
    int len = strlen(s1);
    printf("%d\n",len);

     
}


//指针
void pointer(){
    int a =10;
    int *p = &a;//指针变量
    printf("%d\n",*p);//*p是指针变量p所指向的值
    //改变形参的值
    void test1(int a){
        a = 100;
    }
    test1(a);
    printf("%d\n",a);

    printf("\n\n\n");

    //改变实参的值
    void test2(int *p){
        *p = 100;
    }
    test2(p);
    printf("%d\n",a);
    
}

//指针数组
void pointer_array(){
    int a = 10;
    int b = 20;
    int c = 30;
    int *p[3] = {&a,&b,&c};//指针数组
    char str1[5]="hello";
    
    
    //一个数组的地址就是第一个元素的地址
    //一个数组中的元素的地址是连续的
    //数组的前一个和后一个元素的地址差值是一个数据类型的长度
    printf("%p\n",p[0]);//数组第一位的地址
    printf("%p\n",p[1]);//数组第二位的地址
    printf("%d\n",sizeof(int));//int类型的长度
    
    //更改地址
    for(int* j=p[0];j<=p[2];j++){
        
        printf("%d\n",*j);
        
    }

    printf("\n\n\n");
    
    //更改索引
    for(int i=0;i<3;i++){
        printf("%d\n",*p[i]);
    }
    //！！！
    //数组传参 传入的是数组的地址 只有字符串数组可以这样用
    void test(char *str1){
        for(int i=0;i<strlen(str1);i++){
            printf("%c\n",str1[i]);
        }
    }

    test(str1);
}

//计算闰年
//算法：能被4整除但不能被100整除的年份为闰年，或者能被400整除的年份为闰年
void leap_year(){
    int year;
    printf("请输入年份：");
    scanf("%d",&year);
    if(year%4==0&&year%100!=0||year%400==0){
        printf("%d是闰年\n",year);
    }else{
        printf("%d不是闰年\n",year);
    }
}

//计算质数
//算法：只能被1和它本身整除的数为质数
void prime_number(){
    int num;
    printf("请输入一个数：");
    scanf("%d",&num);
    int flag = 1;
    for(int i=2;i<num;i++){
        if(num%i==0){
            flag = 0;
            break;
        }
    }
    if(flag==1){
        printf("%d是质数\n",num);
    }else{
        printf("%d不是质数\n",num);
    }
}

//十进制转为十六进制
void ten_to_sixteen(){
    int num;
    printf("请输入一个十进制数：");
    scanf("%d",&num);
    int a[100];
    int i = 0;
    while(num!=0){
        a[i] = num%16;
        num = num/16;
        i++;
    }
    for(int j=i-1;j>=0;j--){
        if(a[j]>=10){
            printf("%c",a[j]-10+'A');
        }else{
            printf("%d",a[j]);
        }
    }
    printf("\n");
}

//十进制转为二进制
void ten_to_two(){
    int num;
    printf("输入一个十进制的数：");
    scanf("%d",&num);
    int a[100];
    int i = 0;
    for(i=0;num>0;i++){
        if(num%2==0){
            a[i]=0;
            num=num/2;
        }else{
            a[i]=1;
            num=num/2;
        }
    }

    for(int j = i-1;j>=0;j--){
        printf("%d",a[j]);
    }
    printf("\n");
}

//二进制转为十进制
void two_to_ten(){
    int num;
    printf("输入一个二进制的数：");
    scanf("%d",&num);
    int a[100];
    int i = 0;
    for(i=0;num>0;i++){
        a[i]=num%10;
        num=num/10;
    }
    int sum = 0;
    for(int j=0;j<i;j++){
        sum = sum + a[j]*pow(2,j);
    }
    printf("%d\n",sum);
}
//算法：从右往左取出每一位的数，然后乘以2的n次方，n为这个数的索引，然后相加

//十六进制转为十进制
void sixteen_to_ten(){
    char str[100];
    printf("输入一个十六进制的数：");
    scanf("%s",str);
    int len = strlen(str);
    int sum = 0;
    for(int i=0;i<len;i++){
        if(str[i]>='0'&&str[i]<='9'){
            sum = sum + (str[i]-'0')*pow(16,len-i-1);
        }else if(str[i]>='A'&&str[i]<='F'){
            sum = sum + (str[i]-'A'+10)*pow(16,len-i-1);
        }else if(str[i]>='a'&&str[i]<='f'){
            sum = sum + (str[i]-'a'+10)*pow(16,len-i-1);
        }
    }
    printf("%d\n",sum);
}
//算法：从左往右取出每一位的数，然后乘以16的n次方，n为这个数的索引，然后相加


int main(){
    
    // printf("%d\n",digui(5));
    pointer_array();
    return 0;
}