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

    printf("Inserisci la stringa da speride\n");
    fgets(msg, 100, stdin);

    int fd = open(FIFO, O_WRONLY);

    if (fd == -1) {
        perror("Errore open");
        exit(1);
    }

    write(fd, msg, strlen(msg) + 1);

    close(fd);

    return 0;
}