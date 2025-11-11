#ifndef VECTORES_H
#define VECTORES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Estructura para representar un vector
typedef struct {
    double *datos;
    int tamano;  // CAMBIADO: tamaño -> tamano
} Vector;

// Prototipos de funciones
Vector* crear_vector(int tamano);  // CAMBIADO
void inicializar_aleatorio(Vector *vec, double min, double max);
void inicializar_valor_constante(Vector *vec, double valor);
double obtener_elemento(Vector *vec, int posicion);
Vector* sumar_vectores(Vector *vec1, Vector *vec2);
Vector* restar_vectores(Vector *vec1, Vector *vec2);
double norma_vector(Vector *vec);
double media_vector(Vector *vec);
void mostrar_vector(Vector *vec, const char *nombre);
void liberar_vector(Vector *vec);

#endif