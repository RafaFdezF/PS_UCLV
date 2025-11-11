#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "vectores.h"

int main() {
    void *handle;
    char *error;

    printf("=== CARGA DINÁMICA DE BIBLIOTECA ===\n\n");

    //Cargar la biblioteca compartida (.so)
    handle = dlopen("./libvectores.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error al cargar la biblioteca: %s\n", dlerror());
        return 1;
    }

    // Declarar punteros a las funciones de la biblioteca
    Vector* (*crear_vector)(int);
    void (*inicializar_aleatorio)(Vector*, double, double);
    void (*inicializar_valor_constante)(Vector*, double);
    Vector* (*sumar_vectores)(Vector*, Vector*);
    Vector* (*restar_vectores)(Vector*, Vector*);
    double (*norma_vector)(Vector*);
    double (*media_vector)(Vector*);
    void (*mostrar_vector)(Vector*, const char*);
    void (*liberar_vector)(Vector*);

    //Obtener las direcciones de las funciones
    crear_vector = dlsym(handle, "crear_vector");
    inicializar_aleatorio = dlsym(handle, "inicializar_aleatorio");
    inicializar_valor_constante = dlsym(handle, "inicializar_valor_constante");
    sumar_vectores = dlsym(handle, "sumar_vectores");
    restar_vectores = dlsym(handle, "restar_vectores");
    norma_vector = dlsym(handle, "norma_vector");
    media_vector = dlsym(handle, "media_vector");
    mostrar_vector = dlsym(handle, "mostrar_vector");
    liberar_vector = dlsym(handle, "liberar_vector");

    // Verificar si hubo error con dlsym
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Error al cargar símbolos: %s\n", error);
        dlclose(handle);
        return 1;
    }

    //  Usar las funciones de la biblioteca
    int tamano = 5;
    Vector *v1 = crear_vector(tamano);
    Vector *v2 = crear_vector(tamano);

    if (!v1 || !v2) {
        printf("Error creando vectores.\n");
        dlclose(handle);
        return 1;
    }

    inicializar_aleatorio(v1, 1.0, 10.0);
    inicializar_valor_constante(v2, 2.0);

    printf("Vector 1:\n");
    mostrar_vector(v1, "v1");

    printf("Vector 2:\n");
    mostrar_vector(v2, "v2");

    Vector *suma = sumar_vectores(v1, v2);
    Vector *resta = restar_vectores(v1, v2);

    printf("\nResultado de la suma:\n");
    mostrar_vector(suma, "v1 + v2");

    printf("Resultado de la resta:\n");
    mostrar_vector(resta, "v1 - v2");

    printf("\nNorma de v1: %.3f\n", norma_vector(v1));
    printf("Media de v1: %.3f\n", media_vector(v1));

    //  Liberar memoria
    liberar_vector(v1);
    liberar_vector(v2);
    liberar_vector(suma);
    liberar_vector(resta);

    //  Cerrar biblioteca
    dlclose(handle);

    printf("\n=== CARGA DINÁMICA FINALIZADA ===\n");
    return 0;
}