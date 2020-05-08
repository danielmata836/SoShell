#include "shell.h"

void ftype(char* nome){
    struct stat var;
    stat(nome, &var);
    if((var.st_mode & S_IFREG) == S_IFREG)
        printf("%s: Um ficheiro regular\n", nome);
    if((var.st_mode & S_IFDIR) == S_IFDIR)
        printf("%s: Uma diretoria\n", nome);
    if((var.st_mode & S_IFCHR) == S_IFCHR)
        printf("%s: Um carater especial\n", nome);
    if((var.st_mode & S_IFBLK ) == S_IFBLK )
        printf("%s: Um bloco especial\n", nome); 
    if((var.st_mode & S_IFREG ) == S_IFREG )
        printf("%s: Um bloco regular\n", nome); 
    if((var.st_mode & S_IFLNK ) == S_IFLNK )
        printf("%s: Um link simbólico\n", nome); 
    if((var.st_mode & S_IFSOCK ) == S_IFSOCK )
        printf("%s: Uma socket\n", nome);
    if((var.st_mode & S_IFIFO ) == S_IFIFO )
        printf("%s: Uma FIFO\n", nome);
}

void maior(char* nome1, char* nome2){
    struct stat var1, var2;
    stat(nome1, &var1);
    stat(nome2, &var2);
    if(var1.st_size > var2.st_size)
        printf("Maior %s\n", nome1);
    else
        printf("Maior %s\n", nome2);   
}

void sols(char *nome){
    DIR *dp;
    char pathname[MAXPATHLEN];
    struct dirent *dirp;
    if(strcmp(nome, ".")==0){
        if(getwd(pathname)==NULL)
            printf("Error getting path\n");
        nome=pathname;
    }
    if((dp=opendir(nome))==NULL)
        fprintf(stderr, "Can't open %s\n", nome);
    
    while((dirp = readdir(dp)) != NULL){
        struct stat v;
        stat(dirp->d_name, &v);
        time_t time=v.st_mtime;
        printf("%-15s size=%-15ld last time: %s\n", dirp->d_name, v.st_size, ctime(&time));
    }
    closedir(dp);
}

void setx(char *nome){
    struct stat statbuf;
    if(stat(nome, &statbuf)<0)
        printf("Stat error for %s\n", nome);
    if(chmod(nome, (statbuf.st_mode & S_IXUSR)) < 0)
        printf("Chmod error for %s\n", nome);
}

void removerl(char *nome){
    struct stat statbuf;
    if(stat(nome, &statbuf)<0)
        printf("Stat error for %s\n", nome);
    if(chmod(nome, (statbuf.st_mode &  ~S_IRGRP) | ~S_IROTH) < 0)
        printf("Chmod error for %s\n", nome);
}