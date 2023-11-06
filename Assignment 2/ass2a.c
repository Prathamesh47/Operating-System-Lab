#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int n;
int arr[100];
int choice=0;
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
void merge(int arr[],int l,int mid,int h)
{
    int n1 = mid -l +1;
    int n2 = h-mid;
    int L[n1];
    int R[n2];
    for(int i=0;i<n1;i++)
    {
        L[i]=arr[l+i];
    }
    for(int i=0;i<n2;i++)
    {
        R[i]= arr[mid+1+i];
    }
    int i=0;
    int j=0;
    int k=l;
    while(i<n1&&j<n2)
    {
        if(L[i]<=R[j])
        {
            arr[k]= L[i];
            i++;
        }
        else{
            arr[k]=R[j];
            j++;
        }
        k++;
    }
    while(i<n1)
    {
        arr[k]= L[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        arr[k]=R[j];
        j++;
        k++;
    }


}

void mergesort(int arr[],int l,int h)
{
    if(l<h)
    {
        int mid = l +(h-l)/2;
        mergesort(arr,l,mid);
        mergesort(arr,mid+1,h);

        merge(arr,l,mid,h);
    }
}
void zombie()
{
    
    int p_id = getpid();
    printf("\n Parent's process id is %d ",p_id);
    printf("\n Forking the process");
    pid_t id = fork();
    if(id==-1)
    {
        printf("\n The child is not created ");
    }
    else if(id ==0)
    {
        printf("\n In child process ");
        printf("\n The child process id is %d",getpid());
        printf("\n This child parent id is %d",getppid());
        printf("\n Array before sorting is : ");
        for(int i=0;i<n ;i++)
        {
            printf(" %d",arr[i]);
        }
        printf("\nUsing bubble sort sorting the array");
        bubblesort();
        printf("\nPrinting the sorted array(Bubble sort) : ");
        for(int i=0;i<n ;i++)
        {
            printf(" %d",arr[i]);
        }
        printf("\n Above is the sorted array using bubble sort");
        printf("\n The child process executed successfully");
        exit(0);
    }
    else
    {
        sleep(40);
        printf("\nProcess is with parent its id is : %d",getpid() );
        printf("\nChild is terminated after wait with pid: ");
        printf("\n Array before sorting is : ");
        for(int i=0;i<n ;i++)
        {
            printf(" %d",arr[i]);
        }
         printf("\nUsing merge sort sorting the array");
        mergesort(arr,0,n-1);
        printf("\nPrinting the sorted array(Bubble sort) : ");
        for(int i=0;i<n ;i++)
        {
            printf(" %d",arr[i]);
        }
        printf("Parent executed successfully\n");
        sleep(30);
    }
}
void normal()
{
    pid_t p_id = getpid();
    printf("\n Parent's process id is %d ",p_id);
    printf("\n Forking the process");
    pid_t id = fork();
    if(id==-1)
    {
        printf("\n The child is not created ");
    }
    else if(id ==0)
    {
        printf("\n In child process ");
        printf("\n The child process id is %d",getpid());
        printf("\n This child parent id is %d",getppid());
        printf("\n Array before sorting is : ");
        for(int i=0;i<n ;i++)
        {
            printf(" %d",arr[i]);
        }
        printf("\nUsing bubble sort sorting the array");
        bubblesort();
        printf("\nPrinting the sorted array(Bubble sort) : ");
        for(int i=0;i<n ;i++)
        {
            printf(" %d",arr[i]);
        }
        printf("\n Above is the sorted array using bubble sort");
        printf("\n The child process executed successfully");
    }
    else
    {
        printf("\nProcess is with parent its id is : %d",getpid() );
        pid_t cpid = wait(NULL);
        printf("\nChild is terminated after wait with pid: %d", cpid);
        printf("\n Array before sorting is : ");
        for(int i=0;i<n ;i++)
        {
            printf(" %d",arr[i]);
        }
         printf("\nUsing merge sort sorting the array");
        mergesort(arr,0,n-1);
        printf("\nPrinting the sorted array(Merge sort) : ");
        for(int i=0;i<n ;i++)
        {
            printf(" %d",arr[i]);
        }
        printf("\nParent executed successfully\n");
    }
}
void orphan()
{
    pid_t p_id = getpid();
    printf("\n Parent's process id is %d ",p_id);
    printf("\n Forking the process");
    pid_t id = fork();
    if(id==-1)
    {
        printf("\n The child is not created ");
    }
    else if(id ==0)
    {
        printf("\n In child process ");
        printf("\n The child process id is %d",getpid());
        printf("\n This child parent id is %d",getppid());
        printf("\n Array before sorting is : ");
        for(int i=0;i<n ;i++)
        {
            printf(" %d",arr[i]);
        }
        printf("\nUsing bubble sort sorting the array");
        bubblesort();
        printf("\nPrinting the sorted array(Bubble sort) : ");
        for(int i=0;i<n ;i++)
        {
            printf(" %d",arr[i]);
        }
        printf("\n Above is the sorted array using bubble sort");
        sleep(30);
        printf("\n The child process executed successfully");
        printf("\n The child process id is %d",getpid());
        printf("\n This child parent id is %d",getppid());
    }
    else
    {
        printf("\nProcess is with parent its id is : %d",getpid() );
        // pid_t cpid = wait(NULL);
        // printf("\nChild is terminated after wait with pid: %d", cpid);
        printf("\n Array before sorting is : ");
        for(int i=0;i<n ;i++)
        {
            printf(" %d",arr[i]);
        }
         printf("\nUsing merge sort sorting the array");
        mergesort(arr,0,n-1);
        printf("\nPrinting the sorted array(Merge sort) : ");
        for(int i=0;i<n ;i++)
        {
            printf(" %d",arr[i]);
        }
        printf("\nParent executed successfully\n");
    }
}
void input()
{
    printf("\nEnter no of elements : ");
    scanf("%d",&n);
    printf("\nEnter elements of array : ");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("\n---------------- MENU ----------------\n");
    printf("1) Normal Execution\n");
    printf("2) Zombie\n");
    printf("3) Orphan\n");
    printf("Please enter your choice: \n");
    scanf("%d", &choice);
    if(choice==1)
    {
        normal();
    }
    else if (choice==2)
    {
        zombie();
    }
    else if (choice==3)
    {
        orphan();
    }

}



int main()
{
    input();
    return 0;
}
