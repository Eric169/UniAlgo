#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    const char errorMessage[] = "Non e' stato inserito un valore valido\n";
    int limit;
    bool valid;
    do{
        valid = 1;
        printf("Vuoi inserire un limite di tentativi?\nno[0] - si[1]\n");
        if(scanf("%d", &limit) != 1){
            printf(errorMessage);
            valid = 0;
            fflush(stdin);
        }
        if(valid && limit != 0 && limit != 1){
            printf(errorMessage);
            valid = 0;
        }
    }while(!valid);
    if(limit){
        do{
            valid = 1;
            printf("Limite di tentativi: ");
            if(scanf("%d", &limit) != 1){
                printf(errorMessage);
                valid = 0;
                fflush(stdin);
            }
            if(valid && limit <= 0){
                printf(errorMessage);
                valid = 0;
            }
        }while(!valid);
    }
    //se non vuole inserire un limite lo metto a un numero molto grande
    else limit = INT_MAX;
    int l, r;
    do{
        valid = 1;
        printf("Valore minimo: ");
        if(scanf("%d", &l) != 1){
            printf(errorMessage);
            valid = 0;
            fflush(stdin);
        }
        if(valid && l <= 0){
            printf("Il valore minimo deve essere positivo\n");
            valid = 0;
        }
    }while(!valid);
    do{
        valid = 1;
        printf("Valore massimo: ");
        if(scanf("%d", &r) != 1){
            printf(errorMessage);
            valid = 0;
            fflush(stdin);
        }
        if(valid && r < l){
            printf("Il valore massimo deve essere maggiore o uguale del minimo\n");
            valid = 0;
        }
    }while(!valid);
    printf("Pensa a un numero tra %d e %d, provero a indovinarlo\n", l, r);
    int attempts = 0;
    bool found = 0;
    while(!found && limit--){
        int guess = (l+r)/2;
        printf("Tentativo %d: il tuo numero e' %d?\n", ++attempts, guess);
        int res;
        do{
            valid = 1;
            printf("Piu grande[0] - Piu piccolo[1] - Corretto[2]\nRisposta: ");
            if(scanf("%d", &res) != 1){
                printf(errorMessage);
                valid = 0;
                fflush(stdin);
            }
            if(valid && (res < 0 || res > 2)){
                printf(errorMessage);
                valid = 0;
            }
        }while(!valid);
        switch(res){
            case 0:
                l = guess+1;
                break;
            case 1:
                r = guess-1;
                break;
            case 2:
                printf("HO INDOVINATO!");
                found = 1;
                break;
            default:
                printf("Unexpected Error");
                break;
        }
        if(l > r){
            //se non ho ancora trovato il numero giusto vuol dire che l'utente ha fatto qualche errore nel darmi le indicazioni
            printf("Mi sa che hai sbagliato qualche risposta . . .\n");
            break;
        }
    }
    if(!found){
        printf("Purtroppo non sono riuscito ad indovinare :(");
    }
    return 0;
}