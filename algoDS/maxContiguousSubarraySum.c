/*gcc -Wall -Wpedantic -std=c90 nome_src nome_exe*/

#include <stdlib.h>
#include <stdio.h>

#define INF 1000000000


/*max contiguous subarray sum*/
int solve(int *a, int n){
    int currSum = 0, bestSum = -INF, i;
    for(i = 0; i<n; i++){
        currSum += a[i];
        bestSum = (currSum > bestSum) ? currSum : bestSum;
        if(currSum < 0) currSum = 0;
    }
    return bestSum;
}

int main(){
    int a[11] = {3,-5,10,2,-3,1,4,-8,7,-6,-1};
    printf("%d", solve(a, 11));
    return 0;
}