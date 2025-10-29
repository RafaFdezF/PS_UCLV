#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <setjmp.h>
#include <math.h>

jmp_buf buf;

void manejar_error()
{
    srand(time(NULL));
    float pendiente_aleatoria = (float)rand() / RAND_MAX * 100.0;
    printf("Error de división por cero. Pendiente aleatoria: %.2f\n", pendiente_aleatoria);
    longjmp(buf, 1);
}

int main()
{
    signal(SIGFPE, manejar_error);

    float x1, y1, x2, y2;
    printf("Ingrese coordenadas (x1 y1 x2 y2): ");
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);

    if (setjmp(buf) == 0)
    {
        // Verificar manualmente división por cero
        if (x2 - x1 == 0.0f)
        {
            // Forzar señal SIGFPE
            raise(SIGFPE);
        }
        else
        {
            float pendiente = (y2 - y1) / (x2 - x1);
            printf("Pendiente calculada: %.2f\n", pendiente);
        }
    }

    return 0;
}