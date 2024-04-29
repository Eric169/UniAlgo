#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "minheap.h"

MinHeap *minheap_create(int size){
    MinHeap *h = (MinHeap*)malloc(sizeof(*h));
    assert(size > 0);
    h->size = size+1;
    h->pos = (int*)calloc(size-1, sizeof(int));
    h->n = 0;
    h->heap = (HeapElem*)malloc(sizeof(HeapElem)*h->size);
    return h;
}

int minheap_is_empty(const MinHeap *h){
    return h->n == 0;
}

int minheap_is_full(const MinHeap *h){
    return h->n == h->size;
}

int minheap_get_n(const MinHeap *h){
    return h->n;
}

int minheap_min(const MinHeap *h){
    return h->heap[1].key;
}

void swap(MinHeap* h, int i, int j){
    HeapElem tmp = h->heap[i];
    /*printf("swap: %d %d %f, %d %d %f\n", i, h->heap[i].key, h->heap[i].prio, j, h->heap[j].key, h->heap[j].prio);*/
    h->pos[h->heap[i].key] = j;
    h->pos[h->heap[j].key] = i;
    h->heap[i] = h->heap[j];
    h->heap[j] = tmp;
}

void minheap_insert(MinHeap *h, int key, double prio){
    HeapElem elem;
    int i;
    assert(!minheap_is_full(h));
    elem.key = key;
    elem.prio = prio;
    h->n++;
    i = h->n;
    h->heap[i] = elem;
    h->pos[key] = i;
    moveUp(h, i);
}

int minheap_delete_min(MinHeap *h){
    int key = h->heap[1].key;
    assert(h->n > 0);
    swap(h, 1, h->n);
    h->n--;
    moveDown(h, 1);
    h->pos[key] = 0;
    return key;
}

void minheap_change_prio(MinHeap *h, int key, double new_prio){
    int id = keyIdx(h, key);
    double prec_prio = h->heap[id].prio;
    assert(id != -1);
    h->heap[id].prio = new_prio;
    if(prec_prio > new_prio)
        moveUp(h, id);
    else
        moveDown(h, id);
    
}

int keyIdx(MinHeap* h, int key){
    assert(!minheap_is_empty(h) && h->pos[key] != 0);
    return h->pos[key];
}

void moveUp(MinHeap* h, int i){
    while(i > 1 && h->heap[i/2].prio > h->heap[i].prio){
        swap(h, i, i/2);
        i/=2;
    }
}

void moveDown(MinHeap *h, int i){
    while(i*2 <= h->n && (h->heap[i*2].prio < h->heap[i].prio || (i*2+1 <= h->n && h->heap[i*2+1].prio < h->heap[i].prio))){
        int l = (i*2+1 <= h->n && h->heap[i*2].prio < h->heap[i*2+1].prio) || i*2+1 > h->n;
        if(l){
            swap(h, i, i*2);
            i*=2;
        }
        else {
            swap(h, i, i*2+1);
            i = i*2+1;
        }
    }
}

void minheap_print(const MinHeap *h)
{
    int i, j, width = 1;
    assert(h != NULL);

    printf("\n** Contenuto dello heap:\n\n");
    printf("n=%d size=%d\n", h->n, h->size-1);
    printf("Contenuto dell'array heap[] (stampato a livelli:\n");
    i = 1;
    while (i <= h->n) {
        j = 0;
        while (j<width && i <= h->n) {
            printf("h[%2d]=(%2d, %6.2f) ", i-1, h->heap[i].key, h->heap[i].prio);
            i++;
            j++;
        }
        printf("\n");
        width *= 2;
    }
    printf("\nContenuto dell'array pos[]:\n");
    for(i = 0; i<h->size-1; i++) printf("pos[%d]=%d ", i, h->pos[i]-1);
    printf("\n\n** Fine contenuto dello heap\n\n");
}

void minheap_clear(MinHeap *h){
    h->n = 0;
}

void minheap_destroy(MinHeap *h){
    free(h->heap);
    free(h);
}