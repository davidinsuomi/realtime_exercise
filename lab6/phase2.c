#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
    int main(){
    pid_t pid;
    char fd_str[10];
    int fd_int;
    fd_int=open("log.txt",O_CREAT|O_RDWR,0700);
    sprintf(fd_str,"%d",fd_int);
    pid=fork();
    if(pid==0){  //child
        execl("./child","./child",fd_str,(char *) 0);
    }

    // this is the parent
       while((pid=waitpid(-1,NULL,WNOHANG))>=0)
	    {   if(pid==0){
	        fflush(stdout);
            printf("Parent is working");}
            if(pid>0){
             printf("\nChild %d has teminated\n",pid);


            }
	    }
	        char buffer[7];
	        int m;
            lseek(fd_int,0L,SEEK_SET);

            while((m=read(fd_int,buffer,sizeof(buffer)))>0)
                printf("%s",buffer);

            fflush(stdout);



	    exit(0);
}
