/* eventos_wsl.c */
//Tuve que modificar el programa porque no cuando utilizo los comandos kill -USR1 <PID> o kill -USR2 <PID> no pasa nada al parecer es por el WSL
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <termios.h>

volatile sig_atomic_t contador = 0;
volatile sig_atomic_t seguir = 1;

/* Handler de SIGALRM: incrementa el contador */
void manejador(int signo) {
    if (signo == SIGALRM) {
        contador++;
    }
}

/* Configuración de terminal para leer un carácter sin esperar Enter */
void modo_no_canonical(struct termios *oldt) {
    struct termios newt;
    tcgetattr(STDIN_FILENO, oldt);   // guardar estado original
    newt = *oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // desactivar buffer y eco
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void restaurar_terminal(struct termios *oldt) {
    tcsetattr(STDIN_FILENO, TCSANOW, oldt);
}

int main(void) {
    struct sigaction sa;
    struct itimerval timer;
    struct termios oldt;

    /* Configurar SIGALRM */
    sa.sa_handler = manejador;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    /* Temporizador: SIGALRM cada 1 segundo */
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(1);
    }

    /* Mensaje inicial */
    printf("Contador iniciado. Presiona:\n");
    printf(" r -> reiniciar contador\n");
    printf(" s -> mostrar contador\n");
    printf(" q -> salir\n");

    /* Terminal en modo no canonical */
    modo_no_canonical(&oldt);

    /* Bucle principal */
    while (seguir) {
        char c = getchar(); // leer un carácter
        if (c == 'r') {
            contador = 0;
            printf("Contador reiniciado.\n");
        } else if (c == 's') {
            printf("Contador actual = %d\n", contador);
        } else if (c == 'q') {
            seguir = 0;
            printf("Saliendo...\n");
        }
    }

    /* Restaurar terminal */
    restaurar_terminal(&oldt);
    return 0;
}
