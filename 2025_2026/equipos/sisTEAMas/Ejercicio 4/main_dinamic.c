#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "vector.h"

int main() {
    void *handle;
    Vector* (*create_vector)(size_t);
    void (*init_vector_random)(Vector*);
    void (*init_vector_value)(Vector*, double);
    Vector* (*add_vectors)(const Vector*, const Vector*);
    Vector* (*subtract_vectors)(const Vector*, const Vector*);
    void (*print_vector)(const Vector*);
    void (*free_vector)(Vector*);

    // 1️⃣ Carga dinámica de la biblioteca
    handle = dlopen("./libvector.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error al cargar la biblioteca: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    // 2️⃣ Obtención de las direcciones de las funciones
    create_vector = dlsym(handle, "create_vector");
    init_vector_random = dlsym(handle, "init_vector_random");
    init_vector_value = dlsym(handle, "init_vector_value");
    add_vectors = dlsym(handle, "add_vectors");
    subtract_vectors = dlsym(handle, "subtract_vectors");
    print_vector = dlsym(handle, "print_vector");
    free_vector = dlsym(handle, "free_vector");

    // Verifica errores
    char *error;
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "Error al cargar símbolo: %s\n", error);
        exit(EXIT_FAILURE);
    }

    // 3️⃣ Uso de las funciones cargadas
    int size = 5;
    Vector *v1 = create_vector(size);
    Vector *v2 = create_vector(size);

    init_vector_random(v1);
    init_vector_value(v2, 3.0);

    printf("Vector 1 (aleatorio):\n");
    print_vector(v1);
    printf("\nVector 2 (valor fijo):\n");
    print_vector(v2);

    Vector *sum = add_vectors(v1, v2);
    Vector *diff = subtract_vectors(v1, v2);

    printf("\nSuma de vectores:\n");
    print_vector(sum);
    printf("\nResta de vectores:\n");
    print_vector(diff);

    // 4️⃣ Liberar memoria y cerrar biblioteca
    free_vector(v1);
    free_vector(v2);
    free_vector(sum);
    free_vector(diff);

    dlclose(handle);

    return 0;
}
