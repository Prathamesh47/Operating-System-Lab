#include<stdlib.h>
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;
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

void bsort(struct process processes[],int n)
{
    
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(processes[j+1].arrival<processes[j].arrival)
            {
                struct process temp1=processes[j];
                processes[j]=processes[j+1];
                processes[j+1]=temp1;
            }
        }
    }
}
void roundrobin(struct process round[],int n)
{
    int tq;
    printf("Enter the time Quantum\n");
    scanf("%d",&tq);
    bool done[n];

    for(int i=0; i<n; i++)
    {
        done[i]=0;
    }
    queue<int>q;
    int inq[n];
    
    for(int i=0; i<n; i++)
    {
        inq[i]=0;
    }
    inq[0]=1;
    q.push(0);
    int ctime=0;
    while(!q.empty())
    {
        int curr=q.front();
        q.pop();

        printf(" P%d",round[curr].id);

        if(round[curr].rt<=tq)
        {   
            ctime+=round[curr].rt;
            done[curr]=1;
            round[curr].ct=round[curr].rt;
            round[curr].rt=0;
        }
        else{
            ctime+=tq;
            round[curr].rt-=tq;
        }
        for(int i=0; i<n; i++)
        {
            if(!done[i] && i!=curr && round[i].arrival<=ctime && inq[i]!=1)
            {
                q.push(i);
                inq[i]=1;
            }
        }
        inq[curr]=0;
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
    // sjf(processes,n);
    roundrobin(processes,n);
    return 0;
}
