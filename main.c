#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(void) {

    int dati[12] = {3,7,2,9,4,6,8,1,5,10,2,7};

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            printf("Errore fork");
            exit(-1);
        } else if (pid == 0) {
            // Codice figli

            int somma = 0;

            if (i == 0) {
                for (int j = 0; j < 4; j++) {
                    somma += dati[j];
                }
                printf("[Figlio 1, PID %d] somma parziale: %d\n", getpid(), somma);
                exit(somma);
            }
            if (i == 1) {
                for (int j = 4; j < 8; j++) {
                    somma += dati[j];
                }
                printf("[Figlio 2, PID %d] somma parziale: %d\n", getpid(), somma);
                exit(somma);
            }
            if (i == 2) {
                for (int j = 8; j < 12; j++) {
                    somma += dati[j];
                }
                printf("[Figlio 3, PID %d] somma parziale: %d\n", getpid(), somma);
                exit(somma);
            }
        }
    }

    // padre

    int somma = 0;

    for (int i = 0; i < 3; i++) {
        int status;

        wait(&status);

        if (WIFEXITED(status)) {
            int risultato = WEXITSTATUS(status);

            somma += risultato;
        }
    }

    printf("[Padre] Somma totale: %d\n", somma);

    return 0;
}