#include <stdio.h>
#include <stdlib.h>
// Function to find a safe sequence using the Banker's algorithm
void bank(int n, int m, int max[n][m], int alloc[n][m], int ava[n], int need[n][m])
{
    int finish[n]; // An array to keep track of whether a process is completed
   for (int i = 0; i < n; i++)
    {
        finish[i] = 0;
    }
    int k, l, ind = 0;
    int ans[n];


    for (k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int flag = 0;

                // Check if the process can be executed with the available resources

                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > ava[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                // Check if the process can be executed with the available resources

                if (flag == 0)
                {
                    ans[ind++] = i;

                    // Update the available resources after executing the process

                    for (l = 0; l < m; l++)
                    {
                        ava[l] += alloc[i][l];
                    }
                    finish[i] = 1;
                }
            }
        }
    }
    int flag = 1;
    for (int i = 0; i < n; i++)
    {
        if (finish[i] == 0)
        {
            printf("Sequence is not safe ");
            flag = 0;
            break;
        }
    }
    if (flag == 1)
    {
        printf("Safe sequence is : ");
        for (int i = 0; i < n - 1; i++)
        {
            printf("P%d --> ", ans[i]);
        }
        printf("P%d ", ans[n - 1]);
    }
}
// Function to handle resource requests
void resourcerequest(int n, int m, int max[n][m], int alloc[n][m], int ava[n])
{

    int pid, request[n][m];
    printf("\n Enter process number : ");


        scanf("%d", &pid);
    printf("\n Enter additional request : \n");
    for (int i = 0; i < m; i++)
    {
        printf(" Request for resource %d : ", i + 1);
        scanf("%d", &request[0][i]);
    }
    int need[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    for (int i = 0; i < m; i++)
    {
        if (request[0][i] > need[pid][i])
        {
            printf("\n ******Error encountered******\n");
            exit(0);
        }
    }
    for (int i = 0; i < m; i++)
    {
        ava[i] -= request[0][i];
        alloc[pid][i] += request[0][i];
        need[pid][i] -= request[0][i];
    }
    bank(n, m, max, alloc, ava, need);
}
int main()
{
    int n, m;
    printf("Enter the number of process : ");
    scanf("%d", &n);
    printf("Enter the number of resource : ");
    scanf("%d", &m);
    int ava[m];
    printf("Enter the number of available resource of each type ");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &ava[i]);
    }
    int max[n][m];
    printf("Maximum demand of each process : ");
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Allocated resource of each process : ");
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
    bank(n, m, max, alloc, ava, need);
    resourcerequest(n, m, max, alloc, ava);
    return 0;
}