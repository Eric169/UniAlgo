#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFERSIZE 256

struct ipotesi{
    int ristoranteNeiParaggi;
    int areaBarPerAttesa;
    int venerdiOSabato;
    int fame;
    int affollamento;
    int prezzo;
    int pioggia;
    int prenotazione;
    int tipoRistorante;
    int attesaStimata;
    int esito;
};

struct listaIpotesi{
    struct ipotesi* ipotesiTotali;
    int size;
};

void PrintIpotesi(struct ipotesi* ipotesi){
    printf("Ristorante nei paraggi = %d\nArea Bar = %d\nVenerdi/sabato = %d\nFame = %d\nAffollamento = %d\nPrezzo = %d\nPioggia = %d\nPrenotazione = %d\nTipo ristorante = %d\nAttesa stimata = %d\nEsito = %d\n\n\n",
    ipotesi->ristoranteNeiParaggi, ipotesi->areaBarPerAttesa, ipotesi->venerdiOSabato, ipotesi->fame, ipotesi->affollamento,
    ipotesi->prezzo, ipotesi->pioggia, ipotesi->prenotazione, ipotesi->tipoRistorante, ipotesi->attesaStimata, ipotesi->esito);
}

void Compare(struct ipotesi* current, struct ipotesi* toCompare){
    if(current->ristoranteNeiParaggi != -1 && current->ristoranteNeiParaggi != toCompare->ristoranteNeiParaggi) current->ristoranteNeiParaggi=-1;
    if(current->areaBarPerAttesa != -1 && current->areaBarPerAttesa != toCompare->areaBarPerAttesa) current->areaBarPerAttesa=-1;
    if(current->venerdiOSabato != -1 && current->venerdiOSabato != toCompare->venerdiOSabato) current->venerdiOSabato=-1;
    if(current->fame != -1 && current->fame != toCompare->fame) current->fame=-1;
    if(current->affollamento != -1 && current->affollamento != toCompare->affollamento) current->affollamento=-1;
    if(current->prezzo != -1 && current->prezzo != toCompare->prezzo) current->prezzo=-1;
    if(current->pioggia != -1 && current->pioggia != toCompare->pioggia) current->pioggia=-1;
    if(current->prenotazione != -1 && current->prenotazione != toCompare->prenotazione) current->prenotazione=-1;
    if(current->tipoRistorante != -1 && current->tipoRistorante != toCompare->tipoRistorante) current->tipoRistorante=-1;
    if(current->attesaStimata != -1 && current->attesaStimata != toCompare->attesaStimata) current->attesaStimata=-1;
}

void CopyIpotesi(struct ipotesi *res, struct ipotesi *toCopy){
    res->affollamento = toCopy->affollamento;
    res->areaBarPerAttesa = toCopy->areaBarPerAttesa;
    res->attesaStimata = toCopy->attesaStimata;
    res->fame = toCopy->fame;
    res->pioggia = toCopy->pioggia;
    res->prenotazione = toCopy->prenotazione;
    res->prezzo = toCopy->prezzo;
    res->ristoranteNeiParaggi = toCopy->ristoranteNeiParaggi;
    res->tipoRistorante = toCopy->tipoRistorante;
    res->venerdiOSabato = toCopy->venerdiOSabato;
    res->esito = 1;
}

int CalcolaIpotesi(struct listaIpotesi* ipotesiTotali, struct ipotesi* ipotesiFinale){
    int i;
    struct ipotesi result;
    for(i = 0; i<ipotesiTotali->size; i++)
        if(ipotesiTotali->ipotesiTotali[i].esito){
            result = ipotesiTotali->ipotesiTotali[i];
            break;
        }
    if(i == ipotesiTotali->size) return 0;
    i++;
    for(; i < ipotesiTotali->size; i++){
        struct ipotesi toCompare = ipotesiTotali->ipotesiTotali[i];
        if(toCompare.esito)
            Compare(&result, &toCompare);
    }
    CopyIpotesi(ipotesiFinale, &result);
    return 1;
}

