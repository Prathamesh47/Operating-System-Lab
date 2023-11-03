#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t mutex,wr;
int readcnt=0;

int a=10;
int rn,wn;
void *reader(void* arg)
{
    int id=*((int*)arg);
    pthread_mutex_lock(&mutex);
    readcnt++;
    pthread_mutex_unlock(&mutex);
    if(readcnt==1)
    {
        pthread_mutex_lock(&wr);
    }
    printf("Reader %d is in critical section",id);
    printdf("Reader %d is reading data %d",id,a);
    sleep(1);
    pthread_mutex_lock(&mutex);
    readcnt--;
    pthread_mutex_unlock(&mutex);
    if(readcnt==0)
    {
        pthread_mutex_unlock(&wr);
    }
    printf("Reader is left the critical section !!!\n");
}

void *writer(void* arg)
{
    int id=*((int*)arg);
    pthread_mutex_lock(&wr);
    printf("Writer %d is in critical section",id);
    printdf("Writer %d is writing data %d",id,a++);
    sleep(1);
    pthread_mutex_unlock(&wr);
    printf("Writer is left the critical section !!!\n");
}


int main()
{
    printf("\nEnter No.of reader:");
    scanf("%d",&rn);
    printf("\nEnter No.of writer:");
    scanf("%d",&wn);
    pthread_mutex_init(&wr,NULL);
    pthread_mutex_init(&mutex,NULL);
    pthread_t reader_thread[rn];
    pthread_t writer_thread[wn];
    int reader_id[rn];
    int writer_id[wn];
    for(int i=0;i<rn;i++)
    {
        reader_id[i]=i+1;
        pthread_create(&reader_thread[i],NULL,reader,&reader_id[i]);
    }
    for(int i=0;i<wn;i++)
    {
        writer_id[i]=i+1;
        pthread_create(&writer_thread[i],NULL,writer,&writer_id[i]);
    }
    for(int i=0;i<rn;i++)
    {
        pthread_join(reader_thread[i],NULL);
    }
    for(int i=0;i<wn;i++)
    {
        pthread_join(writer_thread[i],NULL);
    }


}
