#include<stdio.h>
#include<stdlib.h>
// int p,r;

void banker(int p, int r, int alloc[p][r],int max[p][r],int need[p][r],int avai[p])
{
    int finish[p];
    int ans[p];
    int ind=0;

    for(int l=0; l<p; l++)
    {
        finish[l]=0;
    }
    for(int k=0; k<p; k++)
    {
        for(int i=0; i<p; i++)
        {
            if(finish[i]==0)
            {
                int flag=0;
                for(int j=0;j<r; j++)
                {
                    if(need[i][j]>avai[j])
                    {
                        flag=1;
                        break;
                    }
                }

                if(flag==0)
                {
                    ans[ind++]=i;

                    for(int j=0; j<r; j++)
                    {
                        avai[j]+=alloc[i][j];
                    }
                    finish[i]=1;
                   
                }
            }
        }
    }
    for(int i=0; i<p; i++)
    {
         printf("%d ",finish[i]);
    }
    int flag=1;
    for(int i=0; i<p; i++)
    {
        if(finish[i]==0)
        {
            flag=0;
            printf("The condition is not safe");
            break;
        }
    }
    if(flag==1)
    {   
        printf("It is safe sequence");
        for(int i=0; i<p-1; i++)
        {
            printf("P%d->",ans[i]);
        }
        printf("P%d",ans[p-1]);

    }
}
int main()
{
    int n, m;
    // printf("Enter the number of process : ");
    scanf("%d", &n);
    // printf("Enter the number of resource : ");
    scanf("%d", &m);
    int ava[m];
    // printf("Enter the number of available resource of each type ");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &ava[i]);
    }
    int max[n][m];
    // printf("Maximum demand of each process : ");
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    // printf("Allocated resource of each process : ");
    int alloc[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }
    int need[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    banker(n, m, alloc,max , need, ava);
    // resourcerequest(n, m, max, alloc, ava);
    return 0;
}