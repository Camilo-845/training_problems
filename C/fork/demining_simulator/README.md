# Simulación de Operaciones de Desminado Utilizando Multiprocesamiento y Tuberías

**Universidad del Magdalena**  
**Sistemas Operativos – Ingeniería de Sistemas**

---

## Objetivo

Solucionar problemas computacionales que impliquen comunicación entre procesos mediante tuberías y multiprocesamiento mediante `fork()`.

---

## Descripción

La remoción segura de minas antipersonales es fundamental para la recuperación y preservación de áreas afectadas por conflictos. La detección y desactivación tradicional de minas supone riesgos para los desminadores y la población civil circundante.

Para enfrentar este desafío sin exponer a los equipos humanos, se utilizarán drones que tomen imágenes.

Cada imagen representa un campo minado como una **matriz** grande, donde cada celda puede:

- **1**: Indicar un objeto detectable (posible mina)
- **0**: Indicar espacio libre
- **2**: Indicar perturbación o excavación del terreno

Una posición contiene una mina si hay al menos una evidencia de excavación alrededor de ella.

---

El sistema debe dividir la matriz en **múltiples segmentos** (cantidad divisible entre 4), asignando **un proceso hijo por cada cuadrante**. Cada subproceso escaneará un segmento específico de la matriz. Se usarán **técnicas de procesamiento paralelo** para optimizar tiempo y precisión.

---

## Entrada esperada

El programa leerá desde un archivo una matriz que represente el campo minado:

```text
Descripción:    Ejemplo:
#filas          5
#columnas       10
Fila1           0000020100
Fila2           1110000210
Fila3           0000100000
Fila4           0000021000
Fila5           0000010000
```
