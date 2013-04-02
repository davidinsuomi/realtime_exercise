#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

static void user_handler(int);

int main(){
    if(signal(SIGUSR1,user_handler)==SIG_ERR)
        fprintf(stderr,"Cannot set signal handler");
    pid_t pid;
    pid=fork();

    if(pid==0){        //this is child
         while(1){
			
                    write(1,"1",1);
                    kill(getppid(),SIGUSR1);
                    pause();
                }
    }

    if(pid>0)
        {

            while(1){
            pause();
            write(1,"2",1);
            kill(pid,SIGUSR1);
		
        }
        }
	//return 0;
}

static void user_handler(int sig_no){

    return;
}


