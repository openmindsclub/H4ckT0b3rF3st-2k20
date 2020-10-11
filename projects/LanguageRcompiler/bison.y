%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "table_symbole.c"
//#include <windows.h>
#include "quad.c"
extern FILE* yyin;/*fichier contenant le code à compiler*/
extern int line;
extern int col;
int sauvtype = 0;
int nbr_inst_if=0;
int ntemp=1;
int qcW[20],qcF[20];
int qcWI=-1,qcFI=-1;
int qcT[20][4];
int qcTI=-1;
int ifelse=-1;
char * idf_prgm;
char varr[100][255];
int j=0; 
int k;
%}
%union
{	int num;
	float flo;
	char *chaine;
	 struct{
		 int type;
		 char *val;
	 } NT;
	
}
%token PRGRM INTEGER FLOAT CHAR BOOL ENND IN 
%token IF ELSEIF ELSE FOR WHILE AND OR
%token DeuxPoints ADD SUB MUL DIV MOD
%token SUPE SUP INFE INF EGAL AFF DIFF PO PF VIR AOUV AFER COUV CFER Sautt 
%token <chaine>IDF
%token <chaine>inte
%token <chaine>reel
%token <chaine>caractere
%token <chaine>booleen

%left PO PF
%left AND
%left OR
%left SUPE SUP INFE INF EGAL DIFF
%left ADD SUB
%left MUL DIV

%type <NT>valeur
%type <NT>Expression_Arth
%type <NT>lgiq
%type <NT>Expression_lgiq
%start start_code
%%

start_code: PRGRM IDF  corps ENND
;

corps:  Instructions corps
		
	
		|
;

Instructions:Declaration
			|Affectation
			|Inst_If
			|boucle_while
			|boucle_for
			;


Declaration:MC_type IDF COUV valeur CFER
			{
			if(declared($2)==1)
			{	yyerror("\n******************* double declaration *****************\n");}
			else 
			{	if(!(($4.type==1)&&(atoi($4.val)>=0)))
				{	err_taille_tab($4.type,$4.val);}	
				else
				{
					inserer($2,10+sauvtype,"tableau",$4.val);
					generer("BOUNDS","1",$4.val,"");
					generer("ADEC",$2,"","");
				}							
			}
			}
			|MC_type IDF COUV IDF CFER
			{
			if(declared($2)==1)
			{	yyerror("\n******************* double declaration *****************\n");}
			else 
			{	if(!((gettype($4)==1)&&(atoi(getValeur($4))>=0)))
				{	err_taille_tab(gettype($4),getValeur($4));}	
				else
				{
					inserer($2,10+sauvtype,"tableau",getValeur($4));
					generer("BOUNDS","1",getValeur($4),"");
					generer("ADEC",$2,"","");
				}							
			}
			}
			|MC_type IDF AFF valeur
			{
				if(declared($2)==1){yyerror("\n***************** double declaration *****************\n");}
				else{
					inserer($2,sauvtype,"variable",$4.val);
					generer("=",$4.val,"",$2);
				}
			}
			
			|MC_type  idfs	
			;
				idfs: IDF	VIR  idfs
						{	
							if(declared($1)==1)
							{	yyerror("\n*****************double declaration *****************\n"); }
							else
							{
								inserer($1,sauvtype,"variable","0");
												
							} 
						} 
					  |IDF
					  {
						if(declared($1)==1)
						{	yyerror("\n*****************double declaration *****************\n");}
						else
						{	inserer($1,sauvtype,"variable","0");}	    
					  }
						;

		MC_type: INTEGER {sauvtype=1;}
				|FLOAT {sauvtype=2;}
				|CHAR {sauvtype=3;}
				|BOOL{sauvtype=4;}
				;

		valeur: inte{{$$.type=1;$$.val=$1;}}
				|reel{{$$.type=2;$$.val=$1;}}
				|caractere{$$.type=3;$$.val=substring($1);	}
				|booleen{$$.type=4;$$.val=$1;}
				;




