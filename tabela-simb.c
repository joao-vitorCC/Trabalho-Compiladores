#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int s=0;
enum tipo{
	VAR,
	FUN
};
struct elem{
	char nome[100];
	enum tipo t;
	int pos;
};
struct tbs{
	struct  tbs *pai;
	struct elem elems[4];
	struct  tbs *filho;
};
struct  tbs * iniciarTabelaSim(){
	struct tbs * ini;
	ini = (struct tbs *)malloc(sizeof(struct tbs));
	ini->pai = NULL;
	ini->filho = NULL;
return ini;	
}
void novoEscopo(struct tbs * tb){
	struct tbs * novo;
	novo = iniciarTabelaSim();
	tb->filho = novo;
	novo->pai = tb;
}
/*void criaVet(struct tbs * tb){
	tb->elems = (struct elem *)malloc(4 * sizeof(struct elem));
}*/
void insereVar(struct tbs * tb,char name[],int type,int position){
	tb->elems[s].pos = position;
	strcpy(tb->elems[s].nome,name);
	tb->elems[s].t = VAR;
}
struct  tbs* encontraUltimo(struct  tbs* tb){
	struct tbs * ultimo;
	ultimo = tb;
	while(ultimo->filho != NULL){
		ultimo = ultimo->filho;
	} 
return ultimo;
}
struct  tbs* encontraPrimeiro(struct  tbs* tb){
	struct tbs * primeiro;
	primeiro = tb;
	while(primeiro->pai != NULL){
		primeiro = primeiro->pai;
	} 
return primeiro;
}
/*struct tbs * busca(struct tbs * tb,char valor[]){
	int tam;
}*/ 
/*int tamanhoVetor(struct elem * vet){
	printf("%ld\n");
	return sizeof(vet)/sizeof(vet[0]);
}*/
int main(){
	struct tbs * tb1;
	struct tbs * tb2;
	struct elem * e;
	tb1 = iniciarTabelaSim();
	insereVar(tb1,"var1",VAR,10);
	e = tb1->elems;
	//strcpy(tb1->elems[0].nome,"fun1");
	//tb1->elems[0].t = FUN;
	novoEscopo(tb1);
	novoEscopo(tb1->filho);
	printf("%ld\n",sizeof(*tb1));
	tb2 = encontraPrimeiro(tb1->filho);
	printf("1 %s - %d - %p\n",tb1->elems[2].nome,tb1->elems[0].t,tb1);
	printf("%p %p\n",tb2,tb2->filho);
	/*
	strcpy(tb1.elems[0].nome,"var1");
	tb1.elems[0].t = FUN;
	tb1.pTbs = &tb2;
	printf("%s - %d",tb1.elems[0].nome,tb1.elems[0].t);*/
return 0;
}
