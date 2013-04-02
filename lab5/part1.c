#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>


int main(){
    pid_t pid1,pid2,pid3,pid4,pid;
    pid1=fork();
    if(pid1==0) //child1
     { printf("a");
     exit (0);
     }
     pid2=fork();
     if(pid2==0)//child2
     {
         printf("B");
         sleep(1);
         printf("B");
         sleep(1);
        exit (0);
     }
     pid3=fork();
     if(pid3==0){     //child 3
         printf("C");
         sleep(1);
         printf("C");
         sleep(1);
         printf("C");
         sleep(1);
         exit (0);
     }
     pid4=fork();
     if(pid4==0){     //child4
          printf("D");
         sleep(1);
         printf("D");
         sleep(1);
         printf("D");
         sleep(1);
         printf("D");
         sleep(1);
          exit (0);
     }

     //parent

     while((pid=waitpid(-1,NULL,0))>0){
         printf("Child %d has terminated",pid);
     }
     exit (0);
}
