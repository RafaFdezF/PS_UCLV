#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


volatile sig_atomic_t bandera = 1;


void manejador_hijo(int sig) {
    if (sig == SIGUSR1) {
        printf("\n(Hijo): Recibí la señal SIGUSR1. Terminando proceso...\n");
        bandera = 0;
    }
}

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Error al crear el proceso hijo");
        exit(1);
    }

    if (pid == 0) {
        //PROCESO HIJO
        signal(SIGUSR1, manejador_hijo);

        printf("(Hijo): Iniciando bucle...\n");


        while (bandera) {
            printf("(Hijo): Trabajando...\n");
            sleep(1);
        }

        printf("(Hijo): Proceso finalizado correctamente.\n");
        exit(0);
    }
    else {
        //PROCESO PADRE
        printf("(Padre): PID del hijo: %d\n", pid);
        sleep(5);

        printf("(Padre): Enviando señal SIGUSR1 al hijo...\n");
        kill(pid, SIGUSR1);

        wait(NULL);
        printf("(Padre): El hijo ha terminado. Fin del programa.\n");
    }

    return 0;
}
