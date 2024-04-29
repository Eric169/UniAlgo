#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

//0 empty, 1 mine, 2 battery, 3 end, 4 start
enum square {empty, mine, battery, end, start};
const char print[] = {'.', '#', '%', '@', 'S'};
const double reward[] = {-1, -100, 1, 100, -1};

struct gamingBoard{
    int rows, cols;
    enum square ** data;    
};

struct Q_Table{
    int rows, cols, actions;
    //tasso di apprendimento, sconto per le future ricompense
    double learningRate, gamma;
    double *** values;
};

struct pair{
    int first, second;
};

//right, left, down, up
const struct pair mov[] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

void vaildInput(char* inputMessage, int* val, char* errorMessage){
    int valid;
    do{
        printf("%s",inputMessage);
        if(!(valid=scanf("%d", val))) printf("Non e' stato inserito un valore valido\n");
        if(valid && *val < 2){
            printf("%s",errorMessage);
            valid = 0;
        }
        char c;
        while((c = getchar()) != '\n' && c != EOF);
    }while(!valid);
}

void printGrid(struct gamingBoard *gb){
    printf("FREE [%c], MINE [%c], BATTERY [%c], END [%c], START [%c]\n",
        print[empty], print[mine], print[battery], print[end], print[start]);
    for(int i = 1; i<gb->rows-1; i++){
        for(int j = 1; j<gb->cols-1; j++)
            printf("%c ", print[gb->data[i][j]]);
        printf("\n");
    }
    printf("\n\n");
}

struct pair best(struct pair *pos, struct Q_Table *q){
    //first value, second index
    struct pair res = {-1e9,0};
    for(int k = 0; k < q->actions; k++) {
        if(q->values[pos->first][pos->second][k] > res.first){
            res.first = q->values[pos->first][pos->second][k];
            res.second = k;
        }
    }
    return res;
}

struct pair sum(struct pair *a, const struct pair *b){
    struct pair res = {a->first + b->first, a->second + b->second};
    return res;
}

struct Q_Table learn(struct gamingBoard *gb, int explorations, struct pair start){
    struct Q_Table q = {gb->rows, gb->cols, 4, 0.1, 0.9, NULL};
    q.values = (double ***)malloc(q.rows*sizeof(double**));
    for(int i = 0; i<q.rows; i++) q.values[i] = (double**)malloc(q.cols*sizeof(double*));
    for(int i = 0; i<q.rows; i++){
        for(int j = 0; j<q.cols; j++)
            q.values[i][j] = (double*)calloc(q.actions, sizeof(double));
    }
    //epsilon è la percentuale con cui sceglie un' azione random e cala andando avanti con le esplorazioni
    double expDec = pow(explorations,-1), epsilon = 1;
    const int MAX_ACTIONS = gb->rows*gb->cols/1.5;
    //se torna in una cella già visitata riduco il reward
    int** vis = (int**)malloc(q.rows*sizeof(int*));
    for(int i = 1; i<=explorations; i++){
        struct pair currPos = start;
        int finished = 0, actions = 0;

        for(int j = 0; j<q.rows; j++) vis[j] = (int*)calloc(q.cols, sizeof(int));
        do{
            vis[currPos.first][currPos.second] = 1;
            double r = (double)rand() / RAND_MAX;
            double rew;
            struct pair next, maxi = best(&currPos, &q);
            //se trova una mina cambia direzione dopo aver aggiornato la Q-Table (solo per una volta)
            //e sceglie comunque random, non è influenzato dalla scelta fatta quindi non si rompe il learning
            int poss = 1;
            do{
                //random action
                if(r < epsilon)
                    maxi.second = rand()%q.actions;
                actions++;
                next = sum(&currPos, &mov[maxi.second]);
                rew = reward[gb->data[next.first][next.second]];
                if(vis[next.first][next.second]) rew-=10;
                double curr = q.values[currPos.first][currPos.second][maxi.second];
                q.values[currPos.first][currPos.second][maxi.second] = (1-q.learningRate) * curr + q.learningRate * (rew + q.gamma * best(&next,&q).first);
            }while(rew == -100 && poss--);
            currPos = next;
            if(rew == 100 || rew == -100) finished = 1;
        }while(!finished && actions < MAX_ACTIONS);
        epsilon = exp(-expDec*i);
        for(int j = 0; j<q.rows; j++) free(vis[j]);
    }
    free(vis);
    return q;
}

