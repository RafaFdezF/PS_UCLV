#include "vectores.h"

int main() {
    const int TAMANIO = 5;  // CAMBIADO: TAMAÑO -> TAMANIO
    
    printf("=== PROGRAMA PRINCIPAL - OPERACIONES CON VECTORES ===\n\n");
    
    // Crear vectores
    Vector *vec1 = crear_vector(TAMANIO);
    Vector *vec2 = crear_vector(TAMANIO);
    
    if (!vec1 || !vec2) {
        printf("Error al crear los vectores\n");
        return 1;
    }
    
    // Inicializar vectores según especificaciones
    printf("Inicializando vectores...\n");
    inicializar_aleatorio(vec1, 1.0, 10.0);
    inicializar_valor_constante(vec2, 2.5);
    
    // Mostrar vectores iniciales
    printf("\n--- Vectores Iniciales ---\n");
    mostrar_vector(vec1, "1 (aleatorio)");
    mostrar_vector(vec2, "2 (constante)");
    
    // Operaciones solicitadas
    printf("\n--- Operaciones ---\n");
    
    // d) Sumar vectores
    Vector *suma = sumar_vectores(vec1, vec2);
    if (suma) {
        mostrar_vector(suma, "SUMA (vec1 + vec2)");
        liberar_vector(suma);
    }
    
    // e) Restar vectores
    Vector *resta = restar_vectores(vec1, vec2);
    if (resta) {
        mostrar_vector(resta, "RESTA (vec1 - vec2)");
        liberar_vector(resta);
    }
    
    // Otras operaciones
    printf("\n--- Metricas Adicionales ---\n");
    printf("Norma del vector 1: %.4f\n", norma_vector(vec1));
    printf("Norma del vector 2: %.4f\n", norma_vector(vec2));
    printf("Media del vector 1: %.4f\n", media_vector(vec1));
    printf("Media del vector 2: %.4f\n", media_vector(vec2));
    
    // Recuperar elemento específico
    printf("\n--- Elementos Especificos ---\n");
    printf("Elemento en posicion 0 del vector 1: %.2f\n", obtener_elemento(vec1, 0));
    printf("Elemento en posicion 2 del vector 2: %.2f\n", obtener_elemento(vec2, 2));
    
    // Liberar memoria
    liberar_vector(vec1);
    liberar_vector(vec2);
    
    return 0;
}