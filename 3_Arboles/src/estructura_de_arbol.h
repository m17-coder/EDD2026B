#ifndef ARBOL_LCRS_H
#define ARBOL_LCRS_H

#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct Nodo_arbol {
    T dato;
    Nodo_arbol<T>* izq; // Primer hijo directo (Sucesor)
    Nodo_arbol<T>* der; // Siguiente hermano (Compañero sucesor)

    Nodo_arbol(T d) {
        dato = d;
        izq = nullptr;
        der = nullptr;
    }
};

template <typename T>
class Arbol {
private:
    Nodo_arbol<T>* root;

    // Liberación recursiva de memoria
    void liberar(Nodo_arbol<T>* actual) {
        if (actual == nullptr) return;
        liberar(actual->izq);
        liberar(actual->der);
        delete actual;
    }

    // Impresión en horizontal
    void imprimirInterno(Nodo_arbol<T>* actual, string prefijo, bool esIzquierdo) {
        if (actual == nullptr) return;

        // Procesar subárbol derecho (hermanos/ramas superiores en pantalla)
        imprimirInterno(actual->der, prefijo + (esIzquierdo ? "│   " : "    "), false);

        // Imprimir nodo actual. Asumimos que T tiene un método o sobrecarga para mostrarse.
        cout << prefijo;
        cout << (esIzquierdo ? "└── " : "┌── ");
        imprimirDato(actual->dato);

        // Procesar subárbol izquierdo (hijos/ramas inferiores en pantalla)
        imprimirInterno(actual->izq, prefijo + (esIzquierdo ? "    " : "│   "), true);
    }

    // Función auxiliar para imprimir los datos del nodo
    void imprimirDato(const T& dato) {
        // Imprime el nombre y apellido.
        cout << dato.name << " " << dato.last_name;
        if (dato.is_boss) cout << " [CAPO]";
        if (dato.in_jail) cout << " (PRISIÓN)";
        if (dato.is_dead) cout << " (X)";
        cout << "\n";
    }

public:
    Arbol() : root(nullptr) {}
    ~Arbol() { liberar(root); }

    Nodo_arbol<T>* getRoot() { return root; }
    void setRoot(Nodo_arbol<T>* nuevoRoot) { root = nuevoRoot; }

    // Función para buscar un nodo por ID
    Nodo_arbol<T>* buscarPorId(Nodo_arbol<T>* actual, int id) {
        if (actual == nullptr) return nullptr;
        if (actual->dato.id == id) return actual;

        Nodo_arbol<T>* encontrado = buscarPorId(actual->izq, id);
        if (encontrado != nullptr) return encontrado;

        return buscarPorId(actual->der, id);
    }

    // Inserción basada estrictamente en la jerarquía id_boss
    void insertarEstructural(T miembro) {
        Nodo_arbol<T>* nuevo = new Nodo_arbol<T>(miembro);
        if (root == nullptr) {
            root = nuevo;
            return;
        }

        Nodo_arbol<T>* jefe = buscarPorId(root, miembro.id_boss);
        if (jefe == nullptr) {
            // Si no encuentra al jefe (raíces huérfanas), lo añade como hermano de la raíz
            Nodo_arbol<T>* temp = root;
            while (temp->der != nullptr) temp = temp->der;
            temp->der = nuevo;
            return;
        }

        if (jefe->izq == nullptr) {
            jefe->izq = nuevo; // Primer subordinado
        } else {
            Nodo_arbol<T>* hermano = jefe->izq;
            while (hermano->der != nullptr) {
                hermano = hermano->der;
            }
            hermano->der = nuevo; // Siguiente hermano en la cadena
        }
    }

    void Mostrar_arbol() {
        imprimirInterno(root, "", true);
    }
};

#endif