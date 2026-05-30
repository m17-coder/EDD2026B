#include <iostream>
#include "listas.h"

using namespace std;

template <typename T>
class CacheLRU {
private:
    int capacidadMaxima;
    int tamanoActual;
    ListaDobleEnlazada<T> lista; // Contenedor del caché

public:
    CacheLRU(int capacidad) {
        capacidadMaxima = capacidad;
        tamanoActual = 0;
    }

    // Método para simular el uso o acceso a un dato
    void usar(T dato) {
        for (Nododoble<T>* actual = lista.head; actual != nullptr; actual = actual->getSiguiente()) {
            if (actual->getDato() == dato) {
                // Cache Hit: Mover este nodo al frente (head)
                if (actual != lista.head) {
                    // Desconectar el nodo de su posición actual
                    if (actual->getAnterior() != nullptr) {
                        actual->getAnterior()->setSiguiente(actual->getSiguiente());
                    }
                    if (actual->getSiguiente() != nullptr) {
                        actual->getSiguiente()->setAnterior(actual->getAnterior());
                    }
                    // Si el nodo es la cola, actualizar la cola
                    if (actual == lista.tail) {
                        lista.tail = actual->getAnterior();
                    }
                    // Conectar el nodo al frente
                    actual->setSiguiente(lista.head);
                    actual->setAnterior(nullptr);
                    if (lista.head != nullptr) {
                        lista.head->setAnterior(actual);
                    }
                    lista.head = actual;
                }
                return; // Salir después de manejar el cache hit
            }
        }
        
        // 1. CONDICIÓN DE BÚSQUEDA:
        // Recorre la lista para ver si el "dato" ya existe en el caché.
        
        // 2. SI EL DATO YA EXISTE (Cache Hit):
        // a) Si el dato ya es la cabeza (head), no haces nada.
        // b) Si el dato está en otra posición (incluso la cola), tienes que hacer CIRUGÍA.
        //    Desconéctalo de sus vecinos usando la lógica que aprendiste.
        //    Vuelve a conectarlo al principio de la lista (como nuevo head).
        //    (No olvides actualizar 'tail' si resulta que el dato que moviste era la cola original).
        
        // 3. SI EL DATO NO EXISTE (Cache Miss):
        // a) Usa la lógica normal de instanciar un nuevo NodoDoble y colocarlo como 'head'.
        // b) Incrementa 'tamanoActual'.
        // c) Si 'tamanoActual' superó 'capacidadMaxima':
        //    Debes "evictar" (borrar) el último nodo (el de la cola).
        //    Usa pop_back (desconecta el tail, actualiza el nuevo tail y delete).
        //    Disminuye 'tamanoActual'.
        Nododoble<T>* nuevoNodo = new Nododoble<T>(dato);
        nuevoNodo->setSiguiente(lista.head);
        if (lista.head != nullptr) {
            lista.head->setAnterior(nuevoNodo);
        }
        lista.head = nuevoNodo;
        lista.tail = (lista.tail == nullptr) ? nuevoNodo : lista.tail; // Si la lista estaba vacía, el nuevo nodo es también la cola
        tamanoActual++;

        if (tamanoActual > capacidadMaxima) {
            // Evictar el último nodo (el de la cola)
            Nododoble<T>* tail = lista.tail;
            if (tail != nullptr) {
                lista.tail = tail->getAnterior();
                if (lista.tail != nullptr) {
                    lista.tail->setSiguiente(nullptr);
                }
                delete tail;
                tamanoActual--;
            }
        }

    }

    void imprimirCache() {
        cout << "Cache actual (Mas reciente -> Menos reciente): ";
        lista.imprimir();
    }
};

int main() {
    // Creamos un caché que solo puede recordar 3 elementos a la vez
    CacheLRU<string> navegador(3);

    navegador.usar("google.com");
    navegador.usar("youtube.com");
    navegador.usar("github.com");
    navegador.imprimirCache(); // Debería ser: github, youtube, google

    // Accedemos a google.com (Cache Hit). Debería moverse al frente.
    cout << "\n-> Usuario abre google.com de nuevo\n";
    navegador.usar("google.com");
    navegador.imprimirCache(); // Debería ser: google, github, youtube

    // Accedemos a un sitio nuevo (Cache Miss). 
    // Como el caché es de tamaño 3, "youtube.com" (el menos usado y actual tail) deberia ser borrado.
    cout << "\n-> Usuario abre stackoverflow.com (Sobrepasa capacidad)\n";
    navegador.usar("stackoverflow.com");
    navegador.imprimirCache(); // Debería ser: stackoverflow, google, github

    return 0;
}
