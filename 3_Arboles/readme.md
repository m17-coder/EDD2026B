# Prototipo - Casa Nostra: Sistema de Sucesión

Este proyecto es un programa en C++ diseñado para gestionar el organigrama y la línea de sucesión de una familia de la mafia italiana. El sistema asegura que, ante cualquier eventualidad, la familia nunca se quede sin un líder, aplicando de manera automática y rigurosa las leyes de sucesión de la organización.

## 🎯 ¿Qué se logra con este proyecto?

El programa cumple con los siguientes objetivos y funcionalidades principales:

* **Conversión de Datos:** Transforma un archivo plano (`miembros.csv`) en un **Árbol Binario (LCRS)** en memoria dinámica, respetando jerarquías complejas sin el uso de arreglos dinámicos como `std::vector`.
* **Visualización de la Jerarquía:** Muestra en pantalla la línea de sucesión actual, filtrando automáticamente a los miembros fallecidos.
* **Gestión de Sucesión Automática:** Si el Jefe Supremo muere, va a prisión o supera los 70 años, el sistema evalúa automáticamente la jerarquía para designar al nuevo líder bajo un estricto sistema de reglas (buscando hijos aptos, hermanos, tíos, o aplicando contingencias extremas desde la cárcel).
* **Edición Segura de Miembros:** Permite actualizar el estado de cualquier miembro (edad, estado vital, estatus penal) protegiendo la integridad estructural del árbol (bloqueando la modificación de los identificadores principales).
* **Persistencia de Datos:** Todos los cambios realizados o las sucesiones automáticas se guardan inmediatamente en el archivo CSV para evitar la pérdida de información y mantener la base de datos sincronizada con la estructura física en RAM.

---

## 📂 Estructura de carpetas

El proyecto separa de forma estricta el código fuente de los archivos ejecutables y la base de datos, siguiendo esta estructura:

```text
📁 raiz_del_proyecto
├── 📄 README.md
├── 📁 bin
│   ├── main.exe    (Ejecutable generado tras compilar)
│   └── miembros.csv     (Base de datos inicial)
└── 📁 src
    ├── estructura_de_arbol.h
    ├── utilidades.h
    └── main.cpp

**Nota para la compilación:** El ejecutable debe generarse dentro de la carpeta `bin/`, ya que desde allí buscará el archivo `miembros.csv`.
