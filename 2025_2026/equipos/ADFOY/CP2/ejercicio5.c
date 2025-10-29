#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void manejar_sigint()
{
    printf("Proceso %d: Recibí la señal SIGINT\n", getpid());
}

int main(void)
{
    signal(SIGINT, manejar_sigint);
    printf("Antes de enviar la señal ...\n");
    kill(getpid(), SIGINT);
    printf("Después de recibir la señal ...\n");
    return 0;
}