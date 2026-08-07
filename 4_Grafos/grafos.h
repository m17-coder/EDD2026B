#ifndef GRAFO_LIBRERIA_H
#define GRAFO_LIBRERIA_H
#include <iostream>

struct NodoArista {
    int indice_destino;
    int peso;
    NodoArista* siguiente;

    NodoArista(int dest, int p, NodoArista* sig = nullptr)
        : indice_destino(dest), peso(p), siguiente(sig) {}
};

template <typename T>
class Cola {
private:
    struct NodoCola {
        T dato;
        NodoCola* siguiente;
        NodoCola(const T& val) : dato(val), siguiente(nullptr) {}
    };
    NodoCola* frente;
    NodoCola* final_nodo;

public:
    Cola() : frente(nullptr), final_nodo(nullptr) {}
    ~Cola() {
        while (!vacia()) desencolar();
    }

    bool vacia() const { return frente == nullptr; }

    void encolar(const T& valor) {
        NodoCola* nuevo = new NodoCola(valor);
        if (vacia()) {
            frente = final_nodo = nuevo;
        } else {
            final_nodo->siguiente = nuevo;
            final_nodo = nuevo;
        }
    }

    T desencolar() {
        if (vacia()) return T();
        NodoCola* temp = frente;
        T valor = temp->dato;
        frente = frente->siguiente;
        if (frente == nullptr) final_nodo = nullptr;
        delete temp;
        return valor;
    }
};

template <typename T>
class Pila {
private:
    struct NodoPila {
        T dato;
        NodoPila* siguiente;
        NodoPila(const T& val, NodoPila* sig = nullptr) : dato(val), siguiente(sig) {}
    };
    NodoPila* tope;

public:
    Pila() : tope(nullptr) {}
    ~Pila() {
        while (!vacia()) desapilar();
    }

    bool vacia() const { return tope == nullptr; }

    void apilar(const T& valor) {
        tope = new NodoPila(valor, tope);
    }

    T desapilar() {
        if (vacia()) return T();
        NodoPila* temp = tope;
        T valor = temp->dato;
        tope = tope->siguiente;
        delete temp;
        return valor;
    }
    
};
template <typename T>
class GrafoMatriz {
private:
    T* vertices;
    int** matriz;
    int capacidad_maxima;
    int num_vertices;
    bool es_dirigido;

    int buscar_indice(const T& vertice) const {
        for (int i = 0; i < num_vertices; ++i) {
            if (vertices[i] == vertice) return i;
        }
        return -1;
    }

public:
    GrafoMatriz(int capacidad, bool dirigido = false) 
        : capacidad_maxima(capacidad), num_vertices(0), es_dirigido(dirigido) {
        
        if (capacidad <= 0) {
            std::cout << "[ERROR] La capacidad del grafo debe ser mayor a 0.\n";
            capacidad_maxima = 10;
        }

        vertices = new T[capacidad_maxima];
        matriz = new int*[capacidad_maxima];
        for (int i = 0; i < capacidad_maxima; ++i) {
            matriz[i] = new int[capacidad_maxima];
            for (int j = 0; j < capacidad_maxima; ++j) {
                matriz[i][j] = 0;
            }
        }
    }

    ~GrafoMatriz() {
        delete[] vertices;
        for (int i = 0; i < capacidad_maxima; ++i) {
            delete[] matriz[i];
        }
        delete[] matriz;
    }

    int agregar_vertice(const T& vertice) {
        int idx = buscar_indice(vertice);
        if (idx != -1) return idx; // Ya existe

        if (num_vertices >= capacidad_maxima) {
            std::cout << "[ADVERTENCIA] Capacidad maxima de vertices alcanzada (" 
                      << capacidad_maxima << "). No se agrego: " << vertice << "\n";
            return -1;
        }

        vertices[num_vertices] = vertice;
        return num_vertices++;
    }

