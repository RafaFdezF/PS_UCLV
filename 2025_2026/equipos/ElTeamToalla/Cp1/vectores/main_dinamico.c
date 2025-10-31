#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "vector.h"

int main() {
    // Abrir la biblioteca dinámica
    void *handle = dlopen("./libvector.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error al cargar la biblioteca: %s\n", dlerror());
        return 1;
    }
    
    // Limpiar errores previos
    dlerror();
    
    // Definir punteros a funciones
    Vector* (*crear_vector_fn)(int);
    void (*inicializar_aleatorio_fn)(Vector*, int, int);
    void (*inicializar_valor_fn)(Vector*, double);
    void (*mostrar_vector_fn)(Vector*);
    Vector* (*sumar_vectores_fn)(Vector*, Vector*);
    Vector* (*restar_vectores_fn)(Vector*, Vector*);
    double (*norma_vector_fn)(Vector*);
    double (*media_vector_fn)(Vector*);
    void (*liberar_vector_fn)(Vector*);
    
    // Cargar las funciones dinámicamente
    crear_vector_fn = (Vector* (*)(int))dlsym(handle, "crear_vector");
    inicializar_aleatorio_fn = (void (*)(Vector*, int, int))dlsym(handle, "inicializar_aleatorio");
    inicializar_valor_fn = (void (*)(Vector*, double))dlsym(handle, "inicializar_valor");
    mostrar_vector_fn = (void (*)(Vector*))dlsym(handle, "mostrar_vector");
    sumar_vectores_fn = (Vector* (*)(Vector*, Vector*))dlsym(handle, "sumar_vectores");
    restar_vectores_fn = (Vector* (*)(Vector*, Vector*))dlsym(handle, "restar_vectores");
    norma_vector_fn = (double (*)(Vector*))dlsym(handle, "norma_vector");
    media_vector_fn = (double (*)(Vector*))dlsym(handle, "media_vector");
    liberar_vector_fn = (void (*)(Vector*))dlsym(handle, "liberar_vector");
    
    // Verificar que todas las funciones se cargaron correctamente
    char *error;
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Error al cargar símbolos: %s\n", error);
        dlclose(handle);
        return 1;
    }
    
    printf("=== CARGA DINÁMICA DE BIBLIOTECA ===\n\n");
    printf("Biblioteca cargada exitosamente con dlopen\n\n");
    
    // Usar las funciones cargadas dinámicamente
    int tamano;
    printf("Ingrese el tamaño de los vectores: ");
    scanf("%d", &tamano);
    
    // Crear vectores usando las funciones cargadas
    Vector *v1 = crear_vector_fn(tamano);
    Vector *v2 = crear_vector_fn(tamano);
    
    if (v1 == NULL || v2 == NULL) {
        printf("Error al crear los vectores\n");
        dlclose(handle);
        return 1;
    }
    
    // Inicializar vectores
    printf("\nInicializando vector 1 con valores aleatorios...\n");
    inicializar_aleatorio_fn(v1, 0, 10);
    printf("Vector 1: ");
    mostrar_vector_fn(v1);
    
    double valor;
    printf("\nIngrese el valor para inicializar el vector 2: ");
    scanf("%lf", &valor);
    inicializar_valor_fn(v2, valor);
    printf("Vector 2: ");
    mostrar_vector_fn(v2);
    
    // Realizar operaciones
    printf("\n=== OPERACIONES CON CARGA DINÁMICA ===\n");
    
    Vector *suma = sumar_vectores_fn(v1, v2);
    if (suma != NULL) {
        printf("Suma (v1 + v2): ");
        mostrar_vector_fn(suma);
    }
    
    Vector *resta = restar_vectores_fn(v1, v2);
    if (resta != NULL) {
        printf("Resta (v1 - v2): ");
        mostrar_vector_fn(resta);
    }
    
    printf("\nNorma del vector 1: %.4f\n", norma_vector_fn(v1));
    printf("Media del vector 1: %.4f\n", media_vector_fn(v1));
    
    // Liberar memoria
    liberar_vector_fn(v1);
    liberar_vector_fn(v2);
    liberar_vector_fn(suma);
    liberar_vector_fn(resta);
    
    // Cerrar la biblioteca
    dlclose(handle);
    printf("\nBiblioteca cerrada exitosamente\n");
    
    return 0;
}

/*
 * Para compilar este programa con carga dinámica:
 * gcc -o programa_carga_dinamica main_dinamico.c -ldl
 * 
 * Nota: La biblioteca libvector.so debe existir en el directorio actual
 * 
 * Ventajas de la carga dinámica con dlopen:
 * 1. Permite cargar bibliotecas en tiempo de ejecución
 * 2. Posibilidad de cargar diferentes implementaciones según condiciones
 * 3. Útil para sistemas de plugins
 * 4. Permite verificar si una biblioteca existe antes de usarla
 * 5. Control total sobre cuándo cargar y descargar la biblioteca
 */