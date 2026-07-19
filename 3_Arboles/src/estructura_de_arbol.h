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

    int contarSucesoresIdoneos(NodoMiembro* actual) const {
        if (actual == nullptr) return 0;
        int cuenta = 0;
        if (!actual->dato.is_dead && !actual->dato.in_jail && actual->dato.age <= 70) {
            cuenta = 1;
        }
        return cuenta + contarSucesoresIdoneos(actual->izq) + contarSucesoresIdoneos(actual->der);
    }

    
    NodoMiembro* buscarEnRamaEncarcelada(NodoMiembro* actual) const {
        if (actual == nullptr) return nullptr;

        if (actual->dato.in_jail && !actual->dato.is_dead) {
            NodoMiembro* candidato = obtenerPrimeroLibreYVivo(actual->izq);
            if (candidato != nullptr) return candidato;
        }

        NodoMiembro* candidatoIzq = buscarEnRamaEncarcelada(actual->izq);
        if (candidatoIzq != nullptr) return candidatoIzq;

        return buscarEnRamaEncarcelada(actual->der);
    }

    NodoMiembro* buscarNodoPorId(NodoMiembro* nodo, int id_buscado) {
        // Caso base 1: Llegamos a una hoja vacía y no lo encontramos
        if (nodo == nullptr) {
            return nullptr;
        }

        // Caso base 2: ¡Lo encontramos en el nodo actual!
        if (nodo->dato.id == id_buscado) {
            return nodo;
        }
        
        // Buscamos en toda la rama izquierda
        NodoMiembro* encontradoIzq = buscarNodoPorId(nodo->izq, id_buscado);
        if (encontradoIzq != nullptr) {
            return encontradoIzq; // Si lo encontró en la izquierda, lo devuelve
        }
        
        // Si no estaba en la izquierda, buscamos en la rama derecha
        return buscarNodoPorId(nodo->der, id_buscado);
    }

    void guardarNodoEnCSV(NodoMiembro* nodo, ofstream& archivo) {
        if (nodo == nullptr) return;

        archivo << nodo->dato.id << ","
                << nodo->dato.name << ","
                << nodo->dato.last_name << ","
                << nodo->dato.gender << ","
                << nodo->dato.age << ","
                << nodo->dato.id_boss << ","
                << (int)nodo->dato.is_dead << ","
                << (int)nodo->dato.in_jail << ","
                << (int)nodo->dato.was_boss << ","
                << (int)nodo->dato.is_boss << "\n";

        guardarNodoEnCSV(nodo->izq, archivo);
        guardarNodoEnCSV(nodo->der, archivo);
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
       void aplicarCambiosYGuardar(const Miembro& datosModificados) {
        NodoMiembro* objetivo = buscarNodoPorId(root, datosModificados.id);
        
        if (objetivo == nullptr) return; // Validación de seguridad

        // 1. Aplicar los datos modificados al nodo
        objetivo->dato = datosModificados;

        // 2. Reglas de negocio: Inhabilitación automática del jefe actual
        if (objetivo->dato.is_boss && (objetivo->dato.is_dead || objetivo->dato.in_jail || objetivo->dato.age > 70)) {
            cout << "\n[!] ALERTA CRITICA: El Jefe actual ha sido incapacitado (Muerto, Preso o >70 anos).\n";
            cout << "[!] Ejecutando reglas de sucesion automaticamente...\n";
            simularSucesion(objetivo->dato.id); 
        }

        // 3. GUARDADO FÍSICO
        cout << "\nGuardando cambios en la base de datos (miembros.csv)...\n";
        if (actualizarCSV("miembros.csv")) { 
            cout << "[+] Todos los cambios han sido guardados exitosamente en el archivo.\n";
        }
    }
    

    bool actualizarCSV(const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "\n[!] Error: No se pudo abrir " << nombreArchivo << " para guardar los cambios.\n";
            return false;
        }

        archivo << "id,name,last_name,gender,age,id_boss,is_dead,in_jail,was_boss,is_boss\n";
        guardarNodoEnCSV(root, archivo);
        archivo.close();
        return true;
    }
    

    void simularSucesion(int idJefe) {
        NodoMiembro* jefe = buscarPorId(root, idJefe);
        if (jefe == nullptr) {
            cout << "[!] Error: No se encontro ningun miembro con ID " << idJefe << ".\n";
            return;
        }

        cout << "\n--- EJECUTANDO ALGORITMO DE SUCESIÓN EN CADENA ---\n";
        NodoMiembro* nuevoJefe = nullptr;
        NodoMiembro* padre = encontrarPadre(root, jefe->dato.id); 
        if (padre == nullptr && jefe != root) padre = root; 

        // REGLA 1: Primer sucesor vivo fuera de prisión en SU propia rama (subárbol izquierdo)
        if (jefe->izq != nullptr) {
            nuevoJefe = obtenerPrimeroLibreYVivo(jefe->izq);
        }

        // REGLAS 2 Y 3: Buscar en la rama del hermano
        if (nuevoJefe == nullptr && jefe->der != nullptr) {
            if (jefe->der->izq != nullptr) {
                nuevoJefe = obtenerPrimeroLibreYVivo(jefe->der->izq);
            }
            
            if (nuevoJefe == nullptr) {
                NodoMiembro* hermano = jefe->der;
                if (!hermano->dato.is_dead && !hermano->dato.in_jail && hermano->dato.age <= 70) {
                    cout << "[Regla 3] Los sobrinos no aplican. El hermano se vuelve el jefe.\n";
                    nuevoJefe = hermano;
                }
            }
        }   

        // REGLAS 4 Y 5: Escalada vertical
        if (nuevoJefe == nullptr) {
            NodoMiembro* ancestro = padre; 
            bool esPrimerNivelSuperior = true;
        
            while (ancestro != nullptr && nuevoJefe == nullptr) {
                if (esPrimerNivelSuperior) {
                    cout << "[Regla 4] Buscando en el arbol del compañero del anterior jefe...\n";
                    nuevoJefe = obtenerPrimeroLibreYVivo(ancestro->izq);
                    esPrimerNivelSuperior = false; 
                } 
                else if (contarSucesoresIdoneos(ancestro->izq) >= 2) {
                    cout << "[Regla 5] Jefe superior lejano encontrado con contingencia (>=2 aptos): " 
                         << ancestro->dato.name << "\n";
                    nuevoJefe = obtenerPrimeroLibreYVivo(ancestro->izq);
                }
                
                ancestro = encontrarPadre(root, ancestro->dato.id);
            }
        } 

        if (nuevoJefe == nullptr) {
            cout << "[Regla 6] Contingencia extrema: Buscando sucesores libres desde miembros encarcelados...\n";
            
            NodoMiembro* ancestroActual = jefe;
            
            while (ancestroActual != nullptr && nuevoJefe == nullptr) {
                nuevoJefe = buscarEnRamaEncarcelada(ancestroActual);
                
                if (nuevoJefe == nullptr) {
                    ancestroActual = encontrarPadre(root, ancestroActual->dato.id);
                }
            }

            if (nuevoJefe == nullptr) {
                nuevoJefe = buscarEnRamaEncarcelada(root);
                }
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