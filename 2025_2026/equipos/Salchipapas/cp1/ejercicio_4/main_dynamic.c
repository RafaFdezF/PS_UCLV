#include "vlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

const int N = 5;

int main() {
    void *handle;
    char *error;
    
    // Cargar la biblioteca compartida
    handle = dlopen("./libvlib.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error al cargar la biblioteca: %s\n", dlerror());
        return 1;
    }

    // Cargar los símbolos de las funciones
    Vector* (*v_create)(size_t) = dlsym(handle, "v_create");
    void (*v_destroy)(Vector*) = dlsym(handle, "v_destroy");
    void (*v_fill_rand)(Vector*) = dlsym(handle, "v_fill_rand");
    void (*v_fill)(Vector*, double) = dlsym(handle, "v_fill");
    double (*v_get)(const Vector*, size_t) = dlsym(handle, "v_get");
    Vector* (*v_add)(const Vector*, const Vector*) = dlsym(handle, "v_add");
    Vector* (*v_sub)(const Vector*, const Vector*) = dlsym(handle, "v_sub");
    double (*v_norm)(const Vector*) = dlsym(handle, "v_norm");
    double (*v_mean)(const Vector*) = dlsym(handle, "v_mean");
    void (*v_print)(const Vector*) = dlsym(handle, "v_print");

    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Error al cargar símbolos: %s\n", error);
        dlclose(handle);
        return 1;
    }

    // Usar las funciones normalmente
    Vector *v1 = v_create(N);
    Vector *v2 = v_create(N);

    if (!v1 || !v2) {
        fprintf(stderr, "Error: No se pudo crear los vectores.\n");
        dlclose(handle);
        return 1;
    }

    v_fill_rand(v1);
    v_fill(v2, 2.0);

    printf("Vector v1: "); v_print(v1);
    printf("Vector v2: "); v_print(v2);

    // Operaciones
    Vector *suma = v_add(v1, v2);
    Vector *resta = v_sub(v1, v2);

    if (suma) {
        printf("v1 + v2 = "); v_print(suma);
        printf("Norma de la suma: %.2f\n", v_norm(suma));
    }

    if (resta) {
        printf("v1 - v2 = "); v_print(resta);
        printf("Media de la resta: %.2f\n", v_mean(resta));
    }

    // Mostrar norma y media de los vectores originales
    printf("Norma de v1: %.2f\n", v_norm(v1));
    printf("Media de v1: %.2f\n", v_mean(v1));
    printf("Norma de v2: %.2f\n", v_norm(v2));
    printf("Media de v2: %.2f\n", v_mean(v2));

    // Recuperar un elemento específico
    printf("Elemento 0 de v1: %.2f\n", v_get(v1, 0));

    // Liberar memoria
    v_destroy(v1);
    v_destroy(v2);
    if (suma) v_destroy(suma);
    if (resta) v_destroy(resta);

    // Cerrar la biblioteca
    dlclose(handle);
    return 0;
}