// 计算阶乘：
// 编写一个递归函数，计算给定正整数的阶乘。例如，5 的阶乘是 5 × 4 × 3 × 2 × 1。

#include<stdio.h>

int recursion(int a){
    if(a == 1){
        return 1;
    }else{
        return a*recursion(a-1);
    }
}

int main(){
    int a = 3;
    int b = 0;
    printf("%d\n",a);
    b = recursion(a);
    printf("%d",b);
    return 0;
}