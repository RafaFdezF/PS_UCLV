/**
 * @file vlib.h
 * @brief Biblioteca de operaciones básicas para vectores dinámicos en C.
 *
 * Proporciona funciones para crear, inicializar, operar y mostrar vectores de forma segura.
 */

#ifndef VLIB_H
#define VLIB_H

#include <stddef.h>

/**
 * @struct Vector
 * @brief Representa un vector dinámico de números reales.
 */
typedef struct {
    double *data;   /**< Puntero a los datos del vector */
    size_t size;   /**< Número de elementos */
} Vector;

/**
 * @brief Crea un vector dinámico de tamaño n.
 * 
 * @param n Tamaño del vector a crear.
 * @return Puntero al vector creado, o NULL si falla la asignación de memoria.
 */
Vector* v_create(size_t n);

/**
 * @brief Libera la memoria asociada a un vector.
 * 
 * @param v Puntero al vector a destruir.
 */
void v_destroy(Vector *v);

/**
 * @brief Inicializa el vector con valores aleatorios en [0, 100].
 * 
 * @param v Puntero al vector.
 */
void v_fill_rand(Vector *v);

/**
 * @brief Inicializa el vector con un valor constante.
 * 
 * @param v Puntero al vector.
 * @param value Valor a asignar a todos los elementos.
 */
void v_fill(Vector *v, double value);

/**
 * @brief Devuelve el elemento i del vector.
 * 
 * @param v Puntero al vector.
 * @param i Índice del elemento (0 ≤ i < v->size).
 * @return Valor del elemento i, o NAN en caso de error.
 */
double v_get(const Vector *v, size_t i);

/**
 * @brief Calcula la norma euclidiana del vector.
 * 
 * @param v Puntero al vector.
 * @return Norma del vector, o NAN en caso de error.
 */
double v_norm(const Vector *v);

/**
 * @brief Calcula la media de los elementos del vector.
 * 
 * @param v Puntero al vector.
 * @return Media de los elementos, o NAN en caso de error.
 */
double v_mean(const Vector *v);

/**
 * @brief Suma dos vectores del mismo tamaño.
 * 
 * @param a Primer vector.
 * @param b Segundo vector.
 * @return Vector con el resultado de la suma, o NULL en caso de error.
 */
Vector* v_add(const Vector *a, const Vector *b);

/**
 * @brief Resta dos vectores del mismo tamaño.
 * 
 * @param a Primer vector.
 * @param b Segundo vector.
 * @return Vector con el resultado de la resta, o NULL en caso de error.
 */
Vector* v_sub(const Vector *a, const Vector *b);

/**
 * @brief Muestra los elementos del vector en consola.
 * 
 * @param v Puntero al vector.
 */
void v_print(const Vector *v);

#endif
