#include <stdio.h>

int main() {
    int n, f;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter page reference string: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frames[f], time[f], faults = 0;
    for(int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nPage\tFrames\n-------------------\n");

    for(int i = 0; i < n; i++) {
        int page = pages[i], found = 0;

        // Check if page is already in frame
        for(int j = 0; j < f; j++) {
            if(frames[j] == page) {
                found = 1;
                time[j] = i + 1; // Update last used time
                break;
            }
        }

        if(!found) { // Page fault
            faults++;
            int replace = -1;

            // Find empty frame
            for(int j = 0; j < f; j++) {
                if(frames[j] == -1) {
                    replace = j;
                    break;
                }
            }

            // If no empty frame, replace LRU page
            if(replace == -1) {
                int minTime = time[0], pos = 0;
                for(int j = 1; j < f; j++) {
                    if(time[j] < minTime) {
                        minTime = time[j];
                        pos = j;
                    }
                }
                replace = pos;
            }

            frames[replace] = page;
            time[replace] = i + 1;
        }

        // Print frames after each step
        printf("%d\t", page);
        for(int j = 0; j < f; j++)
            if(frames[j] != -1) printf("%d ", frames[j]);
            else printf("- ");
        printf("\n");
    }

    printf("-------------------\nTotal Page Faults = %d\n", faults);
    return 0;
}
