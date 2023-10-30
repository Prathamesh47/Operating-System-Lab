// Read
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
int main()
{
    // ftok to generate a unique key
    key_t key1 = ftok(".", 'a'); // Changed 'aaa' to 'a' for a shorter key
    printf("Key: %d\n", key1);
    // shmget returns an identifier in shmid
    int shmid = shmget(key1, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }
    // shmat to attach to shared memory
    char *str = (char *)shmat(shmid, (void *)0, 0);
    if (str == (char *)(-1))
    {
        perror("shmat");
        return 1;
    }
    printf("\nMemory address: %p\n", (void *)str);
    printf("Data read from memory: %s\n", str);
    // Detach from shared memory
    shmdt(str);
    // Destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

/*
// how to run
gcc -o read_shared_memory read_shared_memory.c
gcc -o write_shared_memory write_shared_memory.c
./write_shared_memory
./read_shared_memory
*/