#include <stdio.h>

int main() {
    int n, bt[20], at[20], wt[20], tat[20], ct[20], remaining_bt[20];
    int quantum, time = 0;
    float avwt = 0, avtat = 0;
    int i, j, done;

    printf("Enter total number of processes (maximum 20): ");
    scanf("%d", &n);

    printf("Enter Process Arrival Time and Burst Time\n");
    for (i = 0; i < n; i++) {
        printf("P[%d] Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P[%d] Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        remaining_bt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    while (1) {
        done = 1; // Assume all processes are done
        for (i = 0; i < n; i++) {
            if (remaining_bt[i] > 0) {
                done = 0; // There is a pending process
                if (remaining_bt[i] > quantum && at[i] <= time) {
                    // Execute for the time quantum
                    time += quantum;
                    remaining_bt[i] -= quantum;
                } else if (at[i] <= time) {
                    // Execute remaining burst time
                    time += remaining_bt[i];
                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    avwt += wt[i];
                    avtat += tat[i];
                    remaining_bt[i] = 0; // Process is completed
                }
            }
        }
        if (done) break; // If all processes are done, exit the loop
    }

    avwt /= n;
    avtat /= n;

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i], ct[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", avwt);
    printf("Average Turnaround Time: %.2f\n", avtat);

    return 0;
}


