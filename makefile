all:
	flex goianinha.l
	
	gcc -o goi lex.yy.c -lfl



