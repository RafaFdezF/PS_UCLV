# a. Biblioteca estatica

# 1 Compilar el codigo fuente en un archivo objeto

gcc -c vlib.c -o vlib.o

# 2 Crear la biblioteca estatica a partir del archivo objeto

ar rcs libvlib.a vlib.o

# 3 Compilar el programa principal enlazando con la biblioteca

gcc main.c -L. -lvlib -o programa_estatico

# 4 Ejecutar el programa

./programa_estatico



# b. Biblioteca compartida

# 1 Compilar el codigo fuente como "PIC"

gcc -fPIC -c vlib.c -o vlib.o

# 2 Crear la biblioteca compartida

gcc -shared -o libvlib.so vlib.o

# 3 Compilar el programa principal enlazando con la biblioteca

gcc main.c -L. -lvlib -o programa_dinamico

# 4. Indicar al sistema dónde buscar la biblioteca compartida
export LD_LIBRARY_PATH=.

# 5. Ejecutar el programa
./programa_dinamico