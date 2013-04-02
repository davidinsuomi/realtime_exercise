#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void){
    pid_t pid;
    int fd_arr[2],i,flag=1;
    char chr;
    pipe(fd_arr);
    pid=fork();
    if(pid==0){
    close(fd_arr[0]);   //child close read
    for(i=0;i<10;i++)
    {   chr='0'+i;
        write(fd_arr[1],&chr,1);
        sleep(1);
    }


    close(fd_arr[1]);
    exit(0);
    }

    //this is parent


       close(fd_arr[1]);    //parent close write to the pipe
        while(1){

           flag=read(fd_arr[0],&chr,1);

            if(flag==0){
                close(fd_arr[0]);
                exit(0);}
         write(1,&chr,1);
          sleep(1);
        }


}
