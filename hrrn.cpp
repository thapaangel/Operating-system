#include <stdio.h>
#include <limits.h>

int main() {
    int n, bt[20], at[20], wt[20], tat[20], ct[20], completed[20] = {0};
    float avwt = 0, avtat = 0;
    int i, time = 0, count = 0;
    float response_ratio[20];

    printf("Enter total number of processes (maximum 20): ");
    scanf("%d", &n);

    printf("Enter Process Arrival Time and Burst Time\n");
    for (i = 0; i < n; i++) {
        printf("P[%d] Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P[%d] Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
    }

    while (count < n) {
        int selected = -1;
        float max_response_ratio = -1.0;

        // Calculate response ratios for all processes
        for (i = 0; i < n; i++) {
            if (completed[i] == 0 && at[i] <= time) {
                response_ratio[i] = ((time - at[i]) + bt[i]) / (float) bt[i];
                if (response_ratio[i] > max_response_ratio) {
                    max_response_ratio = response_ratio[i];
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            time++;
            continue;
        }

        // Execute the selected process
        time += bt[selected];
        ct[selected] = time;
        tat[selected] = ct[selected] - at[selected];
        wt[selected] = tat[selected] - bt[selected];
        completed[selected] = 1;
        count++;

        avwt += wt[selected];
        avtat += tat[selected];

        printf("P[%d] executed at time %d\n", selected + 1, time);
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

