#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

int main(void) {

    int array[10] = {1,2,3,4,67,30,7,8,9,10};
    int fd[2];

    if (pipe(fd) == -1) {
        perror("Errore pipe");
        exit(-1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        printf("Errore fork");
        exit(-1);
    } else if (pid == 0) {
        // FIGLIO

        close(fd[0]); // read

        int somma = 0;

        for (int i = 0; i < 10; i++) {
            if (array[i] % 2 == 0) {
                somma += array[i];
            }
        }

        write(fd[1], &somma, sizeof(somma));
        close(fd[1]);

    } else {
        // PADRE
        close(fd[1]);

        int somma = 0;

        for (int i = 0; i < 10; i++) {
            if (array[i] % 2 == 1) {
                somma += array[i];
            }
        }

        int pari;

        read(fd[0], &pari, sizeof(pari));
        close(fd[0]);

        wait(NULL);

        int tot = pari + somma;

        printf("Pari: %d\n", pari);
        printf("Dispari: %d\n", somma);
        printf("Totale: %d\n", tot);

        exit(1);
    }

    return 0;
}