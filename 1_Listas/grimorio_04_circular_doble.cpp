// =================================================================
// GRIMORIO 04: LISTA CIRCULAR DOBLEMENTE ENLAZADA (La Reina Madre)
// =================================================================
#include <iostream>
#include "listas.h"
using namespace std;

// 1. REVERSE (Intercambio en anillo)
template<typename T>
void reverse_circular_doble(ListaCircularDoble<T>& lista) {
    if (!lista.head || lista.head == lista.tail) return;

    Nododoble<T>* current = lista.head;
    Nododoble<T>* temp = nullptr;
    Nododoble<T>* old_head = lista.head;

    do {
        // Swap intrapersonal de agujas
        temp = current->getAnterior();
        current->setAnterior(current->getSiguiente());
        current->setSiguiente(temp);
        
        // Magia negra: Al invertir el nodo, el "siguiente natural" ahora habita 
        // temporalmente en el puntero 'anterior'. Es contraintuitivo pero asi avanzamos.
        current = current->getAnterior();
    } while (current != old_head);

    lista.tail = lista.head;
    lista.head = temp->getAnterior(); // Conecta al nuevo patron
}

// 2. FUSION (Merge en O(1) de dos anillos)
template <typename T>
void fusionar_circulares_dobles(ListaCircularDoble<T>& list1, ListaCircularDoble<T>& list2) {
    if (list2.head == nullptr) return; 
    if (list1.head == nullptr) {
        list1.head = list2.head;
        list1.tail = list2.tail;
        list2.head = nullptr;
        list2.tail = nullptr;
        return;
    }
    
    // Anotamos limites
    Nododoble<T>* tail1 = list1.tail;
    Nododoble<T>* head1 = list1.head;
    Nododoble<T>* tail2 = list2.tail;
    Nododoble<T>* head2 = list2.head;
    
    // Reconectamos en X cruzando los confines de los anillos viejos.
    // list1 deja de morder su propia cabeza para morder la de list2
    tail1->setSiguiente(head2);
    head2->setAnterior(tail1);
    
    // list2 deja de morder su propia cabeza para morder la de list1 original
    tail2->setSiguiente(head1);
    head1->setAnterior(tail2);
    
    // Ajuste logico
    list1.tail = tail2;
    list2.head = nullptr;
    list2.tail = nullptr;
}

// 3. GHOST SWAP ROTATORIO (El mismo principio de Ghost Swap que hiciste, 
// pero los if/else que protegien de NullPtr aquí nunca ocurrirán salvo si hay un solo nodo,
// por la propia naturaleza circular, facilitándolo muchisimo).
// NOTA: Para examen basico de circular doble, normalmente no evaluan Swap.

int main() {
    cout << "--- COMPILACION DE GRIMORIO 4: EXITOSA ---" << endl;
    return 0;
}