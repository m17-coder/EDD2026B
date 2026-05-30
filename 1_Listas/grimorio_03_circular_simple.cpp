// ==============================================================
// GRIMORIO 03: LISTA CIRCULAR SIMPLE (Con Head y Tail)
// ==============================================================
#include <iostream>
#include "listas.h"
using namespace std;

// 1. REVERSE (Voltear el circulo) - EXTREMADAMENTE SENSIBLE
template<typename T>
void reverse_circular_simple(ListaCircularSimple<T>& lista) {
    if (!lista.head || lista.head == lista.tail) return;

    // La clave en circulares: el "previo" del head, logicamente es el tail
    NodoSimple<T>* prev = lista.tail; 
    NodoSimple<T>* current = lista.head;
    NodoSimple<T>* next = nullptr;
    NodoSimple<T>* old_head = lista.head;

    do {
        next = current->getSiguiente();
        current->setSiguiente(prev);
        prev = current;
        current = next;
    } while (current != old_head); // Nos detenemos al dar la vuelta entera

    lista.tail = lista.head; // El viejo head ahora es el final de la secumencia
    lista.head = prev;       // Y prev es el ultimo que volteamos (el viejo tail)
}

// 2. ELIMINAR POSICION EN CIRCUITO CONSERVANDO LA CIRCULARIDAD
template<typename T>
void eliminar_pos_circular(ListaCircularSimple<T>& lista, int pos) {
    if (!lista.head || pos < 0) return;

    if (pos == 0) { // Eliminar el Head
        NodoSimple<T>* borrar = lista.head;
        if (lista.head == lista.tail) { // Si unicamente habia 1 elemento
            lista.head = nullptr;
            lista.tail = nullptr;
        } else {
            lista.head = lista.head->getSiguiente();
            lista.tail->setSiguiente(lista.head); // Re-anclar la circularidad del tail al nuevo head
        }
        delete borrar;
        return;
    }

    // Buscamos hasta el nodo anterior al que queremos borrar
    NodoSimple<T>* actual = lista.head;
    for (int i = 0; i < pos - 1 && actual->getSiguiente() != lista.head; i++) {
        actual = actual->getSiguiente();
    }

    if (actual->getSiguiente() == lista.head) return; // Dio la vuelta, posicion invalida

    NodoSimple<T>* borrar = actual->getSiguiente();
    actual->setSiguiente(borrar->getSiguiente());
    
    if (borrar == lista.tail) { // CUIDADO: Si decapitas a la cola, el puente (actual) se vuelve la cola
        lista.tail = actual;
    }
    delete borrar;
}

int main() {
    cout << "--- COMPILACION DE GRIMORIO 3: EXITOSA ---" << endl;
    return 0;
}