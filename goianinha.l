%{
enum tokens{
   CAR,INT,PROGRAMA,
   RETORNE,LEIA,ESCREVA,NOVALINHA,
   SE, ENTAO,SENAO,ENQUANTO,EXECUTE,PV,
   AP,FP,ATRIB,EQUAL,DIF,V,MAIOR,MENOR,
   MAIOREQUAL,MENOREQUAL,SUM,SUB,MUL,DIV	
}; 
%}
DIGIT[0-9]
CARACTER[A-Z][a-z]
ID ("_" | {CARACTER}){CARACTER}({CARACTER}*|{DIGIT}*|("_")*)*
%%
"car"   {printf("%s",yytext);return CAR;}
"int"   {printf("%s",yytext);return INT;}
"programa" {printf("%s",yytext);return PROGRAMA;}
"retorne" {printf("%s",yytext);return RETORNE;}
"leia"	{printf("%s",yytext);return LEIA;}
"escreva"	{printf("%s",yytext);return ESCREVA;}
"novalinha" {printf("%s",yytext);return NOVALINHA;}
"se"	{printf("%s",yytext);return SE;}
"entao"	{printf("%s",yytext);}
"senao"	{printf("%s",yytext);}
"enquanto"	{printf("%s",yytext);}
"execute"	{printf("%s",yytext);}
";"	{printf("%s",yytext);return PV;}
"," 	{printf("%s",yytext);return V;}
"("	{printf("%s",yytext);return AP;}
")"	{printf("%s",yytext);return FP;}
"="	{printf("%s",yytext);return ATRIB;}
"=="	{printf("%s",yytext);return EQUAL;}
"!="	{printf("%s",yytext);return DIF;}
">"	{printf("%s",yytext);return MAIOR;}
"<"	{printf("%s",yytext);return MENOR;}
">="	{printf("%s",yytext);return MAIOREQUAL;}
"<="	{printf("%s",yytext);return MENOREQUAL;}
"+"	{printf("%s",yytext);return SUM;}
"-"	{printf("%s",yytext);return SUB;}
"*"	{printf("%s",yytext);return MUL;}
"/"	{printf("%s",yytext);return DIV;}
ID 	{printf("%s",yytext);}
.	{printf("ERRO");}
%%

void main(){
    yylex();
}
