#ifndef ARBOL_MIEMBROS_H
#define ARBOL_MIEMBROS_H

#include <iostream>
#include <string>

using namespace std;

struct Miembro {
    int id;
    string name;
    string last_name;
    char gender;
    int age;
    int id_boss;
    bool is_dead;
    bool in_jail;
    bool was_boss;
    bool is_boss;
};

struct NodoMiembro {
    Miembro dato;
    NodoMiembro* izq;
    NodoMiembro* der;

    NodoMiembro(const Miembro& m){
        dato = m;
        izq = nullptr;
        der = nullptr;
    }
};

class ArbolMiembros {
private:
    NodoMiembro* root;

    void liberar(NodoMiembro* actual) {
        if (actual == nullptr) return;
        liberar(actual->izq);
        liberar(actual->der);
        delete actual;
    }

    NodoMiembro* buscarPorId(NodoMiembro* actual, int id) const {
        if (actual == nullptr) return nullptr;
        if (actual->dato.id == id) return actual;

        NodoMiembro* encontrado = buscarPorId(actual->izq, id);
        if (encontrado != nullptr) return encontrado;

        return buscarPorId(actual->der, id);
    }

    NodoMiembro* ultimoHermano(NodoMiembro* actual) const {
        if (actual == nullptr) return nullptr;
        while (actual->der != nullptr) {
            actual = actual->der;
        }
        return actual;
    }

    void imprimirMiembro(const Miembro& miembro) const {
        cout << miembro.id << " - " << miembro.name << " " << miembro.last_name;
        cout << " | sexo: " << miembro.gender;
        cout << " | edad: " << miembro.age;
        cout << " | jefe: " << miembro.id_boss;
        if (miembro.is_boss) cout << " | CAPO";
        if (miembro.was_boss) cout << " | ex jefe";
        if (miembro.in_jail) cout << " | prision";
        if (miembro.is_dead) cout << " | muerto";
        cout << '\n';
    }

    void mostrarInterno(NodoMiembro* actual, string prefijo, bool esIzquierdo) const {
        if (actual == nullptr) return;

        mostrarInterno(actual->der, prefijo + (esIzquierdo ? "│   " : "    "), false);

        cout << prefijo;
        cout << (esIzquierdo ? "└── " : "┌── ");
        imprimirMiembro(actual->dato);

        mostrarInterno(actual->izq, prefijo + (esIzquierdo ? "    " : "│   "), true);
    }

public:
    ArbolMiembros() : root(nullptr) {}

    ~ArbolMiembros() {
        liberar(root);
    }

    NodoMiembro* getRoot() const {
        return root;
    }

    void insertarMiembro(const Miembro& miembro) {
        NodoMiembro* nuevo = new NodoMiembro(miembro);

        if (root == nullptr) {
            root = nuevo;
            return;
        }

        if (buscarPorId(root, miembro.id) != nullptr) {
            delete nuevo;
            cout << "[Aviso] ID duplicado ignorado: " << miembro.id << '\n';
            return;
        }

        if (miembro.id_boss == 0) {
            NodoMiembro* ultimo = ultimoHermano(root);
            ultimo->der = nuevo;
            return;
        }

        NodoMiembro* jefe = buscarPorId(root, miembro.id_boss);
        if (jefe == nullptr) {
            NodoMiembro* ultimo = ultimoHermano(root);
            ultimo->der = nuevo;
            return;
        }

        if (jefe->izq == nullptr) {
            jefe->izq = nuevo;
            return;
        }

        NodoMiembro* ultimoHijo = ultimoHermano(jefe->izq);
        ultimoHijo->der = nuevo;
    }

    bool buscarMiembro(int id, Miembro& encontrado) const {
        NodoMiembro* nodo = buscarPorId(root, id);
        if (nodo == nullptr) return false;
        encontrado = nodo->dato;
        return true;
    }

    void Mostrar_arbol() const {
        if (root == nullptr) {
            cout << "[Arbol vacio]" << '\n';
            return;
        }
        mostrarInterno(root, "", true);
    }
};

#endif