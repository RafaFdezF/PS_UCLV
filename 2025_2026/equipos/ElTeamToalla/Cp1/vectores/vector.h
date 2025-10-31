#ifndef VECTOR_H
#define VECTOR_H

// Estructura para representar un vector
typedef struct {
    double *elementos;
    int tamano;
} Vector;

// a) Creación del vector
Vector* crear_vector(int tamano);

// b) Inicialización del vector
void inicializar_aleatorio(Vector *v, int min, int max);
void inicializar_valor(Vector *v, double valor);

// c) Recuperar elemento
double obtener_elemento(Vector *v, int posicion);

// d) Suma de vectores
Vector* sumar_vectores(Vector *a, Vector *b);

// e) Resta de vectores
Vector* restar_vectores(Vector *a, Vector *b);

// f) Norma del vector
double norma_vector(Vector *v);

// g) Media del vector
double media_vector(Vector *v);

// h) Mostrar vector
void mostrar_vector(Vector *v);

// Función auxiliar para liberar memoria
void liberar_vector(Vector *v);

#endif