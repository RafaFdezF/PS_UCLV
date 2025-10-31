# Ejercicio 1

## ¿Qué es una señal?

Una **señal** (signal) es un **mecanismo del sistema operativo** que permite **notificar a un proceso que ha ocurrido un evento**.

## a. ¿Cuáles acciones se pueden tomar para su tratamiento?

Un proceso puede responder a una señal de tres maneras principales:

- Ignorar la señal

- Capturar la señal (manejarla con una función propia)

- Usar el comportamiento por defecto
  
## b. ¿Todas las señales pueden ser ignoradas?

Hay dos señales que no pueden ser ignoradas ni capturadas:

- `SIGKILL`: termina inmediatamente el proceso.

- `SIGSTOP`: detiene el proceso.

Estas señales están reservadas por el sistema operativo para mantener el control sobre los procesos.
