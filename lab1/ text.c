// This is very simple input generator.
// A separate process generates input at 1 second
// time intervals. Input is characters A B C, ..., Z.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<fcntl.h>

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
    char chr_fellow, chr;
    int r;




    int file_flags;
    file_flags=fcntl(fellow_desc,F_GETFL);
    file_flags=file_flags|O_NONBLOCK;
    fcntl(fellow_desc,F_SETFL,file_flags);


	fellow_desc = OpenChatFellow();

	read(0, &chr, 1);

	// This program blocks and does not work in realtime
	// You are asked to to modify it so that it will be working in realtime
	// Use the Polling method (non-blocking i/o)
	do {



		r = read(fellow_desc, &chr_fellow, 1);
		// r == 1 if one byte read
		// r == -1 if error. Also data not ready is an error (EAGAIN)

		// r == 0 not an error , but eof was detected
		if(r==1)
		{printf("%c", chr_fellow);
		fflush(stdout);

		if (chr_fellow == 'z')
			break;
		}
		else if(r==0)
		{
		 printf("end of file");
		}
		else
		 exit(0);




		if(!read(0, &chr, 1))
		{

		printf("%c", chr);
		fflush(stdout);

		}
	} while (chr != 'q');
    return 0;
}

