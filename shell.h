#include <stdio.h>
#include <stdlib.h>  
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <dirent.h>

typedef struct { 
    char msg[100];
    int tempo;
} aviso_t;

typedef struct {
    char fonte[100]; 
    char destino[100];
} copiar_t;

int parse(char *buf, char **args);

void execute(int numargs, char **args);

int builtin (char **args);

void socp(char *fonte, char *destino);

void ioCopy(int entrada, int saida);

void calc(char *value1, char *op, char *value2);

void bits(char *op1, char *op, char *op2);

int isjpg(int fd);

int* decToBinary(int n);

int redirects (int numargs, char *args[]);

int containsPipe (int numArgs, char **args);

void aviso(char *mesg, int tempo);

void *avisowrapper (void *args);

void *avisowrapperC(void *args);

void *socpThread(void *args);

//funcionalidades adicionais
void ftype(char* nome);
//---
void maior(char* nome1, char* nome2);

void setx(char* nome);

void removerl(char *nome);

void sols(char *nome);

/* constantes que podem tornar uteis*/

#define BG 0
#define FG 1

//ficheiros
#define MAXPATHLEN 50