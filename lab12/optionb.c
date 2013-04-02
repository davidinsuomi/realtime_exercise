#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>


int count=0;

static void user_handler(int sig_no) {
	 count++;
	 return;
}


int main(){
    int i,m;
    pid_t pid;
	if(signal(SIGUSR1,user_handler)==SIG_ERR)
		fprintf(stderr,"Cannot set signal handler");


	// Construct a structure that specifies what signal is generated
	// and how signal handler is called


    for(i=0;i<5;i++){
          pid=fork();
    if(pid==0){        //this is child
                for(m=0;m<20;m++)
                   kill(getppid(),SIGUSR1);

            exit(0);
    }
    }

       while((pid=waitpid(-1,NULL,0))>0)
	    {
            printf("Child %d has teminated\n",pid);
            printf("%d\n",count);

	    }
}



