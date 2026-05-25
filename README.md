# Estructuras Dinámicas de Datos (EDD)

Este repositorio almacena la información, apuntes y prácticas sobre la materia "Estructuras Dinámicas de Datos" cursada en la universidad, basándose en el material impartido en las clases

Las estructuras dinámicas de datos permiten crear estructuras que cambian de tamaño durante la ejecución del programa, logrando una enorme flexibilidad en el manejo y relación de los datos mediante nodos y punteros.

## Organización del Repositorio

El repositorio está organizado en las siguientes carpetas en este orden:

### 1. [Listas](./1_Listas)
Las listas abiertas son una estructura dinámica donde cada elemento dispone de un puntero que apunta al siguiente elemento de la lista, o apunta a `NULL` si es el último. Existen también variaciones como las listas doblemente enlazadas y las listas circulares.

### 2. [Pilas y colas](./2_Pilas_y_colas)
- **Pilas:** Son listas tipo LIFO (*Last In, First Out*). El último elemento que entra es el primero en salir. Se apilan de tal manera que solo puede añadirse y leerse información desde la cima (el último elemento ingresado).
- **Colas:** Son listas tipo FIFO (*First In, First Out*). El primer elemento en entrar es el primero en salir. Los elementos se añaden por un extremo y son extraídos por el extremo opuesto.

### 3. [Árboles](./3_Arboles)
Las estructuras en árbol se componen de nodos con dos o más punteros que nunca referencian a elementos anteriores, haciendo que la estructura se ramifique. Puede incluir Árboles Binarios, Árboles de Búsqueda (ABB), AVL, etc.

### 4. [Grafos](./4_Grafos)
El siguiente nivel de complejidad después de los árboles. Los grafos pueden ser considerados como estructuras arborescentes pero sin una estricta jerarquización, definiendo múltiples relaciones entre nodos.

### 5. [Tareas prácticas](./5_Tareas_practicas)
Carpeta destinada a almacenar todas las actividades prácticas, ejercicios y tareas desarrolladas a lo largo de la cursada sobre cada una de las estructuras mencionadas.
