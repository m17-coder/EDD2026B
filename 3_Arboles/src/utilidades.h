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

// Lee texto carácter por carácter. Cancela con ESC.
bool pedirTextoCancelable(const char* mensaje, char* destino, int tamano) {
    cout << mensaje << ": ";

    int i = 0;
    char tecla;

    while (true) {
        tecla = _getch();

        if (tecla == 27) {
            cout << "\n[!] Operación cancelada por el usuario." << endl;
            pausarYlimpiarpantalla();
            return false;
        }
        else if (tecla == '\r') {
            destino[i] = '\0';
            cout << endl;
            return true;
        }
        else if (tecla == '\b' && i > 0) {
            i--;
            cout << "\b \b";
        }
        else if (i < tamano - 1 && tecla >= 32 && tecla <= 126) {
            destino[i] = tecla;
            i++;
            cout << tecla;
        }
    }
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
    ifstream archivo(ruta_archivo);
    if (!archivo.is_open()) return false;
    
    string linea;
    getline(archivo, linea); // saltar encabezado

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string dato;
        Miembro nuevo;


        getline(ss, dato, ','); nuevo.id = stoi(dato);
        getline(ss, nuevo.name, ',');
        getline(ss, nuevo.last_name, ',');
        
        getline(ss, dato, ','); nuevo.gender = dato[0];
        
        getline(ss, dato, ','); nuevo.age = stoi(dato);
        getline(ss, dato, ','); nuevo.id_boss = stoi(dato);
        
        getline(ss, dato, ','); nuevo.is_dead = (stoi(dato) == 1);
        getline(ss, dato, ','); nuevo.in_jail = (stoi(dato) == 1);
        getline(ss, dato, ','); nuevo.was_boss = (stoi(dato) == 1);
        getline(ss, dato, ','); nuevo.is_boss = (stoi(dato) == 1);

        
        // Llamada al método de tu clase ArbolMiembros
        arbol.insertarMiembro(nuevo);
    }
    archivo.close();

    arbol.verificarYAutoAsignarJefeInicial();
    return true;
}