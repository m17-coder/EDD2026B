/*Diseña las clases NodoSimple<T> y NodoDoble<T>, 
asegurándote de encapsular correctamente sus atributos.
 Luego, diseña las clases gestoras para:
Lista Simplemente Enlazada.
Lista Doblemente Enlazada.
Lista Circular Simple.
Lista Circular Doblemente Enlazada.*/

#include <iostream>
using namespace std;

template <typename T>
class NodoSimple{
    private:
        T dato;
        NodoSimple<T>* siguiente;
    public:
        NodoSimple(T valor){
            dato = valor;
            siguiente = nullptr;
        }
        T getDato(){
            return dato;
        }
        NodoSimple<T>* getSiguiente(){
            return siguiente;
        }
        void setSiguiente(NodoSimple<T>* nodo){
            siguiente = nodo;
        }
};

template <typename T>
class Nododoble{
    private:
        T dato;
        Nododoble<T>* siguiente;
        Nododoble<T>* anterior;
    public:
        Nododoble(T valor){
            dato = valor;
            siguiente = nullptr;
            anterior = nullptr;
        }
        T getDato(){
            return dato;
        }
        Nododoble<T>* getSiguiente(){
            return siguiente;
        }
        Nododoble<T>* getAnterior(){
            return anterior;
        }
        void setSiguiente(Nododoble<T>* nodo){
            siguiente = nodo;
        }
        void setAnterior(Nododoble<T>* nodo){
            anterior = nodo;
        }
};
template <typename T>
class ListaEnlazada{
    private:
        NodoSimple<T>* head;
    public:
        ListaEnlazada(){
            head = nullptr;
        }
        void agregar(T valor){
            NodoSimple<T>* nuevoNodo = new NodoSimple<T>(valor);
            if(head == nullptr){
                head = nuevoNodo;
            } else {
                NodoSimple<T>* actual = head;
                while(actual->getSiguiente() != nullptr){
                    actual = actual->getSiguiente();
                }
                actual->setSiguiente(nuevoNodo);
            }
        }
        void imprimir(){
            NodoSimple<T>* actual = head;
            while(actual != nullptr){
                cout << actual->getDato() << " ";
                actual = actual->getSiguiente();
            }
            cout << endl;
        }
        ~ListaEnlazada(){
            NodoSimple<T>* actual = head;
            while(actual != nullptr){
                NodoSimple<T>* temp = actual;
                actual = actual->getSiguiente();
                delete temp;
            }
        }
};
template <typename T>
class ListaDobleEnlazada{
    private:
        Nododoble<T>* head;
        Nododoble<T>* tail;
    public:
        ListaDobleEnlazada(){
            head = nullptr;
            tail = nullptr;
        }
        void agregar(T valor){
            Nododoble<T>* nuevoNodo = new Nododoble<T>(valor);
            if(head == nullptr){
                head = nuevoNodo;
                tail = nuevoNodo;
            } else {
                tail->setSiguiente(nuevoNodo);
                nuevoNodo->setAnterior(tail);
                tail = nuevoNodo;
            }
        }
        void imprimir(){
            Nododoble<T>* actual = head;
            while(actual != nullptr){
                cout << actual->getDato() << " ";
                actual = actual->getSiguiente();
            }
            cout << endl;
        }
        ~ListaDobleEnlazada(){
            Nododoble<T>* actual = head;
            while(actual != nullptr){
                Nododoble<T>* temp = actual;
                actual = actual->getSiguiente();
                delete temp;
            }
        }
};
template <typename T>
class ListaCircularSimple{
    private:
        NodoSimple<T>* head;
        NodoSimple<T>* tail;
    public:
        ListaCircularSimple(){
            head = nullptr;
            tail = nullptr;
        }
        void agregar(T valor){
            NodoSimple<T>* nuevoNodo = new NodoSimple<T>(valor);
            if(head == nullptr){
                head = nuevoNodo;
                tail = nuevoNodo;
                head->setSiguiente(head);
            } else {
                tail->setSiguiente(nuevoNodo);
                nuevoNodo->setSiguiente(head);
                tail = nuevoNodo;
            }
        }
        void imprimir(){
            if(head == nullptr) return;
            NodoSimple<T>* actual = head;
            do {
                cout << actual->getDato() << " ";
                actual = actual->getSiguiente();
            } while(actual != head);
            cout << endl;
        }
        ~ListaCircularSimple(){
            if(head == nullptr) return;
            
            // EL TRUCO MAGISTRAL: Romper el círculo.
            // Al hacer que el tail apunte a nullptr, la lista circular
            // se convierte lógicamente en una lista lineal normal.
            tail->setSiguiente(nullptr); 
            
            NodoSimple<T>* actual = head;
            while(actual != nullptr){
                NodoSimple<T>* temp = actual;
                actual = actual->getSiguiente();
                delete temp;
            }
        }
};
template <typename T>
class ListaCircularDoble{
    private:
        Nododoble<T>* head;
        Nododoble<T>* tail;
    public:
        ListaCircularDoble(){
            head = nullptr;
            tail = nullptr;
        }
        void agregar(T valor){
            Nododoble<T>* nuevoNodo = new Nododoble<T>(valor);
            if(head == nullptr){
                head = nuevoNodo;
                tail = nuevoNodo;
                head->setSiguiente(head);
                head->setAnterior(head);
                tail->setSiguiente(head);
                tail->setAnterior(head);
            } else {
                tail->setSiguiente(nuevoNodo);
                nuevoNodo->setAnterior(tail);
                nuevoNodo->setSiguiente(head);
                head->setAnterior(nuevoNodo);
                tail = nuevoNodo;
            }
        }
        void imprimir(){
            if(head == nullptr) return;
            Nododoble<T>* actual = head;
            do {
                cout << actual->getDato() << " ";
                actual = actual->getSiguiente();
            } while(actual != head);
            cout << endl;
        }
        ~ListaCircularDoble(){
            if(head == nullptr) return;
            
            // Rompemos el círculo aquí también.
            tail->setSiguiente(nullptr); 
            
            Nododoble<T>* actual = head;
            while(actual != nullptr){
                Nododoble<T>* temp = actual;
                actual = actual->getSiguiente();
                delete temp;
            }
        }
};