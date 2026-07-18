#pragma once

#include <iostream>
#include <limits>
#include <conio.h>
#include <cstdlib>
#include <cctype>
#include <string>

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
