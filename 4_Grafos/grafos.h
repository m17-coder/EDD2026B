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
};

#endif