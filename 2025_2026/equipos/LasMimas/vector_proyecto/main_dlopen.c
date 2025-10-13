#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main() {
    void *handle;
    double* (*vec_create)(size_t);
    void (*vec_randomize)(double*, size_t, double, double);
    void (*vec_fill)(double*, size_t, double);
    void (*vec_add)(const double*, const double*, double*, size_t);
    void (*vec_subtract)(const double*, const double*, double*, size_t);
    void (*vec_print)(const double*, size_t);
    void (*vec_free)(double*);

    // Cargar la biblioteca compartida
    handle = dlopen("./libvector.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error al cargar la biblioteca: %s\n", dlerror());
        return 1;
    }

    // Limpiar errores previos
    dlerror();

    // Cargar los símbolos (funciones)
    vec_create = dlsym(handle, "vec_create");
    vec_randomize = dlsym(handle, "vec_randomize");
    vec_fill = dlsym(handle, "vec_fill");
    vec_add = dlsym(handle, "vec_add");
    vec_subtract = dlsym(handle, "vec_subtract");
    vec_print = dlsym(handle, "vec_print");
    vec_free = dlsym(handle, "vec_free");

    // Verificar si alguna función falló al cargarse
    char *error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Error al cargar símbolo: %s\n", error);
        dlclose(handle);
        return 1;
    }

    // Crear y operar con vectores
    size_t n;
    printf("Ingrese el tamaño de los vectores: ");
    scanf("%zu", &n);

    double *a = vec_create(n);
    double *b = vec_create(n);
    double *c = vec_create(n);

    if (!a || !b || !c) {
        printf("Error: no se pudo crear uno de los vectores.\n");
        dlclose(handle);
        return 1;
    }

    vec_randomize(a, n, 0.0, 10.0);
    vec_fill(b, n, 5.0);

    printf("\n--- Vector A (aleatorio) ---\n");
    vec_print(a, n);

    printf("\n--- Vector B (fijo = 5.00) ---\n");
    vec_print(b, n);

    vec_add(a, b, c, n);
    printf("\n--- Vector C = A + B ---\n");
    vec_print(c, n);

    vec_subtract(a, b, c, n);
        vec_subtract(a, b, c, n);
    printf("\n--- Vector C = A - B ---\n");
    vec_print(c, n);

    vec_free(a);
    vec_free(b);
    vec_free(c);

    // Cerrar la biblioteca compartida
    dlclose(handle);
    return 0;
}

