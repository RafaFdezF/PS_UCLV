# Makefile: soporte para biblioteca estática (.a) y compartida (.so)
CC = gcc
CFLAGS = -Wall -Wextra -O2
PICFLAGS = -fPIC

# Fuentes / nombres
LIB_SRC = vlib.c
LIB_HDR = vlib.h
LIB_OBJ = vlib.o

# Nombres de las librerías (estática sin prefijo lib, compartida con lib)
STATIC_LIB = vlib.a
SHARED_LIB = libvlib.so

# Ejecutables
MAIN_SRC = main.c
MAIN_STATIC = main_static      # ejecutable enlazado con vlib.a
MAIN_SHARED = main_dynamic    # ejecutable enlazado con libvlib.so

.PHONY: all static shared main static_exec shared_exec run_static run_shared clean

all: static shared static_exec shared_exec

# 1) compilar objeto (usar -fPIC si también se usará para .so)
$(LIB_OBJ): $(LIB_SRC) $(LIB_HDR)
	$(CC) $(CFLAGS) $(PICFLAGS) -c $< -o $@

# 2) crear biblioteca estática vlib.a (contiene vlib.o)
$(STATIC_LIB): $(LIB_OBJ)
	ar rcs $@ $^

# 3) crear biblioteca compartida libvlib.so a partir de vlib.o
$(SHARED_LIB): $(LIB_OBJ)
	$(CC) -shared -Wl,-soname,$(SHARED_LIB) -o $@ $^

# 4a) compilación del ejecutable enlazando la .a (estático respecto a vlib)
$(MAIN_STATIC): $(MAIN_SRC) $(STATIC_LIB)
	$(CC) $(CFLAGS) $< $(STATIC_LIB) -o $@

# 4b) compilación del ejecutable enlazando la .so (dinámico)
# -L. -lvlib busca libvlib.so en el directorio actual; -rpath usa $ORIGIN para buscar en el mismo dir
$(MAIN_SHARED): $(MAIN_SRC) $(SHARED_LIB)
	$(CC) $(CFLAGS) $< -L. -lvlib -Wl,-rpath,'$$ORIGIN' -o $@

# Atajos
static: $(STATIC_LIB)
shared: $(SHARED_LIB)
static_exec: $(MAIN_STATIC)
shared_exec: $(MAIN_SHARED)

run_static: $(MAIN_STATIC)
	./$(MAIN_STATIC)

run_shared: $(MAIN_SHARED)
	LD_LIBRARY_PATH=. ./$(MAIN_SHARED)

# Limpiar todo generado
clean:
	rm -f $(LIB_OBJ) $(STATIC_LIB) $(SHARED_LIB) $(MAIN_STATIC) $(MAIN_SHARED)
