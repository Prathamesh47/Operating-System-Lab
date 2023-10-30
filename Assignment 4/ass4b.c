#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
void *writer_thr(void *temp);
void *reader_thr(void *temp);
sem_t mutex;
sem_t wrt;
int readcount = 0, n_writers, n_readers;
int main()
{
    long int i;
    sem_init(&mutex, 0, 1);

    sem_init(&wrt, 0, 1);
    pthread_t readers[100], writers[100];
    printf("\nEnter number of readers: ");
    scanf("%d", &n_readers);
    printf("\nEnter number of writers: ");
    scanf("%d", &n_writers);
    for (i = 1; i <= n_writers; i++)
    {
        int *writer_id = malloc(sizeof(int));
        *writer_id = i;
        pthread_create(&writers[i], NULL, writer_thr, (void *)writer_id);
    }
    for (i = 1; i <= n_readers; i++)
    {
        int *reader_id = malloc(sizeof(int));
        *reader_id = i;
        pthread_create(&readers[i], NULL, reader_thr, (void *)reader_id);
    }
    for (i = 1; i <= n_writers; i++)
    {
        pthread_join(writers[i], NULL);
    }
    for (i = 1; i <= n_readers; i++)
    {
        pthread_join(readers[i], NULL);
    }
    sem_destroy(&wrt);
    sem_destroy(&mutex);
    pthread_exit(NULL); // Exit the main thread gracefully
}
void *reader_thr(void *temp)
{
    int *id_ptr = (int *)temp;
    int id = *id_ptr;
    free(id_ptr);
    printf("\nReader %d is attempting to read.", id);
    sem_wait(&mutex);
    readcount++;

    if (readcount == 1)
        sem_wait(&wrt);
    sem_post(&mutex);
    printf("\nReader %d is reading.", id);
    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);
    sem_post(&mutex);
    printf("\nReader %d finished reading.\n", id);
    sleep(3);
    pthread_exit(NULL);
}
void *writer_thr(void *temp)
{
    int *id_ptr = (int *)temp;
    int id = *id_ptr;
    free(id_ptr);
    printf("\nWriter %d is attempting to write.", id);
    sem_wait(&wrt);
    printf("\nWriter %d is writing.", id);
    sleep(3);
    printf("\nWriter %d finished writing.\n", id);
    sem_post(&wrt);
    pthread_exit(NULL);
}