#A Simple Example Makefile for soshell
#  
# Syntax:
# Alvo: Dependencias
# tab Action 1
# tab Action 2
#
# Variaveis: Compiler, compiler flags, libraries to link, name of of object files
#
CC=cc #definição de variáveis para facilitar a escrita em baixo
FLAGS=-c -Wall
LIBS=-lm -lpthread
OBS=main.o execute.o parse.o socp.o calc.o redirects.o avisos.o ficheiros.o

#Alvo por defeito é o primeiro
all :  soshell
#a seguir aos : seguem.se os ficheiros que são necessários/de que depende o/ao main.o
main.o : shell.h main.c 
	$(CC) $(FLAGS) main.c
execute.o : shell.h execute.c
	$(CC) $(FLAGS) execute.c
parse.o : shell.h parse.c
	$(CC) $(FLAGS) parse.c
socp.o : shell.h socp.c
	$(CC) $(FLAGS) socp.c 
calc.o : shell.h calc.c
	$(CC) $(FLAGS) calc.c
redirects.o: shell.h redirects.c
	$(CC) $(FLAGS) redirects.c
avisos.o : shell.h avisos.c
	$(CC) $(FLAGS) avisos.c
ficheiros.o: shell.h ficheiros.c
	$(CC) $(FLAGS) ficheiros.c
soshell : $(OBS) 
	$(CC) -o soshell  $(OBS) $(LIBS)
#executa com um dos comandos anteriores e corre as linhas abaixo 
clean limpar :S
	rm -f soshell *.o
	rm -f *~
	echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"
