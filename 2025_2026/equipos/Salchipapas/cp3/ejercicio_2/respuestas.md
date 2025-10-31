### **Ejercicio 2**

### **Explique como pueden ser enviadas señales a un proceso**

---

Las señales en sistemas Linux representan un mecanismo fundamental de comunicación interprocesos que permite notificar eventos de forma asíncrona. Su envío puede realizarse desde múltiples fuentes, cada una con características específicas que determinan el contexto y propósito de la notificación.

### **Métodos de Envío de Señales a Procesos**

#### **1. Desde el Kernel**
- Excepciones de hardware detectadas por el procesador
- Eventos de gestión de recursos del sistema
- Expiración de temporizadores del sistema

#### **2. Desde Terminal**
- Combinaciones de teclas específicas (`Ctrl+C`, `Ctrl+Z`, `Ctrl+\`)
- Desconexión de sesión terminal

#### **3. Comando kill**
- *kill -[SEÑAL] [PID]*
- `kill -TERM 1234` - Envío de SIGTERM
- `kill -KILL 5678` - Envío de SIGKILL

##### **4. Desde Otros Procesos**
- `kill()`: Envío a proceso por PID
- `sigsend()`: Envío a grupos de procesos
- `sigqueue()`: Señales tiempo real con datos

##### **5. Autogeneración**
- `raise()`: Proceso enviándose señal a sí mismo
- `alarm()`: Temporizadores internos del proceso
