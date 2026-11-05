#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>

int main(void) {

    pid_t pid = fork();

    if (pid < 0) {
        printf("Errore");
        return -1;
    } else if (pid > 0) {

        // padre
        int status;

        wait (&status);

        if (WIFEXITED(status)) {
            int risultato = WEXITSTATUS(status);

            if (risultato == 1) {
                printf("il numero è primo");
            } else if (risultato == 2) {
                printf("Il numero è pari");
            } else if (risultato == 3) {
                printf("il numero è dispari");
            }
        }
    } else {
        int numero;

        printf("Inserisci il numero");
        scanf("%d",&numero);

        if (numero < 3) {
            exit(1);
        } else if (numero % 2 == 0) {
            exit(2);
        } else {
            exit(3);
        }


    }


    return 0;
}