all:
	flex goianinha.l

	bison goianinha.y

	gcc -c lex.yy.c

	gcc -c goianinha.tab.c
	
	gcc -g -Wall -ansi -lm lex.yy.o goianinha.tab.o -o goianinha



