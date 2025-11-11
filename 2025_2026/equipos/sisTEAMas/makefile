# Compilador
CC = gcc
# Flags de compilación
CFLAGS = -Wall -Wextra
# Flags para biblioteca compartida
SHARED_FLAGS = -fPIC

# Nombres de bibliotecas
STATIC_LIB = libvector.a
DYNAMIC_LIB = libvector.so
# Nombres de ejecutables
STATIC_EXE = programa_estatico
DYNAMIC_EXE = programa_dinamico

# Regla principal - construye todo
all: static dynamic

# --- BIBLIOTECA ESTÁTICA ---
static: $(STATIC_EXE)

$(STATIC_EXE): main.c $(STATIC_LIB)
	$(CC) main.c -L. -lvector -o $(STATIC_EXE) -lm

$(STATIC_LIB): vector.o
	ar rcs $(STATIC_LIB) vector.o

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c -o vector.o

# --- BIBLIOTECA DINÁMICA ---
dynamic: $(DYNAMIC_EXE)

$(DYNAMIC_EXE): main.c $(DYNAMIC_LIB)
	$(CC) main.c -L. -lvector -o $(DYNAMIC_EXE) -lm

$(DYNAMIC_LIB): vector_shared.o
	$(CC) -shared -o $(DYNAMIC_LIB) vector_shared.o

vector_shared.o: vector.c vector.h
	$(CC) $(CFLAGS) $(SHARED_FLAGS) -c vector.c -o vector_shared.o

# Limpieza
clean:
	rm -f *.o *.a *.so $(STATIC_EXE) $(DYNAMIC_EXE)

# Reglas phony
.PHONY: all static dynamic clean