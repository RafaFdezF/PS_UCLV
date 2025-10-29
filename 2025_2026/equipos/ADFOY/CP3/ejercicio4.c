#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

int recibido = 0;

void trat_sigusr1(int signum)
{
    recibido = 1;
}

int main(int argc, char *argv[])
{
    int nhijos, mipid;
    int ret, i;
    char buf[80];
    struct sigaction trat;

    trat.sa_handler = trat_sigusr1;
    trat.sa_flags = 0;
    sigemptyset(&trat.sa_mask);
    sigaction(SIGUSR1, &trat, NULL);
    nhijos = atoi(argv[1]);
    mipid = getpid();

    for (i = 0; i < nhijos; i++)
    {
        ret = fork();
        if (ret > 0)
        {
            // Proceso padre
            sleep(3); // Espera 3 segundos antes de crear el siguiente proceso
            if (mipid != getpid())
            {
                while (!recibido)
                    ;
            }
            kill(ret, SIGUSR1);
            waitpid(-1, NULL, 0);
            sprintf(buf, "Soy el proceso hijo %d y acabo la ejecución\n", getpid());
            write(1, buf, strlen(buf));
            exit(0);
        }
    }

    sprintf(buf, "Soy el proceso padre %d y acabo la ejecución\n", getpid());
    write(1, buf, strlen(buf));
    return 0;
}