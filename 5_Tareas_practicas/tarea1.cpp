/*programar una funcion que evalue que no exista
un bucle dentro de una lista doble enlazada de nodos
*/
#include <iostream>
using namespace std;
template <typename T>
struct Nodo{
    T dato;
    Nodo *otronodo;
    Nodo *anterior;
};

template <typename P>
Nodo<P>* conectarnodos(Nodo<P>* header, Nodo<P>* nuevo_nodo){
    // Validamos el nodo "anterior" y si ya tiene conexiones para evitar un bucle
    if (nuevo_nodo->anterior != nullptr || nuevo_nodo->otronodo != nullptr) {
        cout << "Validacion: El nodo a insertar ya tiene enlaces previos o siguientes." << endl;
        cout << "Se omitio la conexion para evitar un bucle." << endl;
        return header;
    }

    // Si la cadena está vacía, el nuevo nodo es el primero
    if(header == nullptr){
        header = nuevo_nodo;
        header->anterior = nullptr; // Aseguramos inicializar anterior
    } else {
        // Si no, recorremos la cadena hasta llegar al último nodo actual
        Nodo<P>* actual = header;
        while(actual->otronodo != nullptr){
            // Verificacion extra: que el nodo no este ya en la cadena
            if(actual == nuevo_nodo) {
                cout << "Validacion: El nodo ya se encuentra en la lista." << endl;
                return header;
            }
            actual = actual->otronodo;
        }
        
        if(actual == nuevo_nodo) {
             cout << "Validacion: El nodo ya se encuentra en la lista." << endl;
             return header;
        }

        // Conectamos el nuevo nodo al final
        actual->otronodo = nuevo_nodo;
        nuevo_nodo->anterior = actual; // Se crea el enlace doble
    }
    return header;
}

bool verificarbucle(Nodo<int>* header, Nodo<int>* tail){
    Nodo<int>* lento = header;
    Nodo<int>* rapido = header;
    
    Nodo <int>* ultimolento = tail;
    Nodo <int>* ultimorapido = tail;
    while(rapido != nullptr && rapido->otronodo != nullptr){
        lento = lento->otronodo;
        rapido = rapido->otronodo->otronodo;
    
        if(lento == rapido){
            cout << "El bucle se encuentra en la lista desde adelante hacia atras" << endl;
            return true;
        }
        }
            while(ultimorapido != nullptr && ultimorapido->anterior != nullptr){
                ultimolento = ultimolento->anterior;
                ultimorapido = ultimorapido->anterior->anterior;
                
                if (ultimolento == ultimorapido){
                    cout << "El bucle se encuentra en la lista desde atras hacia adelante" << endl;
                    return true;
                }
            }
            return false;
        
}



int main(){
    Nodo <int>* n1 = new Nodo<int>();
    Nodo <int>* n2 = new Nodo<int>();
    n1->otronodo = nullptr;
    n1->anterior = nullptr;
    n2->otronodo = nullptr;
    n2->anterior = nullptr;
    
    cout<< "ingrese dato1:"<< endl;
    cin>> n1->dato;
    cout<< "ingrese dato2:"<< endl;
    cin>> n2->dato;
    
    Nodo <int>* header = nullptr;
    header = conectarnodos<int>(header, n1);
    header = conectarnodos<int>(header, n2);
    
    cout << "Head vale:" << header << endl;
    cout << "Siguiente de n1:" << n1->otronodo << " (deberia ser n2)" << endl;
    cout << "Anterior de n2:" << n2->anterior << " (deberia ser n1)" << endl;
    
    Nodo <int>* n3 = new Nodo<int>();
    n3->otronodo = nullptr;
    n3->anterior = nullptr;
    cout << "ingrese dato3:" << endl;
    cin >> n3->dato;
    header = conectarnodos<int>(header, n3);
    
    Nodo <int>* n4 = new Nodo<int>();
    n4->otronodo = nullptr;
    n4->anterior = nullptr;
    cout << "ingrese dato4:" << endl;
    cin >> n4->dato;
    header = conectarnodos<int>(header, n4);
    n1->anterior = nullptr;
    n2->anterior = n1;
    n3->anterior = n2;
    // Esto crea un bucle hacia atras entre n2, n3 y n4
    n4->anterior = n3;
    n2->anterior = n4; 
    Nodo<int>* tail = n4;
    cout << "Head vale:" << header << endl;
    cout << "Siguiente de n2:" << n2->otronodo << " (deberia ser n3)" << endl;
    cout << "Siguiente de n3:" << n3->otronodo << " (deberia ser n4)" << endl;
    cout << "Siguiente de n4:" << n4->otronodo << " (deberia ser 0/null)" << endl;
    
    if(verificarbucle(header, tail)){
        cout << "Se encontro un bucle en la lista." << endl;
    } else {
        cout << "No se encontro un bucle en la lista." << endl;
    }
    
    return 0;
}
