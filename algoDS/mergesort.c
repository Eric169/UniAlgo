#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void Merge(int*a, int l, int m, int r, int* buff){
    int i, q, curr;
    for(i = l; i<=r; i++) buff[i] = a[i];
    for(curr = l, i = l, q = m+1; curr <= r; curr++){
        if(i > m)
            a[curr] = buff[q++];
        else if(q > r)
            a[curr] = buff[i++];
        else{
            if(buff[i] < buff[q])
                a[curr] = buff[i++];
            else
                a[curr] = buff[q++];
        }
    }
}

void MergeSort(int *a, int l, int r, int *buff){
    if(l < r){
        int m = (l+r)/2;
        MergeSort(a, l, m, buff);
        MergeSort(a, m+1, r, buff);
        Merge(a, l, m, r, buff);
    }
}

int compare(const void *a, const void *b){
    return (*((int*)a) - *((int*)b));
}

int compare_vec(const int *v1, const int *v2, int n)
{
    int i;
    for (i=0; i<n; i++) {
        if (v1[i] != v2[i])
            return i;
    }
    return -1;
}

int test(int *v, int n)
{
    int result;
    int *tmp = (int*)malloc(n * sizeof(*tmp)), *buff = (int*)malloc(n*sizeof(int));
    clock_t tstart, elapsed;
    int diff;

    memcpy(tmp, v, n*sizeof(*v));
    qsort(tmp, n, sizeof(*tmp), compare);
    tstart = clock();
    MergeSort(v, 0, n-1, buff);
    elapsed = clock() - tstart;
    diff = compare_vec(v, tmp, n);
    if (diff < 0) {
        printf("Test OK (%f seconds)\n", ((double)elapsed) / CLOCKS_PER_SEC);
        result = 1;
    } else {
        printf("Test FALLITO: v[%d]=%d, atteso=%d\n", diff, v[diff], tmp[diff]);
        result = 0;
    }
    free(buff);
    free(tmp);
    return result;
}

int main(){
    int n, i;
    int *a;
    srand(0);
    printf("N: ");
    scanf("%d", &n);
    a = (int*)malloc(n*sizeof(int));
    for(i = 0; i<n; i++) {
        a[i] = rand();
    }
    test(a, n);
    free(a);
    return 0;
}