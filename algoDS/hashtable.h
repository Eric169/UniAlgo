#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct HashNode {
    char *key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **items;
    int size;
    int values_count;
} HashTable;

/* Questa funzione mappa un intero k arbitrario in una posizione
   dell'array *items[] dell'hash table */
unsigned long hash_function(const HashTable *h, unsigned long k);

/* Trasforma una sequenza di caratteri in un intero senza segno */
unsigned long encode(const char *key);

/* Crea una nuova tabella hash con `size` slot */
HashTable *ht_create(int size);

/* Svuota la tabella hash */
void ht_clear(HashTable *h);

/* Libera tutta la memoria occupata dalla tabella hash */
void ht_destroy(HashTable *h);

/* Inserisci la coppia (key, value) nella hash table. Se la chiave è
   già presente, aggiorna il valore associato al vecchio nodo già
   presente. Se viene creato un nuovo nodo, questa funzione deve
   creare una copia di `key`, e salvarne il contenuto nella chiave nel
   nodo. Restituisce 1 se viene creato un nuovo nodo, 0 se viene
   aggiornato un nodo esistente. */
int ht_insert(HashTable *h, const char *key, int value);

/* Ritorna il nodo contenente le informazioni associate alla chiave
   `key`; se la chiave non è presente, ritorna NULL */
HashNode *ht_search(HashTable *h, const char *key);

/* Rimuove la chiave `key` e il valore associato dalla hash table; se
   la chiave non è presente, non fa nulla. Ritorna 1 se la chiave era
   presente ed è stata cancellata, 0 altrimenti. */
int ht_delete(HashTable *h, const char *key);

/* Ritorna il numero di coppie (chiave, valore) presenti nella hash
   table */
int ht_count(const HashTable *h);

/* Stampa il contenuto della tabella hash; da usare per debug */
void ht_print(const HashTable *h);

#endif
