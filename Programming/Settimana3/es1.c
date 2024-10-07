#include <stdlib.h>
#include <stdio.h>
#include <time.h>
const short DEFAULT_X = 400;
const short DEFAULT_Y = 400;
struct earth{
    //top left = 0,0
    //bottom right = 399, 399
    //0,x1,x2,399
    //y
    //0,x3,x4,399
    short x1,x2;
    short y;
    short x3,x4;
    short MAX_X;
    short MAX_Y;
};
//compile with gcc name.c -lm if needed
//inclusive
int randBetween(int a, int b){
    return (rand() % (b-a+1)) + a;
}
struct earth scaleMap(struct earth earth_map){
    struct earth new_map = {
        (earth_map.x1 * 100) / earth_map.MAX_X,
        (earth_map.x2 * 100) / earth_map.MAX_X,
        (earth_map.y * 100) / earth_map.MAX_Y,
        (earth_map.x3 * 100) / earth_map.MAX_X,
        (earth_map.x4 * 100) / earth_map.MAX_X,
        100, 100
    };
    return new_map;
}
void drawMap(struct earth earth_map) {
    //mx : MAX_X = x : 100
    fflush(stdout);
    for(int y = 0; y < earth_map.MAX_X; y++){
        printf("-");
    }
    printf("\n");
    for (int y = 1; y < earth_map.MAX_Y / 3 ; y++) {
        printf("-");
        for (int x = 1; x < earth_map.MAX_X-1; x++) {
           if(x == earth_map.x1 && y <  earth_map.y / 3){
            printf("-");
           }else if(x == earth_map.x2 && y <  earth_map.y / 3){
            printf("-");
           }else if(x == earth_map.x3 && y >= earth_map.y / 3){
            printf("-");
           }else if(x == earth_map.x4 && y >= earth_map.y / 3){
            printf("-");
           }
           else{
            printf(" ");
           }
        }
        if(y == earth_map.y / 3 - 1){
            printf("\n");
            for (int x = 0; x < earth_map.MAX_X; x++) {
                printf("-");
            }   
        }else{
            printf("-");
        }
        printf("\n");
    }
    for(int y = 0; y < earth_map.MAX_X; y++){
        printf("-");
    }
    printf("\n");
}
int main(){
    srand(time(NULL));
    struct earth earth_map;
    earth_map.y = randBetween(50, DEFAULT_Y - 50); // (50, 350)
    earth_map.x1 = randBetween(30, 200);
    earth_map.x2 = randBetween(earth_map.x1+50, DEFAULT_X-1);
    earth_map.x3 = randBetween(30, 200);
    earth_map.x4 = randBetween(earth_map.x3+50, DEFAULT_X-1);
    earth_map.MAX_X = DEFAULT_X; earth_map.MAX_Y = DEFAULT_Y;
    struct earth bo = scaleMap(earth_map);
    printf("%d %d %d %d\n",earth_map.x1,earth_map.x2, earth_map.x3, earth_map.x4);
    drawMap(scaleMap(earth_map));
    return 0;
}