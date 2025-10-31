# Nombre del compilador
CC = gcc

# Flags de compilación
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm
DLFLAGS = -ldl

# Archivos fuente
SRC = crear.c inicializar.c operaciones.c mostrar.c
OBJ = $(SRC:.c=.o)

# Biblioteca estática
STATIC_LIB = libvector.a

# Biblioteca dinámica
SHARED_LIB = libvector.so

# Ejecutables
EXEC_STATIC = programa_estatico
EXEC_DYNAMIC = programa_dinamico

# -------------------------------
# Reglas principales
# -------------------------------
all: $(STATIC_LIB) $(SHARED_LIB) $(EXEC_STATIC) $(EXEC_DYNAMIC)

# Crear objetos
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# -------------------------------
# Biblioteca estática
# -------------------------------
$(STATIC_LIB): $(OBJ)
	ar rcs $@ $^

# -------------------------------
# Biblioteca dinámica
# -------------------------------
$(SHARED_LIB): $(SRC)
	$(CC) -fPIC -shared -o $@ $^ $(LDFLAGS)

# -------------------------------
# Ejecutable estático
# -------------------------------
$(EXEC_STATIC): main.c $(STATIC_LIB)
	$(CC) $(CFLAGS) main.c -L. -lvector -o $@ $(LDFLAGS)

# -------------------------------
# Ejecutable con carga dinámica
# -------------------------------
$(EXEC_DYNAMIC): main_dinamico.c $(SHARED_LIB)
	$(CC) $(CFLAGS) main_dinamico.c -o $@ $(DLFLAGS)

# -------------------------------
# Limpiar archivos generados
# -------------------------------
clean:
	rm -f *.o $(STATIC_LIB) $(SHARED_LIB) $(EXEC_STATIC) $(EXEC_DYNAMIC)

.PHONY: all clean
