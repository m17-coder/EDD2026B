
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
            case '3': {
                cout << "\n--- SIMULAR SUCESIÓN (Presione ESC para cancelar) ---\n";
                int idJefe = 0;
                if (pedirEnteroCancelable("Ingrese el ID del jefe actual a reemplazar: ", idJefe)) {
                    mafiaTree.simularSucesion(idJefe);
                } else {
                    cout << "\nOperacion cancelada.\n";
                }
                break;
            }
            case '4': { 
                cout << "\n--- MODIFICACION DE REGISTROS (Presione ESC en cualquier momento para cancelar) ---\n";
                int idBuscar = 0;
                
                if (!pedirEnteroCancelable("Ingrese el ID del miembro a modificar: ", idBuscar)) {
                    cout << "\nOperacion cancelada por el usuario al inicio.\n";
                    break;
                }

                Miembro objTemp;
                if (!mafiaTree.buscarMiembro(idBuscar, objTemp)) {
                    cout << "\n[!] No se encontro ningun miembro con el ID " << idBuscar << ".\n";
                    break;
                }

                bool salir = false;
                bool huboCambios = false;

                while (!salir) {
                    cout << "\n======================================================\n";
                    cout << " MODIFICANDO A: " << objTemp.name << " " << objTemp.last_name << "\n";
                    cout << "======================================================\n";
                    cout << "1. Nombre: " << objTemp.name << "\n";
                    cout << "2. Apellido: " << objTemp.last_name << "\n";
                    cout << "3. Genero: " << objTemp.gender << "\n";
                    cout << "4. Edad: " << objTemp.age << "\n";
                    cout << "5. Estado Vital: " << (objTemp.is_dead ? "Muerto" : "Vivo") << "\n";
                    cout << "6. Estado Legal: " << (objTemp.in_jail ? "En prision" : "Libre") << "\n";
                    cout << "7. Estatus 'Fue Jefe': " << (objTemp.was_boss ? "Si" : "No") << "\n";
                    cout << "8. Estatus 'Es Jefe': " << (objTemp.is_boss ? "Si" : "No") << "\n";
                    cout << "0. Salir de modificaciones\n";
                    cout << "------------------------------------------------------\n";
                    cout << "Seleccione el campo a modificar (ESC o 0 para cancelar/salir): ";

                    char opcion = _getch();
                    bool cambioActual = false; 

                    switch (opcion) {
                        case 27: 
                        case '0':
                            cout << (opcion == '0' ? "0\n" : "\n") << "\nSaliendo del menu de modificacion...\n";
                            salir = true; 
                            break;
                        case '1':
                            cout << opcion << "\nNuevo nombre: ";
                            cin >> objTemp.name;
                            cambioActual = true;
                            break;
                        case '2':
                            cout << opcion << "\nNuevo apellido: ";
                            cin >> objTemp.last_name;
                            cambioActual = true;
                            break;
                        case '3':
                            cout << opcion << "\nNuevo genero (H/M): ";
                            char g; cin >> g;
                            objTemp.gender = toupper(g);
                            cambioActual = true;
                            break;
                        case '4': {
                            cout << opcion << "\n";
                            int nuevaEdad;
                            if (pedirEnteroCancelable("Nueva edad (ESC para cancelar): ", nuevaEdad)) {
                                objTemp.age = nuevaEdad;
                                cambioActual = true;
                            }
                            break;
                        }
                        case '5':
                            cout << opcion << "\n";
                            objTemp.is_dead = !objTemp.is_dead;
                            cout << "Estado vital cambiado a: " << (objTemp.is_dead ? "Muerto" : "Vivo") << "\n";
                            cambioActual = true;
                            break;
                        case '6':
                            cout << opcion << "\n";
                            objTemp.in_jail = !objTemp.in_jail;
                            cout << "Estado legal cambiado a: " << (objTemp.in_jail ? "En prision" : "Libre") << "\n";
                            cambioActual = true;
                            break;
                        case '7':
                            cout << opcion << "\n";
                            objTemp.was_boss = !objTemp.was_boss;
                            cout << "Estatus 'Fue Jefe' cambiado.\n";
                            cambioActual = true;
                            break;
                        case '8':
                            cout << opcion << "\n";
                            objTemp.is_boss = !objTemp.is_boss;
                            cout << "Estatus 'Es Jefe' cambiado.\n";
                            cambioActual = true;
                            break;
                        default:
                            cout << opcion << "\nOpcion no valida. No se hicieron cambios.\n";
                            break;
                    }

                    if (cambioActual && !salir) {
                        huboCambios = true; 
                        cout << "\n¿Desea salir de las modificaciones con los cambios ya hechos?\n";
                        cout << "(Presione ESC o 'S' para salir, cualquier otra tecla para seguir modificando): ";
                        char respuesta = _getch();
                        if (respuesta == 27 || respuesta == 's' || respuesta == 'S') {
                            cout << "\n\nSaliendo de la modificacion de " << objTemp.name << ".\n";
                            salir = true; 
                        } else {
                            cout << "\n\nContinuando con las modificaciones...\n";
                        }
                    }
                }

                if (huboCambios) {
                    mafiaTree.aplicarCambiosYGuardar(objTemp);
                } else {
                    cout << "\nNo se detectaron cambios. Archivo sin alteraciones.\n";
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
    