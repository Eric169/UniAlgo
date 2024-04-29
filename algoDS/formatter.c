#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

/* massima lunghezza di una parola */
#define WORDLEN 1024

/* Legge la prossima parola dal file `f` e la memorizza in `s`; il
   buffer `s` deve essere creato dal chiamante e avere capienza
   `WORDLEN`. Restituisce il numero di caratteri letti, oppure 0 se
   non è stata letta alcuna parola. */
int read_word(FILE *f, char *s)
{
    int i=0;
    int c;

    /* Salta gli eventuali spazi */
    do {
        c = fgetc(f);
    } while (c != EOF && isspace(c));
    /* Leggi la parola */
    while (c != EOF && !isspace(c)) {
        assert(i < WORDLEN-1);
        s[i] = c;
        i++;
        c = fgetc(f);
    }
    s[i] = '\0';
    return i;
}

/* Stampa una riga di intestazione di lunghezza `n` */
void header(int n)
{
    int i;

    for (i=1; i<=n; i++) {
        printf("%c", i%10 ? '-' : '|');
    }
    printf("\n");
}

int main( int argc, char *argv[] )
{
    FILE *filein = stdin;
    int Lmax, len, currlen;
    char w[WORDLEN];
    if (argc != 3) {
        fprintf(stderr, "Uso: %s Lmax filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    Lmax = atoi(argv[1]);

    if (strcmp(argv[2], "-") != 0) {
        filein = fopen(argv[2], "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    header(Lmax);
    /* [TODO]: il blocco seguente legge e stampa le "parole" dal file,
       una per riga. Si tratta solo di un esempio di uso della
       funzione `read_word()`, e andrà modificato (o riscritto) per
       risolvere il problema. */

    currlen = 0;
    while ((len = read_word(filein, w)) > 0 ) {
        if(currlen + len > Lmax){
          printf("\n%s ", w);
          currlen = len+1;
        }
        else{
          currlen += len+1;
          printf("%s ", w);
        }
    }
    printf("\n");
    if (filein != stdin) fclose(filein);
    return EXIT_SUCCESS;
}
