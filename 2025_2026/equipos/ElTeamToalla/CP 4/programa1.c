/* kill_after_timeout.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* Proceso hijo: simulamos trabajo largo */
        printf("Hijo (%d): iniciando trabajo (5s)...\n", getpid());
        sleep(5); /* hijo tarda 5s */
        printf("Hijo (%d): terminado normalmente.\n", getpid());
        exit(EXIT_SUCCESS);
    } else {
        /* Proceso padre */
        int elapsed = 0;
        int status;
        pid_t r;

        /* Esperamos hasta 4 segundos comprobando periódicamente si ya terminó */
        while (elapsed < 4) {
            r = waitpid(pid, &status, WNOHANG);
            if (r == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            } else if (r == 0) {
                /* hijo aún no terminó */
                sleep(1);
                elapsed++;
            } else {
                /* r == pid -> hijo terminó */
                if (WIFEXITED(status))
                    printf("Padre: hijo terminó con código %d\n", WEXITSTATUS(status));
                else if (WIFSIGNALED(status))
                    printf("Padre: hijo terminó por señal %d\n", WTERMSIG(status));
                return 0;
            }
        }

        /* Si llegamos aquí, han pasado 4s y el hijo sigue vivo -> matarlo */
        printf("Padre: hijo sigue vivo después de 4s, enviando SIGKILL...\n");
        if (kill(pid, SIGKILL) == -1) {
            perror("kill");
        }

        /* Esperamos a que el hijo sea recolectado */
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        printf("Padre: hijo eliminado.\n");
    }

    return 0;
}
