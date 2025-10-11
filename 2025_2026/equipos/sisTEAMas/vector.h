#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h> 

typedef struct {
    double *data;
    size_t size;
} Vector;

Vector* create_vector(size_t size);
void init_vector_random(Vector *vec);
void init_vector_value(Vector *vec, double value);
double get_element(const Vector *vec, size_t index);
Vector* add_vectors(const Vector *a, const Vector *b);
Vector* subtract_vectors(const Vector *a, const Vector *b);
double norm_vector(const Vector *vec);
double mean_vector(const Vector *vec);
void print_vector(const Vector *vec);
void free_vector(Vector *vec);

#endif 