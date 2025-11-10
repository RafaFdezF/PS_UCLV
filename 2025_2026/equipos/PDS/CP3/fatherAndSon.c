#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

volatile sig_atomic_t bandera = 0;

void manejador_sigusr1(int sig) {
    bandera = 1;
}

int main(void) {
    pid_t pid;
    struct sigaction sa;
    sigset_t mask, oldmask;
    
    // Configurar máscara para bloquear SIGUSR1 inicialmente
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    if (sigprocmask(SIG_BLOCK, &mask, &oldmask) == -1) {
        perror("sigprocmask");
        exit(1);
    }
    
    pid = fork();
    
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    
    if (pid == 0) { 
        // Proceso hijo
        printf("Hijo [PID:%d]: Iniciando...\n", getpid());
        
        // Configurar manejador para SIGUSR1
        sigemptyset(&mask);
        sa.sa_handler = manejador_sigusr1;
        sa.sa_mask = mask;
        sa.sa_flags = 0;
        
        if (sigaction(SIGUSR1, &sa, NULL) == -1) {
            perror("hijo: sigaction");
            exit(1);
        }
        
        // Desbloquear SIGUSR1 y esperar
        if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1) {
            perror("sigprocmask unblock");
            exit(1);
        }
        
        printf("Hijo [PID:%d]: Esperando señal SIGUSR1...\n", getpid());
        
        // Espera eficiente usando sigsuspend
        sigfillset(&mask);
        sigdelset(&mask, SIGUSR1);
        
        while (!bandera) {
            sigsuspend(&mask);  // Se bloquea hasta recibir SIGUSR1
        }
        
        printf("Hijo [PID:%d]: Recibió SIGUSR1 - Terminando\n", getpid());
        exit(0);
        
    } else { 
        // Proceso padre
        printf("Padre [PID:%d]: Hijo creado con PID %d\n", getpid(), pid);
        
        // Dar tiempo al hijo para configurar el manejador
        sleep(1);
        
        printf("Padre [PID:%d]: Enviando SIGUSR1 al hijo %d\n", getpid(), pid);
        
        if (kill(pid, SIGUSR1) == -1) {
            perror("padre: kill");
            exit(1);
        }
        
        // Esperar a que el hijo termine
        int status;
        pid_t child_terminated = wait(&status);
        
        if (child_terminated == -1) {
            perror("wait");
        } else {
            printf("Padre [PID:%d]: Hijo %d terminó ", getpid(), child_terminated);
            if (WIFEXITED(status)) {
                printf("con estado %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("por señal %d\n", WTERMSIG(status));
            }
        }
    }
    
    return 0;
}


/*
    Salida esperada del programa:
    Padre [PID:1234]: Hijo creado con PID 1235
    Hijo [PID:1235]: Iniciando...
    Hijo [PID:1235]: Esperando señal SIGUSR1...
    Padre [PID:1234]: Enviando SIGUSR1 al hijo 1235
    Hijo [PID:1235]: Recibió SIGUSR1 - Terminando
    Padre [PID:1234]: Hijo 1235 terminó con estado 0
*/