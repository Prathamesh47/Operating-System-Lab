#include <stdio.h>
#define MAX_QUEUE_SIZE 100

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time; // New attribute to store completion time
};

void customEnqueue(int queue[], int *rear, int process_id)
{
    if (*rear == MAX_QUEUE_SIZE - 1)
    {
        printf("Queue is full. Process P%d couldn't be enqueued.\n", process_id);
        return;
    }
    queue[++(*rear)] = process_id;
}

int customDequeue(int queue[], int *front, int *rear)
{
    if (*front > *rear)
    {
        printf("Queue is empty.\n");
        return -1;
    }
    return queue[(*front)++];
}

void roundRobinScheduling()
{
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    int queue[MAX_QUEUE_SIZE], front = 0, rear = -1;

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;

        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);

        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);

        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0; // Initialize completion time to 0
    }

    int current_time = 0;

    printf("\nGantt Chart:\n");
    printf("Time | Process\n");
    printf("-------------\n");

    while (1)
    {
        int all_completed = 1;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time)
            {
                all_completed = 0;

                int execute_time = (processes[i].remaining_time < time_quantum) ? processes[i].remaining_time : time_quantum;
                processes[i].remaining_time -= execute_time;
                current_time += execute_time;

                printf("%-5d | P%d\n", current_time, processes[i].id);

                if (processes[i].remaining_time == 0)
                {
                    processes[i].completion_time = current_time; // Set completion time
                }
                else
                {
                    customEnqueue(queue, &rear, processes[i].id);
                }
            }
        }

        if (all_completed)
            break;

        // Round-robin: Dequeue and enqueue processes
        if (front <= rear)
        {
            int next_process = customDequeue(queue, &front, &rear);
            customEnqueue(queue, &rear, next_process);
        }
        else
        {
            current_time++;
        }
    }

    // Calculate and display turnaround time and waiting time for each process
    float total_turnaround_time = 0, total_waiting_time = 0;

    printf("\nTurnaround Time and Waiting Time:\n");

    for (int i = 0; i < n; i++)
    {
        int turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        int waiting_time = turnaround_time - processes[i].burst_time;

        printf("P%d - Turnaround Time: %d, Waiting Time: %d\n", processes[i].id, turnaround_time, waiting_time);
        total_turnaround_time += turnaround_time;
        total_waiting_time += waiting_time;
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
}

void shortestJobFirst()
{
    int n, time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;

        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);

        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);

        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("\nGantt Chart:\n");
    printf("Time | Process\n");
    printf("-------------\n");

    int completed = 0;

    while (completed < n)
    {
        int shortest = -1;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0)
            {
                if (shortest == -1 || processes[i].remaining_time < processes[shortest].remaining_time)
                {
                    shortest = i;
                }
            }
        }

        if (shortest == -1)
        {
            time++;
            continue;
        }

        processes[shortest].remaining_time--;
        time++;

        if (processes[shortest].remaining_time == 0)
        {
            completed++;
            processes[shortest].completion_time = time;
            total_turnaround_time += (time - processes[shortest].arrival_time);
            total_waiting_time += (time - processes[shortest].arrival_time - processes[shortest].burst_time);
        }

        printf("%-5d | P%d\n", time, processes[shortest].id);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main()
{
    int choice;
    int running = 1;

    while (running == 1)
    {
        printf("\n1. Shortest Job First (preemption)");
        printf("\n2. Round Robin");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            shortestJobFirst();
            break;
        case 2:
            roundRobinScheduling();
            break;

        case 3:
            running = 0;
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    }

    return 0;
}
