#include "vlib.h"
#include <stdio.h>

const int N = 5;

int main() {
    // Crear dos vectores de tamaño N
    Vector *v1 = v_create(N);
    Vector *v2 = v_create(N);

    if (!v1 || !v2) {
        fprintf(stderr, "Error: No se pudo crear los vectores.\n");
        return 1;
    }

    // Inicializar v1 con valores aleatorios
    v_fill_rand(v1);

    // Inicializar v2 con un valor fijo 
    v_fill(v2, 2.0);

    // Mostrar vectores originales
    printf("Vector v1: "); v_print(v1);
    printf("Vector v2: "); v_print(v2);

    // Sumar vectores
    Vector *suma = v_add(v1, v2);
    if (suma) {
        printf("v1 + v2 = "); v_print(suma);
    } else {
        fprintf(stderr, "Error al sumar vectores\n");
    }

    // Restar vectores
    Vector *resta = v_sub(v1, v2);
    if (resta) {
        printf("v1 - v2 = "); v_print(resta);
    } else {
        fprintf(stderr, "Error al restar vectores\n");
    }

    // Liberar memoria
    v_destroy(v1);
    v_destroy(v2);
    v_destroy(suma);
    v_destroy(resta);

    return 0;
}
