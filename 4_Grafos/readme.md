LIBRERIA DE GRAFOS (grafos.h)
=============================

Libreria generica de grafos implementada en C++ puro con gestion 
dinamica de memoria y punteros, sin depender de contenedores de 
la Biblioteca Estandar (STL) vector o queue. Esta 
pensada como template, asi que el tipo de dato que guarda cada 
vertice lo decide quien usa la libreria (pudiendo trabajar con 
caracteres, enteros o tipos personalizados), lo que ofrece una 
gran flexibilidad para adaptarse a diferentes requerimientos 
academicos y profesionales.


ESTRUCTURA INTERNA
-------------------

La libreria incluye estructuras auxiliares propias diseñadas desde 
cero para garantizar un funcionamiento completamente autonomo, 
eficiente y libre de dependencias externas:

- Cola<T> y Pila<T>: Estructuras de datos implementadas mediante 
  nodos dinamicos encadenados. Se encargan de manejar con precision 
  los flujos de datos FIFO (First In, First Out) necesarios para los 
  recorridos en anchura (BFS), y LIFO (Last In, First Out) para los 
  recorridos en profundidad (DFS), gestionando la memoria de forma 
  limpia sin recurrir a contenedores prefabricados de la STL.

- GrafoMatriz<T> y GrafoLista<T>: Las dos clases principales que 
  permiten modelar el grafo segun los requerimientos de memoria y 
  velocidad. La primera utiliza una matriz bidimensional dinamica 
  de adyacencia (ideal para grafos densos donde las conexiones son 
  frecuentes), mientras que la segunda organiza las conexiones mediante 
  listas enlazadas dinamicas con soporte para pesos en las aristas 
  (optimizada para grafos dispersos ahorrando memoria).


FUNCIONES Y METODOS DISPONIBLES:
--------------------------------

Consultas y Operaciones Base:
  - agregar_vertice(vertice): Inserta un vertice nuevo en la 
    estructura de manera segura, realizando validaciones previas 
    para evitar duplicados indeseados y asegurando que el espacio 
    reservado sea suficiente.
  - agregar_arista(origen, destino, peso): Conecta dos vertices 
    estableciendo un costo o peso especifico entre ellos, adaptandose 
    automaticamente si el grafo es dirigido o no dirigido (duplicando 
    el enlace en este ultimo caso para mantener la simetria).
  - mostrar_grafo(): Recorre e imprime de forma clara, ordenada y 
    estructurada toda la representacion interna del grafo (ya sea 
    matriz o listas) directamente en la consola para facilitar el 
    diagnostico.
  - existe_vertice(vertice): Realiza una busqueda rapida dentro de 
    la estructura interna para certificar de forma booleana si un 
    vertice especifico ya forma parte del grafo.
  - existe_arista(origen, destino): Comprueba de forma directa si 
    hay una conexion activa y establecida entre dos vertices determinados 
    dentro de las listas o la matriz.
  - obtener_peso(origen, destino): Consulta y devuelve el valor 
    numerico del peso asociado a la arista que une directamente a 
    dos nodos especificos.
  - obtener_vecinos(vertice, cantidad): Genera, dimensiona y retorna 
    un arreglo dinamico independiente con todos los elementos vecinos 
    que colindan de forma directa con el vertice consultado.

Modificacion y Memoria:
  - eliminar_arista(origen, destino): Remueve la conexion existente 
    entre dos nodos, ajustando de manera automatica la bidireccionalidad 
    en caso de que el grafo lo requiera para mantener la consistencia 
    estructural.
  - eliminar_vertice(vertice): Borra por completo un vertice de la 
    estructura, limpiando de forma segura las referencias o aristas 
    colgadas en otros nodos, reacomodando indices internos y liberando 
    de manera estricta la memoria correspondiente para evitar fugas 
    (memory leaks).
  - redimensionar(nueva_capacidad): Permite ampliar de manera dinamica 
    la capacidad maxima de almacenamiento del grafo cuando este se queda 
    sin espacio asignado, conservando intactos todos los datos, aristas y 
    nodos previos mediante un realojo seguro de memoria.

Recorridos y Algoritmos Avanzados:
  - bfs(inicio): Ejecuta el recorrido en anchura (Breadth-First Search) 
    explorando el grafo nivel por nivel desde el nodo de origen, apoyandose 
    en la estructura Cola propia para procesar los nodos en orden estricto 
    de cercania.
  - dfs(inicio): Ejecuta el recorrido en profundidad (Depth-First Search) 
    explorando lo mas lejos posible a lo largo de cada rama antes de retroceder, 
    apoyandose en la Pila propia para gestionar el rastro de la exploracion.
  - dijkstra(origen, destino): Aplica el algoritmo clasico de rutas minimas 
    sobre los pesos de las aristas para calcular la distancia acumulada menor 
    y reconstruir paso a paso el trayecto optimo entre dos vertices determinados.
  - prim(inicio): Ejecuta el algoritmo de Prim para calcular y mostrar 
    en consola el Arbol de Expansion Minima (MST), conectando todos los 
    vertices del grafo con el menor costo total acumulado posible sin formar 
    ciclos.
