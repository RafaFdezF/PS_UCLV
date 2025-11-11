#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
// Variable global para indicar si hubo error
volatile sig_atomic_t division_por_cero = 0;
// Manejador de señal para SIGFPE (Error de operación aritmética)
void manejar_sigfpe(int sig) {
    division_por_cero = 1;
    printf("¡Capturada división por cero! Generando pendiente aleatoria...\n");
}
// Función para calcular pendiente
double calcular_pendiente(double x1, double y1, double x2, double y2) {
    if (x2 == x1) {
        raise(SIGFPE);
    }
    return (y2 - y1) / (x2 - x1);
}
// Función para generar pendiente aleatoria
double pendiente_aleatoria() {
    // Generar pendiente entre -10 y 10
    return (rand() % 2001 - 1000) / 100.0;
}

int main() {
    double x1, y1, x2, y2;
    double pendiente;
    
    // Inicializar semilla para números aleatorios
    srand(time(NULL));
    
    // Configurar el manejador de señales
    struct sigaction sa;
    sa.sa_handler = manejar_sigfpe;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    if (sigaction(SIGFPE, &sa, NULL) == -1) {
        perror("Error al configurar manejador de señal");
        return 1;
    }
    
    printf("=== CALCULADORA DE PENDIENTES ===\n");
    printf("(Ingrese coordenadas para calcular pendiente, Ctrl+C para salir)\n\n");
    
    while (1) {
        division_por_cero = 0;
        
        // Leer coordenadas
        printf("Ingrese coordenadas del punto 1 (x1 y1): ");
        if (scanf("%lf %lf", &x1, &y1) != 2) {
            printf("Entrada inválida. Saliendo...\n");
            break;
        }
        
        printf("Ingrese coordenadas del punto 2 (x2 y2): ");
        if (scanf("%lf %lf", &x2, &y2) != 2) {
            printf("Entrada inválida. Saliendo...\n");
            break;
        }
        
        pendiente = calcular_pendiente(x1, y1, x2, y2);
        
        // Verificar si hubo división por cero
        if (division_por_cero) {
            pendiente = pendiente_aleatoria();
            printf("Pendiente (aleatoria): %.2f\n", pendiente);
        } else {
            printf("Pendiente calculada: %.2f\n", pendiente);
        }
        
        printf("\n");
    }
    
    return 0;
}