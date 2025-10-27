#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

unsigned int counter = 0;  // contador de segundos

// Manejador único para todas las señales
void handler(int signal) {
    if (signal == SIGALRM) {
        counter++;
        alarm(1);  // reprogramar la alarma para dentro de 1 segundo
    } 
    else if (signal == SIGUSR1) {
        counter = 0;
        printf("\n[SIGUSR1 recibida] Contador reiniciado\n");
    } 
    else if (signal == SIGUSR2) {
        printf("\n[SIGUSR2 recibida] Tiempo transcurrido: %d seg\n", counter);
    }
}

int main() {
    struct sigaction sa;

    // Limpiamos la estructura y configuramos el manejador
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Asociamos las señales al mismo manejador
    if (sigaction(SIGALRM, &sa, NULL) == -1 ||
        sigaction(SIGUSR1, &sa, NULL) == -1 ||
        sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("Error al configurar sigaction");
        exit(EXIT_FAILURE);
    }

    // Inicia la primera alarma
    alarm(1);

    printf("PID del proceso: %d\n", getpid());
    printf("Envía señales con:\n");
    printf("  kill -USR1 %d: Reinicia contador\n", getpid());
    printf("  kill -USR2 %d: Muestra contador\n", getpid());
    printf("Presiona Ctrl+C para detener el programa.\n\n");

    // Bucle infinito que espera señales
    while (1) {
        pause();  // Suspende el proceso hasta recibir una señal
    }

    return 0;
}
