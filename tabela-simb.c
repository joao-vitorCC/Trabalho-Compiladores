#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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
	struct elem *elems;
	struct  tbs *filho;
};
struct  tbs* iniciarTabelaSim(){
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
void insereVar(struct tbs * tb,char name[],int type,int position){
	tb->elems = (struct elem *)malloc(4 * sizeof(struct elem));
	tb->elems[0].pos = position;
	strcpy(tb->elems[0].nome,name);
	tb->elems[0].t = VAR;
}
int main(){
	struct tbs * tb1;
	struct tbs tb2;
	tb1 = iniciarTabelaSim();
	insereVar(tb1,"var1",VAR,10);
	//strcpy(tb1->elems[0].nome,"fun1");
	//tb1->elems[0].t = FUN;
	novoEscopo(tb1);
	printf("%s - %d - %p",tb1->elems[0].nome,tb1->elems[0].t,tb1->filho);
	/*
	strcpy(tb1.elems[0].nome,"var1");
	tb1.elems[0].t = FUN;
	tb1.pTbs = &tb2;
	printf("%s - %d",tb1.elems[0].nome,tb1.elems[0].t);*/
return 0;
}
