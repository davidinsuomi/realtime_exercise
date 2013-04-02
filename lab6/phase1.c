#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
    int main(){
    pid_t pid;
    char fd_str[10];
    int fd_int;
    fd_int=open("log.txt",O_CREAT|O_RDWR,0700);
    sprintf(fd_str,"%d",fd_int);
    pid=fork();
    if(pid==0){  //child
        execl("./child","./child",fd_str,(char *) 0);
    }

    // this is the parent
       while((pid=waitpid(-1,NULL,WNOHANG))>=0)
	    {   if(pid==0){
	        fflush(stdout);
            printf("Parent is working");}
            if(pid>0){
             printf("\nChild %d has teminated\n",pid);


            }
	    }
	          int size,i;
            struct stat st;
            lseek(fd_int,0L,SEEK_SET);
            stat("log.txt",&st);
            size=st.st_size;
              char *buffer= (char *)malloc(size);


            read(fd_int,buffer,size);
            printf("\n");
            for(i=0;i<size;i++){
            printf("%c",buffer[i]);}


	    exit(0);
}
