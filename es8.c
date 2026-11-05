#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <string.h>
#include <ctype.h>

struct Messaggio {
    char testo[100];
    int vocali;
};

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
        // FIGLIO

        close(pipe1[1]); // read
        close(pipe2[0]); // write
        // pipe 2 per read, pipe1 per write

        char msg[100];

        read(pipe1[0], msg, sizeof(msg));

        for (int i = 0; msg[i] != '\0'; i++) {
            msg[i] = toupper((unsigned char)msg[i]);
        }

        int vocali = 0;

        for (int i = 0; msg[i] != '\0'; i++) {
            if (msg[i] == 'A' || msg[i] == 'E' || msg[i] == 'I' || msg[i] == 'O' || msg[i] == 'U') {
                vocali++;
            }
        }

        struct Messaggio mess;

        strcpy(mess.testo, msg);
        mess.vocali = vocali;

        write(pipe2[1], &mess, sizeof(mess));

        close(pipe1[0]);
        close(pipe2[1]);

        exit(0);

    } else {
        // PADRE
        close(pipe1[0]); // write
        close(pipe2[1]); // read
        // pipe 1 per read, pipe2 per write

        char msg[100];
        printf("Inserisci il messaggio");
        fgets(msg, sizeof(msg), stdin);

        write(pipe1[1], msg, strlen(msg) + 1);

        struct Messaggio mess;

        read(pipe2[0], &mess, sizeof(mess));

        printf("Testo: %s, Vocali: %d", mess.testo, mess.vocali);


        close(pipe1[1]);
        close(pipe2[0]);

        wait(NULL);

        exit(1);
    }


    return 0;
}