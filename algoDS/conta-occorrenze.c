#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#define WORDLEN 128

typedef struct BSTNode {
    char *s;
    int count;
    struct BSTNode *left, *right;
} BSTNode;

int read_word(FILE *f, char *s)
{
    int c;
    int i = 0;
    while(isalpha(c = fgetc(f)))
      s[i++] = tolower(c);
    s[i] = '\0';
    return (c != EOF ? i : EOF);
}

/* Se la parola `s` non è presente nell'albero di radice `t`, crea un
   nuovo nodo e inserisce una copia della parola con conteggio di
   occorrenze posto a uno.  Se la parola è già presente, incrementa il
   contatore di occorrenze. Ritorna la (nuova) radice dell'albero. */
BSTNode *insert(const char *s, BSTNode *t)
{
    BSTNode *new;
    int v;
    if(t == NULL){
        new = (BSTNode*)malloc(sizeof(BSTNode));
        new->s = (char*)malloc(WORDLEN);
        strcpy(new->s, s);
        new->count = 1;
        new->left = NULL;
        new->right = NULL;
        return new;
    }
    v = strcmp(s, t->s);
    if(v == 0) t->count++;
    else if(v > 0) t->right = insert(s, t->right);
    else t->left = insert(s, t->left);
    return t;
}

void preorder(BSTNode *n){
    if(n == NULL) return;
    preorder(n->left);
    printf("%s %d\n", n->s, n->count);
    preorder(n->right);
}

BSTNode *search(BSTNode *t, char* s)
{
    BSTNode *node;
    int val;
    assert(t != NULL);
    node = t;
    while(node != NULL && (val = strcmp(s, node->s)) != 0){
        node = (val < 0) ? node->left : node->right;
    }
    return node;
}

int main( int argc, char *argv[] )
{
    FILE *filein = stdin;
    int nwords, len;
    char s[WORDLEN];
    BSTNode *t = NULL;

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
    while ((len = read_word(filein, s)) >= 0) if(len > 0){
        nwords++;
        t = insert(s, t);
    }
    if (filein != stdin) fclose(filein);
    
    preorder(t);
    return EXIT_SUCCESS;
}
