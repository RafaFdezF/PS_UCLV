#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

// Variable global para almacenar el tiempo
volatile sig_atomic_t contador_segundos = 0;

// Función manejadora de señales
void manejador_señales(int señal) {
    switch(señal) {
        case SIGALRM:
            // Incrementar contador cada segundo
            contador_segundos++;
            alarm(1); // Reprogramar la alarma para el próximo segundo
            break;
            
        case SIGUSR1:
            // Poner contador a cero
            contador_segundos = 0;
            printf("Contador reiniciado a 0\n");
            break;
            
        case SIGUSR2:
            // Mostrar valor actual del contador
            printf("Tiempo transcurrido: %d segundos\n", contador_segundos);
            break;
    }
}

int main() {
    printf("Proceso eventos iniciado. PID: %d\n", getpid());
    printf("Señales disponibles:\n");
    printf("  SIGUSR1 (%d) - Reiniciar contador\n", SIGUSR1);
    printf("  SIGUSR2 (%d) - Mostrar contador\n", SIGUSR2);
    printf("  SIGTERM (%d) - Terminar proceso\n", SIGTERM);
    printf("\n");
    
    // Configurar el manejador de señales
    struct sigaction sa;
    sa.sa_handler = manejador_señales;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    // Registrar manejador para las señales
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("Error configurando SIGALRM");
        exit(1);
    }
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error configurando SIGUSR1");
        exit(1);
    }
    if (sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("Error configurando SIGUSR2");
        exit(1);
    }
    
    // Configurar la alarma para que se active cada segundo
    alarm(1);
    
    // Bucle infinito
    while(1) {
        pause(); // Esperar por señales
    }
    
    return 0;
}
