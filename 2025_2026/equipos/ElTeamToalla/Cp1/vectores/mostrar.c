#include "vector.h"
#include <stdio.h>

void mostrar_vector(Vector *v) {
    if (v == NULL || v->elementos == NULL) {
        printf("Vector nulo o sin elementos\n");
        return;
    }
    
    printf("[ ");
    for (int i = 0; i < v->tamano; i++) {
        printf("%.2f ", v->elementos[i]);
    }
    printf("]\n");
}