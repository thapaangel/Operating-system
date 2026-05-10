#include <stdio.h>

int main() {
    int nu, at[20], bt[20], rt[20], wt[20], tat[20], ct[20], pri[20];
    int time = 0, completed = 0, smallest, remain;
    float atat = 0, awt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &nu);

    printf("Enter Process Arrival Time:\n");
    for (int i = 0; i < nu; i++) {
        scanf("%d", &at[i]);
    }

    printf("Enter Process Burst Time:\n");
    for (int i = 0; i < nu; i++) {
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter Process Priority:\n");
    for (int i = 0; i < nu; i++) {
        scanf("%d", &pri[i]);
    }

    remain = nu;
    pri[19] = 9999; // A very low priority

    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tCompletion Time\tTurnaround Time\n");

    while (remain != 0) {
        smallest = 19;
        for (int i = 0; i < nu; i++) {
            if (at[i] <= time && pri[i] < pri[smallest] && rt[i] > 0) {
                smallest = i;
            }
        }
        rt[smallest]--;

        if (rt[smallest] == 0) {
            remain--;
            completed = time + 1;
            ct[smallest] = completed;
            wt[smallest] = completed - at[smallest] - bt[smallest];
            tat[smallest] = completed - at[smallest];
            awt += wt[smallest];
            atat += tat[smallest];

            printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", smallest + 1, at[smallest], bt[smallest], pri[smallest], wt[smallest], ct[smallest], tat[smallest]);
        }
        time++;
    }

    atat /= nu;
    awt /= nu;

    printf("\nAverage Waiting Time: %.2f\n", awt);
    printf("Average Turnaround Time: %.2f\n", atat);

    return 0;
}

