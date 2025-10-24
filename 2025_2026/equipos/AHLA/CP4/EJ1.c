#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error al crear el hijo");
        exit(1);
    }

    if (pid == 0) {
        // Proceso hijo
        printf("Hijo (%d): Empieza a trabajar...\n", getpid());
        sleep(10);
        printf("Hijo (%d): Termina normalmente.\n", getpid());
        exit(0);
    } else {
        // Proceso padre
        printf("Padre (%d): Esperando 4 segundos...\n", getpid());
        sleep(4);

        
        if (kill(pid, 0) == 0) {
            printf("Padre: El hijo sigue vivo, enviando SIGKILL...\n");
            kill(pid, SIGKILL);
        } else if (errno == ESRCH) {
            printf("Padre: El hijo ya terminó.\n");
        } else {
            perror("Error al verificar el hijo");
        }

        
        waitpid(pid, NULL, 0);
        printf("Padre: El hijo fue recogido.\n");
    }

    return 0;
}


/*¿Sería posible saber si un proceso hijo ha terminado enviándole una señal 0 mediante kill? 

Sí, pero con matices , se puede usar kill(pid, 0); y no envía una señal real, sino que:
-Si kill(pid, 0) devuelve 0 → el proceso sigue existiendo.
-Si devuelve -1:
.y errno == ESRCH → el proceso no existe (ya terminó).
.y errno == EPERM → el proceso existe, pero no tienes permiso para enviarle señales.

Aunque el hijo haya terminado, si el padre no ha hecho wait() o waitpid(), el proceso sigue en 
el sistema como un "zombie" (proceso terminado pero no recogido).En ese estado, kill(pid, 0) 
aún devuelve éxito (0), porque el PID todavía existe hasta que el padre lo recoja.

Entonces:
-kill(pid, 0) te dice si el PID existe,pero no garantiza que el proceso esté realmente 
ejecutándose (podría ser zombie).

*/