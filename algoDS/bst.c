#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"

static void bst_check_rec( const BST* T, const BSTNode *n )
{
    if (n != NULL) {
        if (n->left) {
            assert(n->left->key <= n->key);
            assert(n->left->parent == n);
            bst_check_rec(T, n->left);
        }
        if (n->right) {
            assert(n->right->key > n->key);
            assert(n->right->parent == n);
            bst_check_rec(T, n->right);
        }
    }
}

static void bst_check( const BST* T )
{
    if (T->root)
        assert(T->root->parent == NULL);
    bst_check_rec(T, T->root);
}

BST *bst_create( void )
{
    BST *T = (BST*)malloc(sizeof(*T));
    assert(T != NULL);

    T->root = NULL;
    T->size = 0;
    bst_check(T);
    return T;
}

/* Funzione ausiliaria che libera ricorsivamente la memoria usata dal
   nodo `n` e da tutti i nodi che discendono da esso */
static void bst_clear_rec(BSTNode *n)
{
    if (n != NULL) {
        bst_clear_rec(n->left);
        bst_clear_rec(n->right);
        free(n);
    }
}

void bst_clear(BST *T)
{
    assert(T != NULL);
    bst_clear_rec(T->root);
    T->root = NULL;
    T->size = 0;
    bst_check(T);
}

void bst_destroy(BST *T)
{
    bst_clear(T);
    free(T);
}

BSTNode *bst_search(const BST *T, BSTKey k)
{
    BSTNode *node;
    assert(T != NULL);
    node = T->root;
    while(node != NULL && node->key != k){
        node = (node->key > k) ? node->left : node->right;
    }
    return node;
}

/*
   La specifica di `bst_insert_rect(n, p, k, inserted)` p la seguente:
   inserisci la chiave `k` nel sottoalbero avente `n` come radice. Il
   nodo `p` deve diventare il padre di `n`; se `p == NULL` significa
   che `n` non ha padre, cioè è la nuova radice. La funzione ritorna
   il puntatore alla radice del sottoalbero eventualmente modificato.

   Se `n == NULL`, stiamo inserendo `k` in un sottoalbero vuoto. Di
   conseguenza, la funzione crea un nuovo nodo di cui viene restituito
   il puntatore. Il nuovo nodo ha `p` come padre (che può essere
   `NULL` nel caso in cui stiamo inserendo un nodo in un albero
   vuoto).

   Se `n != NULL`, stiamo inserendo `k` in un sottoalbero non
   vuoto. Di conseguenza, la funzione viene applicata ricorsivamente a
   uno dei sottoalberi di `n`, in base al valore della chiave `k`. In
   questo caso la funzione ritorna `n`, dato che la radice del
   sottoalbero in cui viene inserito `k` non cambia.

   Nel caso in cui `k` sia già presente nell'albero, nessuna
   modifica deve essere apportata a `T`.

   Il valore puntato da `inserted` viene posto a 1 nel caso in cui
   venga creato un nuovo nodo, 0 se la chiave è già presente
   nell'albero.
*/
static BSTNode *bst_insert_rec(BSTNode *n, BSTNode *p, BSTKey k, int *inserted)
{
    if(n == NULL){
        BSTNode *new_node = (BSTNode*)malloc(sizeof(BSTNode));
        new_node->parent = p;
        new_node->key = k;
        new_node->left = NULL;
        new_node->right = NULL;
        *inserted = 1;
        if(p != NULL){
            if(p->key > k) p->left = new_node;
            else p->right = new_node;
        }
        return new_node;
    }
    if(k == n->key) return n;
    if(k > n->key) bst_insert_rec(n->right, n, k, inserted);
    else bst_insert_rec(n->left, n, k, inserted);
    return n;
}

int bst_insert(BST *T, BSTKey k)
{
    int inserted = 0;
    assert(T != NULL);
    T->root = bst_insert_rec(T->root, NULL, k, &inserted);
    if (inserted)
        T->size++;
    bst_check(T);
    return inserted;
}

static BSTNode *bst_minimum(BSTNode *n)
{
    assert(n != NULL);
    while (n->left != NULL)
        n = n->left;
    return n;
}

BSTNode *bst_successor(BSTNode *n){
    BSTNode *x = n->right;
    if(x != NULL) return bst_minimum(x);
    x = n->parent;
    while(x != NULL && x->right == n){
        n = x;
        x = x->parent;
    }
    return x;
}

void bst_delete_rec(BST *T, BSTNode *n){
    BSTNode *x = (BSTNode*)malloc(sizeof(BSTNode));
    assert(T != NULL);
    assert(n != NULL);
    
    if(n->left == NULL && n->right == NULL) x = NULL;
    if(n->left != NULL && n->right == NULL) x = n->left;
    if(n->left == NULL && n->right != NULL) x = n->right;
    if(n->left != NULL && n->right != NULL){
        x = bst_successor(n);
        printf("\n%d\n", x->key);
        n->key = x->key;
        bst_delete_rec(T, x);
    }
    else{
        if(n->parent == NULL){
            x->parent = NULL;
            T->root = x;
        }
        else{
            if(n->parent->left == n) n->parent->left = x;
            else n->parent->right = x;
            if(x != NULL) x->parent = n->parent;
        }
    }
}

