#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <wait.h>
#include <errno.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO "/tmp/fifo_pari"

int main(void) {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("Errore pipe");
        exit(-1);
    }

    if (mkfifo(FIFO, 0666) == -1) {
        if (errno == EEXIST) {
            printf("La fifo esiste già");
        } else {
            perror("Errore fifo");
            exit(-1);
        }
    }

    pid_t pid = fork();

    if (pid < 0) {
        printf("Errore fork");
        exit(-1);
    } else if (pid == 0) {
        // FIGLIO
        srand(time(NULL));
        close(fd[0]);

        for (int i = 0; i < 20; i++) {
            int numero = rand() % 100 + 1;
            write(fd[1], &numero, sizeof(numero));
        }

        close(fd[1]);
        exit(0);
    } else {
        // PADRE
        close(fd[1]);

        int array[20];
        int cont = 0;

        for (int i = 0; i < 20; i++) {
            int numero;
            read(fd[0], &numero,sizeof(numero));
            if (numero % 2 == 0) {
                array[cont] = numero;
                cont++;
            }
        }

        wait(NULL);

        close(fd[0]);

        int pd = open(FIFO, O_WRONLY);

        write(pd, &cont, sizeof(cont));

        for (int i = 0; i < cont; i++) {
            write(pd, &array[i], sizeof(array[i]));
        }

        close(pd);
        exit(0);
    }












    return 0;
}