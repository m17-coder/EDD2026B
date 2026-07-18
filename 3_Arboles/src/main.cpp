#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>
#include <windows.h>
#include "estructura_de_arbol.h"
#include "utilidades.h"

using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    ArbolMiembros mafiaTree;
    
    // Suponiendo que el ejecutable se ejecuta desde la carpeta /bin
    if (!leerCSV("miembros.csv", mafiaTree)) {
        cout << "Presione cualquier tecla para salir...";
        _getch();
        return 1;
    }

    char opcion = '0';
    while (opcion != '5') {
        cout << "\n============================================\n";
        cout << "      PROTOTIPO - CASA NOSTRA   \n";
        cout << "============================================\n";
        cout << "1. Mostrar estructura completa del organigrama\n";
        cout << "2. Ver linea de sucesion actual \n";
        cout << "3. Simular evento de redefinicion de Jefe\n";
        cout << "4. Modificar datos de un miembro \n";
        cout << "5. Salir del programa\n";
        cout << "--------------------------------------------\n";
        cout << "Seleccione una opcion: ";
        
        opcion = _getch();
        cout << opcion << "\n\n"; // Mostrar la opción elegida

        switch (opcion) {
            case '1':
                cout << "--- ORGANIGRAMA ACTUAL DE LA FAMILIA ---\n\n";
                mafiaTree.Mostrar_arbol();
                break;
            case '2':
                cout << "--- LINEA DE SUCESION ACTUAL ---\n\n";
                mafiaTree.mostrarSoloVIvos();
                break;
            case '3':
                cout << "[Pendiente] Aqui se ejecutaran las reglas de redefinicion.\n";
                break;
            case '4': {
                cout << "--- MODIFICACIÓN DE REGISTROS (Presione ESC para cancelar) ---\n";
                int idBuscar = 0;
                if (pedirEnteroCancelable("Ingrese el ID del miembro a modificar: ", idBuscar)) {
                    cout << "Buscando ID: " << idBuscar << "...\n";
                    // Próximamente enlazaremos con la lógica del Requisito 4
                }
                break;
            }
            case '5':
                cout << "Saliendo del sistema de forma segura. Arrivederci.\n";
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
                break;
        }
    }
    return 0;
}