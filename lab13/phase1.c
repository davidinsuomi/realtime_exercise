#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int count=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void *threadFunction(void *param){
    int n=0;

    for(n=0;n<100000;n++){
    pthread_mutex_lock(&mutex);
    count++;
    pthread_mutex_unlock(&mutex);
    (*(int *)param)++;
    }

    pthread_exit((void *) param);
}

int main(void){
    int i,j;
    pthread_t threadldArr[10];
    int thread_count[10]={0};
    int *pstat;
    for(i=0;i<10;i++){
    if(pthread_create(&threadldArr[i],NULL,threadFunction,thread_count+i)!=0){
        printf("Error in creating a thread");
        exit(1);
    }

    }

    for(j=0;j<10;j++){
    pthread_join(threadldArr[j],(void **)&pstat);
    printf("thread %d  , value%d\n",j,*pstat);
    }
    for(j=0;j<10;j++){
    printf("%d  \n",thread_count[j]);
    }
    printf("totoal count is %d\n",count);
}
