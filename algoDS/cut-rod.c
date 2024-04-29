#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define N 1000

double p[N];    /* p[i] è il prezzo di vendita di un segmento lungo
                   i, i=1..n; p[0] non viene usato */
int n;          /* lunghezza dell'asta da tagliare */
double r[N];    /* r[j] è il massimo guadagno che è possibile ottenere
                   tagliando un'asta lunga j, j=0..n */
int s[N];       /* s[j] è la lunghezza dell'ultimo taglio della
                   soluzione ottima del problema P(j) */

/* Legge l'input dal file `filein` */
void init( FILE *filein )
{
    double val;
    p[0] = 0.0; /* p[0] non viene usato */
    n = 0;
    while (1 == fscanf(filein, "%lf", &val)) {
        n++;
        assert(n < N);
        p[n] = val;
    }
}

/* Determina la soluzione del problema "cut rod". Restituisce il
   guadagno massimo */
double solve( void )
{
    int i,j;
    r[0] = 0.0;
    for(i = 1; i<=n; i++){
        for(j = 1; j<=i; j++){
            if(r[i] < p[j] + r[i-j]){
                r[i] = p[j] + r[i-j];
                s[i] = j;
            }
        }
    }
    return r[n];
}

/* Stampa la soluzione del problema. */
void print( void )
{
    int k = n;
    printf("   Lun   Prezzo\n------ --------\n");
    while(k > 0){
        printf("    %d     %.2f\n", s[k], r[s[k]]);
        k -= s[k];
    }
    printf("Guadagno complessivo: %.2f", r[n]);
}


int main( int argc, char *argv[] )
{
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

    init( filein );
    (void)solve( ); /* il cast a void non serve, ma alcuni compilatori particolarmente solerti potrebbero segnalare un warning perché non stiamo utilizzando il valore di ritorno della funzione */
    print( );
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
