
# Diferencias entre biblioteca estatica y compartida


La biblioteca estática se diferencia de la biblioteca compartida principalmente en el momento y la forma en que se enlazan con el programa.
En una biblioteca estática, el enlace se realiza en tiempo de compilación, lo que significa que el código de la biblioteca se copia directamente dentro del ejecutable final.
Por el contrario, una biblioteca compartida se enlaza en tiempo de ejecución, de manera que el programa carga la biblioteca solo cuando se ejecuta, manteniéndola como un archivo separado del ejecutable.

Otra diferencia importante es que, en el caso de las bibliotecas estáticas, cada programa tiene su propia copia del código de la biblioteca, lo que aumenta el tamaño del ejecutable y el uso de memoria si varios programas utilizan las mismas funciones.
En cambio, las bibliotecas compartidas permiten que distintos programas usen una misma copia de la biblioteca cargada en memoria, lo que reduce el consumo de recursos del sistema.

En cuanto a la dependencia del sistema, los programas que usan bibliotecas estáticas no dependen de archivos externos una vez compilados, ya que toda la información necesaria está incorporada en el ejecutable.
Por el contrario, los programas que usan bibliotecas compartidas sí dependen de que la biblioteca esté presente en el sistema en el momento de ejecución; si falta o tiene una versión incompatible, el programa no podrá ejecutarse correctamente.

Respecto a la mantenibilidad y actualización, las bibliotecas estáticas requieren recompilar todos los programas cada vez que se modifica la biblioteca, ya que cada ejecutable incluye su propia copia.
En cambio, las bibliotecas compartidas pueden actualizarse o corregirse sin recompilar los programas, ya que estos se vinculan con la versión actualizada en tiempo de ejecución.

Finalmente, en términos de rendimiento, los ejecutables creados con bibliotecas estáticas suelen cargar más rápido, ya que todo el código está integrado en un solo archivo, aunque ocupan más espacio en disco.
Por su parte, las bibliotecas compartidas pueden tardar ligeramente más en iniciar, pero ofrecen mayor flexibilidad, menor tamaño de ejecutable y ahorro de memoria al compartir los recursos entre varias aplicaciones.

En resumen, la biblioteca estática es más simple y autosuficiente, ideal para aplicaciones pequeñas o portables, mientras que la biblioteca compartida es más eficiente y flexible, adecuada para sistemas grandes o multitarea donde se busca optimizar recursos y facilitar el mantenimiento del software.