/*gcc -std=c90 -Wall -Wpedantic quicksort.c -o quicksort*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int cmpVec(int* a, int* b, int size){
    int i;
    for(i = 0; i<size; i++) if(a[i] != b[i]) return 0;
    return 1;
}

void swap(int *v, int i, int j){
    int tmp = v[j];
    v[j] = v[i];
    v[i] = tmp;
}

int partition(int *v, int n, int l, int r){
    int pivot = v[l], i = l-1, j = r+1;
    while(1){
        /*non mi è chiaro perchè do while ok e while no*/
        do i++; while(v[i] < pivot);
        do j--; while(v[j] > pivot);
        /*printf("%d %d %d %d %d\n", i, j, v[i], v[j], pivot);*/
        if(i >= j) return j;
        swap(v, i, j);
    }
    return -1;
}

void quicksort(int *v, int n, int l, int r){
    int m;
    if(l >= r || l < 0 || r < 0) return;
    m = partition(v, n, l, r);
    quicksort(v, n, l, m);
    quicksort(v, n, m+1, r);
}

int cmp(const void* a, const void* b){
    return ((*(int*)a)-(*(int*)b));
}

int main(){
    int n = 200000,i;
    int *v = malloc(sizeof(int)*n), *myQuick = malloc(sizeof(int)*n), *realQuick = malloc(sizeof(int)*n);
    clock_t start;
    srand(time(NULL));
    for(i = 0; i<n; i++){
        v[i] = rand()%20;
    }
    memcpy(myQuick, v, n*sizeof(int));
    memcpy(realQuick, v, n*sizeof(int));
    start = clock();
    quicksort(myQuick, n, 0, n-1);
    printf("Test myQuick (%f seconds)\n", ((double)(clock() - start)) / CLOCKS_PER_SEC);
    start = clock();
    qsort(realQuick, n, sizeof(int), cmp);
    printf("Test realQuick (%f seconds)\n", ((double)(clock() - start)) / CLOCKS_PER_SEC);
    if(cmpVec(myQuick, realQuick, n)) printf("SORT OK!\n");
    else printf("SORT MERDA\n");
    free(v);
    free(myQuick);
    free(realQuick);
    return 0;
}