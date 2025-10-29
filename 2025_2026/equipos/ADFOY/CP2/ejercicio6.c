#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

volatile int bandera = 1;

void manejar_sigusr1()
{
    bandera = 0;
}

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        signal(SIGUSR1, manejar_sigusr1);
        while (bandera)
        {
            pause();
        }
        printf("Hijo %d: Recibí SIGUSR1. Terminando.\n", getpid());
        exit(0);
    }
    else
    {
        sleep(1);
        kill(pid, SIGUSR1);
        wait(NULL);
        printf("Padre: Hijo terminado.\n");
    }

    return 0;
}