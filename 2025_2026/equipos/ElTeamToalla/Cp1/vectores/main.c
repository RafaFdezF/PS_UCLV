#include "vector.h"
#include <stdio.h>

int main() {
    int tamano;
    
    printf("=== BIBLIOTECA DE OPERACIONES CON VECTORES ===\n\n");
    printf("Ingrese el tamaño de los vectores: ");
    scanf("%d", &tamano);
    
    // Crear dos vectores
    Vector *v1 = crear_vector(tamano);
    Vector *v2 = crear_vector(tamano);
    
    if (v1 == NULL || v2 == NULL) {
        printf("Error al crear los vectores\n");
        return 1;
    }
    
    // Inicializar el primer vector con valores aleatorios entre 0 y 10
    printf("\nInicializando vector 1 con valores aleatorios...\n");
    inicializar_aleatorio(v1, 0, 10);
    printf("Vector 1: ");
    mostrar_vector(v1);
    
    // Inicializar el segundo vector con un mismo valor
    double valor;
    printf("\nIngrese el valor para inicializar el vector 2: ");
    scanf("%lf", &valor);
    inicializar_valor(v2, valor);
    printf("Vector 2: ");
    mostrar_vector(v2);
    
    // Operaciones
    printf("\n=== OPERACIONES ===\n");
    
    // Suma de vectores (inciso d)
    Vector *suma = sumar_vectores(v1, v2);
    if (suma != NULL) {
        printf("Suma (v1 + v2): ");
        mostrar_vector(suma);
    }
    
    // Resta de vectores (inciso e)
    Vector *resta = restar_vectores(v1, v2);
    if (resta != NULL) {
        printf("Resta (v1 - v2): ");
        mostrar_vector(resta);
    }
    
    // Otras operaciones de demostración
    printf("\n=== OTRAS OPERACIONES ===\n");
    printf("Norma del vector 1: %.4f\n", norma_vector(v1));
    printf("Norma del vector 2: %.4f\n", norma_vector(v2));
    printf("Media del vector 1: %.4f\n", media_vector(v1));
    printf("Media del vector 2: %.4f\n", media_vector(v2));
    
    // Ejemplo de acceso a elemento
    if (tamano > 0) {
        printf("\nPrimer elemento del vector 1: %.2f\n", obtener_elemento(v1, 0));
        printf("Último elemento del vector 2: %.2f\n", obtener_elemento(v2, tamano-1));
    }
    
    // Liberar memoria
    liberar_vector(v1);
    liberar_vector(v2);
    liberar_vector(suma);
    liberar_vector(resta);
    
    return 0;
}