void bst_delete(BST *T, BSTNode *n)
{
    bst_delete_rec(T, n);
    T->size--;
    bst_check(T); /* al termine conviene controllare che la struttura dell'albero sia corretta */
}

/* Funzione ricorsiva che calcola l'altezza dell'albero radicato in
   `n` con la regola seguente:

   - Se `n == NULL`, il risultato deve essere -1;

   - Altrimenti, l'altezza dell'albero radicato in `n` è uguale al
     massimo tra l'altezza di `n->left` e `n->right`, più uno.

   Si noti che, dalla regola precedente, deriva che l'altezza di un
   albero composto da un singolo nodo è zero, il che è il risultato
   corretto (l'altezza di un albero è il numero _massimo_ di archi
   attraversati per andare dalla radice alla foglia più profonda).
*/
static int bst_height_rec(const BSTNode *n)
{
    int hl, hr;
    if(n == NULL) return -1;
    hl = bst_height_rec(n->left), hr = bst_height_rec(n->right);
    return (hl > hr) ? hl+1 : hr+1;
}

int bst_height(const BST *T)
{
    assert(T != NULL);
    return bst_height_rec(T->root);
}

/* Stampa il contenuto del sottoalbero radicato nel nodo `n`. Il
   formato della stampa è:

   (n->key left right)

   dove `n->key` è il valore presente in `n`, mentre `left` e `right`
   sono il contenuto del sottoalbero sinistro e destro di `n`.  Se `n`
   è vuoto (cioè n == NULL), stampa `()`
*/
static void bst_print_rec( const BSTNode *n )
{
    printf("(");
    if (n != NULL) {
        printf("%d ", n->key);
        bst_print_rec(n->left);
        printf(" ");
        bst_print_rec(n->right);
    }
    printf(")");
}

/* Nota: la funzione di stampa assume che `BSTKey` sia il tipo
   `int` */
void bst_print( const BST *T )
{
    assert(T != NULL);
    bst_print_rec(T->root);
    printf("\n");
}

/* Conviene realizzare la funzione `bst_pretty_print()` in modo che
   richiami la funzione ricorsiva `bst_pretty_print_rec()` che
   effettuerà la stampa vera e propria.

   `bst_pretty_print_rec(n, depth)` stampa il sottoalbero radicato nel
   nodo `n`, che si trova a profondità `depth` dell'albero. Il valore
   `depth` serve per decidere quanti spazi vanno stampati a partire
   dal margine sinistro per fare "rientrare" correttamente il
   sottoalbero. Suggerisco di stampare 3*`depth` spazi prima della
   chiave di `n`. */
static void bst_pretty_print_rec( const BSTNode *n, int depth )
{
    if (n != NULL) {
        int i;
        bst_pretty_print_rec(n->right, depth+1);
        for(i = 0; i<depth; i++) printf("   ");
        printf("%d\n", n->key);
        bst_pretty_print_rec(n->left, depth+1);
        /* [TODO] Si suggerisce di procedere come segue:

           1. Stampa ricorsivamente il sottoalbero destro invocando
              bst_pretty_print_rec(n->right, depth+1);

           2. Stampa 3*n spazi, seguiti dal valore della chiave n->key;

           3. Stampa ricorsivamente il sottoalbero sinistro invocando
           bst_pretty_print_rec(n->left, depth+1);
        */
    }
}

void bst_pretty_print( const BST *T )
{
    assert(T != NULL);
    bst_pretty_print_rec(T->root, 0);
}

int bst_size(const BST *T)
{
    assert(T != NULL);
    return T->size;
}

int bst_is_empty(const BST *T)
{
    assert(T != NULL);
    return (T->root == NULL);
}

BSTNode *create_balanced_rec(BSTNode *n, BSTNode *parent, int l, int r, BSTKey *keys){
    int mid;
    if(l == r) return NULL;
    mid = (l+r)/2;
    n = (BSTNode*)malloc(sizeof(BSTNode));
    n->parent = parent;
    n->key = keys[mid];
    n->left = create_balanced_rec(NULL, n, l, mid, keys);
    n->right = create_balanced_rec(NULL, n, mid+1, r, keys);
    return n;
}

BST *create_balanced(BSTKey *keys, int n){
    BST *T = bst_create();
    T->root = create_balanced_rec(NULL, NULL, 0, n, keys);
    T->size = n;
    return T;
}

void preorder(BSTNode *n, int *i, int *keys){
    if(n == NULL) return;
    preorder(n->left, i, keys);
    keys[(*i)] = n->key;
    (*i)++;
    preorder(n->right, i, keys);
}

void balance(BST *T){
    /* riempio un array e poi creo l'albero bilaciato */
    int i = 0;
    BSTKey *keys = (BSTKey*)malloc(sizeof(BSTKey)*(T->size));
    preorder(T->root, &i, keys);
    bst_destroy(T);
    T = create_balanced(keys, i);
}