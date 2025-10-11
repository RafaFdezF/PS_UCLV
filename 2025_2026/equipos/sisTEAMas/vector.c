#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "vector.h"


Vector* create_vector(size_t size) {
    Vector *vec = (Vector*)malloc(sizeof(Vector));
    vec->size = size;
    vec->data = (double*)malloc(size * sizeof(double));
    return vec;
}

void init_vector_random(Vector *vec) {
    srand(time(NULL));
    for (size_t i = 0; i < vec->size; i++) {
        vec->data[i] = rand()%100 ;
    }
}

void init_vector_value( Vector *vec, double value) {
    for (size_t i = 0; i < vec->size; i++) {
        vec->data[i] = value;
    }
}

double get_element(const Vector *vec, size_t index) {
    if (index >= vec->size) return 0;
    return vec->data[index];
}

Vector* add_vectors(const Vector *a, const Vector *b) {
    if (a->size != b->size) return NULL;
    Vector *result = create_vector(a->size);
    for (size_t i = 0; i < a->size; i++) {
        result->data[i] = a->data[i] + b->data[i];
    }
    return result;
}

Vector* subtract_vectors(const Vector *a, const Vector *b) {
    if (a->size != b->size) return NULL;
    Vector *result = create_vector(a->size);
    for (size_t i = 0; i < a->size; i++) {
        result->data[i] = a->data[i] - b->data[i];
    }
    return result;
}

double norm_vector(const Vector *vec) {
    double sum = 0;
    for (size_t i = 0; i < vec->size; i++) {
        sum += vec->data[i] * vec->data[i];
    }
    return sqrt(sum);
}

double mean_vector(const Vector *vec) {
    double sum = 0;
    for (size_t i = 0; i < vec->size; i++) {
        sum += vec->data[i];
    }
    return sum / vec->size;
}

void print_vector(const Vector *vec) {
    printf("[");
    for (size_t i = 0; i < vec->size; i++) {
        printf("%.2f", vec->data[i]);
        if (i < vec->size - 1) printf(", ");
    }
    printf("]\n");
}
void free_vector(Vector *vec) {
        free(vec->data);
        free(vec);
}