int EndPtrOk(char *endPtr){
    if(*endPtr != '\0' && *endPtr != '\n'){
        printf("Errore nella lettura del file\n");
        return 0;
    }
    return 1;
}

int validValue(int val, int check){
    switch (check)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 6:
        case 7:
        case 10:
            return (val == 0 || val == 1);
        case 4:
        case 5:
            return (val == 0 || val == 1 || val == 2);
        case 8:
        case 9:
            return (val == 0 || val == 1 || val == 2 || val == 3);
        default:
            return 0;
    }
}

int LineToIpotesi(char *line, struct ipotesi* toRead){
    char* endPtr;
    int toValid = 0;
    //printf("ristorante nei paraggi\n");
    char* in = strtok(line,"|");
    long res = strtol(in, &endPtr, 10);
    if(!EndPtrOk(endPtr) || !validValue(res, toValid++)) return 0;
    toRead->ristoranteNeiParaggi = res;
    //printf("area bar\n");
    in = strtok(NULL, "|");
    res = strtol(in, &endPtr, 10);
    if(!EndPtrOk(endPtr) || !validValue(res, toValid++)) return 0;
    toRead->areaBarPerAttesa = res;
    //printf("giorno\n");
    in = strtok(NULL, "|");
    res = strtol(in, &endPtr, 10);
    if(!EndPtrOk(endPtr) || !validValue(res, toValid++)) return 0;
    toRead->venerdiOSabato = res;
    //printf("fame\n");
    in = strtok(NULL, "|");
    res = strtol(in, &endPtr, 10);
    if(!EndPtrOk(endPtr) || !validValue(res, toValid++)) return 0;
    toRead->fame = res;
    //printf("affollato\n");
    in = strtok(NULL, "|");
    res = strtol(in, &endPtr, 10);
    if(!EndPtrOk(endPtr) || !validValue(res, toValid++)) return 0;
    toRead->affollamento = res;
    //printf("prezzo\n");
    in = strtok(NULL, "|");
    res = strtol(in, &endPtr, 10);
    if(!EndPtrOk(endPtr) || !validValue(res, toValid++)) return 0;
    toRead->prezzo = res;
    //printf("pioggia\n");
    in = strtok(NULL, "|");
    res = strtol(in, &endPtr, 10);
    if(!EndPtrOk(endPtr) || !validValue(res, toValid++)) return 0;
    toRead->pioggia = res;
    //printf("prenotazione\n");
    in = strtok(NULL, "|");
    res = strtol(in, &endPtr, 10);
    if(!EndPtrOk(endPtr) || !validValue(res, toValid++)) return 0;
    toRead->prenotazione = res;
    //printf("tipo\n");
    in = strtok(NULL, "|");
    res = strtol(in, &endPtr, 10);
    if(!EndPtrOk(endPtr) || !validValue(res, toValid++)) return 0;
    toRead->tipoRistorante = res;
    //printf("attesa\n");
    in = strtok(NULL, "|");
    res = strtol(in, &endPtr, 10);
    if(!EndPtrOk(endPtr) || !validValue(res, toValid++)) return 0;
    toRead->attesaStimata = res;
    //printf("esito\n");
    in = strtok(NULL, "|");
    res = strtol(in, &endPtr, 10);
    if(!EndPtrOk(endPtr) || !validValue(res, toValid++)) return 0;
    toRead->esito = res;
    //printf("ritorno1\n");
    return 1;
}

void AddIpotesi(struct listaIpotesi *ipotesiTotali, struct ipotesi ipotesi){
    ipotesiTotali->size++;
    ipotesiTotali->ipotesiTotali = (struct ipotesi*)realloc(ipotesiTotali->ipotesiTotali, ipotesiTotali->size*sizeof(struct ipotesi));
    ipotesiTotali->ipotesiTotali[ipotesiTotali->size-1] = ipotesi;
}

int inputFile(char* nomeFile, struct listaIpotesi* ipotesiTotali){
    FILE *file = fopen(nomeFile, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return 0;
    }
    char line[BUFFERSIZE];
    while(fgets(line, BUFFERSIZE, file) != NULL){
        struct ipotesi tmp;
        if(!LineToIpotesi(line, &tmp)) return 0;
        AddIpotesi(ipotesiTotali, tmp);
    }
    return 1;
}

