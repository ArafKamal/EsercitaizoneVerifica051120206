#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>


int main(void) {

    if (mkfifo("/tmp/mia_fifo", 0666) == -1) { // percorso, permessi accesso
        if (errno == EEXIST) {
            printf("La FIFO esiste già\n");
        } else {
            perror("Errore mkfifo");
            exit(1);
        }
    }

    // O_RDONLY lettura, O_WRONLY scrittura O_RDWR let e scri

    int fd = open("/tmp/mia_fifo", O_WRONLY);
    printf("FIFO aperta!\n");

    unlink("/tmp/mia_fifo"); // rimuove percorso



    return 0;
}