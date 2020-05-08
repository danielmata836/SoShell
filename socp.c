#include "shell.h"  
#define BUFFSIZE 16 

//cópia de ficheiros via thread
void* socpThread(void *args){
  copiar_t *ptr=(copiar_t*) args;
  socp(ptr->fonte, ptr->destino);
  free(ptr);
  return NULL;
}

//cópia de ficheiros normal
void socp(char *fonte, char *destino){
  int fdIn=open(fonte, O_RDONLY);
  if(fdIn==-1)
  	perror("Erro\n");  	 
  int fdOut=creat(destino, S_IRUSR | S_IWUSR);
  if(fdOut==-1)
  	perror("Erro\n"); 
    int n;
  char *buf = malloc(BUFFSIZE);
  while ((n = read (fdIn, buf, BUFFSIZE)) > 0)
    {
      if (write (fdOut, buf, n) != n)
	perror ("Erro de escrita!\n");
    }
  if (n < 0)
    perror ("Erro de leitura!\n");
}

void ioCopy (int entrada, int saida)	//no error reporting
{
  int n;
  char *buf = malloc(BUFFSIZE);
  while ((n = read (entrada, buf, BUFFSIZE)) > 0)
    {
      if (write (saida, buf, n) != n)
	perror ("Erro de escrita!\n");
    }
  if (n < 0)
    perror ("Erro de leitura!\n");
}