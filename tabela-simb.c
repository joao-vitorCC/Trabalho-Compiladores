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
	struct elem * elems;
	struct  tbs *filho;
	int tamanho;
};
struct  tbs * iniciarTabelaSim(struct  tbs *pai){
	struct tbs * ini;
	ini = (struct tbs *)malloc(sizeof(struct tbs));
	ini->pai = pai;
	ini->filho = NULL;
	ini->elems = (struct elem *)malloc(4 * sizeof(struct elem));
	ini->tamanho = 0;
return ini;	
}
void novoEscopo(struct tbs * tb){
	struct tbs * novo;
	novo = iniciarTabelaSim(tb);
	tb->filho = novo;
}
void insereVar(struct tbs * tb,char name[],int type,int position){
	if (tb->tamanho >= 4) {
      tb->elems  = (struct elem *)realloc(tb->elems, 2 * sizeof(struct elem));
    }
	tb->elems[position].pos = position;
	strcpy(tb->elems[position].nome,name);
	tb->elems[position].t = VAR;
	tb->tamanho++;
	printf("debuger : %d %s %d\n",tb->elems[position].pos,tb->elems[position].nome,tb->elems[position].t);
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
struct tbs * busca(struct tbs * tb,char valor[]){
	int tam;
	struct tbs * atual = encontraUltimo(tb);
	printf("%p\n",atual);
	while (atual != NULL) {
        for (int i = 0; i < atual->tamanho; i++) {
            if (strcmp(atual->elems[i].nome, valor) == 0) {
            	printf("%s - %d - %d\n",atual->elems[0].nome,atual->elems[0].t,atual->tamanho);
                return atual;
            }
        }
        atual = atual->filho;
    }
    return NULL;
}
int main(){
	struct tbs * tb1;
	struct tbs * tb2;
	tb1 = iniciarTabelaSim(NULL);
	insereVar(tb1,"var1",VAR,0);
	insereVar(tb1,"var2",VAR,1);
	insereVar(tb1,"var3",VAR,2);
	insereVar(tb1,"var4",VAR,3);
	insereVar(tb1,"var5",VAR,4);
	insereVar(tb1,"var6",VAR,5);
	novoEscopo(tb1);
	//novoEscopo(tb1->filho);
	insereVar(tb1->filho,"var1",VAR,0);
	printf("%p\n",tb1->filho);
	tb2 = busca(tb1,"var1");
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
