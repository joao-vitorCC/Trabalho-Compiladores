#ifndef TABELASIMB
# define TABELASIMB
#endif
enum tipoVar{
	INT,
	CAR
};
struct elemVar{
	char nome[100];
	int pos;
	enum tipoVar tv;
	
};
struct elemFun{
	char nomeF[100];
	int numArg;
	enum tipoVar tRet;
	struct elemVar * param;
	
};
struct tbs{
	struct  tbs *pai;
	struct elemVar * elems;
	struct elemFun * elemsf;
	struct  tbs *filho;
	int tamanhoV;
	int tamanhoF;
};
struct  tbs * iniciarTabelaSim(struct  tbs *pai);	

void novoEscopo(struct tbs * tb);
void insereVar(struct tbs * tb,char name[],int type,int position);
void insereFun(struct tbs * tb,char name[],int typeRet,int nParam,struct elemVar Params[100],int position);
void criaParametro(struct elemVar params[100],char name[],int pos,int typeP);
struct  tbs* encontraUltimo(struct  tbs* tb);
struct  tbs* encontraPrimeiro(struct  tbs* tb);
struct tbs * busca(struct tbs * tb,char valor[],int * tipovar);
void removeEscopo(struct tbs * tb);
void desalocaTabela(struct tbs* tb);
struct tbs * buscaEscopo(struct tbs * tb,char valor[]);
struct tbs * buscaEscopoFuncao(struct tbs * tb,char valor[]);
