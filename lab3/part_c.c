#include<stdio.h>
#include<stdlib.h>

int main(){
char  a[]="abcdefghigklmn";
char buffer[5];
int i=0;
setvbuf(stdout,buffer,_IOFBF,5);

//fwrite (a , 1 , 1 , stdout );


    for(i=0;i<sizeof(a)-1;i++){
        putchar(a[i]);
        sleep(1);}
    return 0;

}
