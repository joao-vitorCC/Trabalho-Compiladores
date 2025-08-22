ALFANUM [0-9a-z][a-z0-9]*
%%
"car"   {printf("%s",yytext);}
"int"   {printf("%s",yytext);}
"programa" {printf("%s",yytext);}
"retorne" {printf("%s",yytext);}
"leia"	{printf("%s",yytext);}
"escreva"	{printf("%s",yytext);}
"novalinha" {printf("%s",yytext);}
"se"	{printf("%s",yytext);}
"entao"	{printf("%s",yytext);}
"senao"	{printf("%s",yytext);}
"enquanto"	{printf("%s",yytext);}
"execute"	{printf("%s",yytext);}
"/*"{ALFANUM}"*/" {printf("Comentario");}
.	{printf("ERRO");}
%%

void main(){
    yylex();
}

