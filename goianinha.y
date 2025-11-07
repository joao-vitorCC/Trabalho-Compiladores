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
	struct no *	no;
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
%token NUM
%token PROGRAMA
%token <str> CADEIA
%type<str> tipo
%type<str> lvalueexpr
%type<no> programa declfunvar declprog declvar declfunc listaparametros bloco
%type<no> listadeclvarlistacomando comando expr orexpr andexpr eqexpr
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
		$$ = yytext;
		printf("no Int -- %s\n",yytext);
	}
	| CAR {
		$$ = yytext;
		printf("no CAR -- %s\n",yytext);
	}; 
listacomando: comando | comando listacomando;
comando: PV | expr PV | RETORNE expr PV | LEIA lvalueexpr PV | ESCREVA expr PV 
| ESCREVA CADEIACARACTER PV | NOVALINHA PV | SE AP expr FP ENTAO comando |
SE AP expr FP ENTAO comando SENAO comando | ENQUANTO AP expr FP EXECUTE comando | bloco;
expr: orexpr ;| lvalueexpr ATRIB expr;
orexpr: orexpr OU andexpr | andexpr;
andexpr: andexpr E eqexpr | eqexpr;
eqexpr: eqexpr EQUAL desigexpr | eqexpr DIF desigexpr | desigexpr;
desigexpr: desigexpr MENOR addexpr | desigexpr MAIOR addexpr | desigexpr MAIOREQUAL addexpr
| desigexpr MENOREQUAL addexpr | addexpr;
addexpr: addexpr SUM mulexpr | addexpr SUB mulexpr | mulexpr;
mulexpr: mulexpr MUL unexpr | mulexpr DIV unexpr | unexpr;
unexpr: SUB primexpr | EXCL primexpr | primexpr;
lvalueexpr: ID {
					$$ = yytext;
					printf("no lvalueexpr %s\n",yytext);
				};
primexpr: ID AP listexpr FP | ID AP FP {$$ = criaNo(exprChamaFuncSParam,"id","",NULL,NULL,NULL,NULL);} | ID {$$ = criaNo(exprVar,"id","",NULL,NULL,NULL,NULL);}| CADEIA |AP expr FP | NUM ;
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

