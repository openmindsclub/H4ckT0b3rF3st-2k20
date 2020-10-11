#include "quad.h"
#include "table_symbole.c"
#include <stdio.h>
#include <string.h>
extern int ntemp;
extern int nbr_inst_if;
extern int varQuad;
/***********************************G�n�ration de quadruplets************************************************/
void generer(char* a, char* b, char* c, char* d){
	liste[qc].opr=strdup(a);
	liste[qc].op1=strdup(b);
	liste[qc].op2=strdup(c);
	liste[qc].res=strdup(d);
	qc++;
}

/**********************************conversion d'un int en chaine de caractere******************************/
char* convert(int i){
	char s[15];
	sprintf(s,"%d",i);
	return strdup(s);
}
/***********************************Quads Expression logiques************************************************/
void quadL(int i, char*b, char* c, char* d){
	switch(i){
		case 1 :
			generer("BNZ",convert(qc+2),b,"");
			
		break;
		case 2 :
			generer("BNZ",convert(qc+4),b,""); 
			generer("BNZ",convert(qc+2),c,"");
			
		break;
		case 3 :
		generer("BZ",convert(qc+4),b,""); 
		generer("BZ",convert(qc+2),c,"");
		
		break;
	}
}

/***********************************Quads Expressions de comparaison************************************************/
void quadC(int i, char* b, char* c, char* d){
	switch(i){
		case 1 :
			generer("-",b,c,d); 
			generer("BG",convert(qc+2),d,"");
		
		break;
		case 2 :
			generer("-",b,c,d); 
			generer("BGE",convert(qc+2),d,"");
			
		break;
		case 3 :
		
			generer("-",b,c,d); 
			generer("BL",convert(ntemp),d,"");	
			
		break;
		case 4 :
			generer("-",b,c,d); 
			generer("BLE",convert(qc+2),d,"");
		
		break;
		case 5 :
			generer("-",b,c,d); 
			generer("BZ",convert(qc+2),d,"");
			
		break;
		case 6 :
			generer("-",b,c,d); 
			generer("BNZ",convert(qc+2),d,"");
			
		break;
	}
}


