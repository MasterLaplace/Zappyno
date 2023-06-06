#include <stdio.h>
#include <time.h>

int main() {
    const int delaySeconds = 8;
    clock_t startTime = clock();  // Initial time in microseconds
    clock_t delay = delaySeconds * CLOCKS_PER_SEC; // Delay in microseconds

    while (1) {
        if (clock() - startTime >= delay) {
            printf("8 seconds have passed.\n");
            startTime = clock();  // reset the timer
        }
    }

    return 0;
}