#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAXN 1500000

int Counting(int *nums, int size){
    int maxi = 0, mini = 1e9, i, *storage;
    for(i = 0; i<size; i++){
        if(nums[i] > maxi) maxi = nums[i];
        if(nums[i] < mini) mini = nums[i];
    }
    storage = (int*)malloc((maxi-mini+1)*sizeof(int));
    for(i = 0; i<size; i++){
        storage[nums[i]-mini]++;
    }
    for(i = 0; i<=maxi-mini; i++) if(storage[i] > 1) return i+mini;
    return -1;
}

int compare(const void* a, const void *b){
    return (*((int*)a) - *((int*)b));
}

int minNumberNotUnique(int *nums, int size, char counting){
    int *tmp = malloc(size*sizeof(int)), i, res;
    clock_t start = clock();
    memcpy(tmp, nums, size*sizeof(int));
    if(counting){
        res = Counting(tmp, size);
        printf("Test counting (%f seconds)\n", ((double)(clock() - start)) / CLOCKS_PER_SEC);
        return res;
    }
    qsort(tmp, size, sizeof(int), compare);
    for(i = 0; i<size-1; i++)
        if(tmp[i] == tmp[i+1]){
            res = tmp[i];
            break;
        }
    printf("Test qsort (%f seconds)\n", ((double)(clock() - start)) / CLOCKS_PER_SEC);
    return res;
}

void res(char* nomeFile){
    FILE *fin = fopen(nomeFile, "r");
    int num_tel, *nums = malloc(MAXN*sizeof(int)), size = 0;
    if (fin == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }
    while (1 == fscanf(fin, "%d", &num_tel)) {
        nums[size++] = num_tel;
    }
    fclose(fin);
    printf("%d\n", minNumberNotUnique(nums, size, 0));
    printf("%d\n", minNumberNotUnique(nums, size, 1));
    return;
}

int main(){
    char nomeFile[256];
    printf("Input: ");
    scanf("%s", nomeFile);
    res(nomeFile);
    return 0;
}