int readInt(char message[]){
    const char errorMessage[] = "Input non valido\n";
    int ok = 0;
    int var;
    while(!ok){
        char c;
        ok = 1;
        printf("%s",message);
        if(scanf("%d", &var) != 1){
            ok = 0;
            printf(errorMessage);
        }
        while((c = getc(stdin)) != EOF && c != '\n');
    }
    return var;
}

char* readString(char message[]){
    char* string = (char*)malloc(100);
    printf("%s", message);
    scanf("%99s", string);
    return string;
}

struct ipotesi inputConsole(struct listaIpotesi* ipotesiTotali, int test){
    int aggiungi = 1;
    while(aggiungi){
        struct ipotesi tmp;
        int in;
        while((in = readInt("C'è un ristorante nei paraggi (vero[1], falso[0])\n")) != 0 && in != 1);
        tmp.ristoranteNeiParaggi = in;
        while((in = readInt("Il ristorante ha un'area bar per l'attesa (vero[1], falso[0])\n")) != 0 && in != 1);
        tmp.areaBarPerAttesa = in;
        while((in = readInt("Giorno della settimana in cui si vuole andare al ristorante (vero[1] se venerdì oppure sabato, falso[0] diversamente)\n")) != 0 && in != 1);
        tmp.venerdiOSabato = in;
        while((in = readInt("Siamo affamati (vero[1], falso[0])\n")) != 0 && in != 1);
        tmp.fame = in;
        while((in = readInt("Quante persone sono presenti nel ristorante (nessuno[0], qualcuno[1], pieno[2])\n")) != 0 && in != 1 && in != 2);
        tmp.affollamento = in;
        while((in = readInt("Categoria di costo del ristorante ($[0], $$[1], $$$[2])\n")) != 0 && in != 1 && in != 2);
        tmp.prezzo = in;
        while((in = readInt("Fuori sta piovendo (vero[1], falso[0])\n")) != 0 && in != 1);
        tmp.pioggia = in;
        while((in = readInt("Abbiamo prenotato (vero[1], falso[0])\n")) != 0 && in != 1);
        tmp.prenotazione = in;
        while((in = readInt("Tipo di ristorante (italiano[0], francese[1], fast-food[2], thai[3])\n")) != 0 && in != 1 && in != 2 && in != 3);
        tmp.tipoRistorante = in;
        while((in = readInt("Stima del tempo di attesa (<10[0], 10-29[1], 30-60[2], >60[3])\n")) != 0 && in != 1 && in != 2 && in != 3);
        tmp.attesaStimata = in;
        while((in = readInt("Conviene aspettare? (si[1], no[0])\n")) != 0 && in != 1);
        tmp.esito = in;
        if(!test){
            AddIpotesi(ipotesiTotali, tmp);
            while((aggiungi = readInt("Vuoi aggiungere altre ipotesi?(si[1], no[0])\n")) != 0 && aggiungi != 1);
        }
        else return tmp;
    }
    struct ipotesi empty;
    return empty;
}

int Test(struct ipotesi *ipotesiFinale, struct ipotesi *test){
    return ((ipotesiFinale->affollamento == -1 || ipotesiFinale->affollamento == test->affollamento) &&
     (ipotesiFinale->areaBarPerAttesa == -1 || ipotesiFinale->areaBarPerAttesa == test->areaBarPerAttesa) &&
     (ipotesiFinale->attesaStimata == -1 || ipotesiFinale->attesaStimata == test->attesaStimata) &&
     (ipotesiFinale->fame == -1 || ipotesiFinale->fame == test->fame) &&
     (ipotesiFinale->pioggia == -1 || ipotesiFinale->pioggia == test->pioggia) &&
     (ipotesiFinale->prenotazione == -1 || ipotesiFinale->prenotazione == test->prenotazione) &&
     (ipotesiFinale->prezzo == -1 || ipotesiFinale->prezzo == test->prezzo) &&
     (ipotesiFinale->ristoranteNeiParaggi == -1 || ipotesiFinale->ristoranteNeiParaggi == test->ristoranteNeiParaggi) &&
     (ipotesiFinale->tipoRistorante == -1 || ipotesiFinale->tipoRistorante == test->tipoRistorante) &&
     (ipotesiFinale->venerdiOSabato == -1 || ipotesiFinale->venerdiOSabato == test->venerdiOSabato));
}

