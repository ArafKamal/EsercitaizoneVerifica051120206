#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {

    int fd[2]; // 0: leggo, 1: scrivo

    if (pipe(fd) == -1) {
        perror("Errore pipe");
        exit(1);
    }

    // (fd[0]); // serve per chiudere quella cosa se tipo uno manda e l'altro scrive

    // int numero = 25;
    // read(fd[0], &numero, sizeof(numero));
    // write(fd[1], &numero, sizeof(numero));

    pid_t pid = fork();

    if (pid < 0) {
        printf("Errore fork");
        exit( -1);
    } else if (pid == 0) {
        // figlio
        close(fd[1]);

        int numero;

        read(fd[0], &numero, sizeof(numero));

        printf("Numero ricevuto: %d\n", numero);

        close(fd[0]);

        exit(0);
    } else {

        close(fd[0]);

        int num;
        printf("Inserisci il numero\n");
        scanf("%d", &num);

        write(fd[1], &num, sizeof(num));

        close(fd[1]);

        wait(NULL);

        exit(1);
    }

    return 0;
}