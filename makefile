
# Variáveis
CC = gcc
CFLAGS = -Wall


# Alvo principal
goianinha: goianinha.tab.o lex.yy.o ast.o main.o tabela-simb.o
	$(CC) $(CFLAGS) -o goianinha lex.yy.o goianinha.tab.o ast.o main.o tabela-simb.o

# flex
lex.yy.c: goianinha.l
	flex  --yylineno goianinha.l
	
# bison
goianinha.tab.c: goianinha.y
	bison -d goianinha.y

# Compilação dos arquivos objeto
lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

goianinha.tab.o: goianinha.tab.c
	$(CC) $(CFLAGS) -c goianinha.tab.c
	
ast.o: ast.c
	$(CC) $(CFLAGS) -c ast.c	

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

tabela-simb.o: tabela-simb.c
	$(CC) $(CFLAGS) -c tabela-simb.c

# Limpeza dos arquivos gerados
clean:
	rm -f *.o main

	
