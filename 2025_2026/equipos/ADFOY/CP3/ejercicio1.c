#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // Proceso hijo
        printf("Hijo: PID = %d\n", getpid());
        sleep(6); // Simula trabajo largo
        printf("Hijo: Terminando\n");
        exit(0);
    }
    else
    {
        // Proceso padre
        sleep(4);

        if (waitpid(pid, NULL, WNOHANG) == 0)
        {
            printf("Padre: Hijo aún activo. Enviando SIGKILL\n");
            kill(pid, SIGKILL);
        }
        wait(NULL); // Limpia el estado del hijo
    }
    return 0;
}