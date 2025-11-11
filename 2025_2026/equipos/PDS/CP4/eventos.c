#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

// Variable global para el contador de tiempo
volatile sig_atomic_t contador_tiempo = 0;

// Función manejadora única para todas las señales
void manejador_seniales(int senial) {
    switch(senial) {
        case SIGALRM:
            // Incrementar contador cada segundo
            contador_tiempo++;
            alarm(1);  // Reprogramar la alarma para el próximo segundo
            break;
            
        case SIGUSR1:
            // Poner el contador a cero
            printf("\nSeñal SIGUSR1 recibida: Reiniciando contador...\n");
            contador_tiempo = 0;
            break;
            
        case SIGUSR2:
            // Mostrar el valor actual del contador
            printf("\nSeñal SIGUSR2 recibida: Tiempo transcurrido = %d segundos\n", contador_tiempo);
            break;
            
        case SIGINT:
            // Manejar Ctrl+C para salir elegantemente
            printf("\nSeñal SIGINT recibida: Terminando programa...\n");
            printf("Tiempo total ejecutado: %d segundos\n", contador_tiempo);
            exit(0);
            break;
    }
}

int main() {
    printf("=== PROGRAMA EVENTOS ===\n");
    printf("PID del proceso: %d\n", getpid());
    printf("Contador iniciado. Envíe señales:\n");
    printf("  kill -SIGUSR1 %d  -> Reiniciar contador\n", getpid());
    printf("  kill -SIGUSR2 %d  -> Mostrar contador\n", getpid());
    printf("  Ctrl+C -> Salir del programa\n\n");
    
    // Configurar el manejador de señales
    struct sigaction sa;
    sa.sa_handler = manejador_seniales;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    // Registrar el mismo manejador para todas las señales
    sigaction(SIGALRM, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
    
    // Configurar la alarma para que se active cada segundo
    alarm(1);
    
    // Bucle infinito
    while(1) {
        // El programa principal no hace nada, solo espera señales
        pause();  // Espera por señales
    }
    
    return 0;
}