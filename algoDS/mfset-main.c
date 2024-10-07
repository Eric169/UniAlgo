#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mfset.h"

int main( int argc, char *argv[] )
{
    char op;
    int x, y, n;
    MFSet *s;
    FILE *filein = stdin;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s filename\n", argv[0]);
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
    printf("mgset_create(%d)\n", n);
    s = mfset_create(n);

    while (1 == fscanf(filein, " %c", &op)) {
        switch (op) {
        case 'm': /* merge */
            fscanf(filein, "%d %d", &x, &y);
            printf("mfset_merge(%d, %d)\n", x, y);
            mfset_merge(s, x, y);
            break;
        case 'q': /* query */
            fscanf(filein, "%d %d", &x, &y);
            printf("query(%d, %d) = %d\n", x, y,
                   mfset_find(s, x) == mfset_find(s, y));
            break;
        default:
            printf("Unknown command %c\n", op);
        }
    }

    mfset_destroy(s);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
