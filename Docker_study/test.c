#include <stdio.h>
#include <string.h>


void insertc(char* str, char c, int n) {
    int len = strlen(str);

    
 
    
    for (int i = len; i >= n; i--) {
        str[i] = str[i - 1];
    }
    str[n - 1] = c;
}

int main() {
    char str[100]; 
    char c;
    int n;

   
    scanf("%s", str);


    scanf(" %c", &c); 

 
    scanf("%d", &n);

 
    insertc(str, c, n);

    printf(" %s\n", str);

    return 0;
}
