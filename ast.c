#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum tiposNo{
	programa,
	declFuncV,
	declP
};
struct no{
	enum tiposNo t;
	char nome[10000]; 
	char valor[10000]; 
	struct no *f1;
	struct no* f2;
	struct no *f3;
	struct no * proximo;
	
};
struct no * criaNo(enum tiposNo t, char nome[],char valor[]){
	struct no * novo;
	novo = (struct no *)malloc(sizeof(struct no));
	novo->t = t;
	strcpy(novo->nome,nome);
	strcpy(novo->valor,valor);
	novo->f1 = NULL;
	novo->f2 = NULL;
	novo->f3 = NULL;
	novo->proximo = NULL;
return novo;	
}
int main(){
	struct no * n1;
	enum tiposNo t1 = programa;
	
	n1 = criaNo(t1,"ID1","10");
	printf("%d %s %s",n1->t,n1->nome,n1->valor);

return 0; 
}
