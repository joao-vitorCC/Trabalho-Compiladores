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
void insereParam(struct no *n,struct elemVar Parametros[100],int * qtd);
int buscaP(struct elemVar Parametros[100],char val[] );
int vParam(struct no *n,struct elemVar Parametros[100]);
void vTbs(struct tbs * tb);
int numParamChamada(struct no *n);
int verificaParamForm(struct no *n,char val[] );
struct  tbs * tb;

int p = 0;
int f = 0;
int esc=0;

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
			printf("----------------");
			printf("----------------");
			printf("----------------");
    		analise(ast);
			printf("----------------");
			printf("----------------");
			printf("----------------");
    		verifica_expr(ast);
			printf("----------------");
			printf("----------------");
			printf("----------------");
			//vTbs(tb);
        }
     }   
     else 
          yyerror("arquivo nao encontrado");
     return(1);
}


void percorreAst(struct no *n) {
	int qtdP = 0;
	struct elemVar Parametros[100];	
	
    if (n == NULL) {
        return;
    }
    
   	switch(n->t){
   		case declV:
   			if(buscaEscopo(tb,n->nome) == NULL){
	   			insereVar(tb,n->nome,identificaTipo(n->valor),p);
	   			//printf("\n%s %s %s inserido na tab\n",n->valor,tb->elems[p].nome,n->nome);
	   			p++;
	   			if(n->proximo != NULL) strcpy(n->proximo->valor,n->valor);
   			}else{printf("\nErro Semântico: Variavel  %s já existe \n",n->nome);return;}
   			percorreAst(n->f1);
			percorreAst(n->f2);
			percorreAst(n->f3);
			percorreAst(n->proximo);
   			
   		break;
   		
   		case declFuncVV:
   		case listaDeclV:
   			if(buscaEscopo(tb,n->nome) == NULL){
	   			insereVar(tb,n->nome,identificaTipo(n->valor),p);
	   			//printf("\n%s %s %s inserido na tab\n",n->valor,tb->elems[p].nome,n->nome);
	   			p++;
	   			if(n->f1 != NULL) strcpy(n->f1->valor,n->valor);
   			}else{printf("\nErro Semântico: Variavel %s já existe \n",n->nome);return;}
   			percorreAst(n->f1);
			percorreAst(n->f2);
			percorreAst(n->f3);
			percorreAst(n->proximo);
   		break;
   		
   		case declFuncVF:
   				if(buscaEscopoFuncao(tb,n->nome) == NULL){
	   				if(n->f1->f1 == NULL){
	   					qtdP = 0;	
	   				}
	   				else if(n->f1->f1->f1->t == listaParUni){
	   					qtdP = 1;
						//printf("\nlistapara %p \n",n->f1->f2->f1);
	   					//printf("\n p = %s\n",n->f1->f1->f1->nome);

	   					criaParametro(Parametros,n->f1->f1->f1->nome,0,identificaTipo(n->f1->f1->f1->valor));	
	   					//printf("\nlistapara %p \n",n->f1->f1->f1);
	   				}
	   				else if(n->f1->f1->f1->t == listaPar){
	   					insereParam(n->f1->f1->f1,Parametros,&qtdP);
	   				}

		   			if(n->f1->f2->f1 != NULL ){
							//printf("\nverifica param %p\n",n->f1->f2->f1);
		   					if(vParam(n->f1->f2->f1,Parametros) != 0){
		   						insereFun(tb,n->nome,identificaTipo(n->valor),qtdP,Parametros,f);
			   					//printf("\n%s %d %s inserido na tab\n",tb->elemsf[f].nomeF,tb->elemsf[f].tRet,tb->elemsf[f].param[0].nome);
			   					f++;
			   				}
			   		   }
					if(n->f1->f2->f1 == NULL ){
						//printf("\nEntrou aqui %s\n",n->f1->f2->f1->nome);
						insereFun(tb,n->nome,identificaTipo(n->valor),qtdP,Parametros,f);
						//printf("\n%s %d %s inserido na tab\n",tb->elemsf[f].nomeF,tb->elemsf[f].tRet,tb->elemsf[f].param[0].nome);
						f++;
					 }	
					
   			   }else{printf("\nErro Semântico: Funcao %s já existe \n",n->nome);return;}
			
   			percorreAst(n->f1->f2);
			
   			percorreAst(n->f1);
			percorreAst(n->f2);
			percorreAst(n->f3);
   			percorreAst(n->proximo);
   		break;
   		
   		case declF:
   		break;
   		case blocoV:
   		case blocoVC:
   			//printf("\n bloco\n");
   			novoEscopo(tb);
   			tb = tb->filho;
   			//printf("\n esc %p\n",tb);
   			esc++;
   			//printf("\nescopo %d\n",esc);
   			p = 0;
   			f = 0;
   			//percorreAst(n->proximo);
   			//printf("\n fecha bloco\n");
   			esc--;
    		//tb = tb->pai;
    		percorreAst(n->f1);
			percorreAst(n->f2);
			percorreAst(n->f3);
   		break;
   		
   		default:
   		percorreAst(n->f1);
    	percorreAst(n->f2);
    	percorreAst(n->f3);
    	percorreAst(n->proximo);
   		break;
   	}	

}

