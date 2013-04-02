#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(){

int sockfd,size;
struct sockaddr_un write_addr, read_addr;
char chr;
int i=0;

unlink("write.sock");

if((sockfd = socket(AF_UNIX,SOCK_DGRAM,0))<0)
    perror("read sockfd error");


read_addr.sun_family=AF_UNIX;
strcpy(read_addr.sun_path,"read.sock");

write_addr.sun_family=AF_UNIX;
strcpy(write_addr.sun_path,"write.sock");



if ((bind(sockfd,( struct sockaddr*)&write_addr,sizeof(write_addr))<0))
     perror("write bind error");
    for(i=0;i<10;i++){
        chr='0'+i;
       if((sendto(sockfd,&chr,1,0,(struct sockaddr*)&read_addr,sizeof(read_addr)))<0)
            perror("write sendto error");

        sleep(1);
        }

recvfrom(sockfd, &chr, 2, 0, NULL, NULL);
write(1,&chr,2);
exit(0);


}

