#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* Variable global para el tiempo en segundos */
volatile sig_atomic_t contador = 0;

/* Manejador único para todas las señales */
void manejador_senal(int signo) {
    switch(signo) {
        case SIGALRM:
            contador++;            // Incrementa cada segundo
            alarm(1);              // Reprograma alarma para 1 segundo
            break;
        case SIGUSR1:
            contador = 0;          // Resetear contador
            printf("[senal SIGUSR1] Contador reiniciado a 0\n");
            fflush(stdout);
            break;
        case SIGUSR2:
            printf("[senal SIGUSR2] Contador actual: %d\n", contador);
            fflush(stdout);
            break;
        default:
            printf("[senal desconocida] signo %d\n", signo);
            fflush(stdout);
    }
}

int main(void) {
    printf("PID del proceso: %d\n", getpid());
    printf("Programa en ejecución. Enviar señales SIGUSR1 y SIGUSR2 desde otra terminal.\n\n");

    /* Registrar manejador para SIGALRM, SIGUSR1 y SIGUSR2 */
    signal(SIGALRM, manejador_senal);
    signal(SIGUSR1, manejador_senal);
    signal(SIGUSR2, manejador_senal);

    /* Programar la primera alarma */
    alarm(1);

    /* Bucle infinito */
    while(1) {
        pause();  // Espera por señales
    }

    return 0;
}