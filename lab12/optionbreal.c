#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>


int count=0;

void rt_handler(int signo, siginfo_t *info, void* p ) {
	 count++;

	 return;
}


int main(){
    int i,m;

	struct sigevent sevent;
	struct sigaction sa;
    union sigval value;
    pid_t pid;
    	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = rt_handler;
	sigaction(SIGRTMAX, &sa, NULL);
	// Construct a structure that specifies what signal is generated
	// and how signal handler is called

	sevent.sigev_notify = SIGEV_SIGNAL;
	sevent.sigev_signo = SIGRTMAX;
	sevent.sigev_value.sival_int = 1; // integer parameter

    fflush(stdout);

    for(i=0;i<5;i++){
          pid=fork();
    if(pid==0){        //this is child
                for(m=0;m<20;m++)
                   sigqueue(getppid(),SIGRTMAX,value);

            exit(0);
    }
    }

       while((pid=waitpid(-1,NULL,0))>0)
	    {
            printf("Child %d has teminated\n",pid);
            printf("%d\n",count);

	    }
}




