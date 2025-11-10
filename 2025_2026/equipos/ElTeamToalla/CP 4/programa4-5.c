/* alarm_usr_program.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/time.h>

volatile sig_atomic_t recibido = 0;
volatile sig_atomic_t segundos = 0;

/* Handler para SIGALRM y SIGUSR1 */
void funcion_alarma(int sig) {
    if(sig == SIGALRM) {
        segundos++;
        char buf[64];
        int len = sprintf(buf, "Segundos transcurridos: %d\n", segundos);
        write(1, buf, len);
    } else if(sig == SIGUSR1) {
        write(1, "Señal SIGUSR1 recibida\n", 24);
        recibido = 1; // bandera para que el padre continúe
    }
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Uso: %s <numero_de_hijos>\n", argv[0]);
        return 1;
    }

    int nhijos = atoi(argv[1]);
    pid_t mipid = getpid();
    pid_t ret;
    int i;
    char buf[80];

    /* Configurar handler para SIGALRM y SIGUSR1 */
    struct sigaction sa;
    sa.sa_handler = funcion_alarma;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    /* Configurar temporizador: SIGALRM cada 1 segundo */
    struct itimerval timer;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    if(setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(1);
    }

    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGALRM);
    sigprocmask(SIG_BLOCK, &mask, &oldmask); // bloquear hasta usar sigsuspend

    for(i = 0; i < nhijos; i++) {
        ret = fork();
        if(ret < 0) {
            perror("fork");
            exit(1);
        }

        if(ret > 0) { // Padre
            if(mipid != getpid()) {
                while(!recibido); // esperar señal SIGUSR1 del hijo
            }
            kill(ret, SIGUSR1);   // enviar señal al hijo
            waitpid(ret, NULL, 0);
            sprintf(buf, "Soy el proceso %d y acabo la ejecución\n", getpid());
            write(1, buf, strlen(buf));

            sleep(3); // <-- esperar 3 segundos antes de crear el siguiente hijo
        } else { // Hijo
            sprintf(buf, "Soy el hijo %d\n", getpid());
            write(1, buf, strlen(buf));
            // El hijo puede esperar una señal antes de terminar
            recibido = 0;
            sigsuspend(&oldmask);
            exit(0);
        }
    }

    // Mensaje final del proceso padre
    sprintf(buf, "Soy el proceso padre %d y terminé todos los hijos\n", getpid());
    write(1, buf, strlen(buf));

    return 0;
}
