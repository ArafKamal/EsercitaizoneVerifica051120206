#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <time.h>

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

    pid_t pidB = fork();

    if (pidB < 0) {
        printf("Errore fork");
        exit(-1);
    } else if (pidB == 0) {
        // PROCESSO B

        close(pipe1[1]); // chiusura write
        close(pipe2[0]); // chiusura read

        int num;
        int i = 0;
        int array[20];

        while (read(pipe1[0], &num, sizeof(num)) > 0) {
            if (num >= 50) {
                array[i] = num;
                i++;
            }
        }

        for (int j = 0; j < i; j++) {
            array[j] = array[j] * array[j];
        }

        write(pipe2[1], &i, sizeof(i));

        for (int j = 0; j < i; j++) {
            write(pipe2[1], &array[j], sizeof(array[j]));
        }

        close(pipe2[1]);
        exit(0);
    }

    pid_t pidC = fork();

    if (pidC < 0) {
        printf("Errore fork");
        exit(-1);
    } else if (pidC == 0) {
        // PROCESSO C

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[1]); // chiusura write

        int len;
        read(pipe2[0], &len, sizeof(len));

        int array[len];

        for (int i = 0; i < len; i++) {
            int num;
            read(pipe2[0], &num, sizeof(num));
            printf("%d\n", num);
            array[i] = num;
        }

        float media = 0;

        for (int i = 0; i < len; i++) {
            media += array[i];
        }

        if (len == 0) {
            printf("Nessun valore ricevuto");
            exit(0);
        }
        media = media / (float)len;

        printf("Media: %.2f", media);

        close(pipe2[0]);
        exit(0);
    }

    // PADRE

    close(pipe1[0]); // chiusura read
    close(pipe2[0]);
    close(pipe2[1]);

    int casuale;
    srand(time(NULL));

    for (int i = 0; i < 20; i++) {
        int numero = rand() % 100 + 1;
        write(pipe1[1], &numero, sizeof(numero));
    }

    close(pipe1[1]);

    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }
    return 0;
}