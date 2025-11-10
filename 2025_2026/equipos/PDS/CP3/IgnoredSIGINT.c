#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void) {
    struct sigaction sa;
    sigset_t mask;
    
    sigemptyset(&mask);
    sa.sa_handler = SIG_IGN;
    sa.sa_mask = mask;
    sa.sa_flags = 0;
    
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
    
    printf("Proceso %d: Antes de enviar la señal...\n", getpid());
    kill(getpid(), SIGINT);
    printf("Proceso %d: Después de recibir la señal (SIGINT ignorada)...\n", getpid());
    return 0;
}