void printTable(struct Q_Table *q){
    for(int i = 1; i<q->rows-1; i++){
        for(int j = 1; j<q->cols-1; j++){
            printf("%s", "[");
            for(int k = 0; k<q->actions; k++){
                printf("%.2f ", q->values[i][j][k]);
            }
            printf("%s", "]");
        }
        printf("\n");
    }
}

int printBestPath(struct pair begin, struct Q_Table *q, struct gamingBoard *gb){
    //vado sempre al best finchè non ritorno in una cella già visitata o non sono alla fine
    int ** vis = (int**)malloc(q->rows*sizeof(int*));
    for(int i = 0; i<q->rows; i++) vis[i] = (int*) calloc(q->cols, sizeof(int));
    struct pair curr = begin;
    int size = 0, endReached = 0;
    struct pair *path = (struct pair*)malloc(size * sizeof(struct pair));
    while(1){
        if(gb->data[curr.first][curr.second] == end){
            endReached = 1;
            size++;
            path = (struct pair*)realloc(path, size*sizeof(struct pair));
            path[size-1] = curr;
            break;
        }
        vis[curr.first][curr.second] = 1;
        struct pair bestAction = best(&curr, q);
        struct pair to = sum(&curr, &mov[bestAction.second]);
        if(vis[to.first][to.second]) break;
        size++;
        path = (struct pair*)realloc(path, size*sizeof(struct pair));
        path[size-1] = curr;
        curr = to;
    }
    #ifndef TEST
    for(int i = 1; i<gb->rows-1; i++){
        for(int j = 1; j<gb->cols-1; j++){
            int found = 0;
            for(int k = 0; k<size && !found; k++){
                if(i == path[k].first && j == path[k].second){
                    if(gb->data[i][j] == start) printf("%c ", print[start]);
                    else if(gb->data[i][j] == end) printf("%c ", print[end]);
                    else printf("%s ", "H");
                    found = 1;
                }
            }
            if(!found) printf("%c ",print[gb->data[i][j]]);
        }
        printf("%c", '\n');
    }
    #endif
    free(path);
    for(int i = 0; i<gb->rows; i++) free(vis[i]);
    free(vis);
    return endReached;
}

int endReachable(struct pair curr, struct gamingBoard *gb, int** vis){
    int m = 0;
    if(gb->data[curr.first][curr.second] == end) return 1;
    for(int i = 0; i<sizeof(mov)/sizeof(struct pair) && !m; i++){
        struct pair to = sum(&curr, &mov[i]);
        //se non l'ho visitato e non è una mina lo visito
        if(!vis[to.first][to.second] && gb->data[to.first][to.second] != mine){
            vis[to.first][to.second] = 1;
            m |= endReachable(to, gb, vis);
        }
    }
    return m;
}

void fillGrid(struct gamingBoard *gb, struct pair begin){
    int **vis = (int**)malloc(gb->rows * sizeof(int*));
    gb->data = (enum square**) malloc(gb->rows * sizeof(enum square*));
    for(int i = 0; i<gb->rows; i++){
        vis[i] = (int*)calloc(gb->cols, sizeof(int));
        gb->data[i] = (enum square*)malloc(gb->cols*sizeof(enum square));
    }
    //creo un guscio intorno di mine per evitare che esca dai bordi
    for(int i = 0; i<gb->rows; i++) {gb->data[i][0] = mine; vis[i][0] = mine;}
    for(int i = 0; i<gb->rows; i++) {gb->data[i][gb->cols-1] = mine; vis[i][gb->cols-1] = mine;}
    for(int i = 0; i<gb->cols; i++) {gb->data[0][i] = mine; vis[0][i] = mine;}
    for(int i = 0; i<gb->cols; i++) {gb->data[gb->rows-1][i] = mine; vis[gb->rows-1][i] = mine;}
    do{
        for(int i = 1; i<gb->rows-1; i++){
            for(int j = 1; j<gb->cols-1; j++){
                gb->data[i][j] = empty;
                vis[i][j] = 0;
            }
        }
        vis[begin.first][begin.second] = 1;
        gb->data[begin.first][begin.second] = start;
        
        //10% mines, 10% batteries, 1 end
        int perc = gb->rows*gb->cols*10/100;
        struct pair pos;
        for(int m = 0; m<perc; m++){
            do{
                pos.first = rand()%(gb->rows-2)+1, pos.second = rand()%(gb->cols-2)+1;
            }while(gb->data[pos.first][pos.second] != empty);
            gb->data[pos.first][pos.second] = mine;
            do{
                pos.first = rand()%(gb->rows-2)+1, pos.second = rand()%(gb->cols-2)+1;
            }while(gb->data[pos.first][pos.second] != empty);
            gb->data[pos.first][pos.second] = battery;
        }
        do{
            pos.first = rand()%(gb->rows-2)+1, pos.second = rand()%(gb->cols-2)+1;
        }while(gb->data[pos.first][pos.second] != empty);
        gb->data[pos.first][pos.second] = end;
    //genero griglie random finchè non ne trovo una in cui è fisicamente possibile raggiungere
    //la fine senza passare su delle mine
    }while(!endReachable(begin, gb, vis));
    for(int i = 0; i<gb->rows; i++) free(vis[i]);
    free(vis);
}

