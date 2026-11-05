#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <unistd.h>

int main(void) {

    pid_t pid = fork();

    if (pid < 0) {
        printf("Errore Fork");
    } else if (pid == 0) {

        // padre

        pid_t pid = fork();

        if (pid < 0) {
            printf("Errore fork");
        } else if (pid == 0) {
            // figlio
            printf("Figlio terminato");
            return  0;

        } else {
            wait(NULL);
            printf("Padre terminato");
            return 0;
        }

    } else {
        // Nonno

        wait(NULL);
        printf("Nonno terminato");
        return 0;
    }

    return 0;
}