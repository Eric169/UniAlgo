#include<stdio.h>

int main(){
    int i = 7;
    while((i%2 != 1) || (i%3 != 1) || (i%4 != 1) || (i%5 != 1) || (i%6 != 1)) i+=7;
    printf("%d", i);
    return 0;
}