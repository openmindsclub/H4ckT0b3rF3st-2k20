typedef struct quad quad;
struct quad
{
	char* opr;
	char* op1;
	char* op2;
	char* res;
};

struct quad liste[2000];
int qc = 0;

void generer(char* a, char* b, char* c, char* d);
void quadL(int i, char*b, char* c, char* d);
char* convert(int i);
void quadC(int i, char* b, char* c, char* d);
void afficher_qdr();
void assembler();


