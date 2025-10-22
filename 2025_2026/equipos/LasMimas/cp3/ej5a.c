#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void) {
    // Ignorar SIGINT
    signal(SIGINT, SIG_IGN);

    printf("Antes de enviar la señal ...\n");
    kill(getpid(), SIGINT);
    printf("Después de recibir la señal ...\n");
    return 0;
}

