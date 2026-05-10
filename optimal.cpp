#include <stdio.h>
#include <stdbool.h>

int main() {
    int n = 20; // Assuming a maximum of 20 page references
    int pages[] = {1, 2, 3, 2, 1, 5, 2, 1, 6, 2, 5, 6, 3, 1, 3, 6, 1, 2, 4, 3}; // Page reference string
    int page_faults = 0;
    int frames[3] = {-1, -1, -1}; // Assuming 3 frames, initialize with -1 (indicating empty)

    printf("Page Replacement Process:\n");

    for (int i = 0; i < n; ++i) {
        int current_page = pages[i];
        bool page_found = false;

        // Check if page is already in frame
        for (int j = 0; j < 3; ++j) {
            if (frames[j] == current_page) {
                page_found = true;
                break;
            }
        }

        // If page is not in frame, find the optimal page to replace
        if (!page_found) {
            int replace_index = -1;
            int farthest = i;
            for (int j = 0; j < 3; ++j) {
                bool found_future = false;
                for (int k = i + 1; k < n; ++k) {
                    if (frames[j] == pages[k]) {
                        found_future = true;
                        if (k > farthest) {
                            farthest = k;
                            replace_index = j;
                        }
                        break;
                    }
                }
                if (!found_future) {
                    replace_index = j;
                    break;
                }
            }

            // Replace the page
            frames[replace_index] = current_page;
            ++page_faults;

            // Print current frames
            for (int j = 0; j < 3; ++j) {
                if (frames[j] == -1) {
                    printf("- ");
                } else {
                    printf("%d ", frames[j]);
                }
            }
            printf("\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}

