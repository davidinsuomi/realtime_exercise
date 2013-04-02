#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

static void user_handler(int);
int count=0;
int main(){
    int i,m;
    if(signal(SIGUSR1,user_handler)==SIG_ERR)
        fprintf(stderr,"Cannot set signal handler");
    pid_t pid;


    for(i=0;i<5;i++){
          pid=fork();
    if(pid==0){        //this is child
                for(m=0;m<20;m++)
                    kill(getppid(),SIGUSR1);
            exit(0);
    }
    }

       while((pid=waitpid(-1,NULL,WNOHANG))>=0)
	    {   if(pid){
            printf("Child %d has teminated\n",pid);
            printf("%d\n",count);
	    }
	    }
}

static void user_handler(int sig_no){
    count++;
    return;
}

