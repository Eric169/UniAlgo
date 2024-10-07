#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mfset.h"

MFSet *mfset_create(int n)
{
    int i;
    MFSet *s = (MFSet*)malloc(sizeof(*s));
    assert(s != NULL);

    s->n = n;
    s->p = (int*)malloc(n * sizeof(*(s->p)));
    assert(s->p != NULL);
    s->h = (int*)malloc(n*sizeof(*(s->h)));
    for (i=0; i<n; i++) {
        s->p[i] = i;
        s->h[i] = 1;
    }
    return s;
}

void mfset_destroy(MFSet *s)
{
    assert(s != NULL);

    s->n = 0;
    free(s->p);
    free(s);
}

void swap(int *x, int *y){
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

int mfset_merge(MFSet *s, int x, int y)
{
    assert(s != NULL);
    assert((x >= 0) && (x < s->n));
    assert((y >= 0) && (y < s->n));

    x = mfset_find(s, x);
    y = mfset_find(s, y);
    if(x == y) return 0;

    if(s->h[x] < s->h[y]) swap(&x, &y);
    s->h[x] += s->h[y];
    s->p[y] = x;
    return 1;
}


int mfset_find(MFSet *s, int x)
{
    assert(s != NULL);
    assert(x >= 0);
    assert(x < s->n);

    if(s->p[x] == x) return x;
    return s->p[x] = mfset_find(s, s->p[x]);
}
