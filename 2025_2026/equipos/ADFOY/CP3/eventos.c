#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int contador = 0;

void manejar_senal(int sig)
{
    if (sig == SIGUSR1)
    {
        contador = 0;
        printf("Contador reiniciado\n");
    }
    else if (sig == SIGUSR2)
    {
        printf("Tiempo transcurrido: %d segundos\n", contador);
    }
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = manejar_senal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("PID del proceso: %d\n", getpid());

    while (1)
    {
        sleep(1);
        contador++;
    }
    return 0;
}