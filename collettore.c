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

    int pd = open(FIFO, O_RDONLY);

    int cont;
    int array[cont + 1];
    read(pd, &cont, sizeof(cont));

    int somma = 0;

    for (int i = 0; i < cont + 1; i++) {
        int n;
        read(pd, &n, sizeof(n));
        printf("Collettore: %d\n", n);
        array[i] = n;
        somma += n;
    }

    printf("Numeri pari ricevuti: %d\n", cont);
    printf("Somma: %d", somma);

    close(pd);
    unlink(FIFO);

    return 0;
}