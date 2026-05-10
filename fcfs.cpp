#include <stdio.h>

int main() {
    int n, bt[20], at[20], wt[20], tat[20], ct[20];
    float awt = 0, atat = 0;
    int i, time = 0;

    printf("Enter total number of processes (maximum 20): ");
    scanf("%d", &n);

    printf("Enter Process Arrival Time \n");
    for (i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }
     printf("Enter Process Burst Time \n");
    for (i = 0; i < n; i++)
	 {
    scanf("%d", &bt[i]);
    }

    // Calculate completion times, waiting times, and turnaround times
    for (i = 0; i < n; i++) {
        if (i == 0) {
            ct[i] = at[i] + bt[i];
        } else {
            if (at[i] > ct[i - 1]) {
                time = at[i];
            } else {
                time = ct[i - 1];
            }
            ct[i] = time + bt[i];
        }
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        awt += wt[i];
        atat += tat[i];
    }

    awt /= n;
    atat /= n;

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i], ct[i]);
    }

    printf("\nAverage Waiting Time: %f\n", awt);
    printf("\nAverage Turnaround Time: %f\n", atat);

    return 0;
}

