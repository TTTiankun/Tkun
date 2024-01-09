// 汉诺塔问题：
// 使用递归解决汉诺塔问题。给定三个柱子（A、B、C）和一堆盘子，要求将所有盘子从柱子 A 移动到柱子 C，规定每次只能移动一个盘子，并且大盘子不能放在小盘子上。

#include<stdio.h>

void hanluota(int a,char source,char auxiliary,char target){
    if(a == 1){
        printf("%c->%c ",source,target);
    }else{
        printf("%c->%c ",source,target);
        hanluota(a-1,auxiliary,source,target);
    }
}

int main(){
    int a = 0;
    scanf("%d",&a);
    hanluota(a,'A','B','C');
    return 0;
}