#include <stdio.h>
#include <ctype.h>

int main(){
    int spaces=0,cntrl=0,digit=0,upper=0,lower=0,total=0,alnum=0,alpha=0,punteggiatura=0;
    char c;
    printf("inserisci il testo:\n");
    scanf("%c", &c);
    while(c != '#'){
        //isgraph() non mi serve usarla ma so che esiste :)
        //stessa cosa per isxdigit
        //ho notato che il \n è considerato come spazio
        spaces += ((isspace(c)!=0) && (!iscntrl(c)));
        punteggiatura += (ispunct(c)!=0);
        cntrl += (iscntrl(c)!=0);
        alpha += (isalpha(c)!=0);
        alnum += (isalnum(c)!=0);
        digit += (isdigit(c)!=0);
        upper += (isupper(c)!=0);
        lower += (islower(c)!=0);
        total++;
        scanf("%c", &c);
    }
    printf("Caratteri totali: %d\nCaratteri di controllo: %d\nCaratteri alfanumerici: %d\nNumeri: %d\nLettere: %d\nMaiuscole: %d\nMinuscole: %d\nSpazi: %d\nPunteggiatura: %d\n",
        total, cntrl, alnum, digit, alpha, upper, lower, spaces, punteggiatura);
}