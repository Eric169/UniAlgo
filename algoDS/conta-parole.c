#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "hashtable.h"

#define WORDLEN 100
#define MAXSIZE 10000


/* Legge la prossima parola dal file `f` e la memorizza bel buffer `s`
   di lunghezza `WORDLEN`; `s` deve essere già stato allocato dal
   chiamante. Restituisce il numero di caratteri letti; 0 indica che
   si non è stato letto alcun carattere, cioè si è raggiunta la fine
   del file. */
int read_word(FILE *f, char *s)
{
    int c;
    int i = 0;
    while(isalpha(c = fgetc(f)))
      s[i++] = tolower(c);
    s[i] = '\0';
    return (c != EOF ? i : EOF);
}

int main( int argc, char *argv[] )
{
    FILE *filein = stdin;
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    char w[WORDLEN];
    int repeated = 0, total = 0, len;
    table = ht_create(MAXSIZE);

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
    /* TODO: una volta completata la funzione read_word(), questo
       ciclo si limita a leggere e stampare le parole lette man mano
       dal file. Lo si modifichi per inserire le parole lette in una
       tabella hash e al termine stampare il numero di elementi della
       tabella chiamando la funzione `ht_round()`. */
    
    while ((len = read_word(filein, w)) >= 0) {
        total += len > 0;
        repeated += (len > 0) ? !ht_insert(table, w, 0) : 0;
    }
    if (filein != stdin) fclose(filein);
    printf("Totali: %d, Ripetute: %d, Distinte: %d\n", total, repeated, total-repeated);
    return EXIT_SUCCESS;
}
