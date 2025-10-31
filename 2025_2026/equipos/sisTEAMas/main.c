#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vector.h"

int main()
{

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

    free_vector(v1);
    free_vector(v2);
    free_vector(sum);
    free_vector(diff);
    return 0;
}