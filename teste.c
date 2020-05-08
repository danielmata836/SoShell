#include "shell.h"

char prompt[100];
int numargs = 0;

int main ()
{
  int len;
  char linha[1024];		/* um comando */
  char *args[64];		/* com um maximo de 64 argumentos */

  strcpy (prompt, "SOSHELL: Introduza um comando : prompt>");
  while (1)
    {
      printf ("%s", prompt);
      if (fgets (linha, 1023, stdin) == NULL)
	{
	  printf ("\n");
	  exit (0);
	}
      len = strlen (linha);
      if (1 == len)
	continue;		/* linha é apenas \n */

      if (linha[len - 1] == '\n')
	linha[len - 1] = '\0';
      numargs = parse (linha, args);	/* particiona a string em argumentos */

      if (!builtin (args))
	execute (numargs, args);	/* executa o comando */
    }
  return 0;
}

int builtin (char **args)	//funcionalidades do shell
{
//---sair---
  if (strcmp (args[0], "sair") == 0)
    {
      exit (0);
      return 1;
    }
//---42---  
  if (strncmp (args[0], "42", 2) == 0)
    {
      printf ("42 is the answer to life the universe and everything\n");
      return 1;			/* funcionalidade embutida */
    }
//---obterinfo---  
  if (0 == strcmp (args[0], "obterinfo"))
    {
      printf ("SoShell 2020 versaõ 1.0\n");
      return 1;			//comando embutido
    }
//---PS1---
  if (strlen (args[0]) > 4 && 0 == strncmp (args[0], "PS1=", 4))
    {
      strcpy (prompt, args[0] + 4);
      return 1;			//comando embutido
    }
//---quemsoueu---  
  if (0 == strcmp (args[0], "quemsoueu"))
    {
      system ("id");
      return 1;			//comando embutido
    }
//---cd---   
  if (0 == strcmp (args[0], "cd"))
    {
      int err;
      if (NULL == args[1] || 0 == strcmp (args[1], "~"))
	err = chdir (getenv ("HOME"));
      else
	err = chdir (args[1]);
      if (err < 0)
	perror (args[1]);
      return 1;			//comando embutido
    }
//---socp--
  if (0 == strcmp (args[0], "socp"))
    {
      socp (args[1], args[2]);
      return 1;			//comando embutido
    }
//---calc--- 
  if (0 == strcmp (args[0], "calc") && (numargs == 4))
    {
      calc (args[1], args[2], args[3]);
      return 1;			//comando embutido
    }
//---bits---
  if (0 == strcmp (args[0], "bits") && (numargs == 4))
    {
      bits (args[1], args[2], args[3]);
      return 1;			//commando embutido
    }
//---JPG---
  if (0 == strcmp (args[0], "jpg") && (numargs == 2))
    {
      int fd = open (args[1], O_RDONLY);
      int t = isjpg (fd);
      printf ("%d\n", t);
      return 1;
    }
//---aviso---
  if (strcmp (args[0], "avisoTeste") == 0)
    {
      aviso (args[1], atoi (args[2]));
      return 1;
    }
//---aviso com thread: implemntação propositadamente incorreta---
  if (strcmp (args[0], "aviso") == 0)
    {
      pthread_t th;
      pthread_create (&th, NULL, avisowrapper, (void *) args);
      return 1;
    }
//---aviso com thread: implementação correta---
  if (strcmp (args[0], "avisoC") == 0)
    {
      pthread_t th;
      aviso_t *ptr = (aviso_t *) malloc (sizeof (aviso_t));
      strcpy (ptr->msg, args[1]);
      ptr->tempo = atoi(args[2]);
      pthread_create (&th, NULL, avisowrapperC, (void *) ptr);
      return 1;
    }
  if(strcmp(args[0], "socpth")==0)
    {
      pthread_t th;
      copiar_t *ptr =(copiar_t*)malloc(sizeof(copiar_t));
      strcpy(ptr->fonte, args[1]);
      strcpy(ptr->destino, args[2]);
      pthread_create(&th, NULL, socpThread, (void*)ptr);
    }
  /* IMPORTANTE : 
     Devolver 0 para indicar que não existe comando embutido e que
     será executado usando exec() na função execute.c
   */
  return 0;
}
