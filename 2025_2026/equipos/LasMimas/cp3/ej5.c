#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Función que se ejecutará cuando llegue SIGINT
void manejar_senal(int sig) {
    printf("\nProceso %d: Recibí la señal SIGINT (Número %d)\n", getpid(), sig);
}

int main(void) {
    // Registrar el manejador de señales
    signal(SIGINT, manejar_senal);

    printf("Antes de enviar la señal ...\n");
    kill(getpid(), SIGINT);
    printf("Después de recibir la señal ...\n");
    return 0;
}
