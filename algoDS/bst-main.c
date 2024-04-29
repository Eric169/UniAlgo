#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bst.h"

int randab(int a, int b)
{
    return a + rand() % (b-a+1);
}

void inputgen( int nops )
{
    const int PROB_INS = 44;
    const int PROB_DEL = 24;
    const int PROB_SEA = 20;
    const int PROB_HEI = 5;
    const int PROB_SIZ = 5;
    int i;

    assert(PROB_INS + PROB_DEL + PROB_SEA + PROB_HEI + PROB_SIZ <= 100);
    srand(nops);
    for (i=0; i<nops; i++) {
        const int coin = randab(0, 99);
        const int val = randab(0, 99);
        if (coin < PROB_INS) {
            printf("+ %d\n", val);
        } else if (coin < PROB_INS + PROB_DEL) {
            printf("- %d\n", val);
        } else if (coin < PROB_INS + PROB_DEL + PROB_SEA) {
            printf("? %d\n", val);
        } else if (coin < PROB_INS + PROB_DEL + PROB_SEA + PROB_HEI) {
            printf("h\n");
        } else if (coin < PROB_INS + PROB_DEL + PROB_SEA + PROB_HEI + PROB_SIZ) {
            printf("s\n");
        } else {
            printf("p\n");
        }
    }
    printf("s\n");
}

#ifndef BALANCED
#ifndef BALANCE
/* Nota: il main assume che BSTKey sia il tipo "int" */
int main( int argc, char *argv[] )
{
    char op;
    BSTKey k;
    BST *T;
    BSTNode *n;
    FILE *filein = stdin;
    int retval;

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "inputgen") == 0) {
        inputgen(atoi(argv[2]));
        return EXIT_SUCCESS;
    }

    if (strcmp(argv[1], "-") != 0) {
        filein = fopen(argv[1], "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    T = bst_create();

    while (1 == fscanf(filein, " %c", &op)) {
        switch (op) {
        case '+': /* insert */
            fscanf(filein, "%d", &k);
            printf("bst_insert(T, %d) = ", k);
            retval = bst_insert(T, k);
            if (retval) {
                printf("OK\n");
            } else {
                printf("ALREADY PRESENT\n");
            }
            break;
        case '-': /* delete */
            fscanf(filein, "%d", &k);
            printf("bst_delete(T, %d) = ", k);
            n = bst_search(T, k);
            if (n) {
                bst_delete(T, n);
                printf("OK\n");
            } else {
                printf("NOT FOUND\n");
            }
            break;
        case '?': /* search */
            fscanf(filein, "%d", &k);
            printf("bst_search(T, %d) = ", k);
            n = bst_search(T, k);
            if (n != NULL) {
                printf("FOUND\n");
            } else {
                printf("NOT FOUND\n");
            }
            break;
        case 'h': /* height */
            printf("bst_height(T) = %d\n", bst_height(T));
            break;
        case 's': /* size */
            printf("bst_size(T) = %d\n", bst_size(T));
            break;
        case 'p': /* print */
            /*bst_print(T);*/
            bst_pretty_print(T);
            break;
        default:
            printf("Unknown command %c\n", op);
            exit(EXIT_FAILURE);
        }
    }

    bst_destroy(T);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
#endif
#endif

#ifdef BALANCED
int main(){
    int n = 1<<25, i;
    BST *T;
    BSTKey *keys = (BSTKey*)malloc(n*sizeof(BSTKey));
    for(i = 1; i<=n; i++) keys[i-1] = i;
    T = create_balanced(keys, n);
    /*bst_pretty_print(T);*/
    printf("bst_height(T) = %d\n", bst_height(T));
    
    return EXIT_SUCCESS;
}
#endif

#ifdef BALANCE
#include <math.h>
#include <time.h>
#define MANY 1000
#define INC 100
#define START 1000
#define END 1000
#define ALFA 4.311
#define BETA 1.953

int main(){
    /*
    int n = 10, i;
    BST *T = bst_create();
    for(i = 0; i<n; i++){
        bst_insert(T, rand()%50);
    }
    balance(T);
    bst_pretty_print(T);
    printf("bst_height(T) = %d\n", bst_height(T));
    */

    int n, i, j;
    double h, expected;
    BST *T;
    srand(time(NULL));
    for(n = START; n <= END; n+=INC){
        h = 0;
        for(j = 0; j<MANY; j++){
            T = bst_create();
            for(i = 0; i<n; i++){
                bst_insert(T, rand());
            }
            /*balance(T);*/
            h += bst_height(T);
            bst_destroy(T);
        }
        expected = ALFA*log(n) - BETA*log(log(n));
        printf("n = %d expected = %.8f height = %.8f\n\n", n, expected, h/MANY);
    }

    return EXIT_SUCCESS;
}
#endif