### Preguntas Teoricas:

### 1. ¿Qué son las bibliotecas?

Las bibliotecas (también llamadas librerías) son conjuntos de funciones, clases o recursos que han sido programados previamente y que otros programas pueden reutilizar. Su principal objetivo es evitar repetir código y facilitar el desarrollo, ya que permiten que distintos proyectos utilicen las mismas herramientas o rutinas sin tener que volver a escribirlas.
En resumen, una biblioteca es como una “caja de herramientas” que contiene código útil listo para ser usado en varios programas.

### 2. Diferencias entre una biblioteca estática y una compartida (dinámica)

| **Biblioteca Estática**                                                  | **Biblioteca Compartida o Dinámica**                                                               |
| ------------------------------------------------------------------------ | -------------------------------------------------------------------------------------------------- |
| Se incluye dentro del programa cuando se compila.                        | Se carga por separado mientras el programa se está ejecutando.                                     |
| El código de la biblioteca se copia dentro del archivo ejecutable final. | El programa solo guarda una referencia a la biblioteca externa.                                    |
| Genera ejecutables más grandes.                                          | Los ejecutables son más pequeños.                                                                  |
| No necesita archivos externos para funcionar.                            | Necesita que la biblioteca esté instalada en el sistema.                                           |
| Si se actualiza la biblioteca, hay que recompilar el programa.           | Si se actualiza la biblioteca, el programa usa automáticamente la nueva versión.                   |
| Puede ofrecer mejor rendimiento al no requerir carga dinámica.           | Puede tener una leve pérdida de rendimiento por la carga dinámica, pero facilita el mantenimiento. |
