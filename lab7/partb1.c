#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

static void child_handler(int);
static void alarm_handler(int);
//int stop=0;


    int main(){
    pid_t pid;


    if(signal(SIGCHLD,child_handler)==SIG_ERR)
        fprintf(stderr,"Cannot set signal handler\n");
            if(signal(SIGALRM,alarm_handler)==SIG_ERR)
        fprintf(stderr,"Cannot set signal handler\n");


    pid=fork();
    if(pid==0){  //child
     //   execl("./child","./child",fd_str,(char *) 0);
        int n;
        for( n=0;n<5;n++){
        printf("child is working\n");
        fflush(stdout);
        sleep(1);}
    }


        int m;
        for(m=0;m<5;m++){
        printf("Parent is working\n");
        fflush(stdout);
        sleep(1);}






	    exit(0);
}



    static void child_handler(int sig_no){
        if(sig_no==SIGCHLD){
            printf("child terminate");
            fflush(stdout);
        }
        return;
    }
    static void alarm_handler(int sig_no){
        int m;

        printf("alarm is working\n");
        fflush(stdout);
        sleep(1);
    }
