#include "vector.h"
#include <stdlib.h>

Vector* crear_vector(int tamano) {
    Vector *v = (Vector*)malloc(sizeof(Vector));
    if (v == NULL) return NULL;
    
    v->elementos = (double*)malloc(tamano * sizeof(double));
    if (v->elementos == NULL) {
        free(v);
        return NULL;
    }
    
    v->tamano = tamano;
    return v;
}

void liberar_vector(Vector *v) {
    if (v != NULL) {
        if (v->elementos != NULL) {
            free(v->elementos);
        }
        free(v);
    }
}