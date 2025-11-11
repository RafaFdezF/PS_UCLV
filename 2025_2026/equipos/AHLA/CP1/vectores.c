#include "vectores.h"

// a) Creación del vector
Vector* crear_vector(int tamano) {  // CAMBIADO
    if (tamano <= 0) {  // CAMBIADO
        printf("Error: Tamano debe ser mayor que 0\n");  // CAMBIADO
        return NULL;
    }
    
    Vector *vec = (Vector*)malloc(sizeof(Vector));
    if (!vec) {
        printf("Error: No se pudo asignar memoria para el vector\n");
        return NULL;
    }
    
    vec->tamano = tamano;  // CAMBIADO
    vec->datos = (double*)malloc(tamano * sizeof(double));  // CAMBIADO
    
    if (!vec->datos) {
        printf("Error: No se pudo asignar memoria para los datos\n");
        free(vec);
        return NULL;
    }
    
    return vec;
}

// b) Inicializar con valores aleatorios
void inicializar_aleatorio(Vector *vec, double min, double max) {
    if (!vec || !vec->datos) return;
    
    srand(time(NULL));
    
    for (int i = 0; i < vec->tamano; i++) {  // CAMBIADO
        vec->datos[i] = min + ((double)rand() / RAND_MAX) * (max - min);
    }
}

// b) Inicializar con valor constante
void inicializar_valor_constante(Vector *vec, double valor) {
    if (!vec || !vec->datos) return;
    
    for (int i = 0; i < vec->tamano; i++) {  // CAMBIADO
        vec->datos[i] = valor;
    }
}

// c) Recuperar elemento por posición
double obtener_elemento(Vector *vec, int posicion) {
    if (!vec || !vec->datos || posicion < 0 || posicion >= vec->tamano) {  // CAMBIADO
        printf("Error: Posicion invalida\n");
        return 0.0;
    }
    return vec->datos[posicion];
}

// d) Sumar dos vectores
Vector* sumar_vectores(Vector *vec1, Vector *vec2) {
    if (!vec1 || !vec2 || vec1->tamano != vec2->tamano) {  // CAMBIADO
        printf("Error: Vectores deben tener el mismo tamano\n");  // CAMBIADO
        return NULL;
    }
    
    Vector *resultado = crear_vector(vec1->tamano);  // CAMBIADO
    if (!resultado) return NULL;
    
    for (int i = 0; i < vec1->tamano; i++) {  // CAMBIADO
        resultado->datos[i] = vec1->datos[i] + vec2->datos[i];
    }
    
    return resultado;
}

// e) Restar dos vectores
Vector* restar_vectores(Vector *vec1, Vector *vec2) {
    if (!vec1 || !vec2 || vec1->tamano != vec2->tamano) {  // CAMBIADO
        printf("Error: Vectores deben tener el mismo tamano\n");  // CAMBIADO
        return NULL;
    }
    
    Vector *resultado = crear_vector(vec1->tamano);  // CAMBIADO
    if (!resultado) return NULL;
    
    for (int i = 0; i < vec1->tamano; i++) {  // CAMBIADO
        resultado->datos[i] = vec1->datos[i] - vec2->datos[i];
    }
    
    return resultado;
}

// f) Norma del vector
double norma_vector(Vector *vec) {
    if (!vec || !vec->datos) return 0.0;
    
    double suma_cuadrados = 0.0;
    for (int i = 0; i < vec->tamano; i++) {  // CAMBIADO
        suma_cuadrados += vec->datos[i] * vec->datos[i];
    }
    
    return sqrt(suma_cuadrados);
}

// g) Media de los elementos
double media_vector(Vector *vec) {
    if (!vec || !vec->datos || vec->tamano == 0) return 0.0;  // CAMBIADO
    
    double suma = 0.0;
    for (int i = 0; i < vec->tamano; i++) {  // CAMBIADO
        suma += vec->datos[i];
    }
    
    return suma / vec->tamano;  // CAMBIADO
}

// h) Mostrar vector
void mostrar_vector(Vector *vec, const char *nombre) {
    if (!vec || !vec->datos) {
        printf("Vector %s: No valido\n", nombre);
        return;
    }
    
    printf("Vector %s [tamano=%d]: ", nombre, vec->tamano);  // CAMBIADO
    for (int i = 0; i < vec->tamano; i++) {  // CAMBIADO
        printf("%.2f ", vec->datos[i]);
    }
    printf("\n");
}

// Liberar memoria del vector
void liberar_vector(Vector *vec) {
    if (vec) {
        if (vec->datos) {
            free(vec->datos);
        }
        free(vec);
    }
}