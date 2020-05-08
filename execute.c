/* 
   execute . cria um processo progénito e executa um programa
*/
#include "shell.h"

int ultimo ( int *numargs, char **args ) 
{
	if ( args[*numargs-1][0]=='&') {
	*numargs=*numargs-1;
	args[*numargs]=NULL ;
	return BG;
	}
	return FG; /*return FG ou BG definidos no shell.h */
}

int containsPipe (int numArgs, char **args)//deteta pipe e devolve o seu indice ou -1 (caso não exista) 
{
  int index;
  for (index = 0; index < numArgs; index++)
    if (args[index][0] == '|')
      {
	return index;
      }
  return -1;
}

void execute (int numargs, char **args)
{
  int pid, status, fd[2], pidFilho;
int code=ultimo(&numargs, args);
  if ((pid = fork ()) < 0)
    { /* cria um processo progenito */
      perror ("forks");/* NOTE: perror() produz uma pequema mensagem de erro para o stream */
      exit (1);/* estandardizado de erros que descreve o ultimo erro encontrado */
               /* durante uma chamada ao sistema ou funcao duma biblioteca */
    }

  if (pid == 0)
    {
      int indice = containsPipe (numargs, args);
      int red=redirects(numargs, args);
      if (indice == -1)
  	execvp (*args, args);
      if (indice > 0){
    	printf ("pipe detected at index %d\n", indice);
    	printf ("Remove PIPE symbol. Create Pipe. Fork(). Exec in 2 Processes\n");
    	args[indice] = NULL;//atribui null à posição do pipe 
    	pipe (fd);//função que cria o pipe (para intercomunicação entre processos e recebe um file descriptor com 2 posições (fd[0]:read end of the pipe, fd[1]:write end of the pipe)
   	 pidFilho = fork ();
    	if (pidFilho == 0)
     	 {
		//write
		numargs = indice;
		fprintf (stderr, "cmd write to pipe: %s numArgs=%d\n", args[0], numargs);
		dup2 (fd[1], STDOUT_FILENO);
		close (fd[0]);
		close (fd[1]);
	 }
    	else
      	{
		//read
		args = args + indice + 1;
		numargs = numargs - indice - 1;
		fprintf (stderr, "cmd read from pipe: %s numArgs=%d\n", args[0], numargs);
		dup2(fd[0], STDIN_FILENO);	//duplicar o descritor de ficheiro de leitura do PIPE para a posição na tabela de FD do STDIN
		close(fd[1]);//fechar o descritor do ficheiro do pipe que este processo não necessita.
      	}
       execvp(*args, args);		//Chamar a função execvp() para executar os comandos agora ligados via um pipe.
      }
      if (red==-1){
        perror("Error");
      	exit(1);
      }
      execvp (*args, args);/* NOTE: as versoes execv() e
                            * execvp() de execl() sao uteis quando */
      perror (*args);      /* o numero de argumentos nao e. conhecido.
                              * Os argumentos de  */
      exit (1);           /* execv() e execvp() sao o nome do ficheiro
                             * a ser executado e um */
    }                    /* vector de strings que contem os
                            * argumentos. O ultimo argument */
if(FG==code){
while (wait (&status) != pid)
    /*spin fazer nada */  ;
}
  return;
}


