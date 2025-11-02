#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void manejador_sigint(int sig) {
    printf("\nProceso %d: Recibió señal SIGINT (%s)\n",
    getpid(), strsignal(sig));
}

int main(void) {
    struct sigaction sa;
    sigset_t mask;
    
    // Configurar el manejador de forma robusta
    sigemptyset(&mask);
    sa.sa_handler = manejador_sigint;
    sa.sa_mask = mask;
    sa.sa_flags = 0;
    
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
    
    printf("Proceso %d: Antes de enviar la señal...\n", getpid());
    kill(getpid(), SIGINT);
    printf("Proceso %d: Después de recibir la señal...\n", getpid());
    return 0;
}