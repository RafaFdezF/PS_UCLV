#ifndef VECTOR_OPS_H
#define VECTOR_OPS_H

#include <stddef.h>  // Para size_t

// Crea un vector dinámico de tamaño n
double* vec_create(size_t n);

// Libera la memoria de un vector
void vec_free(double* v);

// Llena el vector con un valor fijo
void vec_fill(double* v, size_t n, double value);

// Llena el vector con valores aleatorios entre min y max
void vec_randomize(double* v, size_t n, double min, double max);

// Recupera un elemento del vector
double vec_get(const double* v, size_t n, size_t pos);

// Suma dos vectores: c[i] = a[i] + b[i]
void vec_add(const double* a, const double* b, double* c, size_t n);

// Resta dos vectores: c[i] = a[i] - b[i]
void vec_subtract(const double* a, const double* b, double* c, size_t n);

// Calcula la norma (magnitud) de un vector
double vec_norm(const double* v, size_t n);

// Calcula la media (promedio) de los elementos de un vector
double vec_mean(const double* v, size_t n);

// Muestra el contenido de un vector
void vec_print(const double* v, size_t n);

#endif
