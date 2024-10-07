#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mfset.h"

/* Rappresentiamo il grafo come array di archi. Per questo programma
   non è conveniente usare la struttura Grafo (vista in una lezione
   precedente), perché sarebbe più laborioso (anche se certamente
   possibile) ordinare gli archi. */
typedef struct {
    int src, dst;
    double weight;
} Edge;

int n = 0;        /* numero di nodi del grafo   */
int m = 0;        /* numero di archi del grafo  */
Edge *E = NULL;   /* Array di archi del grafo   */
int nmst = 0;     /* numero archi del MST       */

/* `mst[]` è l'array dei puntatori agli archi che fanno parte del
   MST. L'array avrà al massimo (n-1) elementi, di cui i primi `nmst`
   sono puntatori agli archi che fanno parte del MST (i restanti
   elementi, se presenti, verranno ignorati). L'array `mst[]` deve
   essere allocato nella funzione Kruskal(). */
Edge **mst = NULL;

/* Leggi li grafo dal file `filein`, che deve essere già stato aperto
   in lettura dal chiamante, e alloca l'array `E[]` di archi. Il
   formato dell'input è quello usato dalla struttura dati Graph;
   ricordiamo che, per i grafi non orientati, gli archi sono salvati
   su file una sola volta, anche se in fase di lettura la struttura
   Graph li memorizza _due_ volte nelle liste di adiacenza. Siccome
   non usiamo liste di adiacenza, possiamo leggere gli archi e
   salvarli direttamente nell'array `E[]`. */
void readGraph( FILE* filein )
{
    int i, t;
    int nread;

    nread = fscanf(filein, "%d %d %d", &n, &m, &t);
    assert(nread == 3);
    if (t != 0) {
        fprintf(stderr, "ERRORE: questo programma richiede grafi non orientati\n");
        exit(EXIT_FAILURE);
    }
    E = (Edge*)malloc(m * sizeof(*E)); assert(E != NULL);
    for (i=0; i<m; i++) {
        nread = fscanf(filein, "%d %d %lf", &(E[i].src), &(E[i].dst), &(E[i].weight));
        assert(nread == 3);
    }
}

int cmp(const void *a, const void *b){
    double diff = ((Edge*)a)->weight - ((Edge*)b)->weight;
    return (diff > 0 ? 1 : (diff < 0 ? -1 : 0));
}

/* Calcola il MST usando l'algoritmo di Kruskal e ritorna il peso
   totale dell'albero; alloca l'array `mst[]` e ne definisce i valori
   (l'array `mst[]` contiene puntatori ad archi). Al termine, la
   variabile globale `nmst` deve contenere il numero di archi che
   fanno parte del MST. È consentito allocare più spazio di quello
   strettamente necessario per l'array `mst[]`. */
double Kruskal( void )
{
    int i;
    double tot = 0.0;
    MFSet *dsu = mfset_create(n);
    qsort(E, m, sizeof(Edge), cmp);
    mst = (Edge**)malloc(n-1*sizeof(Edge*));
    for(i = 0; i<m; i++){
        if(mfset_merge(dsu, E[i].src, E[i].dst))
        {
            mst[nmst] = (Edge*)malloc(sizeof(Edge));
            mst[nmst] = &E[i];
            nmst++;  
            tot += E[i].weight;
        }
    }
    return tot;
}

/* Stampa a video l'elenco degli archi del MST nello stesso formato
   usato per il grafo di input. */
void print_mst( void )
{
    int i;

    printf("%d %d 0\n", n, nmst);
    for (i=0; i<nmst; i++) {
        printf("%d %d %f\n", mst[i]->src, mst[i]->dst, mst[i]->weight);
    }
}

int main( int argc, char *argv[] )
{
    double wtot; /* peso totale del MST */
    FILE* filein = stdin;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-") != 0) {
        filein = fopen(argv[1], "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    readGraph(filein);
    wtot = Kruskal();
    print_mst();
    printf("# MST weight = %f\n", wtot);
    free(E);
    free(mst);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
