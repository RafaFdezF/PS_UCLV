#define _POSIX_C_SOURCE 200809L  
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <time.h>
#include <unistd.h>


static sigjmp_buf env;

/* Manejador de SIGFPE */
void manejador_sigfpe(int signo) {
    (void)signo; 
    siglongjmp(env, 1); 
}

/* Genera pendiente aleatoria */
int pendiente_aleatoria(void) {
    return (rand() % 21) - 10; // -10 a 10
}

int main(void) {
    int x1, y1, x2, y2;
    int pendiente;
    struct sigaction sa;

    srand((unsigned)time(NULL));

   
    sa.sa_handler = manejador_sigfpe;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGFPE, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Programa: calcula pendiente. División por cero genera SIGFPE y se usa pendiente aleatoria.\n\n");

    while (1) {
        printf("Ingrese los puntos (x1 y1 x2 y2) o EOF (Ctrl+D) para salir: ");
        fflush(stdout);

        if (scanf("%d %d %d %d", &x1, &y1, &x2, &y2) != 4) {
            printf("\nEntrada finalizada o inválida. Saliendo.\n");
            break;
        }

        /* Punto seguro para capturar SIGFPE */
        if (sigsetjmp(env, 1) != 0) {
            int aleat = pendiente_aleatoria();
            printf("\n Error de coma flotante (división por cero)\n");
            printf("Se usará pendiente aleatoria: %d\n\n", aleat);
            continue;
        }

        printf("Calculando pendiente...\n");

        int numer = y2 - y1;
        int denom = x2 - x1;

        if (denom == 0) {
            raise(SIGFPE); // forzamos la señal
            continue;
        }

        pendiente = numer / denom;
        printf("La pendiente de la recta es: %d\n\n", pendiente);
        sleep(1);
    }

    return 0;
}
