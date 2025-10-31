# Compilador y opciones
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

# Archivos fuente y cabeceras
SRC = vectores.c main.c
OBJ = vectores.o main.o
HEADER = vectores.h

# Nombres de bibliotecas y ejecutables
LIB_STATIC = libvectores.a
LIB_SHARED = libvectores.so
EXEC_STATIC = main_static
EXEC_SHARED = main_shared

# Objetivo por defecto
all: static shared

# --- Biblioteca estática ---
static: $(LIB_STATIC) $(EXEC_STATIC)

$(LIB_STATIC): vectores.o
	ar rcs $@ $^

$(EXEC_STATIC): main.o $(LIB_STATIC)
	$(CC) -o $@ main.o -L. -lvectores $(LDFLAGS)

# --- Biblioteca compartida ---
shared: $(LIB_SHARED) $(EXEC_SHARED)

$(LIB_SHARED): vectores.o
	$(CC) -shared -o $@ $^ $(LDFLAGS)

$(EXEC_SHARED): main.o $(LIB_SHARED)
	$(CC) -o $@ main.o -L. -lvectores $(LDFLAGS)

# --- Compilación de objetos ---
vectores.o: vectores.c $(HEADER)
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

main.o: main.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Limpieza ---
clean:
	rm -f $(OBJ) $(LIB_STATIC) $(LIB_SHARED) $(EXEC_STATIC) $(EXEC_SHARED)

# --- Instalación (opcional, requiere permisos de superusuario) ---
install: $(LIB_SHARED)
	sudo cp $(LIB_SHARED) /usr/local/lib/
	sudo ldconfig

uninstall:
	sudo rm -f /usr/local/lib/$(LIB_SHARED)
	sudo ldconfig

.PHONY: all static shared clean install uninstall