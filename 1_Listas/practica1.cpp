/*crea una plantilla +para un tipo de dato nodo (estructura o class), programar una funcion que conecte nodos
devuelva siempre el puntero al primer nodo de la cadena de nodos
*/

#include <iostream>

using namespace std;

template <typename T>
struct Nodo{
    T dato;
    Nodo<T>* otronodo;
};

template <typename P>
Nodo<P>* conectarnodos(Nodo<P>* header, Nodo<P>* nuevo_nodo){
    
    if(header == nullptr){
        header = nuevo_nodo;
    } else {
        
        Nodo<P>* actual = header;
        while(actual->otronodo != nullptr){
            actual = actual->otronodo;
        }
       
        actual->otronodo = nuevo_nodo;
    }
    
    return header;
}

int main(){
    Nodo <int>* n1 = new Nodo<int>();
    Nodo <int>* n2 = new Nodo<int>();
    n1->otronodo= nullptr;
    n2->otronodo= nullptr;
    cout<< "ingrese dato1:"<< endl;
    cin>> n1-> dato;
    cout<< "ingrese dato2:"<< endl;
    cin>> n2-> dato;
    Nodo <int>* header = nullptr;
    header = conectarnodos<int>(header, n1);
    header = conectarnodos<int>(header, n2);
    
    cout << "Head vale:" << header << endl;
    cout << "Siguiente de n1:" << n1->otronodo << " (deberia ser n2)" << endl;
    
    Nodo <int>* n3 = new Nodo<int>();
    n3->otronodo = nullptr;
    cout << "ingrese dato3:" << endl;
    cin >> n3->dato;
    
    
    header = conectarnodos<int>(header, n3);
    
    cout << "Head vale:" << header << endl;
    cout << "Siguiente de n2:" << n2->otronodo << " (deberia ser n3)" << endl;
    cout << "Siguiente de n3:" << n3->otronodo << " (deberia ser 0/null)" << endl;
    
    return 0;
}