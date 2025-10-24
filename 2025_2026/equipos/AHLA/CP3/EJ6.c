#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

volatile sig_atomic_t bandera = 1;

void manejar_SIGUSR1(int sig) {
    printf("Hijo (%d) recibió la señal SIGUSR1\n", getpid());
    bandera = 0;  // rompe el ciclo
}

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error al crear el proceso hijo");
        exit(1);
    }
    else if (pid == 0) {
        // Proceso hijo
        signal(SIGUSR1, manejar_SIGUSR1);
        printf("Hijo (%d) esperando señal SIGUSR1...\n", getpid());

        while (bandera) {
            pause(); 
        }

        printf("Hijo (%d) termina\n", getpid());
        exit(0);
    }
    else {
        // Proceso padre
        sleep(2); 
        printf("Padre (%d) enviando señal SIGUSR1 al hijo (%d)\n", getpid(), pid);
        kill(pid, SIGUSR1);

        wait(NULL);
        printf("Padre (%d): hijo terminado\n", getpid());
    }

    return 0;
}