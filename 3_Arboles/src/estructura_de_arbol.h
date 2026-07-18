#ifndef ARBOL_MIEMBROS_H
#define ARBOL_MIEMBROS_H

#include <iostream>
#include <string>

using namespace std;

struct Miembro {
    int id;
    string name;
    string last_name;
    char gender;
    int age;
    int id_boss;
    bool is_dead;
    bool in_jail;
    bool was_boss;
    bool is_boss;
};

struct NodoMiembro {
    Miembro dato;
    NodoMiembro* izq;
    NodoMiembro* der;

    NodoMiembro(const Miembro& m){
        dato = m;
        izq = nullptr;
        der = nullptr;
    }
};

class ArbolMiembros {
private:
    NodoMiembro* root;

    void liberar(NodoMiembro* actual) {
        if (actual == nullptr) return;
        liberar(actual->izq);
        liberar(actual->der);
        delete actual;
    }

    NodoMiembro* buscarPorId(NodoMiembro* actual, int id) const {
        if (actual == nullptr) return nullptr;
        if (actual->dato.id == id) return actual;

        NodoMiembro* encontrado = buscarPorId(actual->izq, id);
        if (encontrado != nullptr) return encontrado;

        return buscarPorId(actual->der, id);
    }

    NodoMiembro* ultimoHermano(NodoMiembro* actual) const {
        if (actual == nullptr) return nullptr;
        while (actual->der != nullptr) {
            actual = actual->der;
        }
        return actual;
    }

    void imprimirMiembro(const Miembro& miembro) const {
        cout << miembro.id << " - " << miembro.name << " " << miembro.last_name;
        cout << " | sexo: " << miembro.gender;
        cout << " | edad: " << miembro.age;
        cout << " | jefe: " << miembro.id_boss;
        if (miembro.is_boss) cout << " | JEFAZO SUPREMO";
        if (miembro.was_boss) cout << " | ex jefe";
        if (miembro.in_jail) cout << " | prision";
        if (miembro.is_dead) cout << " | muerto";
        cout << '\n';
    }

    void mostrarInterno(NodoMiembro* actual, string prefijo, bool esIzquierdo) const {
        if (actual == nullptr) return;

        mostrarInterno(actual->der, prefijo + (esIzquierdo ? "│   " : "    "), false);

        cout << prefijo;
        cout << (esIzquierdo ? "└── " : "┌── ");
        imprimirMiembro(actual->dato);

        mostrarInterno(actual->izq, prefijo + (esIzquierdo ? "    " : "│   "), true);
    }

     void mostrarInternoVivos(NodoMiembro* actual, string prefijo, bool esIzquierdo) const {
        if (actual == nullptr) return;

        // Primero recorremos la rama de los hermanos (derecha) para mantener el formato visual invertido
        mostrarInternoVivos(actual->der, prefijo + (esIzquierdo ? "│   " : "    "), false);

        // EVALUACIÓN PEDAGÓGICA: Solo imprimimos el nodo si el miembro NO está muerto
        if (!actual->dato.is_dead) {
            cout << prefijo;
            cout << (esIzquierdo ? "└── " : "┌── ");
            imprimirMiembro(actual->dato);
        }

        // Finalmente recorremos la rama de los subordinados/hijos (izquierda)
        mostrarInternoVivos(actual->izq, prefijo + (esIzquierdo ? "    " : "│   "), true);
    }

    NodoMiembro* encontrarPadre(NodoMiembro* actual, int idBuscar) const {
        if (actual == nullptr) return nullptr;
        
        // Si el hijo izquierdo directo o alguno de sus hermanos es el que buscamos
        NodoMiembro* hijo = actual->izq;
        while (hijo != nullptr) {
            if (hijo->dato.id == idBuscar) return actual;
            hijo = hijo->der;
        }
        
        // Buscar recursivamente en profundidad
        NodoMiembro* padreIzq = encontrarPadre(actual->izq, idBuscar);
        if (padreIzq != nullptr) return padreIzq;
        
        return encontrarPadre(actual->der, idBuscar);
    }

    // Busca el primer sucesor elegible (Vivo y fuera de prisión) recorriendo solo un subárbol
    NodoMiembro* obtenerPrimeroLibreYVivo(NodoMiembro* actual) const {
        if (actual == nullptr) return nullptr;
        
        // Evaluar el nodo actual
        if (!actual->dato.is_dead && !actual->dato.in_jail && actual->dato.age <= 70) {
            return actual;
        }
        
        // Buscar primero en sus subordinados (hijos)
        NodoMiembro* encontrado = obtenerPrimeroLibreYVivo(actual->izq);
        if (encontrado != nullptr) return encontrado;
        
        // Si no, buscar en sus hermanos
        return obtenerPrimeroLibreYVivo(actual->der);
    }

public:
    ArbolMiembros() : root(nullptr) {}

    ~ArbolMiembros() {
        liberar(root);
    }

    NodoMiembro* getRoot() const {
        return root;
    }

