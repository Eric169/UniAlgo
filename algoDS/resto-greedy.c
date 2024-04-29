#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int cmp(const void *a, const void *b){
    return *((int*)b) - *((int*)a);
}

/* Date n monete i cui valori sono memorizzati nell'array m[] (non
   necessariamente ordinato), restituisce il minimo numero di pezzi
   necessari per erogare un resto R. Se il resto non è erogabile
   restituisce -1. La funzione deve anche stampare quali monete usare,
   in caso di resto erogabile, oppure un opportuno messaggio che
   avvisa che il resto non è erogabile. */
int* resto(int R, int m[], int n)
{
    int i = 0, j = 1, *pezzi = (int*)calloc(n+1,sizeof(int)), sum = 0;
    qsort(m, n, sizeof(int), cmp);
    while(R > 0 && i < n){
        if(R - m[i] >= 0){
            R -= m[i];
            sum++;
            pezzi[j++] = m[i];
        }
        i++;
    }
    pezzi[0] = (R == 0 ? sum : -1);
    return pezzi;
}

int main( int argc, char *argv[] )
{
    int R, n, i;
    int *m, *res;
    FILE *filein = stdin;

    if (argc != 2) {
        fprintf(stderr, "Invocare il programma con: %s input_file\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-") != 0) {
        filein = fopen(argv[1], "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    fscanf(filein, "%d %d", &R, &n);
    m = (int*)malloc(n * sizeof(*m));
    assert(m != NULL);
    for (i=0; i<n; i++) {
        if (1 != fscanf(filein, "%d", &m[i])) {
            fprintf(stderr, "Errore durante la lettura della moneta %d di %d\n", i+1, n);
            return EXIT_FAILURE;
        }
    }

    res = resto(R, m, n);
    if(res[0] == -1) printf("RESTO NON EROGABILE\n");
    else{
        printf("Resto %d erogabile con %d monete:\n", R, res[0]);
        for(i = 1; i<=res[0]; i++){
            printf("%d ", res[i]);
        }
    }

    free(m);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
