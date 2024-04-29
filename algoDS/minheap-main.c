#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minheap.h"

/*
gcc -std=c90 -Wall -Wpedantic minheap.c minheap-main.c -o minheap-main
./minheap-main /home/eric/Desktop/uniAlgo/algoDS/input/minheap.in
*/

int main( int argc, char *argv[] )
{
    char op;
    int n, val;
    double prio;
    MinHeap *h;
    FILE *filein = stdin;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s inputfile\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-") != 0) {
        filein = fopen(argv[1], "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    if (1 != fscanf(filein, "%d", &n)) {
        fprintf(stderr, "Missing size\n");
        return EXIT_FAILURE;
    }
    printf("CREATE %d\n", n);
    h = minheap_create(n);
    while (1 == fscanf(filein, " %c", &op)) {
        switch (op) {
        case '+': /* insert */
            fscanf(filein, "%d %lf", &val, &prio);
            printf("INSERT %d %f\n", val, prio);
            minheap_insert(h, val, prio);
            break;
        case '-': /* delete min */
            printf("DELETE_MIN\n");
            minheap_delete_min(h);
            break;
        case '?': /* get min */
            val = minheap_min(h);
            printf("MIN = %d\n", val);
            break;
        case 'c': /* change prio */
            fscanf(filein, "%d %lf", &val, &prio);
            printf("CHANGE_PRIO %d %f\n", val, prio);
            minheap_change_prio(h, val, prio);
            break;
        case 's': /* get n of elements */
            printf("N = %d\n", minheap_get_n(h));
            break;
        case 'p': /* print */
            minheap_print(h);
            break;
        default:
            printf("Unknown command %c\n", op);
            return EXIT_FAILURE;
        }
    }

    minheap_destroy(h);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}