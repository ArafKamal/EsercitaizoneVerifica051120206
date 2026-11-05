#include <wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            printf("Errore fork");
            return -1;

        } else if (pid == 0) {
            // figlio

            printf("[Pid figlio] %d\n", getpid());

            int temp;
            printf("Inserisci la temperature\n");
            scanf("%d", &temp);

            if (temp < 10) {
                exit(1);
            } else if (temp < 31) {
                exit(2);
            } else {
                exit(3);
            }
        }
    }

    // padre

    printf("[padre pid] %d\n", getpid());

    for (int i = 0; i < 3; i++) {
        int status;

        wait(&status);

        if (WIFEXITED(status)) {
            int risultato = WEXITSTATUS(status);

            if (risultato == 1) {
                printf("Temperatura troppo bassa\n");
            } else if (risultato == 2) {
                printf("Temperatura buona\n");
            } else {
                printf("Temperature troppo alta\n");
            }
        }
    }

    return 0;
}