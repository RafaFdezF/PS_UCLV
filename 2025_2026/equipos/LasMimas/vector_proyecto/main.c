#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vector_ops.h"

int main() {
    size_t n;
    double valor_constante = 5.0; // valor para llenar el segundo vector

    printf("Ingrese el tamaño de los vectores: ");
    if (scanf("%zu", &n) != 1 || n == 0) {
        printf("Entrada inválida.\n");
        return 1;
    }

    // Crear los tres vectores (A, B, C)
    double* A = vec_create(n);
    double* B = vec_create(n);
    double* C = vec_create(n);

    if (!A || !B || !C) {
        printf("Error al crear los vectores.\n");
        vec_free(A);
        vec_free(B);
        vec_free(C);
        return 1;
    }

    // Inicializar
    srand(time(NULL));
    vec_randomize(A, n, 0.0, 10.0);  // A con valores aleatorios
    vec_fill(B, n, valor_constante); // B con un valor fijo

    printf("\n--- Vector A (aleatorio) ---\n");
    vec_print(A, n);

    printf("\n--- Vector B (fijo = %.2f) ---\n", valor_constante);
    vec_print(B, n);

    // Suma A + B
    vec_add(A, B, C, n);
    printf("\n--- Vector C = A + B ---\n");
    vec_print(C, n);

    // Resta A - B
    vec_subtract(A, B, C, n);
    printf("\n--- Vector C = A - B ---\n");
    vec_print(C, n);

    // Liberar memoria
    vec_free(A);
    vec_free(B);
    vec_free(C);

    return 0;
}
