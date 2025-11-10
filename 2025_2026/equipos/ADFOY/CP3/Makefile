CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: ejercicio1 ejercicio2 eventos ejercicio4

ejercicio1: ejercicio1.c
	$(CC) $(CFLAGS) -o ejercicio1 ejercicio1.c

ejercicio2: ejercicio2.c
	$(CC) $(CFLAGS) -o ejercicio2 ejercicio2.c

eventos: eventos.c
	$(CC) $(CFLAGS) -o eventos eventos.c

ejercicio4: ejercicio4.c
	$(CC) $(CFLAGS) -o ejercicio4 ejercicio4.c

clean:
	rm -f ejercicio1 ejercicio2 eventos ejercicio4

.PHONY: all clean