// 反向输出字符串：
// 编写一个递归函数，以逆序输出给定字符串。

#include<stdio.h>
#include<string.h>

void recursion(int i,char *a){
    if(i == 0){
        printf("%c",a[i]);
    }else{
        printf("%c",a[i]);
        recursion(i-1,a);
    }
}


int return_string(char *a){
    int i = 0;
    i =strlen(a);
    recursion(i,a);
}

int main(){
    char a[100];
    gets(a);
    return_string(a);
    return 0;
}