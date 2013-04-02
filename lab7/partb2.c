#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

static void child_handler(int);

//int stop=0;


    int main(){
    pid_t pid;


    if(signal(SIGCHLD,child_handler)==SIG_ERR)
        fprintf(stderr,"Cannot set signal handler\n");
            pid=fork();
    if(pid==0){  //child


                alarm(5);


       execl("./child","./child",(char *) 0);

    }


//        int m;
//        for(m=0;m<5;m++){
//        printf("Parent is working\n");
//        fflush(stdout);
//        sleep(1);}






	    exit(0);
}



    static void child_handler(int sig_no){
        if(sig_no==SIGCHLD){
            printf("child terminate");
            fflush(stdout);
        }
        return;}