/***********************************G�n�ration de code machine************************************************/
void assembler(){
	int i,type; element *p;

	printf("\n \n \n");
	FILE* fichier = NULL;
	fichier = fopen("Assembleur.asm", "w+");
	printf("DATA SEGMENT \n");fprintf(fichier,"DATA SEGMENT \n");
	for(i=0;i<200;i++){
		p=TS[i];
		if(p!=NULL){
			do{
				type=gettype(p->nom);
				if(type==1){printf("%s DD ?\n",p->nom);fprintf(fichier,"%s DD ?\n",p->nom);}
				if(type==2){printf("%s DW ?\n",p->nom);fprintf(fichier,"%s DW ?\n",p->nom);}
				if(type==3){printf("%s DB ?\n",p->nom);fprintf(fichier,"%s DB ?\n",p->nom);}
				if(type==4){printf("%s DD ?\n",p->nom);fprintf(fichier,"%s DD ?\n",p->nom);}
				if(type==11){printf("%s DD %s DUP ?\n",p->nom, p->taille);fprintf(fichier,"%s DD %s DUP ?\n",p->nom, p->taille);}
				if(type==12){printf("%s DW %s DUP ?\n",p->nom, p->taille);fprintf(fichier,"%s DW %s DUP ?\n",p->nom, p->taille);}
				if(type==13){printf("%s DB %s DUP ?\n",p->nom, p->taille);fprintf(fichier,"%s DB %s DUP ?\n",p->nom, p->taille);}
				if(type==14){printf("%s DB %s DUP ?\n",p->nom, p->taille);fprintf(fichier,"%s DB %s DUP ?\n",p->nom, p->taille);}
				p=p->suiv;
			} while(p!=NULL);

		}

	}
	
	printf("DATA ENDS\n");fprintf(fichier,"DATA ENDS\n");
	printf("CODE SEGEMENT\n");fprintf(fichier,"CODE SEGEMENT\n");
	printf("ASSUME CS:CODE, DS:DATA\n");fprintf(fichier,"ASSUME CS:CODE, DS:DATA\n");
	printf("MAIN :\n");fprintf(fichier,"MAIN :\n");
	printf("MOV AX,DATA\n");fprintf(fichier,"MOV AX,DATA\n");
	printf("MOV DS,AX\n");fprintf(fichier,"MOV DS,AX\n");
	for(i=0;i<qc;i++){
		printf("etiquette %d : ",i);fprintf(fichier,"etiquette %d : ",i);
		if(strcmp(liste[i].opr,"+")==0){
			if((liste[i].op1[0]=='T')&&(liste[i].op2[0]=='T')){
				printf("ADD AX, BX\n");fprintf(fichier,"ADD AX, BX\n");
			}
			else{
				if(liste[i].op1[0]=='T'){
					printf("ADD AX, %s\n",liste[i].op2);fprintf(fichier,"ADD AX, %s\n",liste[i].op2);
				}
				if(liste[i].op2[0]=='T'){
					printf("ADD AX, %s\n",liste[i].op1);fprintf(fichier,"ADD AX, %s\n",liste[i].op1);
				}
				else{
					printf("MOV AX, %s\n",liste[i].op1);fprintf(fichier,"MOV AX, %s\n",liste[i].op1);
					printf("ADD AX, %s\n",liste[i].op2);fprintf(fichier,"ADD AX, %s\n",liste[i].op2);
				}
			}

	}
		if(strcmp(liste[i].opr,"-")==0){
			if((liste[i].op1[0]=='T')&&(liste[i].op2[0]=='T')){
				printf("SUB AX, BX\n");fprintf(fichier,"SUB AX, BX\n");
			}

			else{
				if(liste[i].op1[0]=='T'){
					printf("SUB AX, %s\n",liste[i].op2);fprintf(fichier,"SUB AX, %s\n",liste[i].op2);
				}
				if(liste[i].op2[0]=='T'){
					printf("SUB AX, %s\n",liste[i].op1);fprintf(fichier,"SUB AX, %s\n",liste[i].op2);
				}
				else{
					printf("MOV AX, %s\n",liste[i].op1);fprintf(fichier,"MOV AX, %s\n",liste[i].op1);
					printf("SUB AX, %s\n",liste[i].op2);fprintf(fichier,"SUB AX, %s\n",liste[i].op2);
				}
			}

	}
	if(strcmp(liste[i].opr,"*")==0){
			if((liste[i].op1[0]=='T')&&(liste[i].op2[0]=='T')){
				printf("MUL AX, BX\n");fprintf(fichier,"MUL AX, BX\n");
			}
			else{
				if(liste[i].op1[0]=='T'){
					printf("MUL AX, %s\n",liste[i].op2);fprintf(fichier,"MUL AX, %s\n",liste[i].op2);
				}
				if(liste[i].op2[0]=='T'){
					printf("MUL AX, %s\n",liste[i].op1);fprintf(fichier,"MUL AX, %s\n",liste[i].op1);
				}
				else{
					printf("MOV AX, %s\n",liste[i].op1);fprintf(fichier,"MOV AX, %s\n",liste[i].op1);
					printf("MUL AX, %s\n",liste[i].op2);fprintf(fichier,"MUL AX, %s\n",liste[i].op2);
				}
			}

	}
	if(strcmp(liste[i].opr,"/")==0){
			if((liste[i].op1[0]=='T')&&(liste[i].op2[0]=='T')){
				printf("DIV AX, BX\n");fprintf(fichier,"DIV AX, BX\n");
			}
			else{
				if(liste[i].op1[0]=='T'){
					printf("DIV AX, %s\n",liste[i].op2);fprintf(fichier,"DIV AX, %s\n",liste[i].op2);
				}
				if(liste[i].op2[0]=='T'){
					printf("DIV AX, %s\n",liste[i].op1);fprintf(fichier,"DIV AX, %s\n",liste[i].op1);
				}
				else{
					printf("MOV AX, %s\n",liste[i].op1);fprintf(fichier,"MOV AX, %s\n",liste[i].op1);
					printf("DIV AX, %s\n",liste[i].op2);fprintf(fichier,"DIV AX, %s\n",liste[i].op2);
				}
			}

	}
	if(strcmp(liste[i].opr,"BR")==0){
			printf("JMP etiquette %s\n",liste[i].op1);fprintf(fichier,"JMP etiquette %s\n",liste[i].op1);
	}
	if(strcmp(liste[i].opr,"BG")==0){
			printf("CMP AX, 0\n");fprintf(fichier,"CMP AX, 0\n");
			printf("JG etiquette %s\n",liste[i].op1);fprintf(fichier,"JG etiquette %s\n",liste[i].op1);
	}
	if(strcmp(liste[i].opr,"BGE")==0){
			printf("CMP AX, 0\n");fprintf(fichier,"CMP AX, 0\n");
			printf("JGE etiquette %s\n",liste[i].op1);fprintf(fichier,"JGE etiquette %s\n",liste[i].op1);
	}
	if(strcmp(liste[i].opr,"BL")==0){
			printf("CMP AX, 0\n");fprintf(fichier,"CMP AX, 0\n");
			printf("JL etiquette %s\n",liste[i].op1);fprintf(fichier,"JL etiquette %s\n",liste[i].op1);
	}
	if(strcmp(liste[i].opr,"BLE")==0){
			printf("CMP AX, 0\n");fprintf(fichier,"CMP AX, 0\n");
			printf("JLE etiquette %s\n",liste[i].op1);fprintf(fichier,"JLE etiquette %s\n",liste[i].op1);
	}
	if(strcmp(liste[i].opr,"BZ")==0){
			printf("CMP AX, 0\n");fprintf(fichier,"CMP AX, 0\n");
			printf("JE etiquette %s\n",liste[i].op1);fprintf(fichier,"JE etiquette %s\n",liste[i].op1);
	}
	if(strcmp(liste[i].opr,"BNZ")==0){
			printf("CMP AX, 0\n");fprintf(fichier,"CMP AX, 0\n");
			printf("JNE etiquette %s\n",liste[i].op1);fprintf(fichier,"JNE etiquette %s\n",liste[i].op1);
	}
	if(strcmp(liste[i].opr,"=")==0){
		if(liste[i].res[0]='T'){
			printf("MOV DX, %s\n",liste[i].op1);fprintf(fichier,"MOV DX, %s\n",liste[i].op1);
		}
		else {printf("MOV %s, AX\n",liste[i].res);fprintf(fichier,"MOV %s, AX\n",liste[i].res);}
	}
}
	printf("FIN :\n");fprintf(fichier,"FIN :\n");
	printf("MOV AH,4CH\n");fprintf(fichier,"MOV AH,4CH\n");
	printf("INT 21h\n");fprintf(fichier,"INT 21h\n");
	printf("CODE ENDS\n");fprintf(fichier,"CODE ENDS\n");
	printf("END MAIN\n");fprintf(fichier,"END MAIN\n");
	fclose(fichier);
}

/***********************************Fonction d'affichage des quadruplets************************************************/
void afficher_qdr()
{
printf("\n*********************Quadruplet***********************\n");
FILE* fichier = NULL;
fichier = fopen("Quadruple.txt", "w+");
int i;
fprintf(fichier,"\n*********************Quadruplet***********************\n");
for(i=0;i<qc;i++)
		{

 printf("\n %d - ( %s  ,  %s  ,  %s  ,  %s )",i,liste[i].opr,liste[i].op1,liste[i].op2,liste[i].res);
 fprintf(fichier,"\n %d - ( %s  ,  %s  ,  %s  ,  %s )",i,liste[i].opr,liste[i].op1,liste[i].op2,liste[i].res);
 printf("\n---------------------------------------------------\n");
fprintf(fichier,"\n---------------------------------------------------\n");
}
fclose(fichier);
}

