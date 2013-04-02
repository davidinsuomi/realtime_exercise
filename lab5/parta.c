#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>


int main(){
    pid_t child[4]=NULL;
    int i=0;
    while (i<5){
        child[i]=fork();
        i++;
        switch(i){


        case 1 :
            if(child[0]==0)

                printf("a");


        case 2:
           if(child[1]==0)



        }
    }





}