Affectation: IDF COUV valeur CFER AFF Expression_lgiq
			{
				if(declared($1)==0)
	    		{	yyerror("\n********* erreur semantique : tableau non declare ********\n");}
	    		else
	    		{	if(!(($3.type==1)&&(atoi($3.val)>=0)))
					{	err_taille_tab($3.type,$3.val);}
		    		else 											
					{	err_incompa_typ_tab(gettype($1),$6.type);
						//printf("une affectation à la valeur de %s[%d] \n",$1,$3);
	    				char*s;
	    				s=strdup($1);
	    				sprintf(s, "%s[%d]",$1,atoi($3.val));
						generer("=",$6.val,"",s);					
	    			}
	    		}
    		}
			|IDF COUV IDF CFER AFF Expression_lgiq
			{
				if(declared($1)==0)
	    		{	yyerror("\n********* erreur semantique : tableau non declare ********\n");}
				if(declared($3)==0)
	    		{	yyerror("\n********* erreur semantique : variable non declare ********\n");}
	    		else
	    		{	if(!((gettype($3)==1)&&(atoi(getValeur($3))>=0)))
					{	err_taille_tab(gettype($3),getValeur($3));}
		    		else 											
					{	err_incompa_typ_tab(gettype($1),$6.type);
						//printf("une affectation à la valeur de %s[%d] \n",$1,$3);
	    				char*s;
	    				s=strdup($1);
	    				sprintf(s, "%s[%s]",$1,$3);
						generer("=",$6.val,"",s);					
	    			}
	    		}
    		}
			|IDF AFF Expression_lgiq
			{	if(declared($1)==1)
	    		{	err_incompa_typ_var(gettype($1),$3.type);	}
			else
				{	
					inserer($1,$3.type,"variable",$3.val);
				}
				generer("=",$3.val,"",$1);
				setValeur($1,$3.val);
				ntemp++;
			}	
			|IDF AFF PO  Expression_lgiq  VIR Expression_Arth VIR Expression_Arth PF
			{
				if(declared($1)==0)
	    		{
	    			yyerror("\n************* erreur semantique : variable non declare *********\n");
				}
				qcTI++;
				qcT[qcTI][0]=qc;
				generer("=",$6.val," ",$1);
				qcT[qcTI][1]=qc;
				generer("BR","","","");
				liste[qcT[qcTI][0]-1].op1=convert(qc);
				generer("=",$8.val," ",$1);
				liste[qcT[qcTI][1]].op1=convert(qc);
				qcTI--;
			}
			|IDF ADD AFF valeur
			{
				if(declared($1)==0)
	    		{
	    			yyerror("\n************* erreur semantique : variable non declare *********\n");
				}
				if(gettype($1)!=1)
				{
					yyerror("\n********* erreur semantique : variable pas de type INTEGER *******\n");	
				}
				if($4.type!=1)
				{
					yyerror("\n********* erreur semantique : valeur pas de type INTEGER *******\n");	
				}
				char sss[10];
				sprintf(sss, "T%d", ntemp);
				generer("=",$1," ",sss);	
				generer("+",sss,$4.val,sss);;					
				generer("=",sss," ",$1);	
				int x= atoi(getValeur($1))+atoi($4.val);
				sprintf(sss,"%d",x);
				setValeur($1,sss);			
				ntemp++;	
				
			}
			|IDF SUB AFF valeur
			{
				if(declared($1)==0)
	    		{	yyerror("\n*********** erreur semantique : variable non declare **********\n");}
				if(gettype($1)!=1)
				{	yyerror("\n********* erreur semantique : variable pas de type INTEGER *******\n");	}
				if($4.type!=1)
				{	yyerror("\n********* erreur semantique : valeur pas de type INTEGER *******\n");}
				
				char sss[10];	sprintf(sss, "T%d", ntemp);			
				generer("=",$1," ",sss);					
				generer("-",sss,$4.val,sss);									
				generer("=",sss," ",$1);								
				int x= atoi(getValeur($1))-atoi($4.val);				
				sprintf(sss,"%d",x);			
				setValeur($1,sss);		
				ntemp++;								
			}