    bool agregar_arista(const T& origen, const T& destino, int peso = 1) {
        int u = agregar_vertice(origen);
        int v = agregar_vertice(destino);

        if (u == -1 || v == -1) {
            std::cout << "[ERROR] No se pudo agregar la arista entre " 
                      << origen << " y " << destino << " (limite alcanzado).\n";
            return false;
        }

        matriz[u][v] = peso;
        if (!es_dirigido) {
            matriz[v][u] = peso;
        }
        return true;
    }

    void mostrar_grafo() const {
        std::cout << "\n=== Matriz de Adyacencia (" << (es_dirigido ? "Dirigido" : "No Dirigido") << ") ===\n  ";
        for (int i = 0; i < num_vertices; ++i) {
            std::cout << vertices[i] << " ";
        }
        std::cout << "\n";

        for (int i = 0; i < num_vertices; ++i) {
            std::cout << vertices[i] << " ";
            for (int j = 0; j < num_vertices; ++j) {
                std::cout << matriz[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    int obtener_num_vertices() const { return num_vertices; }

    void bfs(const T& inicio) const {
        int idx = buscar_indice(inicio);
        if (idx == -1) {
            std::cout << "[ERROR] Vertice de inicio no encontrado.\n";
            return;
        }

        bool* visitado = new bool[num_vertices];
        for (int i = 0; i < num_vertices; ++i) visitado[i] = false;

        Cola<int> cola;
        visitado[idx] = true;
        cola.encolar(idx);

        std::cout << "\nRecorrido BFS (Matriz) desde [" << inicio << "]: ";
        while (!cola.vacia()) {
            int u = cola.desencolar();
            std::cout << vertices[u] << " ";

            for (int v = 0; v < num_vertices; ++v) {
                if (matriz[u][v] != 0 && !visitado[v]) {
                    visitado[v] = true;
                    cola.encolar(v);
                }
            }
        }
        std::cout << "\n";
        delete[] visitado;
    }

    // Algoritmo DFS (Recorrido en Profundidad)
    void dfs(const T& inicio) const {
        int idx = buscar_indice(inicio);
        if (idx == -1) {
            std::cout << "[ERROR] Vertice de inicio no encontrado.\n";
            return;
        }

        bool* visitado = new bool[num_vertices];
        for (int i = 0; i < num_vertices; ++i) visitado[i] = false;

        Pila<int> pila;
        pila.apilar(idx);

        std::cout << "\nRecorrido DFS (Matriz) desde [" << inicio << "]: ";
        while (!pila.vacia()) {
            int u = pila.desapilar();

            if (!visitado[u]) {
                visitado[u] = true;
                std::cout << vertices[u] << " ";
            }

            for (int v = num_vertices - 1; v >= 0; --v) {
                if (matriz[u][v] != 0 && !visitado[v]) {
                    pila.apilar(v);
                }
            }
        }
        std::cout << "\n";
        delete[] visitado;
    }
    // Algoritmo de Dijkstra para Matriz de Adyacencia
    void dijkstra(const T& origen, const T& destino) const {
        int u_start = buscar_indice(origen);
        int u_end = buscar_indice(destino);

        if (u_start == -1 || u_end == -1) {
            std::cout << "[ERROR] Vertice de origen o destino no encontrado.\n";
            return;
        }

        const int INF = 1e9; // Constante para representar infinito
        int* dist = new int[num_vertices];
        bool* visitado = new bool[num_vertices];
        int* previo = new int[num_vertices];

        for (int i = 0; i < num_vertices; ++i) {
            dist[i] = INF;
            visitado[i] = false;
            previo[i] = -1;
        }

        dist[u_start] = 0;

        for (int count = 0; count < num_vertices - 1; ++count) {
            int min_dist = INF;
            int u = -1;

            // Seleccionar el vértice no visitado con la distancia mínima
            for (int v = 0; v < num_vertices; ++v) {
                if (!visitado[v] && dist[v] < min_dist) {
                    min_dist = dist[v];
                    u = v;
                }
            }

            if (u == -1) break; // Vertices restantes inalcanzables

            visitado[u] = true;

            // Actualizar la distancia de los vecinos de u
            for (int v = 0; v < num_vertices; ++v) {
                if (!visitado[v] && matriz[u][v] != 0 && dist[u] + matriz[u][v] < dist[v]) {
                    dist[v] = dist[u] + matriz[u][v];
                    previo[v] = u;
                }
            }
        }

        // Impresión del resultado y reconstrucción del camino
        if (dist[u_end] == INF) {
            std::cout << "\nNo existe camino entre [" << origen << "] y [" << destino << "].\n";
        } else {
            std::cout << "\nDistancia minima (Matriz) de [" << origen << "] a [" << destino << "]: " << dist[u_end] << "\n";
            std::cout << "Camino: ";

            int* camino = new int[num_vertices];
            int tam = 0;
            int curr = u_end;

            while (curr != -1) {
                camino[tam++] = curr;
                curr = previo[curr];
            }

            for (int i = tam - 1; i >= 0; --i) {
                std::cout << vertices[camino[i]] << (i > 0 ? " -> " : "");
            }
            std::cout << "\n";

            delete[] camino;
        }

        delete[] dist;
        delete[] visitado;
        delete[] previo;
    }


    bool existe_vertice(const T& vertice) const {
        return buscar_indice(vertice) != -1;
    }

    bool existe_arista(const T& origen, const T& destino) const {
        int u = buscar_indice(origen);
        int v = buscar_indice(destino);
        if (u == -1 || v == -1) return false;
        return matriz[u][v] != 0;
    }

    int obtener_peso(const T& origen, const T& destino) const {
        int u = buscar_indice(origen);
        int v = buscar_indice(destino);
        if (u == -1 || v == -1) return 0;
        return matriz[u][v];
    }

    // funciones de eliminacion
    bool eliminar_arista(const T& origen, const T& destino) {
        int u = buscar_indice(origen);
        int v = buscar_indice(destino);
        if (u == -1 || v == -1 || matriz[u][v] == 0) return false;

        matriz[u][v] = 0;
        if (!es_dirigido) {
            matriz[v][u] = 0;
        }
        return true;
    }

    bool eliminar_vertice(const T& vertice) {
        int u = buscar_indice(vertice);
        if (u == -1) return false;

        for (int i = u; i < num_vertices - 1; ++i) {
            for (int j = 0; j < num_vertices; ++j) {
                matriz[i][j] = matriz[i + 1][j];
            }
        }
        for (int j = u; j < num_vertices - 1; ++j) {
            for (int i = 0; i < num_vertices; ++i) {
                matriz[i][j] = matriz[i][j + 1];
            }
        }
        for (int i = 0; i < num_vertices; ++i) {
            matriz[num_vertices - 1][i] = 0;
            matriz[i][num_vertices - 1] = 0;
        }

        for (int i = u; i < num_vertices - 1; ++i) {
            vertices[i] = vertices[i + 1];
        }

        num_vertices--;
        return true;
    }

    // Redimensionar memoria
    void redimensionar(int nueva_capacidad) {
        if (nueva_capacidad <= capacidad_maxima) return;

        T* nuevos_vertices = new T[nueva_capacidad];
        for (int i = 0; i < num_vertices; ++i) {
            nuevos_vertices[i] = vertices[i];
        }

        int** nueva_matriz = new int*[nueva_capacidad];
        for (int i = 0; i < nueva_capacidad; ++i) {
            nueva_matriz[i] = new int[nueva_capacidad];
            for (int j = 0; j < nueva_capacidad; ++j) {
                if (i < num_vertices && j < num_vertices) {
                    nueva_matriz[i][j] = matriz[i][j];
                } else {
                    nueva_matriz[i][j] = 0;
                }
            }
        }

        delete[] vertices;
        for (int i = 0; i < capacidad_maxima; ++i) {
            delete[] matriz[i];
        }
        delete[] matriz;

        vertices = nuevos_vertices;
        matriz = nueva_matriz;
        capacidad_maxima = nueva_capacidad;
    }

    // Retorno de vecinos
    T* obtener_vecinos(const T& vertice, int& cantidad) const {
        cantidad = 0;
        int u = buscar_indice(vertice);
        if (u == -1) return nullptr;

        for (int v = 0; v < num_vertices; ++v) {
            if (matriz[u][v] != 0) cantidad++;
        }

        if (cantidad == 0) return nullptr;

        T* vecinos = new T[cantidad];
        int idx = 0;
        for (int v = 0; v < num_vertices; ++v) {
            if (matriz[u][v] != 0) {
                vecinos[idx++] = vertices[v];
            }
        }
        return vecinos;
    }

    // Algoritmo de prim
    void prim(const T& inicio) const {
        int u_start = buscar_indice(inicio);
        if (u_start == -1) {
            std::cout << "[ERROR] Vertice de inicio no encontrado.\n";
            return;
        }

        const int INF = 1e9;
        int* llave = new int[num_vertices];
        bool* incluido_mst = new bool[num_vertices];
        int* padre = new int[num_vertices];

        for (int i = 0; i < num_vertices; ++i) {
            llave[i] = INF;
            incluido_mst[i] = false;
            padre[i] = -1;
        }

        llave[u_start] = 0;

        for (int count = 0; count < num_vertices - 1; ++count) {
            int min_key = INF;
            int u = -1;

            for (int v = 0; v < num_vertices; ++v) {
                if (!incluido_mst[v] && llave[v] < min_key) {
                    min_key = llave[v];
                    u = v;
                }
            }

            if (u == -1) break;
            incluido_mst[u] = true;

            for (int v = 0; v < num_vertices; ++v) {
                if (matriz[u][v] != 0 && !incluido_mst[v] && matriz[u][v] < llave[v]) {
                    padre[v] = u;
                    llave[v] = matriz[u][v];
                }
            }
        }

        std::cout << "\n=== Arbol de Expansion Minima (Prim - Matriz) desde [" << inicio << "] ===\n";
        int peso_total = 0;
        for (int i = 0; i < num_vertices; ++i) {
            if (padre[i] != -1) {
                std::cout << vertices[padre[i]] << " - " << vertices[i] << " (peso: " << matriz[padre[i]][i] << ")\n";
                peso_total += matriz[padre[i]][i];
            }
        }
        std::cout << "Peso total del MST: " << peso_total << "\n";

        delete[] llave;
        delete[] incluido_mst;
        delete[] padre;
    }
};

template <typename T>
class GrafoLista {
private:
    T* vertices;
    NodoArista** cabezas;
    int capacidad_maxima;
    int num_vertices;
    bool es_dirigido;

    int buscar_indice(const T& vertice) const {
        for (int i = 0; i < num_vertices; ++i) {
            if (vertices[i] == vertice) return i;
        }
        return -1;
    }

public:
    GrafoLista(int capacidad, bool dirigido = false) 
        : capacidad_maxima(capacidad), num_vertices(0), es_dirigido(dirigido) {
        
        if (capacidad <= 0) {
            std::cout << "[ERROR] La capacidad del grafo debe ser mayor a 0.\n";
            capacidad_maxima = 10;
        }

        vertices = new T[capacidad_maxima];
        cabezas = new NodoArista*[capacidad_maxima];
        for (int i = 0; i < capacidad_maxima; ++i) {
            cabezas[i] = nullptr;
        }
    }

    ~GrafoLista() {
        for (int i = 0; i < capacidad_maxima; ++i) {
            NodoArista* actual = cabezas[i];
            while (actual != nullptr) {
                NodoArista* aux = actual;
                actual = actual->siguiente;
                delete aux;
            }
        }
        delete[] cabezas;
        delete[] vertices;
    }

    int agregar_vertice(const T& vertice) {
        int idx = buscar_indice(vertice);
        if (idx != -1) return idx;

        if (num_vertices >= capacidad_maxima) {
            std::cout << "[ADVERTENCIA] Capacidad maxima de vertices alcanzada (" 
                      << capacidad_maxima << "). No se agrego: " << vertice << "\n";
            return -1;
        }

        vertices[num_vertices] = vertice;
        return num_vertices++;
    }

    bool agregar_arista(const T& origen, const T& destino, int peso = 1) {
        int u = agregar_vertice(origen);
        int v = agregar_vertice(destino);

        if (u == -1 || v == -1) {
            std::cout << "[ERROR] No se pudo agregar la arista entre " 
                      << origen << " y " << destino << " (limite alcanzado).\n";
            return false;
        }

        cabezas[u] = new NodoArista(v, peso, cabezas[u]);

        if (!es_dirigido) {
            cabezas[v] = new NodoArista(u, peso, cabezas[v]);
        }
        return true;
    }

    void mostrar_grafo() const {
        std::cout << "\n=== Lista de Adyacencia (" << (es_dirigido ? "Dirigido" : "No Dirigido") << ") ===\n";
        for (int i = 0; i < num_vertices; ++i) {
            std::cout << "Vertice [" << vertices[i] << "]:";
            NodoArista* actual = cabezas[i];
            while (actual != nullptr) {
                std::cout << " -> " << vertices[actual->indice_destino] 
                          << "(peso: " << actual->peso << ")";
                actual = actual->siguiente;
            }
            std::cout << " -> nullptr\n";
        }
    }

    int obtener_num_vertices() const { return num_vertices; }

    void bfs(const T& inicio) const {
        int idx = buscar_indice(inicio);
        if (idx == -1) {
            std::cout << "[ERROR] Vertice de inicio no encontrado.\n";
            return;
        }

        bool* visitado = new bool[num_vertices];
        for (int i = 0; i < num_vertices; ++i) visitado[i] = false;

        Cola<int> cola;
        visitado[idx] = true;
        cola.encolar(idx);

        std::cout << "\nRecorrido BFS (Lista) desde [" << inicio << "]: ";
        while (!cola.vacia()) {
            int u = cola.desencolar();
            std::cout << vertices[u] << " ";

            NodoArista* actual = cabezas[u];
            while (actual != nullptr) {
                int v = actual->indice_destino;
                if (!visitado[v]) {
                    visitado[v] = true;
                    cola.encolar(v);
                }
                actual = actual->siguiente;
            }
        }
        std::cout << "\n";
        delete[] visitado;
    }

    // Algoritmo DFS (Recorrido en Profundidad)
    void dfs(const T& inicio) const {
        int idx = buscar_indice(inicio);
        if (idx == -1) {
            std::cout << "[ERROR] Vertice de inicio no encontrado.\n";
            return;
        }

        bool* visitado = new bool[num_vertices];
        for (int i = 0; i < num_vertices; ++i) visitado[i] = false;

        Pila<int> pila;
        pila.apilar(idx);

        std::cout << "\nRecorrido DFS (Lista) desde [" << inicio << "]: ";
        while (!pila.vacia()) {
            int u = pila.desapilar();

            if (!visitado[u]) {
                visitado[u] = true;
                std::cout << vertices[u] << " ";
            }

            NodoArista* actual = cabezas[u];
            while (actual != nullptr) {
                int v = actual->indice_destino;
                if (!visitado[v]) {
                    pila.apilar(v);
                }
                actual = actual->siguiente;
            }
        }
        std::cout << "\n";
        delete[] visitado;
    }
    // Algoritmo de Dijkstra para Lista de Adyacencia
    void dijkstra(const T& origen, const T& destino) const {
        int u_start = buscar_indice(origen);
        int u_end = buscar_indice(destino);

        if (u_start == -1 || u_end == -1) {
            std::cout << "[ERROR] Vertice de origen o destino no encontrado.\n";
            return;
        }

        const int INF = 1e9;
        int* dist = new int[num_vertices];
        bool* visitado = new bool[num_vertices];
        int* previo = new int[num_vertices];

        for (int i = 0; i < num_vertices; ++i) {
            dist[i] = INF;
            visitado[i] = false;
            previo[i] = -1;
        }

        dist[u_start] = 0;

        for (int count = 0; count < num_vertices - 1; ++count) {
            int min_dist = INF;
            int u = -1;

            // Seleccionar el vértice no visitado con la distancia mínima
            for (int v = 0; v < num_vertices; ++v) {
                if (!visitado[v] && dist[v] < min_dist) {
                    min_dist = dist[v];
                    u = v;
                }
            }

            if (u == -1) break;

            visitado[u] = true;

            // Recorrer los nodos vecinos mediante la lista enlazada
            NodoArista* actual = cabezas[u];
            while (actual != nullptr) {
                int v = actual->indice_destino;
                int peso = actual->peso;

                if (!visitado[v] && dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    previo[v] = u;
                }
                actual = actual->siguiente;
            }
        }

        // Impresión del resultado y reconstrucción del camino
        if (dist[u_end] == INF) {
            std::cout << "\nNo existe camino entre [" << origen << "] y [" << destino << "].\n";
        } else {
            std::cout << "\nDistancia minima (Lista) de [" << origen << "] a [" << destino << "]: " << dist[u_end] << "\n";
            std::cout << "Camino: ";

            int* camino = new int[num_vertices];
            int tam = 0;
            int curr = u_end;

            while (curr != -1) {
                camino[tam++] = curr;
                curr = previo[curr];
            }

            for (int i = tam - 1; i >= 0; --i) {
                std::cout << vertices[camino[i]] << (i > 0 ? " -> " : "");
            }
            std::cout << "\n";

            delete[] camino;
        }

        delete[] dist;
        delete[] visitado;
        delete[] previo;
    }

    bool existe_vertice(const T& vertice) const {
        return buscar_indice(vertice) != -1;
    }

    bool existe_arista(const T& origen, const T& destino) const {
        int u = buscar_indice(origen);
        int v = buscar_indice(destino);
        if (u == -1 || v == -1) return false;

        NodoArista* actual = cabezas[u];
        while (actual != nullptr) {
            if (actual->indice_destino == v) return true;
            actual = actual->siguiente;
        }
        return false;
    }

    int obtener_peso(const T& origen, const T& destino) const {
        int u = buscar_indice(origen);
        int v = buscar_indice(destino);
        if (u == -1 || v == -1) return 0;

        NodoArista* actual = cabezas[u];
        while (actual != nullptr) {
            if (actual->indice_destino == v) return actual->peso;
            actual = actual->siguiente;
        }
        return 0;
    }

    bool eliminar_arista(const T& origen, const T& destino) {
        int u = buscar_indice(origen);
        int v = buscar_indice(destino);
        if (u == -1 || v == -1) return false;

        auto borrar_nodo = [](NodoArista*& cabeza, int dest) -> bool {
            NodoArista* actual = cabeza;
            NodoArista* previo = nullptr;
            while (actual != nullptr) {
                if (actual->indice_destino == dest) {
                    if (previo == nullptr) cabeza = actual->siguiente;
                    else previo->siguiente = actual->siguiente;
                    delete actual;
                    return true;
                }
                previo = actual;
                actual = actual->siguiente;
            }
            return false;
        };

        bool borrado = borrar_nodo(cabezas[u], v);
        if (!es_dirigido && borrado) {
            borrar_nodo(cabezas[v], u);
        }
        return borrado;
    }

    bool eliminar_vertice(const T& vertice) {
        int u = buscar_indice(vertice);
        if (u == -1) return false;

        NodoArista* actual = cabezas[u];
        while (actual != nullptr) {
            NodoArista* aux = actual;
            actual = actual->siguiente;
            delete aux;
        }

        for (int i = u; i < num_vertices - 1; ++i) {
            cabezas[i] = cabezas[i + 1];
            vertices[i] = vertices[i + 1];
        }
        cabezas[num_vertices - 1] = nullptr;
        num_vertices--;

        for (int i = 0; i < num_vertices; ++i) {
            NodoArista* curr = cabezas[i];
            NodoArista* prev = nullptr;

            while (curr != nullptr) {
                if (curr->indice_destino == u) {
                    NodoArista* aux = curr;
                    if (prev == nullptr) cabezas[i] = curr->siguiente;
                    else prev->siguiente = curr->siguiente;
                    curr = curr->siguiente;
                    delete aux;
                } else {
                    if (curr->indice_destino > u) {
                        curr->indice_destino--;
                    }
                    prev = curr;
                    curr = curr->siguiente;
                }
            }
        }
        return true;
    }

    // Redimensionar memoria
    void redimensionar(int nueva_capacidad) {
        if (nueva_capacidad <= capacidad_maxima) return;

        T* nuevos_vertices = new T[nueva_capacidad];
        NodoArista** nuevas_cabezas = new NodoArista*[nueva_capacidad];

        for (int i = 0; i < nueva_capacidad; ++i) {
            if (i < num_vertices) {
                nuevos_vertices[i] = vertices[i];
                nuevas_cabezas[i] = cabezas[i];
            } else {
                nuevas_cabezas[i] = nullptr;
            }
        }

        delete[] vertices;
        delete[] cabezas;

        vertices = nuevos_vertices;
        cabezas = nuevas_cabezas;
        capacidad_maxima = nueva_capacidad;
    }

    // Retorno de vecinos
    T* obtener_vecinos(const T& vertice, int& cantidad) const {
        cantidad = 0;
        int u = buscar_indice(vertice);
        if (u == -1) return nullptr;

        NodoArista* actual = cabezas[u];
        while (actual != nullptr) {
            cantidad++;
            actual = actual->siguiente;
        }

        if (cantidad == 0) return nullptr;

        T* vecinos = new T[cantidad];
        actual = cabezas[u];
        int idx = 0;
        while (actual != nullptr) {
            vecinos[idx++] = vertices[actual->indice_destino];
            actual = actual->siguiente;
        }
        return vecinos;
    }

    // Algoritmo de prim
    void prim(const T& inicio) const {
        int u_start = buscar_indice(inicio);
        if (u_start == -1) {
            std::cout << "[ERROR] Vertice de inicio no encontrado.\n";
            return;
        }

        const int INF = 1e9;
        int* llave = new int[num_vertices];
        bool* incluido_mst = new bool[num_vertices];
        int* padre = new int[num_vertices];

        for (int i = 0; i < num_vertices; ++i) {
            llave[i] = INF;
            incluido_mst[i] = false;
            padre[i] = -1;
        }

        llave[u_start] = 0;

        for (int count = 0; count < num_vertices - 1; ++count) {
            int min_key = INF;
            int u = -1;

            for (int v = 0; v < num_vertices; ++v) {
                if (!incluido_mst[v] && llave[v] < min_key) {
                    min_key = llave[v];
                    u = v;
                }
            }

            if (u == -1) break;
            incluido_mst[u] = true;

            NodoArista* actual = cabezas[u];
            while (actual != nullptr) {
                int v = actual->indice_destino;
                int peso = actual->peso;

                if (!incluido_mst[v] && peso < llave[v]) {
                    padre[v] = u;
                    llave[v] = peso;
                }
                actual = actual->siguiente;
            }
        }

        std::cout << "\n=== Arbol de Expansion Minima (Prim - Lista) desde [" << inicio << "] ===\n";
        int peso_total = 0;
        for (int i = 0; i < num_vertices; ++i) {
            if (padre[i] != -1) {
                std::cout << vertices[padre[i]] << " - " << vertices[i] << " (peso: " << llave[i] << ")\n";
                peso_total += llave[i];
            }
        }
        std::cout << "Peso total del MST: " << peso_total << "\n";

        delete[] llave;
        delete[] incluido_mst;
        delete[] padre;
    }
};

#endif