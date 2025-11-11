#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("Error en fork");
        exit(1);
    }
    if (pid == 0) {
        // Hijo: tarea larga
        printf("Hijo (PID: %d) trabajando...\n", getpid());
        
        // Instalar manejador para SIGTERM para limpieza ordenada
        signal(SIGTERM, SIG_DFL);
        
        for (int i = 0; i < 10; i++) {
            printf("Hijo: iteración %d\n", i);
            sleep(1);
        }
        printf("Hijo: completado normalmente\n");
        exit(0);
    } else {
        // Padre
        printf("Padre: creado hijo con PID %d\n", pid);
        // Esperar 4 segundos
        sleep(4);
        // Verificar si el hijo terminó
        if (waitpid(pid, &status, WNOHANG) == 0) {
            printf("Padre: enviando SIGTERM al hijo...\n");
            kill(pid, SIGTERM);
            
            // Esperar a que termine
            waitpid(pid, &status, 0);
            
            if (WIFSIGNALED(status)) {
                printf("Padre: hijo terminado por señal %d\n", WTERMSIG(status));
            }
        } else {
            printf("Padre: hijo ya terminó\n");
        }
    }
    return 0;
}