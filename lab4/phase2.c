#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>


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


int main(void){
    int fd,status;
    pid_t w;

    fd=open("/home/david/Desktop/lab4/write.txt",O_CREAT|O_RDWR,0700);

    pid_t pid_of_child;

    pid_of_child=fork();


if(pid_of_child>0){    //parent process take care of reading the keyborad
    int result;
    char chr_kb;
    while(1){
        result=read(0,&chr_kb,1);
        if(result>0){
            if(chr_kb=='Q'||chr_kb=='q')
                break;
            else{
                printf("%c",chr_kb);
                write(fd,&chr_kb,1);
                fflush(stdout);
            }
        }
        if(result==-1&&errno!=EAGAIN)
            perror("Keyboard error");



    }





            printf("\nwait child.....\n");

            w=wait(&status);
            if(w==-1){
            perror("waitpid");
            exit(EXIT_FAILURE);}
            if(WIFEXITED(status))
                printf("child exited,status=%d\n",WEXITSTATUS(status));

            close(fd);

            exit(0);

}


    if(pid_of_child==0)    // child process reading from the chatfellow
    {

        int fellow_desc;
        char chr_fellow, chr;



        int file_flags;
        char result;
        fellow_desc = OpenChatFellow();
        int i=0;
        while(1)
            {
           result=read(fellow_desc,&chr_fellow,1);
            if(result>0)
            {
                printf("%c",chr_fellow);
                write(fd,&chr_fellow,1);
                i++;
                fflush(stdout);
            }
            if(result==-1&&errno!=EAGAIN)
                perror("Fellow error");

                if(result==0)
                    _exit(i);     //the end of file receieved terminates
            }


    }

}

