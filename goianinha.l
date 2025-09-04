%option noyywrap
/* Enable Warnings */
%option warn
/* Enable line number */
%option yylineno
/* Make flex create a header file */
%option header-file="lex.yy.h"

%{

#include"goianinha.tab.h"		

%}
DIGIT[0-9]
CARACTER[A-Z]|[a-z]
WHITESPACE      [\t' '\n\r]
%x comentario 

%%
  int lin_ini_com;	
"/*" {BEGIN(comentario); lin_ini_com = yylineno;
       fprintf(stdout,"comentario na linha %d\n",yylineno);
      }
<comentario>[^*\n]* 
<comentario>"*"+[^/\n]
<comentario><<EOF>> {
	fprintf(stdout,"ERRO: comentario da linha %d",lin_ini_com);  
	fprintf(stderr,"nao termina\n");
	return(EOF);
}
<comentario>\n
<comentario>"*"+"/" {BEGIN(INITIAL);} 
{WHITESPACE}+ 		 
"car"   {printf("%s - %d",yytext,CAR);return CAR;}
"int"   {printf("%s - %d",yytext,INT);return INT;}
"programa" {printf("%s - %d",yytext,PROGRAMA);return PROGRAMA;}
"retorne" {printf("%s - %d",yytext,RETORNE);return RETORNE;}
"leia"	{printf("%s - %d",yytext,LEIA);return LEIA;}
"escreva"	{printf("%s - %d",yytext,ESCREVA);return ESCREVA;}
"novalinha" {printf("%s - %d",yytext,NOVALINHA);return NOVALINHA;}
"se"	{printf("%s - %d",yytext,SE);return SE;}
"entao"	{printf("%s - %d",yytext,ENTAO);return ENTAO;}
"senao"	{printf("%s - %d",yytext,SENAO);return SENAO;}
"enquanto"	{printf("%s - %d",yytext,ENQUANTO);return ENQUANTO;}
"execute"	{printf("%s - %d",yytext,EXECUTE);return EXECUTE;}
";"	{printf("%s - %d",yytext,PV);return PV;}
"," 	{printf("%s - %d",yytext,V);return V;}
"("	{printf("%s - %d",yytext,AP);return AP;}
")"	{printf("%s - %d",yytext,FP);return FP;}
"="	{printf("%s - %d",yytext,ATRIB);return ATRIB;}
"=="	{printf("%s - %d",yytext,EQUAL);return EQUAL;}
"!="	{printf("%s - %d",yytext,DIF);return DIF;}
">"	{printf("%s - %d",yytext,MAIOR);return MAIOR;}
"<"	{printf("%s - %d",yytext,MENOR);return MENOR;}
">="	{printf("%s - %d",yytext,MAIOREQUAL);return MAIOREQUAL;}
"<="	{printf("%s - %d",yytext,MENOREQUAL);return MENOREQUAL;}
"+"	{printf("%s - %d",yytext,SUM);return SUM;}
"-"	{printf("%s - %d",yytext,SUB);return SUB;}
"*"	{printf("%s - %d",yytext,MUL);return MUL;}
"/"	{printf("%s - %d",yytext,DIV);return DIV;}
"!"	{printf("%s - %d",yytext,EXCL);return EXCL;}
"e"	{printf("%s - %d",yytext,E);return E;}
"ou"	{printf("%s - %d",yytext,OU);return OU;}
"{"	{printf("%s - %d",yytext,AC);return AC;}
"}"	{printf("%s - %d",yytext,FC);return FC;}
("_"|{CARACTER})({DIGIT}*|{CARACTER}*|"_"*)*	{printf("%s - %d",yytext,ID);return ID;}
{DIGIT}+	{printf("%s - %d",yytext,NUM);return NUM;}
.	{printf("ERRO");}
%%

