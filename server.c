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
    char msg[100];

    int fd = open(FIFO, O_RDONLY);

    if (fd == -1) {
        perror("Errore fifo");
        exit(1);
    }

    while (1) {
        read(fd, msg, sizeof(msg));

        if (strcmp(msg, "QUIT") == 0) {
            break;
        }

        printf("[Server] %s\n", msg);
        fflush(stdout);
    }

    close(fd);
    unlink(FIFO);



    return 0;
}