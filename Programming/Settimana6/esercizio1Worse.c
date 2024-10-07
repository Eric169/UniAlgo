#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

//0 empty, 1 mine, 2 battery, 3 end, 4 start(mi serve solo per comodita)
enum square {empty, mine, battery, end, start};
const char print[] = {'.', '#', '~', '@', 'B'};

struct gamingBoard{
    int rows, cols;
    enum square* data;
};

struct Q_Table{
    int rows, cols, actions;
    //tasso di apprendimento, sconto per le future ricompense, epsilonExp aiuta l'esplorazione e mi
    //permette di calcolare un valore epsilon che cala esponenzialmente fino a raggiungere lo zero
    double learningRate, gamma, epsilonExp;
    double *values;
};

struct pair{
    int first, second;
};

//right, left, down, up
const struct pair mov[] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

int id(struct pair *pos, struct gamingBoard *gb){
    return pos->first*gb->cols+pos->second;
}

int idTable(struct pair *pos, struct Q_Table *qtable, int action){
    return (pos->first*qtable->cols+pos->second)*qtable->actions+action;
}

void vaildInput(char* inputMessage, int* val, char* errorMessage){
    int valid;
    do{
        printf("%s",inputMessage);
        if(!(valid=scanf("%d", val))) printf("Non e' stato inserito un valore valido");
        if(valid && *val <= 0){
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
    for(int i = 0; i<gb->rows; i++){
        for(int j = 0; j<gb->cols; j++){
            struct pair pos = {i,j};
            printf("%c ", print[gb->data[id(&pos,gb)]]);
        }
        printf("\n");
    }
}

int posOk(struct pair *pos, struct gamingBoard * gb){
    //printf("posOk = {%d, %d}\n",pos->first, pos->second);
    return (pos->first >= 0 && pos->second >= 0 && pos->first < gb->rows && pos->second < gb->cols);
}

double reward(struct pair *pos, struct gamingBoard *gb){
    int to = gb->data[id(pos, gb)];
    return (to == empty ? -1 : (to == mine ? -100 : (to == end ? 100 : 1)));
}

double best(struct pair *pos, struct Q_Table *q){
    int start = (pos->first * q->cols + pos->second) * q->actions;
    double maxi = -1e9;
    for(int k = start; k < start + q->actions; k++) maxi = (maxi > q->values[k] ? maxi : q->values[k]);
    return maxi;
}

int cmp(const void* a, const void* b){
    int *x = (int*) a;
    int *y = (int*) b;
    return *x-*y;
}

int bestId(struct pair *pos, struct Q_Table *q){
    int start = (pos->first * q->cols + pos->second) * q->actions;
    //printf("pos = {%d, %d}, start = %d\n",pos->first, pos->second, start);
    double maxi = -1e9;
    int res = 0;
    for(int k = start; k < start + q->actions; k++) {
        if(q->values[k] > maxi){
            maxi = q->values[k];
            res = k-start;
        }
    }
    return res;
}

struct pair sum(struct pair *a, const struct pair *b){
    struct pair res = {a->first + b->first, a->second + b->second};
    return res;
}



double epsilon(double x){
    //greater a greater decrement
    double a = 30.0;
    return ((pow(a,x)-1.0)/(a-1.0));
}

struct Q_Table learn(struct gamingBoard *gb, int explorations, struct pair start){
    struct Q_Table q = {gb->rows, gb->cols, 4, 0.1, 0.95, 1, (double*)malloc(q.actions*q.rows*q.cols*sizeof(double))};
    for(int i = 0; i<q.rows; i++){
        for(int j = 0; j<q.cols; j++){
            for(int k = 0; k<q.actions; k++){
                struct pair pos = {i,j};
                struct pair to = sum(&pos, &mov[k]);
                if(posOk(&to, gb)) q.values[idTable(&pos, &q, k)] = 0;
            }
        }
    }
    const int MAX_ACTIONS = gb->rows*gb->cols/1.4;
    for(int i = 0; i<explorations; i++){
        struct pair currPos = start;
        int finished = 0, actions = 0;
        do{
            double r = (double)rand() / RAND_MAX;
            double rew;
            struct pair next;
            int action;
            //random action
            if(r < epsilon(q.epsilonExp))
                action = rand()%q.actions;
            //best action until now
            else
                action = bestId(&currPos, &q);
            next = sum(&currPos, &mov[action]);
            if(!posOk(&next, gb)){
                finished = 1;
                continue;
            }
            rew = reward(&next, gb);    
            double curr = q.values[idTable(&currPos, &q, action)];
            q.values[idTable(&currPos, &q, action)] = (1-q.learningRate) * curr + q.learningRate * (rew + q.gamma * best(&next,&q));
            currPos = next;
            if(rew == 100 || rew == -100) finished = 1;
            
        }while(!finished && ++actions < MAX_ACTIONS);
    }
    return q;
}

void printTable(struct Q_Table *q){
    for(int i = 0; i<q->rows; i++){
        for(int j = 0; j<q->cols; j++){
            printf("%s", "[");
            for(int k = 0; k<q->actions; k++){
                struct pair pos = {i,j};
                printf("%.2f ", (q->values[idTable(&pos, q, k)] > -1e9 ? q->values[idTable(&pos, q, k)] : -10.00));
            }
            printf("%s", "]");
        }
        printf("\n");
    }
}

void printBestPath(struct pair start, struct Q_Table *q, struct gamingBoard *gb){
    //vado sempre al best finchè non ritorno in una cella già visitata o non sono alla fine
    int * vis = (int*)malloc(q->rows*q->cols*sizeof(int));
    for(int i = 0; i<q->rows*q->cols; i++) vis[i] = 0;
    struct pair curr = start;
    int size = 0;
    struct pair *best = (struct pair*)malloc(size * sizeof(struct pair));
    while(1){
        if(gb->data[id(&curr, gb)] == end){
            printf("Reached the end\n");
            size++;
            best = (struct pair*)realloc(best, size*sizeof(struct pair));
            best[size-1] = curr;
            break;
        }
        vis[curr.first*q->cols+curr.second] = 1;
        int bestAction = bestId(&curr, q);
        struct pair to = sum(&curr, &mov[bestAction]);
        if(to.first < 0 || to.first >= gb->rows || to.second < 0 || to.second >= gb->cols)
            printf("to = {%d, %d} ", to.first, to.second);
        if(!posOk(&to,gb) || vis[to.first*q->cols+to.second]) break;
        size++;
        best = (struct pair*)realloc(best, size*sizeof(struct pair));
        best[size-1] = curr;
        curr = to;
    }
    for(int i = 0; i<gb->rows; i++){
        for(int j = 0; j<gb->cols; j++){
            struct pair pos = {i,j};
            int found = 0;
            for(int k = 0; k<size && !found; k++){
                if(pos.first == best[k].first && pos.second == best[k].second){
                    printf("%s ", "H");
                    found = 1;
                }
            }
            if(!found) printf("%c ",print[gb->data[id(&pos, gb)]]);
        }
        printf("%c", '\n');
    }
    free(best);
    free(vis);
}

int endReachable(struct pair curr, struct gamingBoard *gb, int* vis){
    //printf("curr = {%d, %d}\n", curr.first, curr.second);
    int m = 0;
    if(gb->data[id(&curr,gb)] == end) return 1;
    for(int i = 0; i<sizeof(mov)/sizeof(struct pair); i++){
        struct pair to = sum(&curr, &mov[i]);
        //se è dentro la griglia e non l'ho visitato e non è una mina lo visito
        if(posOk(&to,gb) && !vis[id(&to, gb)] && gb->data[id(&curr,gb)] != mine){
            vis[id(&to, gb)] = 1;
            m |= endReachable(to, gb, vis);
        }
    }
    return m;
}

void fillGrid(struct gamingBoard *gb){
    int *vis = (int*)malloc(gb->rows*gb->cols*sizeof(int));
    struct pair begin = {0,0};
    gb->data = (enum square*) malloc(gb->rows * gb->cols * sizeof(enum square));
    do{
        for(int i = 0; i<gb->rows*gb->cols; i++) vis[i] = 0;
        vis[id(&begin, gb)] = 1;
        struct pair pos;
        for(int i = 0; i<gb->rows; i++){
            for(int j = 0; j<gb->cols; j++){
                pos.first = i, pos.second = j;
                gb->data[id(&pos,gb)] = empty;
            }
        }
        gb->data[id(&begin, gb)] = start;
        
        //15% mines, 15% batteries, 1 end
        int perc = gb->rows*gb->cols*15/100;
        for(int m = 0; m<perc; m++){
            do{
                pos.first = rand()%gb->rows, pos.second = rand()%gb->cols;
            }while(gb->data[id(&pos,gb)] != empty);
            gb->data[id(&pos,gb)] = mine;
            do{
                pos.first = rand()%gb->rows,pos.second = rand()%gb->cols;
            }while(gb->data[id(&pos,gb)] != empty);
            gb->data[id(&pos,gb)] = battery;
        }
        do{
            pos.first = rand()%gb->rows,pos.second = rand()%gb->cols;
        }while(gb->data[id(&pos,gb)] != empty);
        gb->data[id(&pos,gb)] = end;
    }while(!endReachable(begin, gb, vis));
    free(vis);
}

int main(){
    srand(time(NULL));
    struct gamingBoard gb;
    vaildInput("Inserire il numero di righe\n", &gb.rows, "Il numero di righe deve essere positivo\n");
    vaildInput("Inserire il numero di colonne\n", &gb.cols, "Il numero di colonne deve essere positivo\n");
    //access [i*m + j]
    fillGrid(&gb);
    printGrid(&gb);
    printf("%s", "\n\n\n");
    struct pair start = {0,0};
    /*
    //inizio da una posizione random
    struct pair start;
    do{
        start.first = rand()%gb.rows, start.second = rand()%gb.cols;
    }while(gb.data[id(&start,&gb)] != empty);
    printf("start = {%d, %d}\n", start.first, start.second);
    */
    struct Q_Table q = learn(&gb, 1e6, start);
    //printTable(&q);
    printBestPath(start, &q, &gb);
    free(q.values);
    free(gb.data);
}