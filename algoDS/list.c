#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

/* Crea un nuovo nuovo oggetto nodo contenente valore `v`. I puntatori
   al successore e predecessore del nuovo nodo puntano a se stesso. */
static ListNode *list_new_node(int v)
{
    ListNode *r = (ListNode *)malloc(sizeof(ListNode));
    assert(r != NULL); /* evitiamo un warning con VS */
    r->val = v;
    r->succ = r->pred = r;
    return r;
}

/* Restituisce l'indirizzo di memoria della sentinella di `L` */
ListNode *list_end(const List *L)
{
    assert(L != NULL);
    return L->sentinel;
}

List *list_create( void )
{
    List *L = (List*)malloc(sizeof(List));
    assert(L != NULL);

    L->length = 0;
    L->sentinel = list_new_node(0); /* il valore contenuto nel nodo sentinella è irrilevante */
    return L;
}

int list_length(const List *L)
{
    assert(L != NULL);
    return L->length;
}

void list_clear(List *L)
{
    ListNode* curr = L->sentinel->succ, *nx;
    while(curr != L->sentinel){
        nx = curr->succ;
        free(curr);
        curr = nx;
    }
    L->sentinel->succ = L->sentinel;
    L->sentinel->pred = L->sentinel;
    L->length = 0;
}

void list_destroy(List *L)
{
    list_clear(L);
    free(L->sentinel);
    free(L);
}

/* Nota: questa funzione assume che `ListInfo` sia il tipo "int" */
void list_print(const List *L)
{
    const ListNode *node;

    assert(L != NULL);

    printf("(");
    for (node = list_first(L); node != list_end(L); node = list_succ(node)) {
        printf("%d ", node->val);
    }
    printf(")\n");
}

int list_is_empty(const List *L)
{
    assert(L != NULL);
    return (list_first(L) == list_end(L));
}

ListNode *list_search(const List *L, ListInfo k)
{
    ListNode* curr = L->sentinel->succ;
    while(curr != L->sentinel){
        if(curr->val == k) return curr;
        curr = curr->succ;
    }
    return curr;
}

ListNode *list_first(const List *L)
{
    assert(L != NULL);
    return L->sentinel->succ;
}

ListNode *list_last(const List *L)
{
    assert(L != NULL);
    return L->sentinel->pred;
}


/* Inserisce un nuovo nodo contenente k all'inizio della lista */
void list_add_first(List *L, ListInfo k)
{
    ListNode* new = list_new_node(k);
    assert(L != NULL);
    new->succ = L->sentinel->succ;
    L->sentinel->succ->pred = new;
    L->sentinel->succ = new;
    new->pred = L->sentinel;
    L->length++;
}

/* Inserisce un nuovo nodo contenente k alla fine della lista */
void list_add_last(List *L, ListInfo k)
{
    ListNode* new = list_new_node(k);
    assert(L != NULL);
    new->pred = L->sentinel->pred;
    L->sentinel->pred->succ = new;
    L->sentinel->pred = new;
    new->succ = L->sentinel;
    L->length++;
}

/* Rimuove il nodo n dalla lista L */
void list_remove(List *L, ListNode *n)
{
    assert(L != NULL);
    assert(n != NULL);
    assert(n != list_end(L));
    n->pred->succ = n->succ;
    n->succ->pred = n->pred;
    L->length--;
    free(n);
}

ListInfo list_remove_first(List *L)
{
    int val = L->sentinel->succ->val;
    list_remove(L, L->sentinel->succ);
    return val;
}

ListInfo list_remove_last(List *L)
{
    int val = L->sentinel->pred->val;
    list_remove(L, L->sentinel->pred);
    return val;
}

ListNode *list_succ(const ListNode *n)
{
    assert(n != NULL);
    return n->succ;
}

ListNode *list_pred(const ListNode *n)
{
    assert(n != NULL);
    return n->pred;
}

ListNode *list_nth_element(const List *L, int n)
{
    int i;
    ListNode* node = L->sentinel;
    if(n < 0 || n >= list_length(L)) return L->sentinel;
    for(i = 0; i<=n; i++){
        node = node->succ;
    }
    return node;
}

void list_concat(List *L1, List *L2)
{
    ListNode* n = L2->sentinel->succ, *tmp;
    assert(L1 != NULL);
    assert(L2 != NULL);
    while(n != L2->sentinel){
        tmp = n->succ;
        n->pred = L1->sentinel->pred;
        n->succ = L1->sentinel;
        n = tmp;
    }
}

int list_equal(const List *L1, const List *L2)
{
    ListNode *n1 = L1->sentinel->succ, *n2 = L2->sentinel->succ;
    if(L1->length != L2->length) return 0;
    while(n1 != L1->sentinel && n2 != L2->sentinel){
        if(n1->val != n2->val) return 0;
    }
    return 1;
}
