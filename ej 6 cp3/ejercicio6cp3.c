#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

volatile sig_atomic_t bandera = 1;  // Variable global modificada por la señal

// Manejador de señal para el hijo
void manejador_hijo(int sig) {
    if (sig == SIGUSR1) {
        printf("Hijo (%d): Recibí la señal SIGUSR1, terminando...\n", getpid());
        bandera = 0;  // Cambia la bandera para salir del bucle
    }
}

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Error al crear el proceso hijo");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Código del HIJO 
        signal(SIGUSR1, manejador_hijo);

        printf("Hijo (%d): Esperando señal SIGUSR1...\n", getpid());

        while (bandera) {
            printf("Hijo (%d): Trabajando...\n", getpid());
            sleep(1);
        }

        printf("Hijo (%d): Finalizado correctamente.\n", getpid());
        exit(EXIT_SUCCESS);
    } else {
        //  Código del PADRE 
        sleep(5);  // Espera un poco antes de enviar la señal
        printf("Padre (%d): Enviando señal SIGUSR1 al hijo (%d)...\n", getpid(), pid);
        kill(pid, SIGUSR1);

        wait(NULL);  // Espera a que el hijo termine
        printf("Padre (%d): El hijo terminó. Fin del programa.\n", getpid());
    }

    return 0;
}
