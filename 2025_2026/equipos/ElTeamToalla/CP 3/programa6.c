#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

volatile sig_atomic_t bandera = 1;

void handler(int sig) {
    printf("Hijo %d: recibió la señal %d, terminando...\n", getpid(), sig);
    bandera = 0;
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Código del hijo
        signal(SIGUSR1, handler);
        while (bandera) {
            // Espera señal
        }
        exit(0);
    } else {
        // Código del padre
        sleep(2); // Dar tiempo al hijo para que inicie
        kill(pid, SIGUSR1); // Enviar señal al hijo
        wait(NULL); // Esperar a que hijo termine
        printf("Padre: hijo %d terminó\n", pid);
    }

    return 0;
}