;

			
						
		
			Expression_Arth: Expression_Arth ADD Expression_Arth
							{	
								if(($1.type==3)||($3.type==3)||($1.type==4)||($3.type==4))
								{
									yyerror("\n******* Erreur semantique :caractere ou booleen dans une expression arithmetique *******\n");
								}
								else
								{ 
								$$.type=max($1.type,$3.type);
								$1.val=strdup($$.val);
								sprintf($$.val, "T%d", ntemp);
								generer("+",$1.val,$3.val,$$.val);
								ntemp++;
								}
							}
							|Expression_Arth SUB Expression_Arth
							{
							if(($1.type==3)||($3.type==3)||($1.type==4)||($3.type==4))
							{	yyerror("\n******* Erreur semantique :caractere ou booleen dans une expression arithmetique *******\n");							}
							else
							{
								$$.type=max($1.type,$3.type);
								$1.val=strdup($$.val);
								sprintf($$.val, "T%d", ntemp);
								generer("-",$1.val,$3.val,$$.val);
								ntemp++;
							}
							}
						
							| Expression_Arth MUL Expression_Arth
							{
							if(($1.type==3)||($3.type==3)||($1.type==4)||($3.type==4))
							{	yyerror("\n******* Erreur semantique :caractere ou booleen dans une expression arithmetique *******\n");}
							else
							{
								$$.type=max($1.type,$3.type);
								$1.val=strdup($$.val);
								sprintf($$.val, "T%d", ntemp);
								generer("*",$1.val,$3.val,$$.val);								
								ntemp++;
							}
							}

							|Expression_Arth DIV Expression_Arth

							{
							if(($1.type==3)||($3.type==3)||($1.type==4)||($3.type==4))
							{
								yyerror("\n******* Erreur semantique :caractere ou booleen dans une expression arithmetique *******\n");
							}
							else
							{
								if(atoi($3.val)==0)
								{	yyerror("\n *******erreur semantique : division par zero******\n ");}
								else
								{
								$$.type=max($1.type,$3.type);
								$1.val=strdup($$.val);
								sprintf($$.val, "T%d", ntemp);
								generer("/",$1.val,$3.val,$$.val);			
								ntemp++;
								}
							}
							} 

							/*|PO Expression_Arth DIV Expression_Arth PF

							{
							if(($2.type==3)||($4.type==3)||($2.type==4)||($4.type==4))
							{
								yyerror("\n******* Erreur semantique :caractere ou booleen dans une expression arithmetique *******\n");
							}
							else
							{
								if(atoi($4.val)==0)
								{
									yyerror("\n *******erreur semantique : division par zero******\n ");
								}
								else
								{
								
								$$.type=max($2.type,$4.type);
								$2.val=strdup($$.val);
								sprintf($$.val, "T%d", ntemp);
								generer("/",$2.val,$4.val,$$.val);
																
								ntemp++;
								}
							}
							} */
							|IDF
							{
							if(declared($1)==0)
							{
								yyerror("\n******* erreur semantique : variable non declare  *******\n");
							}
							else
							{	
								$$.val=strdup(getValeur($1));
								$$.type=gettype($1);
								
							}
							}
							|IDF COUV valeur CFER
							{
							if(declared($1)==0)
							{	yyerror("\n******* erreur semantique : tableau non declare  *******\n");}
							else
							{	
								if(!(($3.type==1)&&(atoi($3.val)>=0)))
								{	err_taille_tab($3.type,$3.val);	}	
								else
								{
								char*s;	
								s=strdup($1);
								sprintf(s, "%s[%d]", $1,atoi($3.val));
								$$.val=strdup(s);
								$$.type=gettype($1);
								
								}
							}
							}
							|IDF COUV IDF CFER
							{
							if(declared($1)==0)
							{	yyerror("\n******** erreur semantique : tableau non declare  ***********\n");	}
							else
							{
							if(declared($3)==0)
							{	yyerror("\n******** erreur semantique : variable non declare  ***********\n");}
							char*s;	
							s=strdup($1);
							sprintf(s, "%s[%s]", $1,$3);
							$$.val=strdup(s);
							$$.type=gettype($1);
							
							}
							}
							|valeur
							{
								$$.val=$1.val;
								$$.type=$1.type;
							}
							| PO Expression_Arth PF
							{
								$$.val=$2.val;
								$$.type=$2.type;
							}
							;						

Expression_lgiq: 	Expression_lgiq AND Expression_lgiq
					{
							$1.val=strdup($$.val);
							sprintf($$.val,"T%d",ntemp);
							quadL(3,$1.val,$3.val,$$.val);							
							ntemp++;
						} 
					|Expression_lgiq OR Expression_lgiq
					{
						$1.val=strdup($$.val);
						sprintf($$.val,"T%d",ntemp);
						quadL(2,$1.val,$3.val,$$.val);			
						ntemp++;
						}
					|lgiq
					{
						$$.type=$1.type;
					}
					|PO Expression_lgiq PF 
					{
						$$.type=$2.type;
						$$.val=$2.val;
					}
					;
				
				lgiq: lgiq SUPE lgiq
				{	if(!($1.type==$3.type))
					{	yyerror("\n******** erreur semantique : types incompatible  ***********\n");}
					else
					{
						if($1.val==NULL||$3.val==NULL){
							yyerror("\n******** erreur semantique : variable non initialise  ***********\n");	}
					$1.val=strdup($$.val);
					sprintf($$.val,"T%d",ntemp);
					quadC(2,$1.val,$3.val,$$.val);					
					ntemp++;
					}
				} 

					|lgiq SUP lgiq
					{	if(!($1.type==$3.type))
						{
							yyerror("\n******** erreur semantique : types incompatible  ***********\n");
						}
						if($1.val==NULL||$3.val==NULL){
							yyerror("\n******** erreur semantique : variable non initialise  ***********\n");
						}
						$1.val=strdup($$.val);
						sprintf($$.val,"T%d",ntemp);
						quadC(1,$1.val,$3.val,$$.val);						
						ntemp++;
					}

					|lgiq INFE lgiq
					{	if(!($1.type==$3.type))
						{
							yyerror("\n******** erreur semantique : types incompatible  ***********\n");
						}
						if($1.val==NULL||$3.val==NULL){
							yyerror("\n******** erreur semantique : variable non initialise  ***********\n");
						}
						$1.val=strdup($$.val);
						sprintf($$.val,"T%d",ntemp);
						quadC(4,$1.val,$3.val,$$.val);						
						ntemp++;
						
					}

					|lgiq INF lgiq
					{	if(!($1.type==$3.type))
						{
							yyerror("\n******** erreur semantique : types incompatible  ***********\n");
						}
						if($1.val==NULL||$3.val==NULL){
							//yyerror("\n******** erreur semantique : variable non initialise  ***********\n");
						}
						$1.val=strdup($$.val);
						sprintf($$.val,"T%d",ntemp);
						quadC(3,$1.val,$3.val,$$.val);						
						ntemp++;				
							
					}

					|lgiq EGAL lgiq
					{	if(!($1.type==$3.type))
						{	
							
							yyerror("\n******** erreur semantique : types incompatible  ***********\n");
						}
						if($1.val==NULL||$3.val==NULL){
							//yyerror("\n******** erreur semantique : variable non initialise  ***********\n");
						}
						$1.val=strdup($$.val);
						sprintf($$.val,"T%d",ntemp);
						quadC(5,$1.val,$3.val,$$.val);						
						ntemp++;
					}

					|lgiq DIFF lgiq
					{	if(!($1.type==$3.type))
						{
							yyerror("\n******** erreur semantique : types incompatible  ***********\n");
						}
						if($1.val==NULL||$3.val==NULL){
							yyerror("\n******** erreur semantique : variable non initialise  ***********\n");
						}
						$1.val=strdup($$.val);
						sprintf($$.val,"T%d",ntemp);
						quadC(6,$1.val,$3.val,$$.val);						
						ntemp++;
					}

					|Expression_Arth
					{
						$$.val=$1.val;
						$$.type=$1.type;
					}
					;


