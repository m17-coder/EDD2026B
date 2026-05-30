/*Historia: Flavio Josefo y N soldados están en un círculo cerrado. 
Deciden ejecutar a cada K-ésima persona hasta que solo quede uno*/

#include <iostream>
#include "listas.h"

using namespace std;

// Función para resolver el problema de Josephus
// N: Número total de soldados (1 a N)
// K: Se elimina a la K-ésima persona contando en círculo
int josephus(int N, int K) {
    if (N <= 0 || K <= 0) return -1;
    if (N == 1) return 1;

    // 1. Crear el círculo usando nuestra clase ListaCircularSimple
    ListaCircularSimple<int> circulo;
    for (int i = 1; i <= N; ++i) {
        circulo.agregar(i);
    }

    // 2. Establecer el punto de inicio
    NodoSimple<int>* actual = circulo.head;
    
    // Necesitamos llevar un rastro del 'anterior' porque en la Lista Simple
    // para borrar el 'actual' necesitamos que su 'anterior' apunte a su 'siguiente'.
    // Al principio, el anterior a 'head' es el 'tail'.
    NodoSimple<int>* previo = circulo.tail;

    // --- AQUÍ EMPIEZA TU MISIÓN ---
    // Mientras haya más de 1 soldado en el círculo...
    // Pista: ¿Cómo sabes que queda 1 solo? Cuando circulo.head == circulo.tail 
    
    while (circulo.head != circulo.tail) {
        
        // a) Avanza K-1 pasos (porque ya estás posicionado en el paso 1).
        // Recuerda avanzar tanto 'actual' como 'previo' juntos (con un bucle for).
        
        for(int i = 1; i < K; ++i) {
            previo = actual;
            actual = actual->getSiguiente();
        }
        // b) ¡Ejecuta al soldado!
        // El soldado a morir en este turno es 'actual'.
        // 1. Imprime quién muere para seguir el rastro: cout << "Muere: " << actual->getDato() << endl;
        // 2. Conecta el puente: el 'previo' debe saltar y apuntar al siguiente de 'actual'.
        // 3. Maneja los casos límite: Si el muerto era el 'head', actualiza circulo.head al siguiente. 
        //    Si era el 'tail', actualiza circulo.tail al 'previo'.
        // 4. Libera la memoria (delete) del actual muerto.
        // 5. El nuevo 'actual' del próximo conteo, será el de la posición siguiente al muerto.
        
        cout << "Muere: " << actual->getDato() << endl;
        previo->setSiguiente(actual->getSiguiente());
        if (actual == circulo.head) {
            circulo.head = actual->getSiguiente();
        }
        if (actual == circulo.tail) {
            circulo.tail = previo;
        }
        NodoSimple<int>* temp = actual;
        actual = actual->getSiguiente();
        delete temp;
    }

    // Cuando termina el bucle, solo queda 1 nodo. (El superviviente)
    int sobreviviente = circulo.head->getDato();
    
    // Limpiamos el nodo superviviente de forma manual para evitar que  
    // el destructor implícito de la lista falle al salir de la función
    delete circulo.head;
    circulo.head = nullptr;
    circulo.tail = nullptr;

    return sobreviviente;
}

int main() {
    int N = 7; // Instancias 7 Soldados
    int K = 3; // La espada cae cada 3 personas
    
    cout << "Simulacion de Josephus (N=" << N << ", K=" << K << ")\n";
    cout << "--------------------------------------\n";
    
    int superviviente = josephus(N, K);
    
    cout << "--------------------------------------\n";
    cout << "El superviviente libre es el soldado numero: " << superviviente << endl;

    return 0;
}