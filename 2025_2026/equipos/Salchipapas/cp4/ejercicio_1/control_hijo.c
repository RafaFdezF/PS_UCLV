#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

int main(void) {
    pid_t pid;
    int status;

    pid = fork();
    
    if (pid == 0) {
        printf("Proceso hijo [PID: %d] iniciado\n", getpid());
        
        // Simular trabajo que puede tomar más de 4 segundos
        printf("Hijo: Realizando tarea larga...\n");
        sleep(6); 
        
        printf("Hijo: Tarea completada\n");
        exit(0);
    }
    else if (pid > 0) {
        printf("Proceso padre [PID: %d] creado, hijo PID: %d\n", getpid(), pid);
        
        // Esperar 4 segundos
        printf("Padre: Esperando 4 segundos...\n");
        sleep(4);
        
        // Verificar si el hijo ha terminado usando waitpid con WNOHANG
        if (waitpid(pid, &status, WNOHANG) == 0) {
            // Hijo aún está ejecutándose
            printf("Padre: Hijo aún en ejecución después de 4 segundos. Enviando SIGTERM...\n");
            
            if (kill(pid, SIGTERM) == 0) {
                printf("Padre: Señal SIGTERM enviada correctamente\n");
                
                // Esperar a que el hijo termine
                waitpid(pid, &status, 0);
                if (WIFSIGNALED(status)) {
                    printf("Padre: Hijo terminado por señal %d\n", WTERMSIG(status));
                }
            } else {
                perror("Padre: Error al enviar señal");
            }
        } else {
            // Hijo ya terminó
            if (WIFEXITED(status)) {
                printf("Padre: Hijo terminó normalmente con código %d\n", WEXITSTATUS(status));
            }
        }
    }
    else {
        perror("Error en fork");
        exit(1);
    }
    
    return 0;
}