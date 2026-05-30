//separacion destructiva//

#include <iostream>
#include "listas.h"

using namespace std;

template <typename T>
void split(ListaDobleEnlazada<T>& original, T pivot, ListaDobleEnlazada<T>& listLess, ListaDobleEnlazada<T>& listGreater) {
    Nododoble<T>* current = original.head;
    while (current != nullptr) {
        // 1. Guardar el siguiente inmediato ANTES de desconectar nada
        Nododoble<T>* siguientetemp = current->getSiguiente();
        
        // 2. DESINFECTAR (Aislar puramente el nodo cortando sus lazos)
        current->setSiguiente(nullptr);
        current->setAnterior(nullptr);

        if (current->getDato() < pivot) {
            if (listLess.head == nullptr) {
                listLess.head = current;
                listLess.tail = current;
            } else {
                listLess.tail->setSiguiente(current);
                current->setAnterior(listLess.tail);
                listLess.tail = current;
            }
        } else {
            if (listGreater.head == nullptr) {
                listGreater.head = current;
                listGreater.tail = current;
            } else {
                listGreater.tail->setSiguiente(current);
                current->setAnterior(listGreater.tail);
                listGreater.tail = current;
            }
        }
        current = siguientetemp;
    }
    // Rompemos las conexiones de la lista original para evitar referencias cruzadas.
    original.head = nullptr;
    original.tail = nullptr;
}

template <typename T>
void reverse(ListaDobleEnlazada<T>& lista) {
    Nododoble<T>* current = lista.head;
    Nododoble<T>* temp = nullptr;

    // Intercambiar 'siguiente' y 'anterior' para cada nodo
    while (current != nullptr) {
        temp = current->getAnterior();
        current->setAnterior(current->getSiguiente());
        current->setSiguiente(temp);
        current = current->getAnterior(); // Mover al siguiente nodo (que ahora es el anterior)
    }

    // Intercambiar head y tail
    if (temp != nullptr) {
        lista.tail = lista.head;
        lista.head = temp->getAnterior(); // El nuevo head es el último nodo procesado
    }
}

int main() {
    ListaDobleEnlazada<int> original;
    original.agregar(5);
    original.agregar(3);
    original.agregar(8);
    original.agregar(1);
    original.agregar(7);

    cout << "Lista Original: ";
    original.imprimir();

    reverse(original);
    cout << "invertir lista original: ";
    original.imprimir();

    ListaDobleEnlazada<int> listLess;
    ListaDobleEnlazada<int> listGreater;

    split(original, 4, listLess, listGreater);

    cout << "Lista Menores que 4: ";
    listLess.imprimir();

    cout << "Lista Mayores o iguales a 4: ";
    listGreater.imprimir();

    cout << "Lista Original despues de la separacion: ";
    original.imprimir();
    return 0;
}