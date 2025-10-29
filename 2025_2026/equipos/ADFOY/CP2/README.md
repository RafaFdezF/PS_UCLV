# Respuestas Teóricas - Manejo de Señales

## 1. ¿Qué es una señal?
Una señal es una notificación asíncrona enviada a un proceso para informarle sobre un evento ocurrido en el sistema o en el propio proceso.

### a. Acciones para el tratamiento de señales
- **Ignorar la señal** (excepto SIGKILL y SIGSTOP).
- **Capturar la señal** y ejecutar un manejador personalizado.
- **Ejecutar la acción por defecto** (terminar, detener, continuar, etc.).

### b. ¿Todas las señales pueden ser ignoradas?
No, señales como **SIGKILL** y **SIGSTOP** no pueden ser ignoradas, capturadas o bloqueadas por razones de seguridad del sistema.

## 2. Formas de enviar señales a un proceso
- **Desde la terminal**: Comandos `kill`, `killall`, `pkill`.
- **Desde el teclado**: Combinaciones como `Ctrl+C` (SIGINT), `Ctrl+Z` (SIGTSTP).
- **Desde código**: Usando la syscall `kill()`.
- **Automáticamente**: Por el kernel ante eventos como errores de segmentación (SIGSEGV).

## 3. Señales disponibles en el sistema
Ejecutar `kill -l` para listar todas las señales.

## Explicación de las salidas
### ejercicio4: Termina abruptamente con SIGINT, posiblemente sin imprimir el segundo mensaje.
### ejercicio5: Captura SIGINT, imprime el PID y continúa.
### ejercicio5a: Ignora SIGINT y ejecuta completamente.
### ejercicio6: El padre envía SIGUSR1 al hijo, que termina tras imprimir un mensaje.
