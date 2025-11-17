#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"tabelasimb.h"
struct  tbs * iniciarTabelaSim(struct  tbs *pai){
	struct tbs * ini;
	ini = (struct tbs *)malloc(sizeof(struct tbs));
	ini->pai = pai;
	ini->filho = NULL;
	ini->elems = (struct elemVar *)malloc(4 * sizeof(struct elemVar));
	ini->elemsf = (struct elemFun *)malloc(4 * sizeof(struct elemFun));
	ini->tamanhoV = 0;
	ini->tamanhoF = 0;
return ini;	
}

void novoEscopo(struct tbs * tb){
	struct tbs * novo;
	novo = iniciarTabelaSim(tb);
	tb->filho = novo;
}

void insereVar(struct tbs * tb,char name[],int type,int position){
	if (tb->tamanhoV >= 4) {
      		tb->elems  = (struct elemVar *)realloc(tb->elems, (tb->tamanhoV+2) * sizeof(struct elemVar));
    	}
	tb->elems[position].pos = position;
	strcpy(tb->elems[position].nome,name);
	tb->elems[position].tv = type;
	tb->tamanhoV++;
}

void insereFun(struct tbs * tb,char name[],int typeRet,int nParam,struct elemVar Params[100],int position){
	if (tb->tamanhoF >= 4) {
      		tb->elemsf  = (struct elemFun *)realloc(tb->elemsf, (tb->tamanhoF+2) * sizeof(struct elemFun));
    	}
	tb->elemsf[position].numArg = nParam;
	strcpy(tb->elemsf[position].nomeF,name);
	tb->elemsf[position].tRet = typeRet;
	if(nParam > 0){
		tb->elemsf[position].param = Params;
	}
	tb->tamanhoF++;
}

void criaParametro(struct elemVar params[100],char name[],int pos,int typeP){
	strcpy(params[pos].nome,name);
	params[pos].tv = typeP;
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
	struct tbs * atual = encontraUltimo(tb);
	printf("%p\n",atual);
	while (atual != NULL) {
        for (int i = 0; i < atual->tamanhoV; i++) {
            if (strcmp(atual->elems[i].nome, valor) == 0) {
            	//printf("%s - %d - %d\n",atual->elems[0].nome,atual->elems[0].t,atual->tamanho);
                return atual;
            }    
        }
         atual = atual->pai;
    }
    return NULL;
}

struct tbs * buscaEscopo(struct tbs * tb,char valor[]){
        for (int i = 0; i < tb->tamanhoV; i++) {
            if (strcmp(tb->elems[i].nome, valor) == 0) {
            	//printf("%s - %d - %d\n",atual->elems[0].nome,atual->elems[0].t,atual->tamanho);
                return tb;
            }    
        }
    return NULL;
}

void removeEscopo(struct tbs * tb){
	struct tbs * atual;
	struct tbs * pai;
	atual = encontraUltimo(tb);
	if(atual->pai != NULL){
		pai = atual->pai;
		free(pai->filho);
		pai->filho = NULL;
		
	}
}
void desalocaTabela(struct tbs* tb) {
    if (tb == NULL) return;
    if(tb->filho != NULL){
    	desalocaTabela(tb->filho);
    }
    free(tb->elems);
    free(tb->elemsf);
    free(tb);
}

