#include "vector.h"
#include <stdlib.h>
#include <time.h>

void inicializar_aleatorio(Vector *v, int min, int max) {
    if (v == NULL || v->elementos == NULL) return;
    
    // Inicializar semilla solo una vez
    static int seed_initialized = 0;
    if (!seed_initialized) {
        srand(time(NULL));
        seed_initialized = 1;
    }
    
    for (int i = 0; i < v->tamano; i++) {
        v->elementos[i] = min + (rand() / (double)RAND_MAX) * (max - min);
    }
}

void inicializar_valor(Vector *v, double valor) {
    if (v == NULL || v->elementos == NULL) return;
    
    for (int i = 0; i < v->tamano; i++) {
        v->elementos[i] = valor;
    }
}