#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
    pid_t pid;
    int i=0;
    while(i<4){
    pid=fork();

    if(pid==0){   //this is child
        int j;
          //this is a question
        for(j=0;j<i+1;j++){
            printf("%c",'A'+i);
            fflush(stdout);
            sleep(1);
            }
        exit(0);  //child terminates
    }
    i++;
    }
    while((pid=waitpid(-1,NULL,0))>0){
         printf("       Child %d has terminated\n",pid);
     }
     exit(0);
}
