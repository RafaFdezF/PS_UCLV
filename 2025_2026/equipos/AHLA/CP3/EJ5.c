#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void manejar_sigint(int sig) {
    printf("\nProceso %d recibió la señal %d (SIGINT)\n", getpid(), sig);
}

int main(void) {
    signal(SIGINT, manejar_sigint);

    printf("Antes de enviar la señal ...\n");
    kill(getpid(), SIGINT);
    printf("Después de recibir la señal ...\n");

    return 0;
}