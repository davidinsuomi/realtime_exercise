#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

void  main(int argc, char ** argv){
    int fd_int;
    int i=0;
    char buffer[5]="AAAAA";
    sscanf(argv[1],"%d",&fd_int);
    for(i;i<5;i++){
    write(fd_int,buffer,5);
    sleep(1);
    }
    exit(0);
}
