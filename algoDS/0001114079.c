/*
Nome: Eric
Cognome: Aquilotti
Matricola: 0001114079
Classe: A
Email: eric.aquilotti2@studio.unibo.it
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*to keep the positions*/
typedef struct{
    int x;
    int y;
}Node;

/*list implementation*/
typedef Node ListInfo;

typedef struct ListNode {
    ListInfo pos;
    struct ListNode *succ, *pred;
} ListNode;

typedef struct {
    int length;
    ListNode *sentinel;
} List;

/* Restituisce l'indirizzo di memoria della sentinella di `L` */
ListNode *list_end(const List *L)
{
    assert(L != NULL);
    return L->sentinel;
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

int list_is_empty(const List *L)
{
    assert(L != NULL);
    return (list_first(L) == list_end(L));
}

static ListNode *list_new_node(Node v)
{
    ListNode *r = (ListNode *)malloc(sizeof(ListNode));
    assert(r != NULL); /* evitiamo un warning con VS */
    r->pos = v;
    r->succ = r->pred = r;
    return r;
}

List *list_create( void )
{
    Node tmp;
    List *L = (List*)malloc(sizeof(List));
    assert(L != NULL);

    L->length = 0;
    L->sentinel = list_new_node(tmp); /* il valore contenuto nel nodo sentinella è irrilevante */
    return L;
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

ListInfo list_remove_last(List *L)
{
    Node val = L->sentinel->pred->pos;
    list_remove(L, L->sentinel->pred);
    return val;
}

/*returns true if position is inside the matrix*/
int posOK(Node tmp, int n, int m){
    return tmp.x >= 0 && tmp.y >= 0 && tmp.x < n && tmp.y < m;
}

/*to know also from where I come from*/
typedef struct{
    long int dist;
    Node parent;
}distValue;

/*fills bestPath by following parent path*/
void getBestPath(Node **bestPath, int *pathLen, distValue **distances, int n, int m){
    Node currNode;
    currNode.x = n-1;
    currNode.y = m-1;
    *pathLen = 0;
    *bestPath = (Node*)malloc(sizeof(Node)*n*m);
    /*loop until I reach the top left corner*/
    while(currNode.x != 0 || currNode.y != 0){
        (*bestPath)[(*pathLen)++] = currNode;
        /*the new node is now the parent*/
        currNode = distances[currNode.x][currNode.y].parent;
    }
    (*bestPath)[(*pathLen)++] = currNode;
}

#define INF 2e16
/*
Shortest Path Faster Algorithm, calculates the shortest path from cell {0, 0} to cell {n-1, m-1}
in worst case the complexity is O(n^2*m^2) but with grids it's usually faster than dijkstra because there are not many edges
in average the complexity is O(n*m)
*/
void SPFA(long int ccell, long int cheight, int n, int m, long int **mat, long int *bestDistance, Node **bestPath, int *pathLen){
    int **inQueue; /*used to know if an element is already in queue*/
    distValue **distances;
    long int cost;
    /*I use movx and movy to move inside the matrix*/
    int i, j, movx[] = {0, 0, 1, -1}, movy[] = {1, -1, 0, 0};
    Node currNode, tmp;
    List *L;
    inQueue = (int**)malloc(sizeof(int*)*n);
    distances = (distValue**)malloc(sizeof(distValue*)*n);
    for(i = 0; i < n; i++){
        inQueue[i] = (int*)calloc(m, sizeof(int));

        distances[i] = (distValue*)malloc(sizeof(distValue)*m);
        /*initialize all distances to inf*/
        for(j = 0; j < m; j++) distances[i][j].dist = INF;
    }


    /*distance on the first cell is ccell*/
    distances[0][0].dist = ccell;
    currNode.x = 0;
    currNode.y = 0;

    L = list_create();
    list_add_first(L, currNode);
    inQueue[currNode.x][currNode.y] = 1;

    while(!list_is_empty(L)){
        currNode = list_remove_last(L);
        inQueue[currNode.x][currNode.y] = 0;

        /*try to go to all directions*/
        for(i = 0; i < 4; i++){
            tmp = currNode;
            tmp.x += movx[i];
            tmp.y += movy[i];
            if(posOK(tmp, n, m)){
                /*calculate cost*/
                cost = ccell + 
                    cheight * (mat[tmp.x][tmp.y] - mat[currNode.x][currNode.y]) * (mat[tmp.x][tmp.y] - mat[currNode.x][currNode.y]);
                
                /*if I found a better distance*/
                if(distances[tmp.x][tmp.y].dist > cost + distances[currNode.x][currNode.y].dist){
                    /*update distances and push if not already in queue*/
                    distances[tmp.x][tmp.y].dist = cost + distances[currNode.x][currNode.y].dist;
                    distances[tmp.x][tmp.y].parent = currNode;

                    if(!inQueue[tmp.x][tmp.y]){
                        list_add_first(L, tmp);
                        inQueue[tmp.x][tmp.y] = 1;
                    }
                }
            }
        }
    }

    *bestDistance = distances[n-1][m-1].dist;
    getBestPath(bestPath, pathLen, distances, n, m);

    /*free everything*/
    for(i = 0; i < n; i++){
        free(distances[i]);
        free(inQueue[i]);
    }
    free(distances);
    free(inQueue);
    list_destroy(L);
}

void printResult(long int bestDistance, Node *bestPath, int pathLen){
    int i;
    for(i = pathLen-1; i >= 0; i--){
        printf("%d %d\n", bestPath[i].x, bestPath[i].y);
    }
    printf("-1 -1\n%ld\n", bestDistance);
}

int readFile(char *filename, long int *ccell, long int *cheight, int *n, int *m, long int ***mat){
    int i, j;
    long int posValue;
    FILE *filein = stdin;
    filein = fopen(filename, "r");
    if (filein == NULL) {
        fprintf(stderr, "Can not open %s\n", filename);
        return 0;
    }

    if (4 != fscanf(filein, "%ld\n%ld\n%d\n%d", ccell, cheight, n, m)) {
        fprintf(stderr, "ERRORE durante la lettura delle costanti\n");
        return 0;
    }

    /*alloco la matrice*/
    *mat = (long int**)malloc((*n)*sizeof(long int*));
    for(i = 0; i<*n; i++) (*mat)[i] = (long int*)malloc((*m)*sizeof(long int));

    /*leggo per righe*/
    for(i = 0; i < (*n); i++){
        for(j = 0; j < (*m) && (1 == fscanf(filein, "%ld ", &posValue)); j++){
            (*mat)[i][j] = posValue;
        }
        if (j != (*m)) {
            fprintf(stderr, "ERRORE durante la lettura della matrice\n");
            return 0;
        }
    }
    if (filein != stdin) fclose(filein);
    return 1;
}

int main(int argc, char *argv[]){
    long int ccell, cheight, **mat = NULL, bestDistance;
    int n, m, pathLen, i;
    Node *bestPath = NULL;
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (strcmp(argv[1], "-") != 0) {
        if(!readFile(argv[1], &ccell, &cheight, &n, &m, &mat)) return EXIT_FAILURE;
    }

    SPFA(ccell, cheight, n, m, mat, &bestDistance, &bestPath, &pathLen);
    printResult(bestDistance, bestPath, pathLen);

    /*free everything*/
    for(i = 0; i < n; i++) free(mat[i]);
    free(mat);
    free(bestPath);

    return EXIT_SUCCESS;
}