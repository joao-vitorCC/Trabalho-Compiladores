%{
#include<stdio.h>
#include"lex.yy.h"
#include"ast.h"
extern int yylex();
//FILE *yyin;
void yyerror(char const *);
extern int yylineno;
extern char * yytext;
struct no * ast = NULL;

%}

%union{
	struct no * no;
	char * str;
}
%start programa
%token <str> INT
%token <str> ID
%token PV
%token V
%token AP
%token FP
%token AC
%token FC
%token CAR
%token RETORNE
%token LEIA
%token ESCREVA
%token <str> CADEIACARACTER
%token NOVALINHA
%token SE
%token ENTAO
%token SENAO
%token ENQUANTO
%token EXECUTE
%token ATRIB
%token OU
%token E
%token EQUAL
%token DIF
%token MENOR
%token MAIOR
%token MAIOREQUAL
%token MENOREQUAL
%token SUM
%token SUB
%token MUL
%token DIV
%token EXCL
%token <str> NUM
%token PROGRAMA
%token <str> CADEIA
%type<str> tipo
%type<no> lvalueexpr
%type<no> programa declfunvar declprog declvar declfunc listaparametros bloco
%type<no> listadeclvar listacomando comando expr orexpr andexpr eqexpr
%type<no> desigexpr addexpr mulexpr unexpr primexpr listexpr 
%%
programa: declfunvar declprog {
					$$ = $2;
					ast = $$;
					printf("No Raiz");
				}
declfunvar: tipo ID declvar PV declfunvar
| tipo ID declfunc declfunvar
|;
declprog: PROGRAMA bloco;
declvar: V ID declvar | ;
declfunc: AP listaparametros FP bloco ;
listaparametros:  | listaparametroscont ;
listaparametroscont: tipo ID| tipo ID V listaparametroscont ;
bloco: AC listadeclvar listacomando FC | AC listadeclvar FC;
listadeclvar: | tipo ID declvar PV listadeclvar;
tipo: INT {
		$$ = "int";
		printf("no Int -- %s\n",yytext);
	}
	| CAR {
		$$ = "car";
		printf("no CAR -- %s\n",yytext);
	}; 
listacomando: comando | comando listacomando;
comando: PV | expr PV | RETORNE expr PV | LEIA lvalueexpr PV | ESCREVA expr PV 
| ESCREVA CADEIACARACTER PV | NOVALINHA PV | SE AP expr FP ENTAO comando |
SE AP expr FP ENTAO comando SENAO comando | ENQUANTO AP expr FP EXECUTE comando | bloco;
expr: orexpr{
			$$ = criaNo(orexpr,"","",$1,NULL,NULL,NULL);
			printf("no orexpr\n");
} 			
| lvalueexpr ATRIB expr{
						$$ = criaNo(exprAtrib,"","",$1,$3,NULL,NULL);
						printf("no atribuicao \n");	
};
orexpr: orexpr OU andexpr{
						$$ = criaNo(exprOr,"","",$1,$3,NULL,NULL);
						printf("no or \n");
} 
| andexpr{
		$$ = criaNo(andexpr,"","",$1,NULL,NULL,NULL);
		printf("no andexpr\n");	
};
andexpr: andexpr E eqexpr{
						$$ = criaNo(exprAnd,"","",$1,$3,NULL,NULL);
						printf("no and \n");
} 
| eqexpr{
		$$ = criaNo(eqexpr,"","",$1,NULL,NULL,NULL);
			printf("no eqexpr\n");
};
eqexpr: eqexpr EQUAL desigexpr{
								$$ = criaNo(exprEq,"","",$1,$3,NULL,NULL);
								printf("no igual\n");
} 
| eqexpr DIF desigexpr{
						$$ = criaNo(exprDif,"","",$1,$3,NULL,NULL);
						printf("no diferente\n");
} 
| desigexpr{
			$$ = criaNo(desigexpr,"","",$1,NULL,NULL,NULL);
			printf("no desigexpr\n");
};
desigexpr: desigexpr MENOR addexpr{
									$$ = criaNo(exprMenor,"","",$1,$3,NULL,NULL);
						  		printf("no menor\n");
}
| desigexpr MAIOR addexpr{
							$$ = criaNo(exprMaior,"","",$1,$3,NULL,NULL);
						  		printf("no maior\n");
} 
| desigexpr MAIOREQUAL addexpr{
								$$ = criaNo(exprMaiorEq,"","",$1,$3,NULL,NULL);
						  		printf("no maior igual\n");
}
| desigexpr MENOREQUAL addexpr{
								$$ = criaNo(exprMenorEq,"","",$1,$3,NULL,NULL);
						  		printf("no menor igual\n");
} 
| addexpr{
			$$ = criaNo(addexpr,"","",$1,NULL,NULL,NULL);
			printf("no addexpr\n");
};
addexpr: addexpr SUM mulexpr{
								 $$ = criaNo(exprAdicao,"","",$1,$3,NULL,NULL);
						  		printf("no adicao\n");
							} 