void analise(struct no *n) {
	int ret;	
    if (n == NULL) {
        return;
    }
   	switch(n->t){
   		case exprVar:
   		if(busca(tb,n->nome,&ret) != NULL || buscaFuncaoParam(tb,n->nome) != NULL){
	   			//printf("\n%s %s encontrado\n",tb->elems[p].nome,n->nome);
   			}else{printf("\nErro Semântico: Variavel %s não declarada\n",n->nome);}
   		break;
		case exprChamaFuncParam:
		case exprChamaFuncSParam:
	   		if(buscaFuncao(tb,n->nome,&ret) != NULL){
		   		//printf("\n%s %s encontrado\n",tb->elemsf[f].nomeF,n->nome);
		   		if(verificaParamForm(n,n->nome) == 0){
		   			printf("\nErro Semântico: numero de parametros invalidos na Funcao %s\n",n->nome);
		   		}
	   		}
			else{printf("\nErro Semântico: Funcao %s não declarada\n",n->nome);}
   		break;
   		default:
		analise(n->f1);
    	analise(n->f2);
   		analise(n->f3);
   		analise(n->proximo);
   		break;
   	}	
   
}

int verifica_expr(struct no *node) {
    if (node == NULL) return -1;


    struct tbs * aux;
    int tipo1, tipo2,ret;

    switch (node->t) {
        case exprIntConst:
            return INT;
        case exprCadeiaConst:
            return CAR; 
        case exprVar:
            aux = busca(tb,node->nome,&ret); 
            if(aux != NULL){
            	if(ret == INT){
		        	//printf("\nINT %s\n",node->nome);
		        	return INT;
            	} 
            	else if(ret == CAR) {
            		//printf("\nCAR %s\n",node->nome);
            		return CAR;
            	}
            }
            break;

        case exprAdicao: 
            tipo1 = verifica_expr(node->f1);
            tipo2 = verifica_expr(node->f2);
			 //printf("\nADD%d - %d \n",tipo1,tipo2);
            if (tipo1 == INT && tipo2 == INT) {
                return INT;
            }
            printf("Erro Semântico: Operação aritmética com tipos incompatíveis.\n");
            return -1;
            break;
		

		 case exprSubtracao: 
            tipo1 = verifica_expr(node->f1);
            tipo2 = verifica_expr(node->f2);
			 //printf("\nSub%d - %d \n",tipo1,tipo2);
            if (tipo1 == INT && tipo2 == INT) {
                return INT;
            }
            printf("Erro Semântico: Operação aritmética com tipos incompatíveis.\n");
            return -1;
            break;			

		case exprMult: 
            tipo1 = verifica_expr(node->f1);
            tipo2 = verifica_expr(node->f2);
			 //printf("\nmult%d - %d \n",tipo1,tipo2);
            if (tipo1 == INT && tipo2 == INT) {
                return INT;
            }
            printf("Erro Semântico: Operação aritmética multiplicacao com tipos incompatíveis.\n");
            return -1;
            break;

			case exprDiv: 
            tipo1 = verifica_expr(node->f1);
            tipo2 = verifica_expr(node->f2);
			 //printf("\ndiv%d - %d \n",tipo1,tipo2);
            if (tipo1 == INT && tipo2 == INT) {
                return INT;
            }
            printf("Erro Semântico: Operação aritmética Divisao com tipos incompatíveis.\n");
            return -1;
            break;		
		
			case exprInv: 
            tipo1 = verifica_expr(node->f1);
			 //printf("\ninv%d  \n",tipo1);
            if (tipo1 == INT) {
                return INT;
            }
            printf("Erro Semântico: Operação aritmética inverter sinal com tipos incompatíveis.\n");
            return -1;
            break;		

			case exprNeg: 
            tipo1 = verifica_expr(node->f1);
			 //printf("\nneg%d\n",tipo1);
            if (tipo1 == INT) {
                return INT;
            }
			else if(tipo1 == CAR){
				return CAR;
			}
            printf("Erro Semântico: Operação negacao com tipos incompatíveis.\n");
            return -1;
            break;				
		
		case exprAtrib: 
		    tipo1 = verifica_expr(node->f1);
		    tipo2 = verifica_expr(node->f2);
            //printf("\natrib%d - %d \n",tipo1,tipo2);

            if (tipo1 != -1 && tipo1 == tipo2) {
				//printf("\nAtribuicao\n");
                return tipo1; 
            }
            printf("Erro Semântico: expressao atribuicao  com tipos incompatíveis.\n");
            return -1;
            break;

		case lvalueexpr: 
   		 aux = busca(tb, node->nome, &ret); 
    
   		 if (aux != NULL) {
       		 if (ret == INT || ret == CAR) { 
            	return ret;
        	  }
        // Tipo não reconhecido, mas a variável existe
        printf("\nErro Semântico: Variável %s com tipo não suportado (%d).\n", node->nome, ret);
        return -1;
       }
    	// Variável NÃO encontrada
   		 printf("\nErro Semântico: Variável %s não declarada no escopo.\n", node->nome);
   		 return -1;
    	

        case exprEq: 
		    tipo1 = verifica_expr(node->f1);
		    tipo2 = verifica_expr(node->f2);
            //printf("\nEQ%d - %d \n",tipo1,tipo2);
            // Tipos devem ser os mesmos (ou compatíveis, e.g., int == char)
            if (tipo1 != -1 && tipo1 == tipo2) {
                return INT; // Expressões relacionais retornam 'bool' (representado por int)
            }
            printf("Erro Semântico: expressao igual Comparação com tipos incompatíveis.\n");
            return -1;
            break;

			case exprDif: 
		    tipo1 = verifica_expr(node->f1);
		    tipo2 = verifica_expr(node->f2);
            //printf("\nDIF%d - %d \n",tipo1,tipo2);
            // Tipos devem ser os mesmos (ou compatíveis, e.g., int == char)
            if (tipo1 != -1 && tipo1 == tipo2) {
                return INT; // Expressões relacionais retornam 'bool' (representado por int)
            }
            printf("Erro Semântico: expressao diferente Comparação com tipos incompatíveis.\n");
            return -1;
            break;

			case exprMenor: 
		    tipo1 = verifica_expr(node->f1);
		    tipo2 = verifica_expr(node->f2);
            //printf("\nmenor%d - %d \n",tipo1,tipo2);
            // Tipos devem ser os mesmos (ou compatíveis, e.g., int == char)
            if (tipo1 != -1 && tipo1 == tipo2) {
                return INT; // Expressões relacionais retornam 'bool' (representado por int)
            }
            printf("Erro Semântico: expressao Menor Comparação com tipos incompatíveis.\n");
            return -1;
            break;

			case exprMaior: 
		    tipo1 = verifica_expr(node->f1);
		    tipo2 = verifica_expr(node->f2);
            //printf("\nmaior%d - %d \n",tipo1,tipo2);
            // Tipos devem ser os mesmos (ou compatíveis, e.g., int == char)
            if (tipo1 != -1 && tipo1 == tipo2) {
                return INT; // Expressões relacionais retornam 'bool' (representado por int)
            }
            printf("Erro Semântico: expressao Maior Comparação com tipos incompatíveis.\n");
            return -1;
            break;

			case exprMaiorEq: 
		    tipo1 = verifica_expr(node->f1);
		    tipo2 = verifica_expr(node->f2);
            //printf("\nmaior igual%d - %d \n",tipo1,tipo2);
            // Tipos devem ser os mesmos (ou compatíveis, e.g., int == char)
            if (tipo1 != -1 && tipo1 == tipo2) {
                return INT; // Expressões relacionais retornam 'bool' (representado por int)
            }
            printf("Erro Semântico: expressao Maior igual Comparação com tipos incompatíveis.\n");
            return -1;
            break;

			case exprMenorEq: 
		    tipo1 = verifica_expr(node->f1);
		    tipo2 = verifica_expr(node->f2);
            //printf("\nmenor igual%d - %d \n",tipo1,tipo2);
            // Tipos devem ser os mesmos (ou compatíveis, e.g., int == char)
            if (tipo1 != -1 && tipo1 == tipo2) {
                return INT; // Expressões relacionais retornam 'bool' (representado por int)
            }
            printf("Erro Semântico: expressao Menor Igual Comparação com tipos incompatíveis.\n");
            return -1;
            break;

            
			case exprOr: 
		        tipo1 = verifica_expr(node->f1); 
		        tipo2 = verifica_expr(node->f2);
            // Tipos devem ser os mesmos (ou compatíveis, e.g., int == char)
            if (tipo1 != -1 && tipo1 == tipo2) {
                return INT; // Expressões relacionais retornam 'bool' (representado por int)
            }
            //printf("\nOR%d - %d \n",tipo1,tipo2);
            printf("Erro Semântico: expressao or tipos incompatíveis.\n");
            return -1;
            break;         
            
            case exprAnd: 
		        tipo1 = verifica_expr(node->f1);
		        tipo2 = verifica_expr(node->f2);
            // Tipos devem ser os mesmos (ou compatíveis, e.g., int == char)
            if (tipo1 != -1 && tipo1 == tipo2) {
                return INT; // Expressões relacionais retornam 'bool' (representado por int)
            }
            //printf("\nAND%d - %d \n",tipo1,tipo2);
            printf("Erro Semântico: expressao and  tipos incompatíveis.\n");
            return -1;
            break; 

			case exprParen: // ( expr )
			case orexpr: // Nós intermediários que propagam o tipo do filho principal (f1)
			case andexpr:
			case eqexpr:
			case desigexpr:
			case addexpr:
			case mulexpr:
			case unexpr:
			case primExpr:
				// Estes nós geralmente apenas propagam o resultado do seu primeiro (e único) filho
				verifica_expr(node->f1);
			break;
			case exprChamaFuncParam:
			case exprChamaFuncSParam:
				if (buscaFuncao(tb,node->nome,&tipo1)!= NULL){
					return tipo1;
				}else{
					return -1;
				}

			//printf("\nErro Semântico: Checagem de chamada de função pendente/erro.\n");
  			//return -1;
			break;
			case comanRet:
				tipo1 = verifica_expr(node->f1);
				if(tipo1 == INT){return INT;}
				else if(tipo1 == CAR){return CAR;}
				else{return -1;}
			break;

			case programa:
				case declP:
				case declV:
				case blocoVC:
				case listaDeclV:
				case listaCom:
				case comanExpr:
				case comanEscrevaExp:
				case listaComUn:
				case comanLinha:
				case declFuncVF:
				case declFuncVV:
				case comanLeia:
				case declF:
				case comanSe:
				case comanSeSenao:
				case comanEnquanto:
				case comanBloco:
				case blocoV:
				case listaParam:
				case listaPar:
				case listaParUni:
				
				verifica_expr(node->f2); 
				verifica_expr(node->f1);
				verifica_expr(node->f3);
				verifica_expr(node->proximo);			
			break;		
	default:
	
    // Para qualquer outro nó não tratado (e que não seja uma expressão válida)
    printf("\nErro Semântico: Tipo de nó de expressão não reconhecido: %d.\n", node->t);
            
    break;        

    }


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
void insereParam(struct no *n,struct elemVar Parametros[100],int * qtd){
	int i = 0;
	while(n != NULL){
		//printf("\n insereP %s\n",n->nome);
		if(buscaP(Parametros,n->nome) != 0){
			criaParametro(Parametros,n->nome,i,identificaTipo(n->valor));
			i++;
			n = n->proximo;
		}else{
			printf("\nErro Semântico: Parametro %s já existe \n",n->nome);
			return;
		}
	}	
	*qtd = i;
	//printf("\n insereP %d\n",i);
}
int verificaParamForm(struct no *n,char val[] ){
	struct no * aux;
	int ret;
	aux = n;
	if(aux->f1 == NULL){
	     buscaFuncaoNumArg(tb,aux->nome,&ret);
	     printf("\nnum arg = %d %d\n",ret,numParamChamada(aux->f1));
	     if(ret != 0){ return 0;} 
	}else{
		 buscaFuncaoNumArg(tb,aux->nome,&ret);
	     if(numParamChamada(aux->f1) != ret){
	     	printf("\nnum arg = %d %d\n",ret,numParamChamada(aux->f1));
	     	return 0;
	     }
	}	
	
return 1;	
}

int numParamChamada(struct no *n){
int qtd = 0;
	if (n == NULL) {
        return -1;
    }
   	switch(n->t){
   		case exprAdicao: 
 		case exprSubtracao:
		case exprMult:
		case exprDiv:
		case exprNeg:
   		case exprVar:
   			qtd++;
   		break;
   		default:
		numParamChamada(n->f1);
    	numParamChamada(n->f2);
   		numParamChamada(n->f3);
   		numParamChamada(n->proximo);
   		break;
   	}	  	
return qtd;
}
int buscaP(struct elemVar Parametros[100],char val[] ){
	for(int i=0;i< 100;i++){
		if(strcmp(Parametros[i].nome,val) == 0){
			return 0;
		}
	}
return 1;	
}

int vParam(struct no *n,struct elemVar Parametros[100]){
	struct no * aux;
	aux = n;
	while(aux != NULL){
		if(buscaP(Parametros,aux->nome) == 0){
			printf("\nErro Semântico: Variavel %s tem mesmo nome de parametro\n",aux->nome);
			return 0;
		}
		aux = aux->proximo;
	}
	return 1;	
}
void vTbs(struct tbs * tb){
	while(tb != NULL){
		printf("\ntb:%p pai:%p filho:%p TamV = %d TamF = %d \n",tb,tb->pai,tb->filho,tb->tamanhoV,tb->tamanhoF);
		for(int i=0; i< tb->tamanhoV; i++){
			printf("\n%s %d\n",tb->elems[i].nome,tb->elems[i].tv);
		}
		for(int i=0; i< tb->tamanhoF; i++){
			printf("\n%s %d\n",tb->elemsf[i].nomeF,tb->elemsf[i].numArg);
			for(int j = 0; j < tb->elemsf[i].numArg; j++){
				printf("\n%s \n",tb->elemsf[i].param[j].nome);
			}
		}
		tb = tb->pai;	
	}
}
