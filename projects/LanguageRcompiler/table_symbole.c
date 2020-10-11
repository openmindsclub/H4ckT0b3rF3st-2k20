#include "table_symbole.h"




/*****************************Initialisation de la table des symboles************************************/
void init () {
	int i;
	for(i=0; i<200; i++){
		TS[i]=NULL;
	}
}

/***********************************Fonction de hachagee************************************************/
int hachage(char chaine [])
{
    int i=0,res=0;
    while(chaine[i]!='\0')
    {
        res+=chaine[i];
        i++;
    }
    res=res%200;
    return res;
}

/***********************************Extraction d'une chaine************************************************/
char * substring(char string[]){
    char subbuff[255];
    memcpy( subbuff, &string[1],strlen(string)-1);
    subbuff[strlen(string)-2]='\0';
    return strdup(subbuff);
}

/***********************************Fonction de recherche************************************************/
int rechercher(char nom[], element ** in)
{
	element * q;
	int i = hachage(nom);
	/* le cas ou nom est introuvable */
	if(TS[i]==NULL) {
		*in = NULL;
        return i;
	}
	if(TS[i]!=NULL){
		q = TS[i];
		while(q!=NULL)
{              /* le cas nom est trouvable */
			if (strcmp(q->nom, nom)==0){
				*in = q;
				return -1;
			}
			q=q->suiv;
		} ;
	}
			*in = NULL;
			return i;
}

/***********************************Fonction qui reccup�re le type***************************************/
int gettype(char nom[]){
	element *p;
	int i = rechercher(nom,&p);
	if(i==-1){return p->code;}
}

/**********************Fonction de v�rification de la declaration d'un idf******************************/
int declared(char nom[]){
	element *p;
	int i = rechercher(nom, &p);
	/* nom est d�clar� */
	if(i==-1) return 1;
	/* nom est non d�clar� */
	else return 0;
}
/***********************************Fonction qui retourne le max****************************************/
int max(int a, int b){
	if(a>b) return a;
	return b;
}

/***********************************Fonction d'insertion***********************************************/
void inserer(char nom[], int code,char nature[30], char taille[255]){
	element *p, *q;
	int i = rechercher(nom, &q);
	if (i!=-1){
		p = malloc(sizeof(element));
		strcpy(p->nom,nom);
		p->code = code;
		strcpy(p->nature,nature);
		strcpy(p->taille,taille);
		
		
		p->used=0;
		p->suiv = TS[i];
		TS[i] = p;
	}
}
/**************************************Fonction d'affichage***********************************************/
void afficher(){
	element *p;
printf("\n********************************************\n");
printf("*            Table des symboles            *\n");
printf("********************************************\n");
printf(" __________________________________________________________________\n");
printf("| NomEntite 	       |Type      	   |Information           |\n");
printf("|______________________|___________________|______________________|\n");

int i=0;
  while(i<200)
  {
  	p=TS[i];

  		while(p!=NULL)
  		{
  			 printf("|%21s |%18s | %20s |\n",p->nom,typeVar(p->code),p->nature);
  			 p=p->suiv;
  		}

   i++;
   }
printf("|______________________|___________________|______________________|\n");
}



/*Fonction modifier*/

void modifier( char nom[], int code){
element *p;
int i=rechercher( nom ,&p );
if(p!=NULL){p->code=code;}
}
void getNature(char nom[],char nature[])
{
    element *p;
   int i=rechercher(nom, &p);
   if(p!=NULL){strcpy(p->nature,nature);}

}

 char* getValeur(char* idf){
	element * adr; 
	rechercher(idf,&adr); 
	
	return adr->taille;
}
void setValeur(char* idf,char* valeur){
	element * adr; 
	rechercher(idf,&adr); 
	 if(adr!=NULL){strcpy(adr->taille,valeur);}
}
char* typeVar(int i){
	if(i==1||i==11){
		return "INTEGER";
	}
	if(i==2||i==12){
		return "NUMERIC";
	}
	if(i==3||i==13){
		return "CHARACTER";
	}
	if(i==4||i==14){
		return "LOGICAL";
	}
	return NULL;
}
/*********************************Erreur de declaration de taille tableau*****************************/
void err_taille_tab(int type,char val[]){
	if(type==2)
	{
		yyerror("\n******************* erreur semantique:taille declare reelle *****************\n");
	}
	if(type==3)
	{
		yyerror("\n******************* erreur semantique:taille declare caractere *****************\n");
	}
	
	if(type==4)
	{
		yyerror("\n******************* erreur semantique:taille declare bool ****************\n");
	}
	if((type==1)&&(atoi(val)<=0))
	{
		yyerror("\n********* erreur semantique:taille declare entier negatif **********\n");
	}
}


/*********************************Erreur incompatibilité de type pour variable *****************************/
void err_incompa_typ_var(int typdec,int typvar)
{
	if(((typdec==1)&&(typvar!=1))||((typdec==2)&&(typvar!=2))
		 ||((typdec==3)&&(typvar!=3))||((typdec==4)&&(typvar!=4)))			
	{
		yyerror("\n********* erreur sémantique : incompatibilité de type ***********\n");
		    	
	}
}

/*********************************Erreur incompatibilité de type pour tableau *****************************/
void err_incompa_typ_tab(int typtab,int typvar)
{
	if(((typtab==11)&&(typvar!=1))||((typtab==12)&&(typvar!=2))
		 ||((typtab==13)&&(typvar!=3))||((typtab==14)&&(typvar!=4)))			
	{
		yyerror("\n********* erreur sémantique : incompatibilité de type ***********\n");
		    	
	}
}