// Esta es la primera modificacion del programa
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) {
    printf("\nProceso %d recibió la señal %d\n", getpid(), sig);
}

int main(void) {
    signal(SIGINT, handler);
    printf("Antes de enviar la señal ...\n");
    kill(getpid(), SIGINT);
    printf("Después de recibir la señal ...\n");
    return 0;
}
