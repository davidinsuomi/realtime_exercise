// This is very simple input generator.
// A separate process generates input at 1 second
// time intervals. Input is characters A B C, ..., Z.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<fcntl.h>
#include <errno.h>
#include <sys/time.h>

int OpenChatFellow() {
    pid_t pid;
    int fd_arr[2];
    int i;
    char chr;

    //This part is done only by parent
    pipe(fd_arr);
    pid = fork();
    if (pid < 0) {
        perror("Process creation error");
    }
    if (pid > 0) {
        close (fd_arr[1]); // parent closes it's read end of the pipe
        return fd_arr[0];
    }
    if (pid == 0)  {   // this is child
    	 close (fd_arr[0]);
         // writing to the pipe
         for( i = 0 ; i < 26 ; i++) {
            chr = 'a' + i;
         	write(fd_arr[1], &chr, 1);
         	sleep(1);

         }
         close(fd_arr[1]);
         exit (0);
    }
}

int main(void) {


    int fellow_desc;
    char chr_fellow;
    char chr_kb;
    int file_flags,result;
    fellow_desc=OpenChatFellow();
    fd_set fdset;

    int n;


    while(1){
        FD_ZERO(&fdset);
        FD_SET(0,&fdset);
        FD_SET(fellow_desc,&fdset);
        n=select(fellow_desc+1,&fdset,NULL,NULL,NULL);
        if(n>0){
            if(FD_ISSET(0,&fdset)){ //keyboard is ready
                read(0,&chr_kb,1);

                    if(chr_kb=='Q'||chr_kb=='q')
                        exit(0);

                    else{
                    printf("%c",chr_kb);
                    fflush(stdout);
                        }
            }
            if(FD_ISSET(fellow_desc,&fdset)){
            result=read(fellow_desc,&chr_fellow,1);
            if(result>0){
                    printf("%c",chr_fellow);
                    fflush(stdout);}
            if(result==-1&&errno!=EAGAIN)
                perror("Fellow error");

            if(result==0)
                exit(0);
            }
        }
    }





    return EXIT_SUCCESS;

}