void MostraTest(struct ipotesi *ipotesiFinale, struct ipotesi *test, struct listaIpotesi *ipotesiTotali){
    int esito = Test(ipotesiFinale, test);
    if(esito == test->esito) printf("Esito = %d Indovinato!\n", esito);
    else{
        printf("Esito = %d Sbagliato, aggiungo il test ai dati del training e ricalcolo l'ipotesi finale\n", esito);
        printf("Test\n");
        PrintIpotesi(test);
        AddIpotesi(ipotesiTotali, *test);
        CalcolaIpotesi(ipotesiTotali, ipotesiFinale);
        printf("Nuova Ipotesi\n");
        PrintIpotesi(ipotesiFinale);
    }
}

int testFile(char* nomeFile, struct listaIpotesi* ipotesiTotali){
    FILE *file = fopen(nomeFile, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return 0;
    }
    char line[BUFFERSIZE];
    struct ipotesi ipotesiFinale;
    if(!CalcolaIpotesi(ipotesiTotali, &ipotesiFinale)){
        printf("Nel file di training non sono presenti ipotesi con esito positivo\n");
        return 0;
    }
    printf("Ipotesi Finale\n");
    PrintIpotesi(&ipotesiFinale);
    while(fgets(line, BUFFERSIZE, file) != NULL){
        struct ipotesi test;
        if(!LineToIpotesi(line, &test)) return 0;
        MostraTest(&ipotesiFinale, &test, ipotesiTotali);
    }
    return 1;
}

void testConsole(struct listaIpotesi* ipotesiTotali){
    int continua = 1;
    struct ipotesi ipotesiFinale;
    if(!CalcolaIpotesi(ipotesiTotali, &ipotesiFinale)){
        printf("Nel training non sono presenti ipotesi con esito positivo\n");
        return;
    }
    printf("Ipotesi Finale\n");
    PrintIpotesi(&ipotesiFinale);
    while(continua){
        printf("Inserisci l'ipotesi test\n");
        struct ipotesi test = inputConsole(ipotesiTotali, 1);
        MostraTest(&ipotesiFinale, &test, ipotesiTotali);
        while((continua = readInt("Vuoi fare altri test? (si[1], no[0])\n")) != 0 && continua != 1);
    }
}

int main(){
    struct listaIpotesi ipotesiTotali = {NULL, 0};
    int console;
    printf("Se l'input viene dato da file i valori sono tutti interi separati da |\nL'ordine dei dati è lo stesso della descrizione dell'esercizio\nValori attesi:\nAlternativa, Bar, Giorno, Fame, Pioggia, Prenotazione: 0,1\nAffollato e prezzo: 0,1,2 (valgono nell'ordine dato nella spiegazione dell'esercizio)\nTipo e Attesa: da 0 a 3 (valgono nell'ordine dato nella spiegazione dell'esercizio)\nL'ultimo carattere deve essere |\n\n");
    while((console = readInt("Vuoi inserire i dati per il training da file[0] o console[1]?\n")) != 0 && console != 1);
    if(console) inputConsole(&ipotesiTotali, 0);
    else{
        char* nomeFile;
        do{
            nomeFile = readString("Nome file: ");
        }while(!inputFile(nomeFile, &ipotesiTotali));
        free(nomeFile);
    }
    while((console = readInt("Vuoi inserire i dati per i test da file[0] o console[1]?\n")) != 0 && console != 1);
    if(console) testConsole(&ipotesiTotali);
    else{
        char* nomeFile;
        do{
            nomeFile = readString("Nome file: ");
        }while(!testFile(nomeFile, &ipotesiTotali));
        free(nomeFile);
    }
    free(ipotesiTotali.ipotesiTotali);
}