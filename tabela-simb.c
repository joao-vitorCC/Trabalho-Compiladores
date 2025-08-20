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
struct tbs{
	struct elem elems[3];
	struct  tbs *pTbs;
};
int main(){
	struct tbs tb1;
	struct tbs tb2;
	strcpy(tb1.elems[0].nome,"var1");
	tb1.elems[0].t = FUN;
	tb1.pTbs = &tb2;
	printf("%s - %d",tb1.elems[0].nome,tb1.elems[0].t);
return 0;
}
