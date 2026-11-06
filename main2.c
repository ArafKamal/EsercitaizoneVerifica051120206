#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/types.h>

int main(void) {

    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1) {
        perror("Errore pipe");
        exit(-1);
    }
    if (pipe(pipe2) == -1) {
        perror("Errore pipe");
        exit(-1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        printf("Errore fork");
        exit(-1);
    } else if (pid == 0) {
        // figlio
        close(pipe1[1]);
        close (pipe2[0]);

        int len;
        read(pipe1[0], &len, sizeof(len));

        int array[len];

        for (int i = 0; i < len; i++) {
            int n2;
            read(pipe1[0], &n2, sizeof(n2));
            array[i] = n2;
        }
        close(pipe1[0]);

        int somma = 0;
        int min = 999999999;
        int max = -999999999;
        for (int i = 0; i < len; i++) {
            if (array[i] < min) {
                min = array[i];
            }
            if (array[i] > max) {
                max = array[i];
            }
            somma += array[i];
        }

        write(pipe2[1], &min, sizeof(min));
        write(pipe2[1], &max, sizeof(max));
        write(pipe2[1], &somma, sizeof(somma));

        close(pipe2[1]);
        exit(0);

    } else {
        // padre
        close(pipe1[0]);
        close(pipe2[1]);

        int n;
        printf("Quanti numeri vuoi inserire?\n");
        scanf("%d", &n);

        write(pipe1[1], &n, sizeof(n));

        for (int i = 0; i < n; i++) {
            int n2;
            printf("Inserisci il numero %d\n: ", i + 1);
            scanf("%d", &n2);

            write(pipe1[1], &n2, sizeof(n2));
        }
        close(pipe1[1]);
        int max;
        int min;
        int somma;

        read(pipe2[0], &min, sizeof(min));
        printf("Min: %d\n", min);
        read(pipe2[0], &max, sizeof(max));
        printf("Max: %d\n", max);
        read(pipe2[0], &somma, sizeof(somma));
        printf("Somma: %d\n", somma);

        close(pipe2[0]);

        wait(NULL);
        exit(0);
    }






    return 0;
}