#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct string{
    int size;
    char* data;
};

void printString(struct string s){
    for(int i = 0; i<s.size; i++){
        printf("%c", s.data[i]);
    }
    printf("\n");
}

int stringCompare(struct string a, struct string b){
    if(a.size != b.size) return 0;
    for(int i = 0; i<a.size; i++)
        if(a.data[i] != b.data[i]) return 0;
    return 1;
}

struct string noLibreria(struct string first, struct string second){
    if(first.size < second.size) return first;
    struct string res;
    res.size = 0;
    res.data = (char*)malloc(0);
    for(int i = 0; i < first.size; i++){
        res.size++;
        if(i <= first.size - second.size){
            struct string tmp;
            tmp.size = second.size;
            tmp.data = (char*)malloc(tmp.size * sizeof(char));
            for(int j = 0; j<second.size; j++)
                tmp.data[j] = first.data[i+j];
            res.data = (char*) realloc(res.data, sizeof(char)*res.size);
            if(stringCompare(second, tmp)){    
                res.data[res.size-1] = '*';
                i += second.size - 1;
            }
            else res.data[res.size-1] = first.data[i];
        }
        else res.data[res.size-1] = first.data[i];
    }
    return res;
}


struct string Libreria(struct string first, struct string second){
    if(first.size < second.size) return first;
    struct string res;
    res.size = 0;
    res.data = (char*)malloc(0);
    for(int i = 0; i < first.size; i++){
        res.size++;
        if(i <= first.size - second.size){
            if(!strncmp(first.data+i, second.data, second.size)){
                res.data[res.size-1] = '*';
                i += second.size - 1;
            }
            else res.data[res.size-1] = first.data[i];
        }
        else res.data[res.size-1] = first.data[i];
    }
    return res;
}

int main(){
    struct string first, second;
    second.data = (char*)malloc(0);
    second.size = 0;
    int ok;
    do{
        printf("Inserire la prima stringa (max 30 caratteri):\n");
        first.data = (char*)malloc(0);
        first.size = 0;
        ok = 1;
        int c;
        while((c = getchar()) != '\n' && c!=EOF){
            first.size++;
            if(first.size > 30)
                ok = 0;
            else{
                first.data = (char*)realloc(first.data, sizeof(char)*first.size);
                first.data[first.size-1] = c;
            }
        }
        if(!ok){
            printf("La stringa inserita è troppo lunga\n");
            free(first.data);
        }
    }while(!ok);

    do{
        printf("Inserire la seconda stringa (max 30 caratteri):\n");
        second.data = (char*)malloc(0);
        second.size = 0;
        ok = 1;
        int c;
        while((c = getchar()) != '\n' && c!=EOF){
            second.size++;
            if(second.size > 30)
                ok = 0;
            else {
                second.data = (char*)realloc(second.data, sizeof(char)*second.size);
                second.data[second.size-1] = c;
            }
        }
        if(!ok){
            printf("La stringa inserita è troppo lunga\n");
            free(second.data);
        }
    }while(!ok);

    printf("Risultato senza utilizzare <string.h>\n");
    printString(noLibreria(first, second));

    printf("Risultato utilizzando <string.h>\n");
    printString(Libreria(first, second));
}