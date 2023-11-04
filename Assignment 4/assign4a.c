#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define BUFFERSIZE 10

int cnt=0, NUM_PRODUCER, NUM_CONSUMER;
sem_t empty, full;
int buffer[BUFFERSIZE];
pthread_mutex_t mutex;

void *producer(void* arg)
{
    int producer_id=*((int*) arg);
    int item;
    while(1)
    {
        item=rand()%100;
        if(cnt==BUFFERSIZE)
        {
            printf("Buffer is full\n");
            sleep(1);
        }
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[cnt++]=item;
        printf("Producer %d produced Item: IO%d\n",producer_id,item);
        printf("Size of Buffer is %d\n",cnt);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
 
    }
    pthread_exit(NULL);

}

void *consumer(void* arg)
{
    int consumer_id=*((int*) arg);
    int item;
    while(1)
    {
        if(cnt==0)
        {
            printf("Buffer is Empty\n");
            sleep(1);
        }
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item= buffer[cnt--];
        printf("Consumer %d consumerd Item No: IO%d\n",consumer_id,item);
        printf("Size of Buffer is %d\n",cnt);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(1);
 
    }
    pthread_exit(NULL);

}

int main()
{
    printf("Enter the number of producer and consumers[P C]:\n");
    scannf("%d%d",&NUM_PRODUCER,&NUM_CONSUMER);

    int producer_ids[NUM_PRODUCER];
    int consumer_ids[NUM_CONSUMER];

    pthread_t thread_producer[NUM_PRODUCER];
    pthread_t thread_consumer[NUM_CONSUMER];

    sem_init(&empty,0,BUFFERSIZE);
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex,NULL);

    for(int i=0; i<NUM_PRODUCER; i++)
    {
        producer_ids[i]=i+1;
        pthread_create(&thread_producer[i],NULL,producer,&producer_ids[i]);
    }
    for(int i=0; i<NUM_CONSUMER; i++)
    {
        consumer_ids[i]=i+1;
        pthread_create(&thread_consumer[i],NULL,consumer,&consumer_ids[i]);
    }
    for(int i=0; i<NUM_PRODUCER; i++)
    {
       
        pthread_join(thread_producer[i],NULL);
    }
     for(int i=0; i<NUM_CONSUMER; i++)
    {

        pthread_join(thread_consumer[i],NULL);
    }
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;

    

}