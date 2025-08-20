#include<stdio.h>
#include<string.h>
enum tipo{
	VAR,
	FUN
};
struct elem{
	char nome[100];
	enum tipo t;
};
int main(){
	struct elem e[3];
	strcpy(e[0].nome,"var");
	e[0].t = FUN;
	printf("%s - %d",e[0].nome,e[0].t);
return 0;
}
