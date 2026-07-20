#pragma once

#include "estructura_de_arbol.h"
#include <iostream>
#include <limits>
#include <conio.h>
#include <cstdlib>
#include <cctype>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

void vaciarBuffer() {
    if (cin.fail()) {
        cin.clear();
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pausarYlimpiarpantalla() {
    cout << "Presione Enter para continuar...";
    vaciarBuffer();
    system("cls");
}


// Captura enteros de forma segura y cancelable.
bool pedirEnteroCancelable(const char* etiqueta, int& valor) {
    cout << etiqueta;

    string entrada;
    char c;

    while (true) {
        c = _getch();

        if (c == 27) {
            cout << " [CANCELADO]" << endl;
            return false;
        }

        if (c == 13) {
            cout << endl;
            break;
        }

        if (isdigit(static_cast<unsigned char>(c))) {
            cout << c;
            entrada += c;
        }

        if (c == 8 && !entrada.empty()) {
            cout << "\b \b";
            entrada.pop_back();
        }
    }

    if (entrada.empty()) {
        valor = 0;
    }
    else {
        valor = stoi(entrada);
    }

    return true;
}

bool leerCSV(const string& ruta_archivo, ArbolMiembros& arbol) {
    // ========================================================
    // PASADA 1: Buscar e insertar ÚNICAMENTE al Jefe Supremo
    // ========================================================
    ifstream archivo1(ruta_archivo);
    if (!archivo1.is_open()) return false;
    
    string linea;
    getline(archivo1, linea); // Saltar encabezado
    
    bool jefeEncontrado = false;
    int idJefeSupremo = -1;

    while (getline(archivo1, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string dato;
        Miembro temporal;

        getline(ss, dato, ','); temporal.id = stoi(dato);
        getline(ss, temporal.name, ',');
        getline(ss, temporal.last_name, ',');
        getline(ss, dato, ','); temporal.gender = dato[0];
        getline(ss, dato, ','); temporal.age = stoi(dato);
        getline(ss, dato, ','); temporal.id_boss = stoi(dato);
        getline(ss, dato, ','); temporal.is_dead = (stoi(dato) == 1);
        getline(ss, dato, ','); temporal.in_jail = (stoi(dato) == 1);
        getline(ss, dato, ','); temporal.was_boss = (stoi(dato) == 1);
        getline(ss, dato, ','); bool esJefeCSV = (stoi(dato) == 1);

        if (esJefeCSV && !jefeEncontrado) {
            temporal.is_boss = true;
            arbol.insertarMiembro(temporal); // Se inserta primero, garantizando que sea la raíz
            jefeEncontrado = true;
            idJefeSupremo = temporal.id;
            break; // Una vez hallado el Jefe, detenemos esta lectura
        }
    }
    archivo1.close();

    // ========================================================
    // PASADA 2: Insertar a todos los demás miembros
    // ========================================================
    ifstream archivo2(ruta_archivo);
    getline(archivo2, linea); // Saltar encabezado

    while (getline(archivo2, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string dato;
        Miembro nuevo;

        getline(ss, dato, ','); nuevo.id = stoi(dato);
        
        // Si el ID coincide con el del Jefe Supremo (ya insertado), lo ignoramos
        if (nuevo.id == idJefeSupremo) continue; 

        getline(ss, nuevo.name, ',');
        getline(ss, nuevo.last_name, ',');
        getline(ss, dato, ','); nuevo.gender = dato[0];
        getline(ss, dato, ','); nuevo.age = stoi(dato);
        getline(ss, dato, ','); nuevo.id_boss = stoi(dato);
        getline(ss, dato, ','); nuevo.is_dead = (stoi(dato) == 1);
        getline(ss, dato, ','); nuevo.in_jail = (stoi(dato) == 1);
        getline(ss, dato, ','); nuevo.was_boss = (stoi(dato) == 1);
        getline(ss, dato, ','); bool esJefeCSV = (stoi(dato) == 1);

        // Si el CSV dice que hay otro jefe, lo degradamos para proteger la jerarquía
        if (esJefeCSV) {
            nuevo.is_boss = false;
            nuevo.was_boss = true;
        } else {
            nuevo.is_boss = false;
        }

        arbol.insertarMiembro(nuevo);
    }
    archivo2.close();

    // ========================================================
    // VERIFICACIÓN INICIAL: Corrección del error 4
    // ========================================================
    // Si la función retorna true, significa que hubo una sucesión automática y el CSV ya se guardó.
    // Por lo tanto, vaciamos la RAM y volvemos a leer para que la estructura física se actualice.
    if (arbol.verificarYAutoAsignarJefeInicial()) {
        cout << "\n[!] Sincronizando organigrama fisico en RAM tras la sucesion...\n";
        arbol.vaciarArbol();
        return leerCSV(ruta_archivo, arbol); 
    }

    return true;
}