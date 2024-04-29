#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "graph.h"

const int NODE_UNDEF = -1;

typedef enum { WHITE, GREY, BLACK } Color; /* colori dei nodi */

Graph *G;
int *p;         /* array di predecessori; `p[i]` è il predecessore di
                   `i` lungo il cammino dal nodo usato come
                   sorgente. Se `i` è un nodo sorgente, si pone `p[i]
                   = -1`. */
int t;          /* tempo corrente (per gli array discover[], finish[]) */
int *discover;  /* `discover[v]` è l'istante di tempo in cui il nodo
                   `v` è stato visitato per la prima volta. */
int *finish;    /* `finish[v]` è l'istante di tempo in cui tutti i
                   discendenti di `v` sono stati visitati. */
Color *color;   /* `color[v]` è il colore del nodo `v` (vedi libro di
                   testo) */


void dfs_visit(int node){
    Edge* currEdge;
    t++;
    color[node] = GREY;
    discover[node] = t;
    currEdge = G->edges[node];
    while(currEdge != NULL){
        if(color[currEdge->dst] == WHITE){
            p[currEdge->dst] = node;
            dfs_visit(currEdge->dst);
        }
        currEdge = currEdge->next;
    }
    color[node] = BLACK;
    t++;
    finish[node] = t;
}
/* Visita il grafo `G` (definito nell'omonima variabile globale)
   usando l'algoritmo di visita in profondità (DFS) partendo da tutti
   i nodi. Non viene passato un nodo sorgente, perché questa versione
   di DFS deve visitare l'intero grafo. */
void dfs( void )
{
    int i;
    for(i = 0; i<G->n; i++)
        color[i] = WHITE;
    t = 0;
    for(i = 0; i<G->n; i++){
        if(color[i] == WHITE){
            p[i] = -1;
            dfs_visit(i);
        }
    }
}

/* Stampa i predecessori di ciascun nodo lungo l'albero di visita;
 stampa inoltre l'istante di apertura (`discover`) e chiusura
 (`finish`) di ciascun nodo. Come visto a lezione, questi valori
 servono tra le altre cose per classificare gli archi ("in avanti",
 "all'indietro"). */
void print_dfs( void )
{
    const int n = graph_n_nodes(G);
    int v;

    printf("     v |   p[v] | discover |   finish\n");
    printf("-------+--------+----------+----------\n");
    for (v=0; v<n; v++) {
        printf("%6d | %6d | %8d | %8d\n", v, p[v], discover[v], finish[v]);
    }
}

int main( int argc, char *argv[] )
{
    FILE *filein = stdin;
    int n;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s file_grafo\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-") != 0) {
        filein = fopen(argv[1], "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    G = graph_read_from_file(filein);
    n = graph_n_nodes(G);
    p = (int*)malloc( n * sizeof(*p) ); assert(p != NULL);
    discover = (int*)malloc( n * sizeof(*discover) ); assert(discover != NULL);
    finish = (int*)malloc( n * sizeof(*finish) ); assert(finish != NULL);
    color = (Color*)malloc( n * sizeof(*color) ); assert(color != NULL);
    dfs( );
    print_dfs( );
    graph_destroy(G);
    free(p);
    free(discover);
    free(finish);
    free(color);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
