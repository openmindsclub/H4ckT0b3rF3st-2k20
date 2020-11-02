%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bison.tab.h"

 int col=1,line=1;
%}

chiffre [0-9]
lettreMaj [A-Z]
lettremin [a-z]
inte ("("[+-]([1-9][0-9]*|0)")")|([1-9][0-9]*|0)

numeric ("("[+-](([1-9][0-9]*|0)"\."[0-9]*[1-9])")")|(([1-9][0-9]*|0)"\."[0-9]*[1-9])
boolean "TRUE"|"FALSE"
comment \#(.)*[\n]
idf {lettreMaj}({lettremin}|{chiffre})*
chare \'.\'





%%

" " {col+=yyleng;}
 
"PROGRAM" {col+=yyleng; yylval.chaine = strdup(yytext);return(PRGRM);}

"END" {col+=yyleng; yylval.chaine = strdup(yytext);return(ENND);}

"INTEGER" {col+=yyleng; yylval.chaine = strdup(yytext);return(INTEGER);}

"NUMERIC" {col+=yyleng; yylval.chaine = strdup(yytext);return(FLOAT);}

"CHARACTER" {col+=yyleng; yylval.chaine= strdup(yytext); return (CHAR);}

"LOGICAL" {col+=yyleng; yylval.chaine= strdup(yytext); return (BOOL);}



"IF" {col+=yyleng; yylval.chaine= strdup(yytext); return (IF);}

"ELSE IF" {col+=yyleng; yylval.chaine= strdup(yytext); return (ELSEIF);}

"ELSE" {col+=yyleng; yylval.chaine= strdup(yytext); return (ELSE);}

"FOR" {col+=yyleng; yylval.chaine= strdup(yytext); return (FOR);}

"IN" {col+=yyleng; yylval.chaine= strdup(yytext); return (IN);}

"WHILE" {col+=yyleng; yylval.chaine= strdup(yytext); return (WHILE);}

"AND" {col+=yyleng; yylval.chaine= strdup(yytext); return (AND);}

"OR"  {col+=yyleng; yylval.chaine= strdup(yytext); return (OR);}

[:] {col+=yyleng; yylval.chaine= strdup(yytext); return(DeuxPoints);}

"+" {col+=yyleng; yylval.chaine = strdup(yytext); return(ADD);}

"-" {col+=yyleng; yylval.chaine = strdup(yytext); return(SUB);}

"*" {col+=yyleng; yylval.chaine = strdup(yytext); return(MUL);}

"/" {col+=yyleng; yylval.chaine = strdup(yytext); return(DIV);}

"%" {col+=yyleng; yylval.chaine = strdup(yytext); return(MOD);}

">=" {col+=yyleng; yylval.chaine = strdup(yytext); return (SUPE);}

">" {col+=yyleng; yylval.chaine = strdup(yytext); return (SUP);}

"<=" {col+=yyleng; yylval.chaine = strdup(yytext); return (INFE);}

"<" {col+=yyleng; yylval.chaine = strdup(yytext); return (INF);}

"=" {col+=yyleng; yylval.chaine = strdup(yytext); return (EGAL);}

"<-" { col+=yyleng; yylval.chaine = strdup(yytext); return (AFF);}

"!=" {col+=yyleng; yylval.chaine = strdup(yytext); return (DIFF);}

"(" {col+=yyleng; yylval.chaine = strdup(yytext); return (PO);}

")" { col+=yyleng; yylval.chaine = strdup(yytext); return (PF);}

[\,] {col+=yyleng; yylval.chaine = strdup(yytext); return (VIR);}

"{" {col+=yyleng; yylval.chaine = strdup(yytext); return (AOUV); }

"}" {col+=yyleng; yylval.chaine = strdup(yytext); return (AFER);}

"[" {col+=yyleng; yylval.chaine = strdup(yytext); return (COUV); }

"]" {col+=yyleng; yylval.chaine = strdup(yytext); return (CFER);}

[\n] { col=1; line+=yyleng; /*return(Sautt);*/}

[\t] {col+=yyleng;}

{boolean} {col+=yyleng; yylval.chaine = strdup(yytext); return(booleen);}

{inte} {
    char* s=yytext;
    if(s[0]=='(')
    {   int i=0,j=1; char* ch[strlen(yytext)-2];
        for(i=0;i<strlen(s)-1;i++){
             ch[i]=&s[j];
             j++;
        }
        
        sprintf(s,"%d",atoi(*ch));
        if(atoi(*ch)>=-32768){col+=yyleng; yylval.chaine = strdup(s); }
        else{printf("erreur lexicale cet entier est inferieur a -32767 \n ");exit(0);}
    }
    else{
    
       
        if(atoi(yytext)<=32767){col+=yyleng; yylval.chaine = strdup(yytext); }
        else{printf(" erreur lexicale cet entier est supperieur a 32767 \n ");exit(0);}
    }
    return(inte);
}


{numeric} {col+=yyleng; yylval.chaine = strdup(yytext);return(reel);}

{chare} {col+=yyleng; yylval.chaine = strdup(yytext); return(caractere);}

{comment} {col+=yyleng; line+=1; yylval.chaine = strdup(yytext);}



{idf} { if(yyleng>10){printf("erreur lexicale:idf trop long ligne %d colonne %d \n",line,col);exit(0);} else{  col+=yyleng; yylval.chaine = strdup(yytext); return(IDF);}}


. {printf ("\n erreur lexicale entite %s ligne %d colonne %d \n",yytext,line,col);col+=yyleng;exit(0);}

%%
int yywrap () {return 1;}
