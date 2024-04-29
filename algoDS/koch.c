#include <stdlib.h>
#include <stdio.h>
#include "libpsgraph.h"

/*gcc -std=c90 -Wall -Wpedantic libpsgraph.c koch.c -lm -o koch*/

#define ROT 60

double len = 0;

void Koch(int n, double x){
    len += x;
    if(n == 0){
        draw(x);
        return;
    }
    Koch(n-1, x/3);
    turn(-ROT);
    Koch(n-1, x/3);
    turn(2*ROT);
    Koch(n-1, x/3);
    turn(-ROT);
    Koch(n-1, x/3);
}

int main(){
    double x;
    int n;
    printf("Millimetri: ");
    scanf("%lf", &x);
    printf("N: ");
    scanf("%d", &n);
    start("koch.ps");
    Koch(n, x);
    #ifdef NEVE
    turn(2*ROT);
    Koch(n, x);
    turn(2*ROT);
    Koch(n, x);
    #endif
    end();
    /*printf("len: %f", len);*/
    return 0;
}