//C语言复习大纲！！！
#include<stdio.h>
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
    char str1[10];
    char str[10];

    scanf("%d",&a);//最常规
    scanf("%f",&b);//最常规
    scanf("%lf",&d);//最常规
    
    scanf("%c",&c);//最常规
    scanf("%s",str);//最常规
   

    printf("%d\n",a);
    printf("%f\n",b);
    printf("%lf\n",d);
    printf("%c\n",c);
    printf("%s\n",str);
    
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
    c = a / b;//除法
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


int main(){
    
    // printf("%d\n",digui(5));
    pointer_array();
    return 0;
}