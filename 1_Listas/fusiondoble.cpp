#include <iostream>
#include "listas.h"

using namespace std;

// Función para fusionar list2 al final de list1
// Ambas son Listas Circulares Dobles.
template <typename T>
void fusionarCirculares(ListaCircularDoble<T>& list1, ListaCircularDoble<T>& list2) {
    // CONDICIONES DE SEGURIDAD (Manejo de listas vacías)
    // Si list2 está vacía, no hay nada que fusionar.
    // Si list1 está vacía, list1 se convierte en list2, y list2 queda vacía.
    if (list2.head == nullptr) {
        return; // No hay nada que fusionar
    }
    if (list1.head == nullptr) {
        list1.head = list2.head;
        list1.tail = list2.tail;
        list2.head = nullptr;
        list2.tail = nullptr;
        return;
    }
    // EL GRAN RETO:
    // Almacena referencias temporales.
    // Abre el anillo entre el tail1 y el head1.
    // Abre el anillo entre el tail2 y el head2.
    // Conecta el tail1 con el head2 (ida y vuelta).
    // Conecta el tail2 con el head1 (ida y vuelta).
    // Actualiza el tail general en list1.
    // Desvincula/vacía list2 lógicamente.
    Nododoble<T>* tail1 = list1.tail;
    Nododoble<T>* head1 = list1.head;
    Nododoble<T>* tail2 = list2.tail;
    Nododoble<T>* head2 = list2.head;
    // Rompemos los anillos para facilitar la conexión.
    tail1->setSiguiente(nullptr);
    head1->setAnterior(nullptr);
    tail2->setSiguiente(nullptr);
    head2->setAnterior(nullptr);
    // Conectamos los extremos de ambas listas.
    tail1->setSiguiente(head2);
    head2->setAnterior(tail1);
    tail2->setSiguiente(head1);
    head1->setAnterior(tail2);
    // Actualizamos el tail de list1 para que apunte al nuevo último nodo.
    list1.tail = tail2;
    // Vacíamos list2 lógicamente.
    list2.head = nullptr;
    list2.tail = nullptr;
}

int main() {
    ListaCircularDoble<int> anilloA;
    anilloA.agregar(1);
    anilloA.agregar(2);
    anilloA.agregar(3);

    ListaCircularDoble<int> anilloB;
    anilloB.agregar(4);
    anilloB.agregar(5);
    anilloB.agregar(6);

    cout << "Anillo A original: ";
    anilloA.imprimir(); // Esperado: 1 2 3

    cout << "Anillo B original: ";
    anilloB.imprimir(); // Esperado: 4 5 6

    fusionarCirculares(anilloA, anilloB);

    cout << "\nAnillo FUSIONADO (A): ";
    anilloA.imprimir(); // Esperado: 1 2 3 4 5 6
    
    // Y si iterásemos hacia atrás desde el tail de A, debería recorrer a la inversa 
    // y saltar del 1 de nuevo al 6 sin romper la circularidad.
    for (Nododoble<int>* actual = anilloA.tail; actual != nullptr; actual = actual->getAnterior()) {
        cout << actual->getDato() << " ";
        if (actual == anilloA.head) break; // Detenerse después de recorrer todo el anillo
    }
    return 0;
}