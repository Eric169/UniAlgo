#ifndef MINHEAP_H
#define MINHEAP_H

typedef struct {
    int key;
    double prio;
} HeapElem;

typedef struct {
    HeapElem *heap;
    int *pos; /* TODO: non inizializzato! Usare solo dopo una implementazione funzionante di minheap_change_prio() in cui la chiave da modificare si trova con una normale ricerca lineare sull'array heap[] */
    int n; /* quante coppie (chiave, prio) sono effettivamente presenti nello heap */
    int size; /* massimo numero di coppie (chiave, prio) che possono essere contenuti nello heap */
} MinHeap;

/* Crea uno heap vuoto in grado di contenere al più `size` coppie
   (chiave, priorità); le chiavi possono essere esclusivamente gli
   interi 0 .. `size` - 1; ogni chiave può essere presente nello heap
   al più una volta. Inizialmente lo heap è vuoto.

   Precondizione: size > 0 */
MinHeap *minheap_create(int size);

/* Svuota lo heap */
void minheap_clear(MinHeap *h);

/* Dealloca la memoria occupata dallo heap h e dal suo contenuto */
void minheap_destroy(MinHeap *h);

/* Restituisce 1 se e solo se lo heap è vuoto */
int minheap_is_empty(const MinHeap *h);

/* Restituisce 1 se e solo se lo heap è pieno */
int minheap_is_full(const MinHeap *h);

/* Ritorna il numero di elementi effettivamente presenti nello heap */
int minheap_get_n(const MinHeap *h);

/* Restituisce la chiave associata alla minima priorità; non modifica
   lo heap */
int minheap_min(const MinHeap *h);

/* Restituisce la coppia (chiave, prio) con priorità minima; non
   modifica lo heap.

   Precondizione: lo heap non deve essere vuoto.

   TODO: questa funzione sostituirà minheap_min() nella prossima
   edizione del corso; per ora non viene usata. */
HeapElem minheap_min2(const MinHeap *h);

/* Inserisce una nuova chiave `key` con priorità `prio`.

   Precondizioni:
   - `key` deve essere una chiave valida;
   - `key` non deve essere già presente nello heap;
   - Lo heap non deve essere pieno. */
void minheap_insert(MinHeap *h, int key, double prio);

/* Rimuove dallo heap la coppia (chiave, prio) con priorità minima, e
   restituisce la chiave di tale coppia.

   Precondizione: lo heap non deve essere vuoto. */
int minheap_delete_min(MinHeap *h);

/* Rimuove dallo heap la coppia (chiave, prio) con priorità minima, e
   restituisce tale coppia.

   Precondizione: lo heap non deve essere vuoto.

   TODO: questa funzione sostituirà minheap_delete_min() nella
   prossima edizione del corso; per ora non viene usata. */
HeapElem minheap_delete_min2(MinHeap *h);

/* Modifica la priorità associata alla chiave `key`.

   Precondizione: la chiave `key` deve essere presente nello heap. */
void minheap_change_prio(MinHeap *h, int key, double new_prio);

/* Stampa il contenuto dello heap */
void minheap_print(const MinHeap *h);

/*swap 2 elements*/
void swap(MinHeap* h, int i, int j);

/*moves an element up*/
void moveUp(MinHeap* h, int i);

/*moves an element down*/
void moveDown(MinHeap* h, int i);

int keyIdx(MinHeap* h, int key);
#endif