Inst_If: IF PO Expression_lgiq PF{qcTI++; qcT[qcTI][0]=qc;}
		AOUV corps AFER {qcT[qcTI][1]=qc;}
		Inst_elif
		;

Inst_elif: ELSEIF	{ifelse=0;generer("BR","","",""); liste[qcT[qcTI][0]-1].op1=convert(qc);}
			 PO Expression_lgiq PF {qcT[qcTI][2]=qc;}
			AOUV corps AFER	{qcT[qcTI][3]=qc;generer("BR","","","");}
			Inst_else 

			|{generer("BR","","","");ifelse=1;}Inst_else

			|{liste[qcT[qcTI][0]-1].op1=convert(qc);qcTI--;}
			;
Inst_else: ELSE {if(ifelse==0)
					{liste[qcT[qcTI][2]-1].op1=convert(qc);}
				if(ifelse==1)
				{
					liste[qcT[qcTI][0]-1].op1=convert(qc);
				}}
			AOUV corps AFER	 	
			{	
				if(ifelse==0){
					liste[qcT[qcTI][3]].op1=convert(qc);
				}
				if(ifelse==1)
				{
					/*liste[qcT[qcTI][0]-1].op1=convert(qc);*/
				}
				liste[qcT[qcTI][1]].op1=convert(qc);
				qcTI--;
			}		
			;










boucle_while: WHILE{qcWI++; qcW[qcWI]=qc;} PO Expression_lgiq PF
				AOUV corps AFER		
				{
					liste[qcW[qcWI]-1].op1=convert(qc);
					generer("BR",convert(qcW[qcWI]),"","");
					qcWI--;
				}
				;

boucle_for: FOR PO IDF IN valeur DeuxPoints valeur PF {
				 if(declared($3)==0){	yyerror("\n******* erreur semantique : idf non declare  *******\n");}
				 if(!(($5.type==1)&&(atoi($5.val)>=0))||!(($7.type==1)&&(atoi($7.val)>=0)))
				{	yyerror("\n******* erreur semantique : valeur pas de type entier positif  *******\n");	}	
				 char s[10];	
				sprintf(s,"T%d",ntemp);
				quadC(3,$5.val,$7.val,s);						
				ntemp++;
				qcFI++;
				qcF[qcFI]=qc;
			 }
			AOUV corps AFER {
					
					generer("BR",convert(qcF[qcFI]-2),"","");
					liste[qcF[qcFI]-1].op1=convert(qc);
				qcFI--;
			}
			;









%%
int yyerror(char* msg)
{printf("%s : ligne %d , colonne : %d\n",msg,line,col);
	exit(EXIT_FAILURE);
}
int main()
{
init();
yyin=fopen("test.txt","r");
if(yyparse()==0)
{		
	printf("\n\t\t***********************************\n");
	printf("\t\t********Parsing Successfull********\t\t\n");
	printf("\t\t***********************************\n");
}
else
{
	printf("faute");
}
afficher();
afficher_qdr();
assembler();
int k=0,h=0;
fclose(yyin);

return 0;

}