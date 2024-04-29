#include <stdlib.h>
#include <stdio.h>

struct node{
    int **val;
    int size;
    int*moves;
};

void push(struct node);
void pop();
struct node top();
int empty();
void printGrid(int**, const int);

struct node* items;
int front = 0, rear = -1, size = 0;

void push(struct node val) {
    items = (struct node*)realloc(items, (++size)*sizeof(struct node));
    rear++;
    items[rear] = val;
}

struct node top(){
    return items[front];
}

void pop() {
    front++;
}

int empty(){
    return front == size;
}

int win(int ** grid, const int n){
    int s = 0, i;
    for(i = 0; i<n; i++){
        int j;
        for(j = 0; j<n; j++){
            s += grid[i][j];
        }
    }
    return s == n*n-1 && !grid[1][1];
}

int lose(int ** grid, const int n){
    int s = 0, i;
    for(i = 0; i<n; i++){
        int j;
        for(j = 0; j<n; j++){
            s += grid[i][j];
        }
    }
    return !s;
}

void shoot(int** grid, int pressed, const int n){
    int i = pressed/n, j = pressed%n;
    if(!grid[i][j]){
        printf("Nella casella non è presente una stella\n");
        return;
    }
    switch (pressed)
    {
    case 0:
        grid[0][0]=0;
        grid[0][1]^=1;
        grid[1][1]^=1;
        grid[1][0]^=1;
        break;
    case 1:
        grid[0][1]=0;
        grid[0][0]^=1;
        grid[0][2]^=1;
        break;
    case 2:
        grid[0][2]=0;
        grid[0][1]^=1;
        grid[1][1]^=1;
        grid[1][2]^=1;
        break;
    case 3:
        grid[0][0]^=1;
        grid[2][0]^=1;
        grid[1][0]^=1;
        break;
    case 4:
        grid[1][1]^=1;
        grid[0][1]^=1;
        grid[1][2]^=1;
        grid[1][0]^=1;
        grid[2][1]^=1;
        break;
    case 5:
        grid[0][2]^=1;
        grid[1][2]^=1;
        grid[2][2]^=1;
        break;
    case 6:
        grid[2][1]^=1;
        grid[2][0]^=1;
        grid[1][1]^=1;
        grid[1][0]^=1;
        break;
    case 7:
        grid[2][1]^=1;
        grid[2][0]^=1;
        grid[2][2]^=1;
        break;
    case 8:
        grid[1][1]^=1;
        grid[1][2]^=1;
        grid[2][1]^=1;
        grid[2][2]^=1;
        break;
    default:
        printf("Not valid position\n");
        break;
    }
    return;
}

int gridEquals(int **a, int **b, const int n){
    int i;
    for(i = 0; i<n; i++){
        int j;
        for(j = 0; j<n; j++){
            if(a[i][j] != b[i][j]) return 0;
        }
    }
    return 1;
}

int gridVisited(int **grid, const int n, int ***visited, int *nVis){
    int i;
    for(i = 0; i < *nVis; i++){
        if(gridEquals(grid, visited[i], n)) return i;
    }
    return 0;
}

void copyGrid(int**source, int**dest, const int n){
    int i;
    for(i = 0; i<n; i++){
        int j;
        for(j = 0; j<n; j++){
            dest[i][j] = source[i][j];
        }
    }
}

void visit(int ***visited, int **toAdd, int *nVis, const int n){
    int v = (*nVis);
    int i;
    ++(*nVis);
    for(i = 0; i<n; i++){
        int j;
        for(j = 0; j<n; j++){
            visited[v][i][j] = toAdd[i][j];
        }
    }
}

