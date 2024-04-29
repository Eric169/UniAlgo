#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "graph.h"
#include "list.h"

/* Si può usare il simbolo NODE_UNDEF per indicare che il predecessore
   della lista dei padri non esiste. */
const int NODE_UNDEF = -1;

typedef enum { WHITE, GREY, BLACK } Color; /* colori dei nodi */

/* Visita il grafo `g` usando l'algoritmo di visita in ampiezza (BFS)
   usando `s` come nodo sorgente. Restituisce il numero di nodi
   raggiungibili da `s`, incluso `s`. */
int bfs( const Graph *g, int s, int *d, int *p)
{
    int i, visited = 0;
    ListInfo currNode;
    Edge *currEdge;
    List *L;
    for(i = 0; i<g->n; i++){
        p[i] = d[i] = -1;
    }
    d[s] = 0;
    L = list_create();
    list_add_first(L, s);
    while(!list_is_empty(L)){
        currNode = list_remove_last(L);
        currEdge = g->edges[currNode];
        while(currEdge != NULL){
            if(p[currEdge->dst] == -1){
                d[currEdge->dst] = d[currNode]+1;
                p[currEdge->dst] = currNode;
                list_add_first(L, currEdge->dst);
                visited++;
            }
            currEdge = currEdge->next;
        }
    }
    return visited;
}

/* Stampa il cammino che da `s` a `d` prodotto dalla visita in
   ampiezza; se `d` non è raggiungibile da `s`, stampa "Non
   raggiungibile". La stampa del cammino deve avere la forma:

   s->n1->n2->...->d

   dove n1, n2... sono gli identificatori (indici) dei nodi
   attraversati. */
void print_path(int s, int d, const int *p)
{
    if (s == d)
        printf("%d", s);
    else if (p[d] < 0)
        printf("Non raggiungibile");
    else {
        print_path(s, p[d], p);
        printf("->%d", d);
    }
}

/* Stampa le distanze dal nodo `src` di tutti gli altri nodi, e i
   cammini per raggiungerli. I cammini sono quelli prodotti dalla
   visita in ampiezza. L'array `p[]` indica l'array dei predecessori,
   cioè `p[i]` è il predecessore del nodo `i` nell'albero
   corrispondente alla visita BFS. Se un nodo non è raggiungibile da
   `src`, la sua distanza viene riportata come "-1" e il cammino viene
   sostituito dalla stringa "Non raggiungibile". */
void print_bfs( const Graph *g, int src, const int *d, const int *p )
{
    const int n = graph_n_nodes(g);
    int v;

    assert(p != NULL);
    assert(d != NULL);

    printf("  src | dest | distanza | path\n");
    printf("------+------+----------+-------------------------\n");
    for (v=0; v<n; v++) {
        printf(" %4d | %4d | %8d | ", src, v, d[v]);
        print_path(src, v, p);
        printf("\n");
    }
}

int main( int argc, char *argv[] )
{
    Graph *G;
    int nvisited; /* n. di nodi raggiungibili dalla sorgente */
    int *p, *d;
    FILE *filein = stdin;
    int src = 0, n;

    if (argc != 3) {
        fprintf(stderr, "Uso: %s nodo_sorgente file_grafo\n", argv[0]);
        return EXIT_FAILURE;
    }

    src = atoi(argv[1]);

    if (strcmp(argv[2], "-") != 0) {
        filein = fopen(argv[2], "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[2]);
            return EXIT_FAILURE;
        }
    }

    G = graph_read_from_file(filein);
    n = graph_n_nodes(G);
    assert((src >= 0) && (src < n));
    p = (int*)malloc( n * sizeof(*p) ); assert(p != NULL);
    d = (int*)malloc( n * sizeof(*d) ); assert(d != NULL);
    nvisited = bfs(G, src, d, p);
    print_bfs(G, src, d, p);
    printf("# %d nodi su %d raggiungibili dalla sorgente %d\n", nvisited, n, src);
    graph_destroy(G);
    free(p);
    free(d);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
