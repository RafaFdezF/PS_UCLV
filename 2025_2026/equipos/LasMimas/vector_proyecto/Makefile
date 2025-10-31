# ==============================================
# Makefile - Proyecto de Operaciones con Vectores
# Autor: Daniela, Amanda, Jennifer , Dayra , Andy 
# Descripción: Automatiza la creación de las bibliotecas
# estática y compartida, y los ejecutables correspondientes.
# ==============================================

# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -Wall -O2
LDFLAGS = -lm

# Archivos fuente y cabeceras
SRC = vector_ops.c
HEADER = vector_ops.h

# Archivos objeto
OBJ = vector_ops.o

# Nombres de las bibliotecas
STATIC_LIB = libvector.a
SHARED_LIB = libvector.so

# Ejecutables
EXEC_STATIC = main_estatico
EXEC_SHARED = main_dinamico

# ==============================================
# Regla principal
# ==============================================
all: $(STATIC_LIB) $(SHARED_LIB) $(EXEC_STATIC) $(EXEC_SHARED)

# Compilar archivo objeto
$(OBJ): $(SRC) $(HEADER)
	$(CC) -fPIC -c $(SRC) -o $(OBJ)

# Crear biblioteca estática (.a)
$(STATIC_LIB): $(OBJ)
	ar rcs $(STATIC_LIB) $(OBJ)

# Crear biblioteca compartida (.so)
$(SHARED_LIB): $(OBJ)
	$(CC) -shared -o $(SHARED_LIB) $(OBJ)

# Compilar ejecutable con biblioteca estática
$(EXEC_STATIC): main.c $(STATIC_LIB)
	$(CC) $(CFLAGS) main.c -L. -lvector $(LDFLAGS) -o $(EXEC_STATIC)

# Compilar ejecutable con biblioteca compartida
$(EXEC_SHARED): main.c $(SHARED_LIB)
	$(CC) $(CFLAGS) main.c -L. -lvector $(LDFLAGS) -o $(EXEC_SHARED)

# ==============================================
# Limpiar archivos compilados
# ==============================================
clean:
	rm -f *.o *.a *.so $(EXEC_STATIC) $(EXEC_SHARED)

# ==============================================
# Ejecutar programa (opcional)
# ==============================================
run: $(EXEC_SHARED)
	@export LD_LIBRARY_PATH=.; ./$(EXEC_SHARED)
