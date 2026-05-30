// ==============================================================
// GRIMORIO 01: LISTA SIMPLEMENTE ENLAZADA (Solo puntero head)
// ==============================================================
#include <iostream>
#include "listas.h"
using namespace std;

// 1. REVERSE (Algoritmo de los 3 punteros) - PREGUNTA CLASICA DE EXAMEN
template<typename T>
void reverse_simple(ListaEnlazada<T>& lista) {
    NodoSimple<T>* prev = nullptr;
    NodoSimple<T>* current = lista.head;
    NodoSimple<T>* next = nullptr;

    while (current != nullptr) {
        next = current->getSiguiente(); // 1. Guardar el progreso futuro
        current->setSiguiente(prev);    // 2. Voltear la flecha hacia atras
        prev = current;                 // 3. El actual se vuelve el previo del futuro
        current = next;                 // 4. Avanzar
    }
    lista.head = prev; // El viejo tail (ltimo validado) es el nuevo head
}

// 2. ELIMINAR EN POSICION INTERMEDIA
template<typename T>
void eliminar_pos_simple(ListaEnlazada<T>& lista, int pos) {
    if (!lista.head || pos < 0) return;
    
    // Caso Borde: Eliminar la Cabeza
    if (pos == 0) {
        NodoSimple<T>* borrar = lista.head;
        lista.head = lista.head->getSiguiente();
        delete borrar;
        return;
    }

    // Navegar hasta el N-1
    NodoSimple<T>* actual = lista.head;
    for (int i = 0; i < pos - 1 && actual->getSiguiente() != nullptr; i++) {
        actual = actual->getSiguiente();
    }

    if (actual->getSiguiente() == nullptr) return; // Rango invalido

    // Bypass
    NodoSimple<T>* borrar = actual->getSiguiente();
    actual->setSiguiente(borrar->getSiguiente());
    delete borrar;
}

// 3. SPLIT DESTRUCTIVO (Alta eficiencia en O(1) mutando las clases temporalmente)
template<typename T>
void split_simple(ListaEnlazada<T>& original, T pivot, ListaEnlazada<T>& listLess, ListaEnlazada<T>& listGreater) {
    NodoSimple<T>* current = original.head;
    
    // Simuladores fisicos de Tails locales para no re-recorrer las sublistas por no tener 'tail' oficial
    NodoSimple<T>* tailLess = nullptr;
    NodoSimple<T>* tailGreater = nullptr;

    while (current != nullptr) {
        NodoSimple<T>* sigTemp = current->getSiguiente();
        current->setSiguiente(nullptr); // Desinfeccion

        if (current->getDato() < pivot) {
            if (!listLess.head) {
                listLess.head = current;
                tailLess = current;
            } else {
                tailLess->setSiguiente(current);
                tailLess = current;
            }
        } else {
            if (!listGreater.head) {
                listGreater.head = current;
                tailGreater = current;
            } else {
                tailGreater->setSiguiente(current);
                tailGreater = current;
            }
        }
        current = sigTemp;
    }
    original.head = nullptr; // RIP Lista Original
}

int main() {
    cout << "--- COMPILACION DE GRIMORIO 1: EXITOSA ---" << endl;
    return 0;
}