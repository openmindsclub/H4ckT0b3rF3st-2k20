#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "fonction.h"
#include <time.h>

int main(int argc, char* argv[])
{
    srand(time(NULL));
    char secret[40]="";
    char question[80]="";
    char letter='0';
    int coups,j,cond,continu,win,won_nb;
    char* hidden = NULL;

    continu=1;
    won_nb=0;

    hidden=malloc(30);
    if(hidden==NULL) exit(0);

    printf("WELCOME TO PENDU !! PRESS ENTER TO START THE GAME ..\n");

    while(continu==1)
    {
        getchar();
        rndm_secret(secret,question);
        j=strlen(secret);
        init(hidden,&cond,&coups,&win,&letter,j);
        while(coups>0 && win==0)
        {
            if (cond)
            {
                coups--;
            }
            printf("ILS VOUS RESTENT : %d COUPS\n",coups);
            printf("%s\n",question);
            printf("MOT SECRET : %s \nTAPEZ UNE LETTRE :",hidden);
            letter=lireCaractere();
            cond=1;
            verify(hidden,secret,letter,&cond);

            if(compare(hidden,secret))
            {
                win=1;
                won_nb++;
            }
            printf("\n\n");
        }
        continu=0;
        if(win)
        {
            printf("*****   BRAVEAU VOUS AVEZ GAGNE %d FOIS !!  *****\nLE MOT SECRET ETAIT : %s \n\n",won_nb,secret);
            printf("VOULEZ CONTINUER ??   1_CONTUNUER    2_QUITER\n");
            scanf("%d",&continu);
        }
        else
        {
            printf("VOULEZ VOUS REESAYER??\n  1_REESAYER    2_QUITER\n");
            scanf("%d",&continu);
        }
        if (continu==1)  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
    free(hidden);
    return 0;
}
