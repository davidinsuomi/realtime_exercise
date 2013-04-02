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
#include <termios.h>
#include <aio.h>
#include <signal.h>

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

void char_ready_handler(int);
char chr;
struct aiocb aiocb;


int main(void) {


    int fellow_desc;
    char chr_fellow;
    char chr_kb;
    int file_flags,result;
    fellow_desc=OpenChatFellow();
    fd_set fdset;

    int n;

    //install signal handler
    struct sigaction sigact,oldact;

    sigemptyset(&sigact.sa_mask);
    sigact.sa_handler=char_ready_handler;
    sigact.sa_flags=0;


    aiocb.aio_fildes=0;
    aiocb.aio_buf=&chr;
    aiocb.aio_nbytes=1;
    aiocb.aio_offset=0;
    aiocb.aio_reqprio=0;
    aiocb.aio_sigevent.sigev_notify=SIGEV_SIGNAL;
    aiocb.aio_sigevent.sigev_value.sival_ptr=&aiocb;
    aiocb.aio_lio_opcode=0;
    aio_read(&aiocb);


    // do the thing parallel with i/o
    do{
       result=read(fellow_desc,&chr_fellow,1);
            if(result>0){
                    printf("%c",chr_fellow);
                    fflush(stdout);}
            if(result==-1&&errno!=EAGAIN)
                perror("Fellow error");


    }while (result!=0);

    sigaction(SIGIO,&oldact,NULL);

    return EXIT_SUCCESS;

}

void char_ready_handler(int sig_no){
    //char answer;
    if(sig_no=SIGIO){
    printf("I/O complete signal is received ,Char was %c\n",chr);
    aio_read(&aiocb);
    }
    return;
}
