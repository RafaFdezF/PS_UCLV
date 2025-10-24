#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <time.h>
#include <unistd.h>

/* Buffer para saltar desde el handler de señales */
static sigjmp_buf env;

/* Manejador de SIGFPE */
void manejador_sigfpe(int signo) {
    (void)signo; // ignoramos el argumento
    siglongjmp(env, 1); // volver al main
}

/* Genera pendiente aleatoria */
int pendiente_aleatoria(void) {
    return (rand() % 21) - 10; // -10 a 10
}

int main(void) {
    int x1, y1, x2, y2;
    int pendiente;

    srand((unsigned)time(NULL));

    /* Instalar handler de SIGFPE */
    signal(SIGFPE, manejador_sigfpe);

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
            printf("\n⚠  Error de coma flotante (división por cero)\n");
            printf("Se usará pendiente aleatoria: %d\n\n", aleat);
            continue; // vuelve a pedir nuevos valores
        }

        printf("Calculando pendiente...\n");
        /* División entera: si x2==x1, se dispara SIGFPE */
        pendiente = (y2 - y1) / (x2 - x1);

        printf("La pendiente de la recta es: %d\n\n", pendiente);
        sleep(1);
    }

    return 0;
}