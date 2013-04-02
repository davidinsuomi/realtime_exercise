#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

static void child_handler(int);
int stop=0;


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




    if(signal(SIGCHLD,child_handler)==SIG_ERR)
        fprintf(stderr,"Cannot set signal handler\n");

        while(!stop){
        printf("Parent is working\n");
        fflush(stdout);
        sleep(1);}




        close(fd_int);
	    exit(0);
}



    static void child_handler(int sig_no){
        if(sig_no==SIGCHLD){
            int child;
        child=wait(NULL);
        printf("\nChild %d  has teminated\n",child);
        int fd_int;
        fd_int=open("log.txt",O_CREAT|O_RDWR,0700);
        char buffer[7];
        int m;
        lseek(fd_int,0L,SEEK_SET);

            while((m=read(fd_int,buffer,sizeof(buffer)))>0)
                printf("%s",buffer);

            fflush(stdout);
        stop=1;
        }
        return;
    }
