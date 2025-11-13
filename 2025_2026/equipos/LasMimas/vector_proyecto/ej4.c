#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

int recibido = 0;

void trat_sigusr(int signum) {
    recibido = 1;
}

int main(int argc, char *argv[]) {
    int nhijos, mipid;
    int ret, i;
    char buf[80];
    struct sigaction trat;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <numero_de_hijos>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    trat.sa_handler = trat_sigusr;
    trat.sa_flags = 0;
    sigemptyset(&trat.sa_mask);
    sigaction(SIGUSR1, &trat, NULL);

    nhijos = atoi(argv[1]);
    mipid = getpid();

    for (i = 0; i < nhijos; i++) {
        if (i > 0) sleep(3); // Espera 3 segundos antes de crear el siguiente hijo

        printf("Creando hijo %d...\n", i + 1); // 👈 Nueva línea para ver el retardo

        ret = fork();

        if (ret > 0) { // proceso padre
            if (mipid != getpid()) {
                while (!recibido); // espera señal
            }
            kill(ret, SIGUSR1);
            waitpid(-1, NULL, 0);
            sprintf(buf, "Soy el proceso %d y acabo la ejecución\n", getpid());
            write(1, buf, strlen(buf));
            exit(0);
        }
    }

    sprintf(buf, "Soy el proceso %d y acabo la ejecución\n", getpid());
    write(1, buf, strlen(buf));

    return 0;
}
