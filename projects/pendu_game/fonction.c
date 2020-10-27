#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "fonction.h"
#include <time.h>


void rndm_secret(char secret[],char question[])
{
    int i=0,n=0;
    FILE *folder=NULL;
    folder=fopen("secret.txt","r");
    while(fgets(secret,40,folder)!=NULL)
    {
        i++;
    }
    rewind(folder);
    n = (rand() % (i - 1 + 1)) + 1;
    i=0;
    while(i<n)
    {
        fgets(question,80,folder);
        fgets(secret,40,folder);
        i+=2;
        //printf("%s",secret);
    }
	question[strlen(question)]='\0';
	secret[strlen(secret)]='\0';
    fclose(folder);
}


void init(char h[],int *cnd,int *cps,int *wn,char *l,int j)
{
    int i;
    for(i=0; i<j-1; i++)
        {
            h[i]='*';
        }
    h[i]='\0';

    printf("  *****  BIENVENUE AU PENDU !! *****\n\n\n\n\n\n\n\n\n\n\n");
    *cnd=0;
    *cps=10;
    *wn=0;
    *l='0';
}


void verify(char h[],char s[],char l,int* cond)
{
    int i;
    for (i=0; i<strlen(s)-1; i++)
    {
        //if(1) printf("\n%d|%c|%s",(s[i]==l),l,s);
        if (s[i]==l)
        {
            //printf("**%c",l);
            h[i]=l;
            *cond=0;
        }
    }
}

char lireCaractere()
{
    char caractere = 0;

    caractere = getchar();
    caractere = toupper(caractere);

    while (getchar() != '\n') ;

    return caractere;
}


int compare(char hidden[],char secret[])
{
    int i;
    for(i=0; i<strlen(secret); i++)
    {
        if(hidden[i]!=secret[i])
        {
            return 0;
        }
    }

    return 1;
}





