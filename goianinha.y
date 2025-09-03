%{
#include<stdio.h>
#include"lex.yy.h"
extern int yylex();
FILE *yyin;
void yyerror(char const *);
extern int yylineno;
%}
%start programa
%token INT
%token ID
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
%token CADEIACARACTER
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
%%
programa: declfunvar declprog {printf("l1");};
declfunvar: tipo ID declvar PV declfunvar| tipo ID declfunc declfunvar | ;
declprog: PROGRAMA bloco;
declvar: V ID declvar | ;
declfunc: AP listaparametros FP bloco ;
listaparametros: | listaparametroscont ;
listaparametroscont: tipo ID| tipo ID V listaparametroscont ;
bloco: AC listadeclvar listacomando FC | AC listadeclvar FC;
listadeclvar: | tipo ID declvar PV listadeclvar;
tipo: INT | CAR; 
listacomando: comando | comando listacomando;
comando: PV | expr PV | RETORNE expr PV | LEIA lvalueexpr PV | ESCREVA expr PV 
| ESCREVA CADEIACARACTER PV | NOVALINHA PV | SE AP expr FP ENTAO comando |
SE AP expr FP ENTAO comando SENAO comando | ENQUANTO AP expr FP EXECUTE comando | bloco;
expr: orexpr ;//| lvalueexpr ATRIB asignexpr;
orexpr: orexpr OU andexpr | andexpr;
andexpr: andexpr E eqexpr | eqexpr;
eqexpr: eqexpr EQUAL desigexpr | eqexpr DIF desigexpr | desigexpr;
desigexpr: desigexpr MENOR addexpr | desigexpr MAIOR addexpr | desigexpr MAIOREQUAL addexpr
| desigexpr MENOREQUAL addexpr | addexpr;
addexpr: addexpr SUM mulexpr | addexpr SUB mulexpr | mulexpr;
mulexpr: mulexpr MUL unexpr | mulexpr DIV unexpr | unexpr;
unexpr: SUB primexpr | EXCL primexpr | primexpr;
lvalueexpr: ID;
primexpr: ID AP listexpr FP | ID AP FP | ID | AP expr FP | NUM ;
listexpr: expr | listexpr V expr;
%%
void yyerror(char const* msg){
printf("%s -- Linha %d\n",msg, yylineno); 
}

int main(int argc, char**argv){
     if(argc!=2){
          printf("Uso correto: calc <nome> \n");
          exit(1);
     }
     yyin=fopen(argv[1],"rt");
     if(yyin)
          return yyparse();
     else 
          yyerror("arquivo nao encontrado");
     return(1);
}

