#include<stdio.h>
#include<string.h>
enum tiposNo{
	programa,
	declFuncV,
	declP
};
struct no{
	enum tiposNo t;
	char nome[10000]; 
	int valor; 
	char *cadeia;
	struct no *f1;
	struct no* f2;
	struct no *f3;
	struct no * proximo;
	
};

int main(){
	struct no n1;
	n1.t = programa;
	strcpy(n1.nome,"ID1");
	n1.valor = 10;
	printf("%d %s %d",n1.t,n1.nome,n1.valor);

return 0; 
}
