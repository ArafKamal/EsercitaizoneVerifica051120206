#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {

    pid_t pid = fork();

    if (pid == 0) {
        // figlio

        for (int i = 1; i < 6; i++) {
            printf("%d\n", i);
        }
    } else if (pid > 0) {
        wait(NULL);

        for (int i = 6; i < 11; i++) {
            printf("%d\n", i);
        }
    }

    return 0;
}