// 斐波那契数列：
// 实现一个递归函数，生成斐波那契数列的第 n 项。斐波那契数列的前几项是：0, 1, 1, 2, 3, 5, 8, 13, 21, ...

#include<stdio.h>

int feibo(int a){
    if(a == 1){
        return 0;
    }else if(a == 2){
        return 1;
    } else{
        return feibo(a-1)+feibo(a-2);
    }
}


int main(){
    int a = 0;
    scanf("%d",&a);
    int b = feibo(a);
    printf("%d",b);
    return 0;
}