| addexpr SUB mulexpr{
						  $$ = criaNo(exprSubtracao,"","",$1,$3,NULL,NULL);
						  printf("no subtracao\n");
					} 

| mulexpr{
		  $$ = criaNo(mulexpr,"","",$1,NULL,NULL,NULL);
			printf("no mulexpr\n");
};
mulexpr: mulexpr MUL unexpr{
							$$ = criaNo(exprMult,"","",$1,$3,NULL,NULL);
							printf("no multiplicacao expr\n");
							} 
| mulexpr DIV unexpr {
						$$ = criaNo(exprDiv,"","",$1,$3,NULL,NULL);
						printf("no divisao expr\n");	
					}
| unexpr{
		$$ = criaNo(unexpr,"","",$1,NULL,NULL,NULL);
		printf("no unexpr\n");	
};
unexpr: SUB primexpr {
						$$ = criaNo(exprInv,"","",$2,NULL,NULL,NULL);
						printf("no iverte sinal expr\n");	
					 }
| EXCL primexpr {
					$$ = criaNo(exprNeg,"","",$2,NULL,NULL,NULL);
					printf("no negacao expr\n");	
				}
| primexpr{
			$$ = criaNo(primExpr,"","",$1,NULL,NULL,NULL);
			printf("no primExpr\n");
};
lvalueexpr: ID {
					if($1 != NULL){
						$$ = criaNo(lvalueexpr,$1,"",NULL,NULL,NULL,NULL);
						printf("no lvalueexpr %s\n",$$->nome);
						free($1);
					}					
				};
primexpr: ID AP listexpr FP {
						if($1 != NULL){
							$$ = criaNo(exprChamaFuncParam,$1,"",$3,NULL,NULL,NULL);
							printf("no funcao sem parametro **%s**",$1);
							free($1);
						 }	
						}

| ID AP FP {
					if($1 != NULL){
						$$ = criaNo(exprChamaFuncSParam,$1,"",NULL,NULL,NULL,NULL);
						printf("no funcao sem parametro **%s**",$1);
						free($1);
					}
} 
| ID {
		if($1 != NULL){
			$$ = criaNo(exprVar,$1,"",NULL,NULL,NULL,NULL);
			printf("no variavel **%s**",$1);
			free($1);
		}
     }
| CADEIA{
			if($1 != NULL){
				printf("no Cadeia **%s**\n",$1);
				$$ = criaNo(exprCadeiaConst,"",$1,NULL,NULL,NULL,NULL);
				free($1);
			}
		} 

|AP expr FP {
				printf("no (expr)\n");
				$$ = criaNo(exprParen,"","",$2,NULL,NULL,NULL);

}

| NUM{
			if($1 != NULL){
			printf("no numero **%s**\n",$1);
			$$ = criaNo(exprIntConst,"",$1,NULL,NULL,NULL,NULL);
			free($1);
			}
   };
	
listexpr: expr | listexpr V expr;
%%
void yyerror(char const* msg){
	printf("%s -- Linha %d\n",msg, yylineno); 
}

int main(int argc, char**argv){
     if(argc!=2){
          printf("Uso correto: goianinha <nome> \n");
          exit(1);
     }
     yyin=fopen(argv[1],"rt");
     if(yyin)
          return yyparse();
     else 
          yyerror("arquivo nao encontrado");
     return(1);
}

