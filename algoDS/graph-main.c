#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"


int main( int argc, char *argv[] )
{
    Graph *G;
    FILE *filein = stdin;

    if (argc != 2) {
        fprintf(stderr, "Invocare il programma con: %s file_grafo\n", argv[0]);
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
    /*graph_print(G);*/
    printf("in = %d", graph_in_degree(G, 731));
    graph_destroy(G);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
