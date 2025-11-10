//Esta es la segunda modificación
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void) {
    signal(SIGINT, SIG_IGN);  // Ignorar SIGINT
    printf("Antes de enviar la señal ...\n");
    kill(getpid(), SIGINT);
    printf("Después de enviar la señal ...\n");  // Se ejecuta sin interrupción
    return 0;
}