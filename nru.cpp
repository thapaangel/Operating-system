#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3 // Number of frames

// Structure to represent a page frame
struct Frame {
    int page_number;
    bool referenced;
    bool modified;
};

int main() {
    int n = 20; // Assuming a maximum of 20 page references
    int pages[] = {1, 2, 3, 2, 1, 5, 2, 1, 6, 2, 5, 6, 3, 1, 3, 6, 1, 2, 4, 3}; // Page reference string
    int page_faults = 0;

    // Initialize frames
    struct Frame frames[MAX_FRAMES];
    for (int i = 0; i < MAX_FRAMES; ++i) {
        frames[i].page_number = -1; // Initialize with -1 (indicating empty)
        frames[i].referenced = false;
        frames[i].modified = false;
    }

    printf("Page Replacement Process:\n");

    for (int i = 0; i < n; ++i) {
        int current_page = pages[i];
        bool page_found = false;

        // Check if page is already in frame
        for (int j = 0; j < MAX_FRAMES; ++j) {
            if (frames[j].page_number == current_page) {
                frames[j].referenced = true; // Set referenced bit
                page_found = true;
                break;
            }
        }

        // If page is not in frame, find a suitable frame to replace
        if (!page_found) {
            // Find a victim page based on NRU criteria (not referenced, not modified)
            int victim_index = -1;
            for (int j = 0; j < MAX_FRAMES; ++j) {
                if (!frames[j].referenced && !frames[j].modified) {
                    victim_index = j;
                    break;
                }
            }

            // If no such page found, look for (not referenced, modified)
            if (victim_index == -1) {
                for (int j = 0; j < MAX_FRAMES; ++j) {
                    if (!frames[j].referenced && frames[j].modified) {
                        victim_index = j;
                        break;
                    }
                }
            }

            // If still no page found, choose any page (circular replacement)
            if (victim_index == -1) {
                victim_index = i % MAX_FRAMES; // Simple circular replacement
            }

            // Replace the victim page
            frames[victim_index].page_number = current_page;
            frames[victim_index].referenced = true; // Set referenced bit
            frames[victim_index].modified = false; // Reset modified bit (for simplicity)

            ++page_faults;

            // Print current frames
            for (int j = 0; j < MAX_FRAMES; ++j) {
                if (frames[j].page_number == -1) {
                    printf("- ");
                } else {
                    printf("%d ", frames[j].page_number);
                }
            }
            printf("\n");
        }
    }
    printf("\nTotal Page Faults: %d\n", page_faults);
    return 0;
}

