#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
 
void imprimir (struct stat estru);
 
main(int argc, char **argv[])
{
struct stat estru;
struct dirent *dt;
DIR *dire;
char *dir;
int bytes=0;
 
system("clear");
 
scanf("%s",&dir);
 
dire=opendir(&dir);
 
while((dt=readdir(dire)) != NULL){

 stat(dt->d_name, &estru);
 imprimir(estru);
 printf("%-20s %d \n",dt->d_name,estru.st_size);
 bytes=bytes+estru.st_size;
}
bytes=bytes/1024;
printf("\nTotal en KB: %d",bytes);
closedir(dire);
 
}
 
void imprimir (struct stat estru){
 printf( (S_ISDIR(estru.st_mode)) ? "d" : "-" );
 printf( (estru.st_mode & S_IRUSR) ? "r" : "-" );
 printf( (estru.st_mode & S_IWUSR) ? "w" : "-" );
 printf( (estru.st_mode & S_IXUSR) ? "x" : "-" );
 printf( (estru.st_mode & S_IRGRP) ? "r" : "-" );
 printf( (estru.st_mode & S_IWGRP) ? "w" : "-" );
 printf( (estru.st_mode & S_IXGRP) ? "x" : "-" );
 printf( (estru.st_mode & S_IROTH) ? "r" : "-" );
 printf( (estru.st_mode & S_IWOTH) ? "w" : "-" );
 printf( (estru.st_mode & S_IXOTH) ? "x" : "-" );
 printf("%-3s");
}
