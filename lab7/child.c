#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
static void alarm_handler(int);

void  main(int argc, char ** argv){


            if(signal(SIGALRM,alarm_handler)==SIG_ERR)
                fprintf(stderr,"Cannot set signal handler\n");
        int m;
        for(m=0;m<8;m++){
        printf("child is working\n");
        fflush(stdout);
        sleep(1);}
        printf("child terminated\n");
    return;
}
    static void alarm_handler(int sig_no){

        printf("Signal received");
        fflush(stdout);

        return;
    }
