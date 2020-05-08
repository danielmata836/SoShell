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
#include"shell.h"
time_t FILE_MODE = S_IRWXU;
//redirects are handled in reverse order
// 2> >> > <
int redirects (int numargs, char *args[])
{
//redirect stdout >
  if (numargs < 3)
    return numargs;
  if (strcmp (args[numargs - 2], ">") == 0)
    {
      int fd = creat (args[numargs - 1], FILE_MODE);
      if (fd < 0){ 
          perror (NULL);
	  return -1;		/*indicar um erro */
	}
      dup2 (fd, STDOUT_FILENO);
      close (fd);
      args[numargs - 2] = NULL;
      numargs = numargs - 2;
    }
 
//tratar do >> open : O_WRONLY | O_APPEND
   if (strcmp (args[numargs - 2], ">>") == 0)
   {
      int fd = open(args[numargs - 1], O_WRONLY | O_APPEND);
    if (fd < 0){ 
       perror (NULL);
       return -1;		/*indicar um erro */
    }
    dup2 (fd, STDOUT_FILENO);
    close (fd);
    args[numargs - 2] = NULL;
    numargs = numargs - 2;
}
//tratar do < open : O_RDONLY
   if (strcmp (args[numargs - 2], "<") == 0)
   {
      int fd = open(args[numargs - 1], O_RDONLY);
    if (fd < 0){ 
       perror ("ERRO");
       return -1;		/*indicar um erro */
    }
    dup2 (fd, STDIN_FILENO);
    close (fd);
    args[numargs - 2] = NULL;
    numargs = numargs - 2;
}
//tratar do 2> 
 if (strcmp (args[numargs - 2], "2>") == 0)
   {
      int fd = open(args[numargs - 1], O_WRONLY | O_RDONLY | FILE_MODE);
    if (fd < 0){ 
       perror ("ERRO");
       return -1;		/*indicar um erro */
    }
    dup2 (fd, STDERR_FILENO);
    close (fd);
    args[numargs - 2] = NULL;
    numargs = numargs - 2;
 }
 return -1;
}