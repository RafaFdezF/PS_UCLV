#include "vlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

Vector* v_create(size_t n) {
    if (n <= 0) {
        fprintf(stderr, "Error: El tamaño debe ser un entero positivo.\n");
        return NULL;
    }

    Vector *v = malloc(sizeof(Vector));
    if (!v) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el vector.\n");
        return NULL;
    }

    v->data = malloc(n * sizeof(double));
    if (!v->data) {
        fprintf(stderr, "Error: No se pudo asignar memoria para los datos del vector.\n");
        free(v);
        return NULL;
    }

    v->size = n;
    return v;
}

void v_destroy(Vector *v) {
    if (!v) return;
    free(v->data);
    free(v);
}

void v_fill_rand(Vector *v) {
    if (!v || !v->data) return;

    srand((unsigned)time(NULL));
    
    for (size_t i = 0; i < v->size; i++) {
        v->data[i] = (double)rand() / RAND_MAX * 100.0; // Valoans entre 0 y 100
    }
}

void v_fill(Vector *v, double value) {
    if (!v || !v->data) return;

    for (size_t i = 0; i < v->size; i++) {
        v->data[i] = value;
    }
}

double v_get(const Vector *v, size_t i) {
    if (!v || !v->data) {
        fprintf(stderr, "Error: Vector no inicializado.\n");
        return NAN;
    }
    
    if (i >= v->size) {
        fprintf(stderr, "Error: Índice fuera de rango.\n");
        return NAN;
    }

    return v->data[i];
}

double v_norm(const Vector *v) {
    if (!v || !v->data) {
        fprintf(stderr, "Error: Vector no inicializado.\n");
        return NAN;
    }
    
    double sum_squares = 0.0;
    for (size_t i = 0; i < v->size; i++) {
        sum_squares += v->data[i] * v->data[i];
    }
    return sqrt(sum_squares);
}


double v_mean(const Vector *v) {
    if (!v || !v->data || v->size == 0) {
        fprintf(stderr, "Error: Vector no inicializado.\n");
        return NAN;
    }
    
    double sum = 0.0;
    for (size_t i = 0; i < v->size; i++) {
        sum += v->data[i];
    }
    return sum / v->size;
}

Vector* v_add(const Vector *a, const Vector *b) {
    if (!a || !b || !a->data || !b->data || a->size != b->size) {
        fprintf(stderr, "Error: Vectores inválidos o de diferente tamaño.\n");
        return NULL;
    }

    Vector *ans = v_create(a->size);
    
    if (!ans) return NULL;

    for (size_t i = 0; i < a->size; i++) {
        ans->data[i] = a->data[i] + b->data[i];
    }

    return ans;
}

Vector* v_sub(const Vector *a, const Vector *b) {
    if (!a || !b || !a->data || !b->data || a->size != b->size) {
        fprintf(stderr, "Error: Vectores inválidos o de diferente tamaño.\n");
        return NULL;
    }

    Vector *ans = v_create(a->size);
    
    if (!ans) return NULL;

    for (size_t i = 0; i < a->size; i++) {
        ans->data[i] = a->data[i] - b->data[i];
    }

    return ans;
}

void v_print(const Vector *v) {
    if (!v || !v->data) {
        fprintf(stderr, "Vector no inicializado.\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < v->size; i++) {
        printf("%.2lf", v->data[i]);
        if (i < v->size - 1) printf(", ");
    }
    printf("]\n");
}
