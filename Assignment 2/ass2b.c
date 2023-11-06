#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<sys/types.h>
#include<unistd.h>
    
int n;
int arr[100];

void bubblesort()
{
    int temp;
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                temp = arr[j+1];
                arr[j+1]=arr[j];
                arr[j]= temp;
            }
        }
    }
}

int main()
{
    char *arg[100], str[100];
    printf("Enter the size of array\n");
    scanf("%d",&n);
    printf("Enter the elements of array\n");
    for(int i=0; i<n; i++)
    {
        scanf("%d",&arr[i]);
    }
      printf("Printing the array before sorting method\n");
        for(int i=0; i<n; i++)
        {
            printf("%d",&arr[i]);
        }
        printf("Sorting Algothim used id Bubble Sort\n Calling the bubble sort algorithm\n");
        bubblesort();
        printf("Printing the array after sorting method\n");
         for(int i=0; i<n; i++)
        {
            printf("%d",&arr[i]);
        }
    pid_t pid=fork();
    if(pid<0)
    {
        printf("Child process failed to create\n");
    }
    else if(pid==0)
    {
        printf("Process Controls shifts to child process\n");
        printf("Child Process id is ",getpid());
        printf("The process id of parent process is ",getppid());
      
        for(int j=0; j<n; j++)
        {
            sprintf(str,"%d",arr[j]);
            arg[j]=malloc(sizeof(str));
            strcpy(arg[j],str);
        }
        printf("Execv Function is calling such that it tranfer to another process to run and terminate itself\n");
        execve("ass2b2.c",arg,NULL);
        printf("Child process get teminated\n");

    }
    else{
        printf("Parent process id %d:\n",getpid());
        wait(NULL);
        printf("Parent process get terminated\n");
    }
}