int minMovesToWin(int **grid, const int n, int ***visited, int *nVis){
    int **cp = (int**)malloc(n*sizeof(int*));
    int k;
    struct node start;
    start.val = (int**)malloc(sizeof(int*)*n);
    for(k = 0; k<n; k++) {
        cp[k] = (int*)malloc(n*sizeof(int));
        start.val[k] = (int*)malloc(n*sizeof(int));
    }
    copyGrid(grid, start.val, n);
    start.size = 0;
    start.moves = (int*)malloc(0);
    push(start);
    visit(visited, grid, nVis, n);
    while(!empty()){
        int i;
        struct node curr = top();
        if(win(curr.val,n)){
            printf("MOSSE PER VINCERE\n");
            for(i = 0; i<curr.size; i++) printf("%d ", curr.moves[i]);
            printf("\n");
            return curr.size;
        }
        for(i = 0; i<n; i++){
            int j;
            for(j = 0; j<n; j++){
                if(curr.val[i][j]){
                    copyGrid(curr.val, cp, n);
                    shoot(cp, i*n+j, n);
                    if(!gridVisited(cp,n,visited,nVis)){
                        struct node add;
                        add.moves = (int*)malloc(sizeof(int)*(curr.size+1));
                        for(k = 0; k<curr.size; k++) add.moves[k] = curr.moves[k];
                        add.moves[curr.size] = i*n+j;
                        add.size = curr.size+1;
                        add.val = (int**)malloc(sizeof(int*)*n);
                        for(k = 0; k<n; k++) add.val[k] = (int*)malloc(sizeof(int)*n);
                        copyGrid(cp, add.val, n);
                        visit(visited, cp, nVis, n);
                        push(add);
                    }
                }
            }
        }
        pop();
    }
    return 0;
}

int minMovesToLose(int **grid, const int n, int ***visited, int *nVis){
    int **cp = (int**)malloc(n*sizeof(int*));
    int k;
    struct node start;
    start.val = (int**)malloc(sizeof(int*)*n);
    for(k = 0; k<n; k++) {
        cp[k] = (int*)malloc(n*sizeof(int));
        start.val[k] = (int*)malloc(n*sizeof(int));
    }
    copyGrid(grid, start.val, n);
    start.size = 0;
    start.moves = (int*)malloc(0);
    push(start);
    visit(visited, grid, nVis, n);
    while(!empty()){
        int i;
        struct node curr = top();
        if(lose(curr.val,n)){
            printf("MOSSE PER PERDERE\n");
            for(i = 0; i<curr.size; i++) printf("%d ", curr.moves[i]);
            printf("\n");
            return curr.size;
        }
        for(i = 0; i<n; i++){
            int j;
            for(j = 0; j<n; j++){
                if(curr.val[i][j]){
                    copyGrid(curr.val, cp, n);
                    shoot(cp, i*n+j, n);
                    if(!gridVisited(cp,n,visited,nVis)){
                        struct node add;
                        add.moves = (int*)malloc(sizeof(int)*(curr.size+1));
                        for(k = 0; k<curr.size; k++) add.moves[k] = curr.moves[k];
                        add.moves[curr.size] = i*n+j;
                        add.size = curr.size+1;
                        add.val = (int**)malloc(sizeof(int*)*n);
                        for(k = 0; k<n; k++) add.val[k] = (int*)malloc(sizeof(int)*n);
                        copyGrid(cp, add.val, n);
                        visit(visited, cp, nVis, n);
                        push(add);
                    }
                }
            }
        }
        pop();
    }
    return 0;
}

void printGrid(int **grid, const int n){
    int i;
    printf("Griglia corrente\n");
    for(i = 0; i<n; i++){
        int j;
        for(j = 0; j<n; j++){
            printf("%c ", (grid[i][j] ? (i*n + j + '0') : '.'));
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    int **grid = (int**)malloc(3*sizeof(int*));
    int i;
    const int n = 3;
    int ***visited = (int***)malloc(sizeof(int**)*1000);
    int nVis = 0;
    for(i = 0; i<1000; i++){
        int j;
        visited[i] = (int**)malloc(sizeof(int*)*n);
        for(j = 0; j<n; j++){
            int k;
            for(k = 0; k<n; k++) visited[i][j] = (int*)malloc(sizeof(int)*n);
        }
    }
    for(i = 0; i<n; i++){
        grid[i] = (int*)calloc(n, sizeof(int));
    }
    grid[1][1] = 1;
    printf("Minimo numero di mosse per vincere = %d\n", minMovesToWin(grid, n, visited, &nVis));
    nVis = 0;
    printf("Minimo numero di mosse per perdere = %d\n", minMovesToLose(grid, n, visited, &nVis));
    return 0;
}