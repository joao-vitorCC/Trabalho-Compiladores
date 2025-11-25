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
int verifica_expr(struct no *node);

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
    		//analise(ast);
    		verifica_expr(ast);
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
   		int ret;
   		if(busca(tb,n->nome,&ret) != NULL){
	   			printf("\n%s %s encontrado\n",tb->elems[p].nome,n->nome);
   			}else{printf("\nVariavel %s não declarada\n",n->nome);}
   		break;
   		default:
   		break;
   	}	
   analise(n->f1);
    analise(n->f2);
   analise(n->f3);
   analise(n->proximo);
}

int verifica_expr(struct no *node) {
    if (node == NULL) return -1;

    // Anotação de Tipo: Você precisará adicionar um campo `tipo_resultado` (int) 
    // na sua struct no. Se não puder mudar a struct, use um mapa de hash
    // ou retorne o tipo diretamente, como feito aqui.
    
    int tipo1, tipo2,ret;

    switch (node->t) {
        case exprIntConst:
            return identificaTipo(node->valor);
        case exprCadeiaConst:
            return identificaTipo(node->valor); // Ou um tipo string
        case exprVar:
            // 1. Busca variável (node->nome) na Tabela de Símbolos (busca)
            struct tbs * aux = busca(tb,node->nome,&ret); 
            if(aux != NULL){
            	if(ret == INT){
		        	printf("\nINT %s\n",node->nome);
		        	return INT;
            	} 
            	else if(ret == CAR) {
            		printf("\nCAR %s\n",node->nome);
            		return CAR;
            	}
            }
            // 2. Se encontrada, retorna seu tipo.
            // 3. Se não, erro semântico e retorna TIPO_ERRO.
            // struct elemVar *var = busca_variavel_info(tabela_simbolos_atual, node->nome);
            // return var != NULL ? var->tv : TIPO_ERRO;
            break;

        case exprAdicao: // Aplica-se a SUM, SUB, MUL, DIV
            tipo1 = verifica_expr(node->f1);
            tipo2 = verifica_expr(node->f2);
            if (tipo1 == INT && tipo2 == INT) {
                return INT;
            }
            printf("Operação aritmética com tipos incompatíveis.\n");
            return -1;
            break;

        case exprEq: 
      				// Aplica-se a EQUAL, DIF, MENOR, MAIOR, etc.
		       tipo1 = verifica_expr(node->f1);
		       tipo2 = verifica_expr(node->f2);
            printf("\nEQ%d - %d \n",tipo1,tipo2);
            // Tipos devem ser os mesmos (ou compatíveis, e.g., int == char)
            if (tipo1 != -1 && tipo1 == tipo2) {
                return INT; // Expressões relacionais retornam 'bool' (representado por int)
            }
            printf("expressao eq Comparação com tipos incompatíveis.\n");
            return -1;
            break;

        case exprChamaFuncParam: // Chamada de Função
            // 1. Busca função (node->nome) na Tabela de Símbolos (busca)
            // 2. Se encontrada, obtém assinatura (tipo de retorno e parâmetros).
            // 3. Checa número de argumentos (percorrendo listexpr node->f1).
            // 4. Verifica compatibilidade de tipos dos argumentos.
            // 5. Retorna o tipo de retorno da função.
            break;
            
			case exprOr: // Aplica-se a EQUAL, DIF, MENOR, MAIOR, etc.
		        tipo1 = verifica_expr(node->f1);
		        tipo2 = verifica_expr(node->f2);
            // Tipos devem ser os mesmos (ou compatíveis, e.g., int == char)
            if (tipo1 != -1 && tipo1 == tipo2) {
                return INT; // Expressões relacionais retornam 'bool' (representado por int)
            }
            printf("\nOR%d - %d \n",tipo1,tipo2);
            printf("expressao or Comparação com tipos incompatíveis.\n");
            return -1;
            break;         
            
            case exprAnd: // Aplica-se a EQUAL, DIF, MENOR, MAIOR, etc.
		        tipo1 = verifica_expr(node->f1);
		        tipo2 = verifica_expr(node->f2);
            // Tipos devem ser os mesmos (ou compatíveis, e.g., int == char)
            if (tipo1 != -1 && tipo1 == tipo2) {
                return INT; // Expressões relacionais retornam 'bool' (representado por int)
            }
            printf("\nAND%d - %d \n",tipo1,tipo2);
            printf("expressao and Comparação com tipos incompatíveis.\n");
            return -1;
            break;          
            
            default:
            break;
        // ... Outros casos (AND, OR, NOT, etc.)
    }
     
     //
      verifica_expr(node->proximo);
     verifica_expr(node->f3);
      verifica_expr(node->f2);
     verifica_expr(node->f1);
    
    
    //return -1; // Fallback
}

int identificaTipo(char str[]){
	if(strcmp(str,"int") == 0){
		return INT;
	}
	else if(strcmp(str,"car") == 0){
		return CAR;
	}
return -1;
}
