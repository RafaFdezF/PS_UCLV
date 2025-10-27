#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void manejador_sigint(int sig) {
    printf("\n[Handler] Proceso %d recibió la señal %d (SIGINT)\n", getpid(), sig);
}

int main(void) {
    // Asociamos SIGINT con el manejador
    signal(SIGINT, manejador_sigint);

    printf("=== Programa en ejecución ===\n");
    printf("PID del proceso: %d\n", getpid());
    printf("Presiona Ctrl+C para enviar SIGINT\n");
    printf("(El programa seguirá corriendo hasta que se ignore la señal)\n\n");

    // Bucle para mantener el proceso activo
    for (int i = 1; i <= 3; i++) {
        printf("Esperando señales... (%d/3)\n", i);
        sleep(5); 
    }

    printf("\nAhora el proceso ignorará SIGINT.\n");
    signal(SIGINT, SIG_IGN);  // A partir de aquí se ignora SIGINT

    printf("Presiona Ctrl+C nuevamente: ya no tendrá efecto.\n");

   
    for (int i = 1; i <= 3; i++) {
        printf("Esperando (señal ignorada)... (%d/3)\n", i);
        sleep(5);
    }

    printf("\nPrograma finalizado.\n");
    return 0;
}
