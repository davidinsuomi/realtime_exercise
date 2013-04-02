#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void){
    struct stat buff;
    stat("/home/david/Desktop/lab3",&buff);
    if (S_ISREG(buff.st_mode))
        printf("\n Is regular file");
        else if(S_ISDIR(buff.st_mode))
            printf("\n Is directory file");
            else if(S_ISCHR(buff.st_mode))
            printf("\n IS character special file");



           printf("\n%o" ,~(buff.st_mode&S_IFMT) & buff.st_mode);





    return 0;
}
