#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

int recibido = 0;

void trat_sigusr(int signum) {
    recibido = 1;
}

int main(int argc, char *argv[]) {
    int nhijos, mipid;
    int ret, i;
    char buff[80];
    struct sigaction trat;
    
    if (argc != 2) {
        printf("Uso: %s <numero_hijos>\n", argv[0]);
        exit(1);
    }

    trat.sa_handler = trat_sigusr;
    trat.sa_flags = 0;
    sigemptyset(&trat.sa_mask);
    sigaction(SIGUSR1, &trat, NULL);

    nhijos = atoi(argv[1]);
    mipid = getpid();
    
    for (i = 0; i < nhijos; i++) {
        // Esperar 3 segundos antes de crear el siguiente proceso hijo
        sleep(3);
        
        ret = fork();
        if (ret > 0) {
            // Código del padre
            if (mipid != getpid()) {
                while(!recibido);
            }
            kill(ret, SIGUSR1);
            waitpid(-1, NULL, 0);
            sprintf(buff, "Soy el proceso %d y acabo la ejecución\n", getpid());
            write(1, buff, strlen(buff));
            exit(0);
        } else {
            // Código del hijo
            sprintf(buff, "Soy el proceso %d y acabo la ejecución\n", getpid());
            write(1, buff, strlen(buff));
        }
    }
    
    return 0;
}