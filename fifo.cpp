#include <stdio.h>

int main() {
    int n = 20; // Assuming a maximum of 20 page references
    int page[] = {1, 2, 3, 2, 1, 5, 2, 1, 6, 2, 5, 6, 3, 1, 3, 6, 1, 2, 4, 3}; // Page reference string
    int page_faults = 0;
    int frame[3] = {-1, -1, -1}; // Assuming 3 frames, initialize with -1 (indicating empty)
    int reference_bit[3] = {0, 0, 0}; // Reference bits for each frame
    int pointer = 0; // Pointer to the current frame to replace

    printf("Page Replacement Process:\n");

    for (int i = 0; i < n; ++i) {
        int current_page = page[i];
        int page_found = 0;

        // Check if page is already in frame
        for (int j = 0; j < 3; ++j) {
            if (frame[j] == current_page) {
                page_found = 1;
                reference_bit[j] = 1; // Set reference bit if page is found
                break;
            }
        }

        // If page is not in frame, replace the least recently used page
        if (!page_found) {
            // Find the first frame with reference bit 0
            while (reference_bit[pointer] == 1) {
                reference_bit[pointer] = 0; // Reset reference bit
                pointer = (pointer + 1) % 3; // Move pointer to next frame circularly
            }

            // Replace the page
            frame[pointer] = current_page;
            reference_bit[pointer] = 1; // Set reference bit for the new page
            pointer = (pointer + 1) % 3; // Move pointer to next frame circularly
            ++page_faults;

            // Print current frames
            for (int j = 0; j < 3; ++j) {
                if (frame[j] == -1) {
                    printf("- ");
                } else {
                    printf("%d ", frame[j]);
                }
            }
            printf("\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}

