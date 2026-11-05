#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            // figlio

            printf("%d\n", getpid());
            return 0;

        } else if (pid < 0) {
            printf("Errore fork");
            return -1;
        }
    }

    // padre
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Figli finiti");

    return 0;
}