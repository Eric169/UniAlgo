#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

const char errorMessage[] = "Non e' stato inserito un valore valido\n";

struct Array
{
    int size;
    int* data;
};

bool validInput(int* var, char message[]){
    printf("%s",message);
    if(scanf("%d", var) != 1){
        printf("%s",errorMessage);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }
    return 1;
}

int cmp(const void* a, const void* b){
    return ( *(int*)a - *(int*)b );
}

struct Array intersection(struct Array a, struct Array b, bool repeated){
    int currSize = 0;
    struct Array res;
    res.data = (int*) malloc(0);
    for(int i=0,j=0; i < a.size && j < b.size;){
        if(a.data[i] == b.data[j]){
            if(repeated || currSize == 0 || a.data[i] != res.data[currSize-1]){
                currSize++;
                res.data = (int*)realloc(res.data, currSize*sizeof(int));
                res.data[currSize-1] = a.data[i];
            }
            i++;j++;
        }
        else if(a.data[i] < b.data[j]) i++;
        else j++;
    }
    res.size = currSize;
    return res;
}

struct Array unione(struct Array a, struct Array b){
    struct Array res;
    res.size = a.size + b.size;
    res.data = (int*)malloc(res.size*sizeof(int));
    for(int i = 0; i<a.size; i++) res.data[i] = a.data[i];
    for(int i = 0; i<b.size; i++) res.data[i+a.size] = b.data[i];
    return res;
}


void printVector(struct Array v){
    for(int i = 0; i<v.size; i++) printf("%d ", v.data[i]);
    printf("\n");
}

int main(){
    srand((unsigned int)time(NULL));
    struct Array a;
    struct Array b;
    bool valid;
    do{
        valid = validInput(&a.size, "Lunghezza del primo vettore: ");
        if(valid && a.size < 1){
            printf(errorMessage);
            valid = 0;
        }
    }while(!valid);
    do{
        valid = validInput(&b.size, "Lunghezza del secondo vettore: ");
        if(valid && (b.size < 1 || b.size==a.size)){
            printf(errorMessage);
            valid = 0;
        }
    }while(!valid);
    
    a.data = (int*)malloc(a.size*sizeof(int));
    b.data = (int*)malloc(b.size*sizeof(int));
    int random = 0;
    do{
        valid = validInput(&random, "Vuoi riempire il primo vettore con valori random? si[1] no[0]\n");
        if(valid && random != 0 && random != 1){
            printf(errorMessage);
            valid = 0;
        }
    }while(!valid);
    if(random){
        printf("Valori generati:\n");
        for(int i = 0; i<a.size; i++){
            a.data[i] = rand();
            printf("%d ", a.data[i]);
        }
        printf("\n");
    }
    else{
        for(int i = 0; i<a.size; i++){
            int value;
            do{
                printf("%d ", i);
                valid = validInput(&value, "valore: ");
                
            }while(!valid);
            a.data[i] = value;
        }
    }
    do{
        valid = validInput(&random, "Vuoi riempire il secondo vettore con valori random? si[1] no[0]\n");
        if(valid && random != 0 && random != 1){
            printf(errorMessage);
            valid = 0;
        }
    }while(!valid);
    if(random){
        printf("Valori generati:\n");
        for(int i = 0; i<b.size; i++){
            b.data[i] = rand();
            printf("%d ", b.data[i]);
        }
        printf("\n");
    }
    else
        for(int i = 0; i<b.size; i++){
            int value;
            do{
                printf("%d ", i);
                valid = validInput(&value, "valore: ");
                
            }while(!valid);
            b.data[i] = value;
        }

    printf("Dimensione del primo vettore in bytes = %ld\n", a.size*sizeof(int));
    printf("Indice : Indirizzo\n");
    for(int i = 0; i<a.size; i++){
        printf("%d : %p\n", i, (void*)&a.data[i]);
    }
    printf("Dimensione del secondo vettore in bytes = %ld\n", b.size*sizeof(int));
    printf("Indice : Indirizzo\n");
    for(int i = 0; i<b.size; i++){
        printf("%d : %p\n", i, (void*)&b.data[i]);
    }

    struct Array united = unione(a,b);
    printf("Unione tra i 2 vettori\n");
    printVector(united);
    printf("Dimensione del vettore unione in bytes = %ld\n", united.size*sizeof(int));
    printf("Indice : Indirizzo\n");
    for(int i = 0; i<united.size; i++){
        printf("%d : %p\n", i, (void*)&united.data[i]);
    }
    //per fare l'intersezione li ordino cosi la complessita diventa O(nlogn)
    //si può fare anche in O(n) con hashing
    qsort(a.data, a.size, sizeof(int), cmp);
    qsort(b.data, b.size, sizeof(int), cmp);
    struct Array interUnique = intersection(a, b, 0);
    struct Array interRepeated = intersection(a, b, 1);

    printf("Intersezione con elementi univoci\n");
    printVector(interUnique);
    printf("Dimensione del vettore intersezione univoco in bytes = %ld\n", interUnique.size*sizeof(int));
    printf("Indice : Indirizzo\n");
    for(int i = 0; i<interUnique.size; i++){
        printf("%d : %p\n", i, (void*)&interUnique.data[i]);
    }
    printf("Intersezione con elementi ripetuti\n");
    printVector(interRepeated);
    printf("Dimensione del vettore intersezione con ripetizione in bytes = %ld\n", interRepeated.size*sizeof(int));
    printf("Indice : Indirizzo\n");
    for(int i = 0; i<interRepeated.size; i++){
        printf("%d : %p\n", i, (void*)&interRepeated.data[i]);
    }
    return 0;
}