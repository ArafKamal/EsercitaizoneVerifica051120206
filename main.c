#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(void) {
    
    pid_t pid = fork();

    if (pid > 0) {
        printf("[padre] uscito");
        wait(NULL);
        return 0;
    } else if (pid == 0) {
        printf("[Figlio] Uscito");
        return 0;
    } else {
        printf("Errore fork");
        return -1;
    }

    return 0;
}