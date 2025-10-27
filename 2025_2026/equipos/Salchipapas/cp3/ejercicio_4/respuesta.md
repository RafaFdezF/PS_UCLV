#### **Salida Observada: No se muestra ningún texto en la terminal**

#### **Explicación del Comportamiento en WSL:**

**1. Buffering de Salida:**
- `stdout` utiliza buffering por línea en terminales interactivas
- La ausencia de `\n` o `fflush()` mantiene el texto en el buffer interno del proceso
- No se produce escritura física en la terminal mientras el texto permanece buffereado

**2. Terminación Abrupta por Señal:**
- `SIGINT` ejecuta la acción por defecto: terminación inmediata del proceso
- En WSL, la terminación por señal no garantiza el vaciado automático de buffers
- El proceso es destruido antes de que el subsistema coordine la operación de E/S

**3. Arquitectura WSL:**
- La capa de traducción entre el subsistema Linux y el kernel Windows
- Posibles diferencias en el manejo de señales y limpieza de procesos comparedo con Linux nativo

**4. Falta de Manejador:**
- Sin manejador personalizado para `SIGINT`, no hay oportunidad para vaciar buffers manualmente
- Comportamiento por defecto ejecutado sin intervención del programa

La ausencia de salida demuestra empíricamente que en WSL las señales no manejadas pueden interrumpir procesos antes de que completen operaciones de E/S buffereadas, sin garantía de vaciado automático de buffers.