#include "vector.h"
#include <stdlib.h>
#include <math.h>

double obtener_elemento(Vector *v, int posicion) {
    if (v == NULL || v->elementos == NULL) return 0.0;
    if (posicion < 0 || posicion >= v->tamano) return 0.0;
    
    return v->elementos[posicion];
}

Vector* sumar_vectores(Vector *a, Vector *b) {
    if (a == NULL || b == NULL) return NULL;
    if (a->tamano != b->tamano) return NULL;
    
    Vector *c = crear_vector(a->tamano);
    if (c == NULL) return NULL;
    
    for (int i = 0; i < a->tamano; i++) {
        c->elementos[i] = a->elementos[i] + b->elementos[i];
    }
    
    return c;
}

Vector* restar_vectores(Vector *a, Vector *b) {
    if (a == NULL || b == NULL) return NULL;
    if (a->tamano != b->tamano) return NULL;
    
    Vector *c = crear_vector(a->tamano);
    if (c == NULL) return NULL;
    
    for (int i = 0; i < a->tamano; i++) {
        c->elementos[i] = a->elementos[i] - b->elementos[i];
    }
    
    return c;
}

double norma_vector(Vector *v) {
    if (v == NULL || v->elementos == NULL) return 0.0;
    
    double suma = 0.0;
    for (int i = 0; i < v->tamano; i++) {
        suma += v->elementos[i] * v->elementos[i];
    }
    
    return sqrt(suma);
}

double media_vector(Vector *v) {
    if (v == NULL || v->elementos == NULL || v->tamano == 0) return 0.0;
    
    double suma = 0.0;
    for (int i = 0; i < v->tamano; i++) {
        suma += v->elementos[i];
    }
    
    return suma / v->tamano;
}