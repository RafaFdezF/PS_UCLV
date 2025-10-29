#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
    printf("Antes de enviar la señal ...");
    kill(getpid(), SIGINT);
    printf("Después de recibir la señal ...");
    return 0;
}