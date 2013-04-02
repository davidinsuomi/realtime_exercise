#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main (void){
    int access_mode,file_flags,fd;

    fd=open("/home/david/Desktop/lab3/file",O_RDONLY);
    file_flags=fcntl(fd,F_GETFL,0);
    if(file_flags&FD_CLOEXEC)
        printf("FD_CLOEXEC ON");
        else
        printf("FD_CLOEXEC OFF");
    access_mode=file_flags&O_ACCMODE;
    printf("\nAccess mode :");
    if(access_mode==O_WRONLY)
        printf("\n write only");
        else if(access_mode==O_RDONLY)
                printf("\nread only");
                else
                    printf("\n Read/Write");
    printf("\n Other flags: \n");

        if(file_flags& O_APPEND)
            printf("O_APPEND: ON \n");
            else
                printf("O_APPEND: OFF \n");

        if(file_flags&O_NONBLOCK)
            printf("O_NONBLOCK: ON \n");
            else
                printf("O_NONBLOCK:OFF \n");


          printf("\ninverts:\n");

                if(file_flags&O_NONBLOCK)
                    file_flags = file_flags & ~O_NONBLOCK;

                else

                    file_flags = file_flags|O_NONBLOCK;

           fcntl(fd,F_SETFL,file_flags);



              file_flags=fcntl(fd,F_GETFL,0);
                    if(file_flags&FD_CLOEXEC)
                        printf("FD_CLOEXEC ON");
                    else
                        printf("FD_CLOEXEC OFF");
            access_mode=file_flags&O_ACCMODE;

    printf("\nAccess mode :");
                if(access_mode==O_WRONLY)
                    printf("\n write only");
        else if(access_mode==O_RDONLY)
                printf("\nread only");
                else
                    printf("\n Read/Write");

            printf("\n Other flags: \n");

        if(file_flags& O_APPEND)
            printf("O_APPEND: ON \n");
            else
                printf("O_APPEND: OFF \n");

        if(file_flags&O_NONBLOCK)
            printf("O_NONBLOCK: ON \n");
            else
                printf("O_NONBLOCK:OFF \n");

        return 0;


}
