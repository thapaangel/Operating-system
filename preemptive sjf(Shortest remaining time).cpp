#include <stdio.h>
#include <limits.h>

int main() {
    int n, bt[20], at[20], wt[20], tat[20], ct[20], rt[20], completed[20] = {0};
    float avwt = 0, avtat = 0;
    int i, time = 0, smallest, count = 0;

    printf("Enter total number of processes (maximum 20): ");
    scanf("%d", &n);

    printf("Enter Process Arrival Time and Burst Time\n");
    for (i = 0; i < n; i++) {
        printf("P[%d] Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P[%d] Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];  // Save burst time to remaining time array
    }

    while (count < n) {
        smallest = -1;
        int min_burst = INT_MAX;

        // Find process with smallest remaining burst time that has arrived
        for (i = 0; i < n; i++) {
            if (completed[i] == 0 && at[i] <= time && rt[i] < min_burst) {
                min_burst = rt[i];
                smallest = i;
            }
        }

        if (smallest == -1) {
            time++;
            continue;
        }

        // Execute one unit of time for the selected process
        printf("P[%d] ", smallest + 1);
        rt[smallest]--;

        // If process completes execution
        if (rt[smallest] == 0) {
            completed[smallest] = 1;
            count++;
            ct[smallest] = time + 1;
            tat[smallest] = ct[smallest] - at[smallest];
            wt[smallest] = tat[smallest] - bt[smallest];
            avwt += wt[smallest];
            avtat += tat[smallest];
        }

        time++;
    }

    printf("\n\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");

    for (i = 0; i < n; i++) {
        printf("P[%d]\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i], ct[i]);
    }

    avwt /= n;
    avtat /= n;
    printf("\nAverage Waiting Time: %.2f\n", avwt);
    printf("Average Turnaround Time: %.2f\n", avtat);

    return 0;
}


