#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define FIFO "/tmp/mia_fifo"

int main(void) {


    if (mkfifo(FIFO, 0666) == -1) {
        if (EEXIST == errno) {
            printf("La fifo esiste già\n");
        } else {
            perror("Errore fifo");
            exit(1);
        }
    }

    char msg[100];

    int fd = open(FIFO, O_WRONLY);

    if (fd == -1) {
        perror("Errore open");
        exit(1);
    }

    while (1) {

        printf("Inserisci un messaggio: ");
        fflush(stdout);
        fgets(msg, sizeof(msg), stdin);

        msg[strcspn(msg, "\n")] = '\0';

        if (strcmp(msg, "QUIT") == 0) {
            write(fd, msg, strlen(msg) + 1);
            break;
        }

        write(fd, msg, strlen(msg) + 1);
    }

    close(fd);

    return 0;
}