    void insertarMiembro(const Miembro& miembro) {
        NodoMiembro* nuevo = new NodoMiembro(miembro);

        if (root == nullptr) {
            root = nuevo;
            return;
        }

        if (buscarPorId(root, miembro.id) != nullptr) {
            delete nuevo;
            cout << "[Aviso] ID duplicado ignorado: " << miembro.id << '\n';
            return;
        }

        if (miembro.id_boss == 0) {
            NodoMiembro* ultimo = ultimoHermano(root);
            ultimo->der = nuevo;
            return;
        }

        NodoMiembro* jefe = buscarPorId(root, miembro.id_boss);
        if (jefe == nullptr) {
            NodoMiembro* ultimo = ultimoHermano(root);
            ultimo->der = nuevo;
            return;
        }

        if (jefe->izq == nullptr) {
            jefe->izq = nuevo;
            return;
        }

        NodoMiembro* ultimoHijo = ultimoHermano(jefe->izq);
        ultimoHijo->der = nuevo;
    }

    bool buscarMiembro(int id, Miembro& encontrado) const {
        NodoMiembro* nodo = buscarPorId(root, id);
        if (nodo == nullptr) return false;
        encontrado = nodo->dato;
        return true;
    }

    void Mostrar_arbol() const {
        if (root == nullptr) {
            cout << "[Arbol vacio]" << '\n';
            return;
        }
        mostrarInterno(root, "", true);
    }

    void mostrarSoloVIvos() const {
        if (root == nullptr) {
            cout << "[Arbol vacio]" << '\n';
            return;
        }
        mostrarInternoVivos(root, "", true);
    }

    void simularSucesion(int idJefe) {
        NodoMiembro* jefe = buscarPorId(root, idJefe);
        if (jefe == nullptr) {
            cout << "[!] Error: No se encontro ningun miembro con ID " << idJefe << ".\n";
            return;
        }

        cout << "\n--- EJECUTANDO ALGORITMO DE SUCESIÓN EN CADENA ---\n";
        NodoMiembro* nuevoJefe = nullptr;
        NodoMiembro* padre = encontrarPadre(root, jefe->dato.id); // Buscamos su jefe superior
        if (padre == nullptr && jefe != root) padre = root; // Mitigación por diseño

        // REGLA 1: Primer sucesor vivo fuera de prisión en SU propio subárbol (hijos)
        if (jefe->izq != nullptr) {
            nuevoJefe = obtenerPrimeroLibreYVivo(jefe->izq);
        }
        /*
         Regla 2 y 3: Si no hay sucesores en el jefe , 
         buscamos en los sucesores del hermano del jefe,
         y si tampoco tiene sucesores, el hermano del jefe se vuelve jefe   
        */
        if (nuevoJefe == nullptr && jefe->der != nullptr) {
            nuevoJefe = obtenerPrimeroLibreYVivo(jefe->der);
        }
        // REGLA 4 Y 5: Buscar en el árbol del jefe de su jefe (padre jerárquico)
        if (nuevoJefe == nullptr && padre != nullptr) {
            cout << "[Regla 4/5] Crisis total en la rama. Apelando al nivel superior (Jefe de Jefes)...\n";
            // Buscamos un compañero libre en el nivel del padre
            nuevoJefe = obtenerPrimeroLibreYVivo(padre->izq);
        }

        // REGLA FINAL: Si todos los libres fallan, buscar los que están en prisión pero vivos
        if (nuevoJefe == nullptr) {
            // Nota: Aquí se implementaría el recorrido inverso/cercano buscando is_dead == false aunque in_jail == true
        }

        // APLICACIÓN AUTOMÁTICA DEL PUESTO
        if (nuevoJefe != nullptr) {
            jefe->dato.is_boss = false;
            jefe->dato.was_boss = true;
            
            nuevoJefe->dato.is_boss = true;
            if (padre != nullptr) {
                nuevoJefe->dato.id_boss = padre->dato.id;
            }
            
            cout << "\n========================================================\n";
            cout << " ¡NUEVO JEFE ASIGNADO AUTOMATICAMENTE! \n";
            cout << "========================================================\n";
            cout << "Nombre: " << nuevoJefe->dato.name << " " << nuevoJefe->dato.last_name << "\n";
            cout << "Motivo: Primer sucesor idoneo segun las leyes de la familia.\n";
            cout << "========================================================\n";
        } else {
            cout << "\n[!] Alerta Critica: La familia ha sido desmantelada. No quedan sucesores vivos.\n";
        }
    }

    void verificarYAutoAsignarJefeInicial() {
        if (root == nullptr) return;

        // Buscamos al miembro que el CSV marcó como jefe principal (is_boss == true)
        // O simplemente evaluamos la raíz del árbol.
        NodoMiembro* jefeActual = root; 
        
        // EVALUACIÓN AUTOMÁTICA DE CONDICIONES INICIALES:
        // Si el jefe asignado por el CSV ya está muerto, en la cárcel o es mayor de 70 años...
        if (jefeActual->dato.is_dead || jefeActual->dato.in_jail || jefeActual->dato.age > 70) {
            cout << "[SISTEMA AUTOMÁTICO] Alerta: El jefe inicial (" << jefeActual->dato.name 
                 << ") no cumple con los requisitos para gobernar (Muerto, en prision o > 70 años).\n";
            cout << "[SISTEMA AUTOMÁTICO] Aplicando reglas de sucesion de forma inmediata...\n";
            
            // Llamamos a la lógica de sucesión que busca al primer heredero idóneo
            simularSucesion(jefeActual->dato.id);
        } else {
            cout << "[SISTEMA AUTOMÁTICO] Jefe principal verificado con exito: " 
                 << jefeActual->dato.name << " " << jefeActual->dato.last_name << " esta al mando.\n";
        }
    }

};

#endif