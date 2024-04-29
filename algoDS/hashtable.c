#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "hashtable.h"

unsigned long hash_function(const HashTable *table, unsigned long k)
{
    assert(table != NULL);
    return k % table->size;
}

unsigned long encode(const char *key)
{
    int i;
    unsigned long s;
    assert(key != NULL);
    s = 0;
    for (i=0; key[i]; i++) {
        s += key[i];
    }
    return s;
}

static int keys_equal(const char *k1, const char *k2)
{
    assert(k1 != NULL);
    assert(k2 != NULL);
    return (0 == strcmp(k1, k2));
}

HashTable *ht_create(const int size)
{
    HashTable *h = (HashTable*)malloc(sizeof(*h));
    int i;
    assert(h != NULL);
    h->size = size;
    h->values_count = 0;
    h->items = (HashNode **) malloc(h->size * sizeof(*(h->items)));
    assert(h->items != NULL);
    for (i = 0; i < h->size; i++) {
        h->items[i] = NULL;
    }
    return h;
}

/* Funzione ausiliaria che crea un nuovo nodo per le liste di trabocco
   contenente una copia della chiave `key` con valore associato il
   valore `value`. Il successore del nuovo nodo viene posto a
   `next`. */
static HashNode *hashtable_new_node(const char *key, int value, HashNode *next)
{
    HashNode *item = (HashNode *) malloc(sizeof(HashNode));
    const int keylen = strlen(key);
    assert(item != NULL);
    item->key = (char*)malloc(keylen+1);
    assert(item->key != NULL);
    strcpy(item->key, key);
    item->next = next;
    item->value = value;
    return item;
}

static void free_node(HashNode *n)
{
    assert(n != NULL);
    free(n->key);
    free(n);
}

int ht_insert(HashTable *h, const char *key, int value)
{
    HashNode* curr;
    unsigned long enc = encode(key);
    enc = hash_function(h, enc);
    curr = h->items[enc];
    while(curr != NULL){
        if(keys_equal(key, curr->key)){
            curr->value = value;
            return 0;
        }
        curr = curr->next;
    }
    h->items[enc] = hashtable_new_node(key, value, h->items[enc]);
    h->values_count++;
    return 1;
}

HashNode *ht_search(HashTable *h, const char *key)
{
    HashNode* curr;
    unsigned long enc = hash_function(h, encode(key));
    curr = h->items[enc];
    while(curr != NULL){
        if(keys_equal(key, curr->key)){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

int ht_delete(HashTable *h, const char *key)
{
    HashNode* curr;
    HashNode* prec = NULL;
    unsigned long enc = hash_function(h, encode(key));
    curr = h->items[enc];
    while(curr != NULL){
        if(keys_equal(key, curr->key)){
            if(prec == NULL)
                h->items[enc] = curr->next;
            else
                prec->next = curr->next;
            free_node(curr);
            h->values_count--;
            return 1;
        }
        prec = curr;
        curr = curr->next;
    }
    return 0;
}

void ht_clear(HashTable *h)
{
    int i;
    assert(h != NULL);
    for (i = 0; i < h->size; i++) {
        HashNode *current = h->items[i];
        while (current != NULL) {
            HashNode *next = current->next;
            free_node(current);
            current = next;
        }
        h->items[i] = NULL;
    }
    h->values_count = 0;
}

void ht_destroy(HashTable *h)
{
    assert(h != NULL);
    ht_clear(h);
    free(h->items);
    h->size = h->values_count = 0;
    free(h);
}

int ht_count(const HashTable *h)
{
    assert(h != NULL);
    return (h->values_count);
}

void ht_print(const HashTable *h)
{
    int i;
    assert(h != NULL);
    for (i=0; i<h->size; i++) {
        const HashNode* iter;
        printf("[%3d] ", i);
        for (iter = h->items[i]; iter != NULL; iter = iter->next) {
            printf("->(%s, %d)", iter->key, iter->value);
        }
        printf("\n");
    }
}
