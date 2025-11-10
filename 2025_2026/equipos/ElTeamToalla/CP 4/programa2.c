#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(void) {
    double x1, y1, x2, y2;
    double pendiente;

    srand((unsigned)time(NULL)); // inicializa generador de números aleatorios

    printf("Ingrese x1 y1 x2 y2 (ej: 0 0 1 1): ");
    if (scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2) != 4) {
        fprintf(stderr, "Entrada inválida\n");
        return 1;
    }

    double dx = x2 - x1;

    if (dx == 0.0) {
        printf("dx == 0 -> división por cero detectada. Generando pendiente aleatoria.\n");
        pendiente = ((double)rand() / RAND_MAX) * 10.0 - 5.0; // entre -5 y 5
    } else {
        pendiente = (y2 - y1) / dx;
        if (!isfinite(pendiente)) {
            printf("Resultado no finito (inf/nan). Generando pendiente aleatoria.\n");
            pendiente = ((double)rand() / RAND_MAX) * 10.0 - 5.0;
        }
    }

    printf("Pendiente resultante: %f\n", pendiente);
    return 0;
}
