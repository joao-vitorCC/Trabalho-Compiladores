#include<stdio.h>
#include<stdlib.h>
#include"ast.h"
#include<string.h>
extern int yylex();
extern FILE *yyin;
extern void yyerror(char const *);
extern int yylineno;
extern char * yytext;
extern struct no * ast;
extern int yyparse();
void percorreAst(struct no *n);


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
    if (n == NULL) {
        return;
    }
	printf("Tipo: %d\n", n->t); // Tipo do nó (se disponível)
    // Imprime informações sobre o nó atual
    if(strcmp(n->nome,"") != 0){
    	printf("Nó: %s\n", n->nome); // Nome do nó
    }
    
        

    // Caso tenha uma subárvore esquerda (esquerda)
    if (n->f1 != NULL) {
        printf("Esquerda de %s:\n", n->nome);
        percorreAst(n->f1);
    }

    // Caso tenha uma subárvore direita (direita)
    if (n->f2 != NULL) {
        printf("Direita de %s:\n", n->nome);
        percorreAst(n->f2);
    }

    // Caso tenha uma lista de próximos nós (por exemplo, comandos ou parâmetros)
    if (n->proximo != NULL) {
        printf("Próximo de %s:\n", n->nome);
        percorreAst(n->proximo);
    }
}
