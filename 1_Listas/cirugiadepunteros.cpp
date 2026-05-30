/*Escribe una función para eliminar en una posición 'N' en tu Lista Doblemente Enlazada,
 manejando los casos en que 'N' sea la cabeza, la cola, o un nodo en todo el medio.
*/

#include <iostream>
#include "listas.h"
using namespace std;
template <typename T>
void eliminarEnPosicion(ListaDobleEnlazada<T>& lista, int n) {
    if (n < 0 || lista.head == nullptr) return;

    Nododoble<T>* actual = lista.head;
    for (int i = 0; i < n && actual != nullptr; i++) {
        actual = actual->getSiguiente();
    }

    if (actual == nullptr) return;

    // Caso 1: Eliminar la cabeza
    if (actual == lista.head) {
        lista.head = actual->getSiguiente();
        if (lista.head != nullptr) {
            lista.head->setAnterior(nullptr);
        } else {
            lista.tail = nullptr;
        }
    }
    // Caso 2: Eliminar la cola
    else if (actual == lista.tail) {
        lista.tail = actual->getAnterior();
        lista.tail->setSiguiente(nullptr);
    }
    // Caso 3: Eliminar un nodo en el medio
    else {
        actual->getAnterior()->setSiguiente(actual->getSiguiente());
        actual->getSiguiente()->setAnterior(actual->getAnterior());
    }
    delete actual;
};
template <typename T>
void swap_nodes(ListaDobleEnlazada<T>& lista, int pos_X, int pos_Y){
    if(pos_X < 0 || pos_Y < 0 || lista.head == nullptr) return;
    if(pos_X == pos_Y) return; // No hay nada que intercambiar

    Nododoble<T>* nodo_X = lista.head;
    for(int i = 0; i < pos_X && nodo_X != nullptr; i++){
        nodo_X = nodo_X->getSiguiente();
    }

    Nododoble<T>* nodo_Y = lista.head;
    for(int i = 0; i < pos_Y && nodo_Y != nullptr; i++){
        nodo_Y = nodo_Y->getSiguiente();
    }

    if(nodo_X == nullptr || nodo_Y == nullptr || nodo_X == nodo_Y) return;

    // PRE-PROCESAMIENTO: Queremos que X siempre sea el nodo que está más a la izquierda.
    if(pos_X > pos_Y) {
        swap(nodo_X, nodo_Y);
        // Si usaste variables temporales X e Y, ahora estarán ordenadas.
    }

    // Guardamos los vecinos originales para evitar perder referencias en el proceso
    Nododoble<T>* antX = nodo_X->getAnterior();
    Nododoble<T>* sigX = nodo_X->getSiguiente();
    Nododoble<T>* antY = nodo_Y->getAnterior();
    Nododoble<T>* sigY = nodo_Y->getSiguiente();

    // ======= CASO 1: NODOS ADYACENTES =======
    if (nodo_X->getSiguiente() == nodo_Y) {
        // Asumiendo que previamente declaraste:
        // Nododoble<T>* antX = nodo_X->getAnterior();
        // Nododoble<T>* sigY = nodo_Y->getSiguiente();

        // La lista es: [antX] <-> X <-> Y <-> [sigY]
        // Queremos que sea: [antX] <-> Y <-> X <-> [sigY]
        
        // 1. Conecta X con su nuevo entorno
        // (X apunta a Y como anterior, y a sigY como siguiente)
        nodo_X->setAnterior(nodo_Y);
        nodo_X->setSiguiente(sigY);
        
        // 2. Conecta Y con su nuevo entorno
        // (Y apunta a antX como anterior, y a X como siguiente)
        nodo_Y->setAnterior(antX);
        nodo_Y->setSiguiente(nodo_X);
        
        // 3. Conecta antX con Y (OJO: verifica si antX era null para actualizar head)
        if (antX != nullptr) {
            antX->setSiguiente(nodo_Y);
        } else {
            lista.head = nodo_Y;
        }

        // 4. Conecta sigY con X (OJO: verifica si sigY era null para actualizar tail)
        if (sigY != nullptr) {
            sigY->setAnterior(nodo_X);
        } else {
            // Si tu clase no implementa 'tail', puedes omitir esta línea
            lista.tail = nodo_X; 
        }
    }
    // ======= CASO 2: NODOS SEPARADOS =======
    else {
        // Tu código exitoso aquí
        // 1.A: Vecino anterior de X
        if (antX != nullptr) {
            antX->setSiguiente(nodo_Y);
        } else {
            lista.head = nodo_Y; // X era la cabeza
        }

    // 1.B: Vecino siguiente de X
    if (sigX != nullptr) {
        sigX->setAnterior(nodo_Y);
    } else {
        lista.tail = nodo_Y; // Suponiendo que tu clase tiene tail
    }

    // 1.C: Vecino anterior de Y
    if (antY != nullptr) {
        antY->setSiguiente(nodo_X);
    } else {
        lista.head = nodo_X; // Y era la cabeza
    }

    // 1.D: Vecino siguiente de Y
    if (sigY != nullptr) {
        sigY->setAnterior(nodo_X);
    } else {
        lista.tail = nodo_X;
    }
    
    
    // PASO 2: Intercambiar "Hacia Afuera" (Los punteros 'siguiente' y 'anterior' que contienen X e Y)
    // Hay que hacer que nodo_X termine apuntando a los antiguos vecinos de Y, y nodo_Y a los antiguos de X.
    
    Nododoble<T>* temp_siguiente = nodo_X->getSiguiente();
    Nododoble<T>* temp_anterior  = nodo_X->getAnterior();

    // 2.A: Actualiza el 'siguiente' y 'anterior' de nodo_X con los de nodo_Y
    // Ahora X cree que sus vecinos son los que antes rodeaban a Y
    nodo_X->setSiguiente(nodo_Y->getSiguiente());
    nodo_X->setAnterior(nodo_Y->getAnterior());

    // 2.B: Actualiza el 'siguiente' y 'anterior' de nodo_Y con los temporales de X
    // Ahora Y cree que sus vecinos son los que antes rodeaban a X
    nodo_Y->setSiguiente(temp_siguiente);
    nodo_Y->setAnterior(temp_anterior);
}
}


int main() {
    ListaDobleEnlazada<int> lista;
    lista.agregar(10);
    lista.agregar(20);
    lista.agregar(30);
    lista.agregar(40);
    lista.agregar(50);

    cout << "Lista antes de eliminar: ";
    lista.imprimir();
    
    swap_nodes(lista, 0, 1); // Intercambiar nodos en posiciones 0 y 1
    cout << "Lista despues de intercambiar nodos: ";
    lista.imprimir();

    swap_nodes(lista, 1, 2); // Intercambiar nodos en posiciones 1 y 2
    cout << "Lista despues de intercambiar nodos: ";
    lista.imprimir();

    eliminarEnPosicion(lista, 0); // Eliminar la cabeza
    cout << "Lista despues de eliminar la cabeza: ";
    lista.imprimir();

    eliminarEnPosicion(lista, 2); // Eliminar un nodo en el medio
    cout << "Lista despues de eliminar un nodo en el medio: ";
    lista.imprimir();

    eliminarEnPosicion(lista, 1); // Eliminar la cola
    cout << "Lista despues de eliminar la cola: ";
    lista.imprimir();

    return 0;
}