#### **¿Sería posible saber si un proceso hijo ha terminado enviando una señal 0 mediante kill?**

**NO**, no es posible determinar si un proceso hijo ha terminado usando `kill(pid, 0)` cuando el padre no ha llamado a `wait()` o `waitpid()`.

**Explicación técnica**:
- Cuando un proceso hijo termina pero el padre no ha hecho `wait()`, el proceso entra en estado **"zombie"**
- Un proceso **zombie** sigue existiendo en la tabla de procesos del sistema
- `kill(pid, 0)` verifica si un proceso con ese PID existe, no su estado de ejecución
- Por lo tanto, `kill(pid, 0)` devolverá éxito (0) tanto para procesos en ejecución como para zombies