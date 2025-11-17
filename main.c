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
void analise(struct no *n);

struct  tbs * tb; 
int p = 0;

int main(int argc, char**argv){
     if(argc!=2){
          printf("Uso correto: goianinha <nome> \n");
          exit(1);
     }
     yyin=fopen(argv[1],"rt");
     if(yyin){
        int r = yyparse();
        if(r != 1){
        	tb = iniciarTabelaSim(NULL);
    		percorreAst(ast);
    		analise(ast);
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
    
   	switch(n->t){
   		case declFuncVV:
   		case declV:
   		case listaDeclV:
   			if(buscaEscopo(tb,n->nome) == NULL){
	   			insereVar(tb,n->nome,identificaTipo(n->valor),p);
	   			printf("\n%s %s inserido na tab\n",tb->elems[p].nome,n->nome);
	   			p++;
   			}else{printf("\nVariavel %s já existe \n",n->nome);}
   		    
   		break;
   		case programa:
   		break;
   		case declFuncVF:
   		break;
   		case declF:
   		break;
   		case blocoV:
   		case blocoVC:
   			printf("\n bloco\n");
   			novoEscopo(tb);
   			tb = tb->filho;
   			p = 0;
   		break;
   		default:
   		break;
   	}	
   		/*case declV:
   			insereVar(tb,n->nome,identificaTipo(n->valor),p);
   			printf("\n%s %s inserido na tab\n",n->valor,n->nome);
   			p++;
   		break;
   		
   		case listaDeclV:
   			insereVar(tb,n->nome,identificaTipo(n->valor),p);
   			printf("\n%s %s inserido na tab\n",n->valor,n->nome);
   			p++;
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
    }*/
   percorreAst(n->f1);
    percorreAst(n->f2);
   percorreAst(n->f3);
   percorreAst(n->proximo);
}

void analise(struct no *n) {	
    if (n == NULL) {
        return;
    }
    
   	switch(n->t){
   		case exprVar:
   		if(busca(tb,n->nome) != NULL){
	   			printf("\n%s %s encontrado\n",tb->elems[p].nome,n->nome);
   			}else{printf("\nVariavel %s não declarada\n",n->nome);}
   		break;
   		case exprOr:
   		break;
   		default:
   		break;
   	}	
   		/*case declV:
   			insereVar(tb,n->nome,identificaTipo(n->valor),p);
   			printf("\n%s %s inserido na tab\n",n->valor,n->nome);
   			p++;
   		break;
   		
   		case listaDeclV:
   			insereVar(tb,n->nome,identificaTipo(n->valor),p);
   			printf("\n%s %s inserido na tab\n",n->valor,n->nome);
   			p++;
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
    }*/
   analise(n->f1);
    analise(n->f2);
   analise(n->f3);
   analise(n->proximo);
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