void test(int nTest, int rows, int cols, int epochs){
    int correct = 0;
    for(int i = 1; i<=nTest; i++){
        struct gamingBoard gb;
        #ifdef TEST
        if(i % 10 == 0) printf("test %d\n", i);
        gb.rows = rows, gb.cols = cols;
        #else
        vaildInput("Inserire il numero di righe\n", &gb.rows, "Il numero di righe deve essere almeno 2\n");
        vaildInput("Inserire il numero di colonne\n", &gb.cols, "Il numero di colonne deve essere almeno 2\n");
        #endif
        //aumento di 2 le dimensioni per fare i bordi
        gb.cols+=2, gb.rows+=2;
        //inizio sempre da in alto a sinistra
        struct pair begin = {rand()%(gb.rows-2)+1, rand()%(gb.cols-2)+1};
        fillGrid(&gb, begin);
        struct Q_Table q = learn(&gb, epochs, begin);
        #ifndef TEST
        printf("%s", "\n\n\n");
        printGrid(&gb);
        printf("start = {%d, %d}\n", begin.first, begin.second);
        #endif
        int endReached = printBestPath(begin, &q, &gb);
        correct += endReached;
        #ifdef TEST
        if(!endReached){
            printf("\n");
            printGrid(&gb);
            printf("\n");
        }
        #endif
        #ifndef TEST
        printf("%s", "Q-Table\n");
        printTable(&q);
        if(endReached) printf("Reached the end :)\n");
        else printf("It didn't learn enough :(\n");
        #endif
        //free all the things
        for(int i = 0; i<q.rows; i++)
            for(int j = 0; j<q.cols; j++)
                free(q.values[i][j]);
        for(int i = 0; i<q.rows; i++)
            free(q.values[i]);
        free(q.values);
        for(int i = 0; i<gb.rows; i++)
            free(gb.data[i]);
        free(gb.data);
    }
    #ifdef TEST
    printf("Correct answers = %d\nPercentage over total tests = %.3f%%\n",correct, (double)correct/nTest*100);
    #endif
}

int main(int argc, char *argv[]) {
    int epochs = 1e5;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc) {
                if(argv[i+1] >= 0)
                    epochs = atoi(argv[i + 1]);
                break;
            }
        }
    }
    printf("Per fare dei test e vedere la percentuale di riuscita dopo vari test aggiunga -DTEST in compilazione\nSe vuole usare un numero di esplorazioni custom aggiunga -i NUMERO\n");
    printf("epochs = %d\n", epochs);
    srand(time(NULL));
    int nTest = 1, rows, cols;
    #ifdef TEST
    vaildInput("Inserire il numero di test\n", &nTest, "Il numero di test deve essere almeno 2\n");
    vaildInput("Inserire il numero di righe\n", &rows, "Il numero di righe deve essere almeno 2\n");
    vaildInput("Inserire il numero di colonne\n", &cols, "Il numero di colonne deve essere almeno 2\n");
    #endif
    test(nTest, rows, cols, epochs);
    return 0;
}