#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"tabelasimb.h"
int main(){
	struct tbs * tb1;
	struct tbs * tb2;
	struct elemVar params[100];
	tb1 = iniciarTabelaSim(NULL);
	insereVar(tb1,"var1",INT,0);
	insereVar(tb1,"var2",CAR,1);
	insereVar(tb1,"var3",INT,2);
	insereVar(tb1,"var4",CAR,3);
	insereVar(tb1,"var5",CAR,4);
	insereVar(tb1,"var6",INT,5);
	criaParametro(params,"p1",0,INT);
	criaParametro(params,"p2",1,INT);
	criaParametro(params,"p3",2,INT);
	insereFun(tb1,"f1",INT,3,params,0);
	printf("%s %s\n",tb1->elemsf[0].param[2].nome,tb1->elems[1].nome);
	removeEscopo(tb1);
	desalocaTabela(tb1);
	//novoEscopo(tb1);
	//novoEscopo(tb1->filho);
	//insereVar(tb1->filho,"var1",CAR,0);
	//printf("%p\n",tb1->filho);
	//tb2 = busca(tb1,"var1");
	//desalocaTabela(tb1);
	//desalocaTabela(tb2);
	//printf("%ld\n",sizeof(*tb1));
	//tb2 = encontraPrimeiro(tb1->filho);
	//printf("%s - %d - %d\n",tb2->elems[0].nome,tb2->elems[0].t,tb2->tamanho);
	//printf("%p %p\n",tb2,tb2->filho);
	/*
	strcpy(tb1.elems[0].nome,"var1");
	tb1.elems[0].t = FUN;
	tb1.pTbs = &tb2;
	printf("%s - %d",tb1.elems[0].nome,tb1.elems[0].t);*/
return 0;
}
