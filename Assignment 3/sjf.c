#include<stdlib.h>
#include<stdio.h>

// int process[10], arrival[10], burst[10], turnAround[10],waiting[10], ct[10];
int n;
int waiting[10],tat[10];
int finish[10];

struct process{
    int id;
    int arrival,burst,ct,rt;
};

void sort(struct process processes[],int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(processes[j].rt>processes[j+1].rt)
            {
                struct process temp=processes[j];
                processes[j]=processes[j+1];
                processes[j+1]=temp;
            }
            else if(processes[j].rt==processes[j+1].rt)
            {
                if(processes[j].arrival>processes[j+1].arrival)
                {
                     struct process temp=processes[j];
                    processes[j]=processes[j+1];
                    processes[j+1]=temp;
                }
            }
        }
    }
}

void sjf(struct process processes[],int n)
{
    int pending=n;
    for(int i=0; i<n; i++)
    {
        finish[i]=0;
    }
    int cnt=0;
    int ctime=0;
    sort(processes,n);
    for(int i=0; i<n; i++)
    {
        printf("%d ",processes[i].rt);
    }
    while(pending>0)
    {
        sort(processes,n);
        for(int i=0; i<n; i++)
        {
            if(finish[i]!=1 && processes[i].arrival<=ctime)
            {
                ctime+=1;
                if(processes[i].rt>0)
                {
                processes[i].rt-=1;

                }
                
                printf("P%d",processes[i].id);
                
                if (processes[i].rt == 0) {
                    finish[i] = 1; // Set the process as finished
                    pending--;
                    processes[i].ct = ctime;
                    tat[i] = processes[i].ct - processes[i].arrival;
                    waiting[i] = tat[i] - processes[i].burst;
                }

                break;
            }
        }
    }
}

int main()
{
    printf("Enter the number of process:\n");
    scanf("%d",&n);
    struct process processes[n];
    for(int i=0; i<n; i++)
    {
        processes[i].id=i+1;
        printf("Enter the Arrival time for process P%d",i+1);
        scanf("%d",&processes[i].arrival);
        printf("Enter the Burst time for process P%d",i+1);
        scanf("%d",&processes[i].burst);
        processes[i].rt=processes[i].burst;
    }
    sjf(processes,n);
    return 0;
}
