#include<stdio.h>
#include<stdlib.h>
#include"ast.h"
#include"tabelasimb.h"
#include<string.h>
extern int yylex();
extern FILE *yyin;
extern void yyerror(char const *);
extern int yylineno;
extern char * yytext;
extern struct no * ast;
extern int yyparse();
void percorreAst(struct no *n);
int identificaTipo(char str[]);

int main(int argc, char**argv){
     if(argc!=2){
          printf("Uso correto: goianinha <nome> \n");
          exit(1);
     }
     yyin=fopen(argv[1],"rt");
     if(yyin){
        int r = yyparse();
        if(r != 1){
    		percorreAst(ast);
        }
     }   
     else 
          yyerror("arquivo nao encontrado");
     return(1);
}

//Função recursiva para percorrer e imprimir a AST
void percorreAst(struct no *n) {
	struct  tbs * tb; 
	int p = 0;
    if (n == NULL) {
        return;
    }
    tb = iniciarTabelaSim(NULL);
   	switch(n->t){
   		case declFuncVV:
   			insereVar(tb,n->nome,identificaTipo(n->valor),p);
   			printf("\n%s %s inserido na tab\n",n->valor,n->nome);
   			p++;
   		break;
   		
   		case declV:
   			insereVar(tb,n->nome,identificaTipo(n->valor),p);
   			printf("\n%s %s inserido na tab\n",n->valor,n->nome);
   			p++;
   		break;
   		
   		case listaDeclV:
   			insereVar(tb,n->nome,identificaTipo(n->valor),p);
   			printf("\n%s %s inserido na tab\n",n->valor,n->nome);
   			p++;
   		break;
   		
   		default:
   		break;
   	}
     printf("Tipo: %d\n", n->t); // Tipo do nó (se disponível)
    // Imprime informações sobre o nó atual
    if(strcmp(n->nome,"") != 0){
    	printf("Nó: %s\n", n->nome); // Nome do nó
    }
    
        

    // Caso tenha uma subárvore esquerda (esquerda)
    if (n->f1 != NULL) {
    	if(strcmp(n->nome,"") != 0){
		printf("Esquerda de %s:\n", n->nome);
        }
        percorreAst(n->f1);
    }

    // Caso tenha uma subárvore direita (direita)
    if (n->f2 != NULL) {
    	if(strcmp(n->nome,"") != 0){
		printf("Direita de %s:\n", n->nome);
        }
        percorreAst(n->f2);
    }

    // Caso tenha uma lista de próximos nós (por exemplo, comandos ou parâmetros)
    if (n->proximo != NULL) {
    	if(strcmp(n->nome,"") != 0){
		printf("Próximo de %s:\n", n->nome);
	}
	percorreAst(n->proximo);	
    }
}

int identificaTipo(char str[]){
	if(strcmp(str,"int") == 0){
		return 0;
	}
	else if(strcmp(str,"car") == 0){
		return 1;
	}
return -1;
}
