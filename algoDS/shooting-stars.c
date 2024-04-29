#include <stdlib.h>
#include <stdio.h>

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
    const int n = 3;
    int **grid = (int**)malloc(n*sizeof(int*));
    int i;
    for(i = 0; i<n; i++){
        grid[i] = (int*)calloc(n, sizeof(int));
    }
    grid[1][1] = 1;
    printGrid(grid, n);
    do{
        int pressed;
        printf("Inserire un numero da 0 a 8 (<0 per terminare): ");
        scanf("%d", &pressed);
        if(pressed < 0) break;
        shoot(grid, pressed, n);
        printGrid(grid, n);

    }while(!win(grid, n) && !lose(grid, n));
    if(win(grid, n)){
        printf("Yeee. Hai vinto!\n");
    }
    else if(lose(grid, n)){
        printf("Nooo, hai perso!\n");
    }
    for(i = 0; i<n; i++) free(grid[i]);
    free(grid);
    return 0;
}