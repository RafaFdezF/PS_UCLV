#include "vector_ops.h"
#include <stdlib.h>  // malloc y free
#include <stdio.h>   // printf para depuración
#include <time.h>    // time, srand
#include <math.h>    // sqrt()

// Crea un vector dinámico de tamaño n
double* vec_create(size_t n) {
    if (n == 0) {
        printf("Error: tamaño del vector no puede ser 0.\n");
        return NULL;
    }

    double *v = (double*) malloc(n * sizeof(double));

    if (v == NULL) {
        printf("Error: no se pudo asignar memoria para el vector.\n");
        return NULL;
    }

    return v;
}

// Libera la memoria del vector
void vec_free(double* v) {
    free(v);
}

// Llena el vector con un valor fijo
void vec_fill(double* v, size_t n, double value) {
    if (!v) return;
    for (size_t i = 0; i < n; ++i) {
        v[i] = value;
    }
}

// Llena el vector con valores aleatorios entre min y max
void vec_randomize(double* v, size_t n, double min, double max) {
    if (!v) return;
    for (size_t i = 0; i < n; ++i) {
        double r = (double)rand() / (double)RAND_MAX;  // número entre 0 y 1
        v[i] = min + r * (max - min);
    }
}

// Recupera un elemento del vector en la posición indicada
double vec_get(const double* v, size_t n, size_t pos) {
    if (v == NULL) {
        printf("Error: el vector no existe.\n");
        return 0.0;
    }

    if (pos >= n) {
        printf("Error: posición fuera de rango (pos=%zu, tamaño=%zu).\n", pos, n);
        return 0.0;
    }

    return v[pos];
}

// Suma dos vectores: c[i] = a[i] + b[i]
void vec_add(const double* a, const double* b, double* c, size_t n) {
    if (!a || !b || !c) {
        printf("Error: uno de los vectores es nulo.\n");
        return;
    }

    for (size_t i = 0; i < n; ++i) {
        c[i] = a[i] + b[i];
    }
}

// Resta dos vectores: c[i] = a[i] - b[i]
void vec_subtract(const double* a, const double* b, double* c, size_t n) {
    if (!a || !b || !c) {
        printf("Error: uno de los vectores es nulo.\n");
        return;
    }

    for (size_t i = 0; i < n; ++i) {
        c[i] = a[i] - b[i];
    }
}

// Calcula la norma (magnitud) de un vector
double vec_norm(const double* v, size_t n) {
    if (!v) {
        printf("Error: el vector es nulo.\n");
        return -1.0;
    }

    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        sum += v[i] * v[i];
    }

    return sqrt(sum);
}

// Calcula la media (promedio) de los elementos de un vector
double vec_mean(const double* v, size_t n) {
    if (!v || n == 0) {
        printf("Error: vector nulo o tamaño inválido.\n");
        return 0.0;
    }

    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        sum += v[i];
    }

    return sum / n;
}


// Muestra el contenido de un vector en pantalla
void vec_print(const double* v, size_t n) {
    if (!v) {
        printf("Error: el vector es nulo.\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < n; ++i) {
        printf("%.2f", v[i]);
        if (i < n - 1)
            printf(", ");
    }
    printf("]\n");
}
