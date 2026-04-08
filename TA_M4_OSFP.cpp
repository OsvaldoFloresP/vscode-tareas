#include <iostream>
#include <fstream> // Esta es una librería vital para el manejo de archivos (guardar y abrir)
#include <string>

using namespace std;

// =========================================================================
// DECLARACIÓN DE PROTOTIPOS DE FUNCIONES
// =========================================================================
void mostrarBienvenida();
void visualizarEquipos(int equipos[], int total);
void registrarVisitante(int equipos[], string bitacora[][3], int &contador_registros);
void generar_reporte(string bitacora[][3], int contador_registros);
void consultar_reporte();

// =========================================================================
// FUNCIÓN PRINCIPAL
// =========================================================================
int main() {
    // 1. Arreglo unidimensional para los equipos (0 = Disponible, 1 = Ocupado)
    int equipos[20] = {0}; 
    
    // 2. Arreglo bidimensional para la bitácora (10 filas/registros x 3 columnas: ID, Nombre, Hora)
    string bitacora[10][3]; 
    
    int contador_registros = 0; // Lleva el control de cuántos usuarios van en el día
    int opcion;

    mostrarBienvenida();

    do {

        cout << "===================================================================================\n";
        cout << "                          MENU PRINCIPAL SIG-Conecta v3.0                          \n";
        cout << "===================================================================================\n";
        cout << " 1. Visualizar disponibilidad de equipos\n";
        cout << " 2. Registrar nuevo visitante\n";
        cout << " 3. Generar reporte del dia (Guardar archivo)\n";
        cout << " 4. Consultar reporte del dia (Abrir archivo)\n";
        cout << " 5. Salir del sistema\n";
        cout << "-----------------------------------------------------------------------------------\n";
        cout << " Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                visualizarEquipos(equipos, 20);
                break;
            case 2:
                registrarVisitante(equipos, bitacora, contador_registros);
                break;
            case 3:
                generar_reporte(bitacora, contador_registros);
                break;
            case 4:
                consultar_reporte();
                break;
            case 5:
                cout << "\nSaliendo y cerrando el sistema de manera segura. iHasta pronto!\n";
                break;
            default:
                cout << "\nError: Opcion no valida. Intente de nuevo.\n";
        }
    } while(opcion != 5);

    return 0;
}

// =========================================================================
// DEFINICIÓN DE FUNCIONES
// =========================================================================

// Función 1: Portada
void mostrarBienvenida() {
    cout << "===================================================================================\n";
    cout << "...................................................................................\n";
    cout << "..........@@@.......%%%%..%%%.%%%%...%%%.%%%%%%%.....%%%%%.........................\n";
    cout << ".........@...@.......%%....%...%%%%...%..%%....%%..%%%....%........................\n";
    cout << ".........@@@@@@@@....%%....%...%.%%%.:%..%%...%%...%%..............................\n";
    cout << ".........@...@...@...%%....%...%...%%:%..%%%%%%%...%%..............................\n";
    cout << "......@@@@@@@@@@@....%%%..%%...%....%%%..%%....%%..%%%....%........................\n";
    cout << ".....@...@...@........%%%%%...%%%....%%.:%%%...%%%...%%%%%.........................\n";
    cout << "......@@@@@@@@.....................................................................\n";
    cout << ".........@...@......Universidad...Nacional...Rosario...Castellasnos................\n";
    cout << "..........@@@......................................................................\n";
    cout << "...................................................................................\n";
    cout << "===================================================================================\n";
    cout << "                Bienvenido al Sistema de Control de Visitantes v3.0                \n";
    cout << "===================================================================================\n";
}

// Función 2: Recorre el arreglo unidimensional para mostrar el estatus de las PCs
void visualizarEquipos(int equipos[], int total) {
    cout << "\n--- ESTADO ACTUAL DEL LABORATORIO ---\n";
    for(int i = 0; i < total; i++) {
        cout << "PC #" << (i + 1) << ": ";
        if(equipos[i] == 0) {
            cout << "[ Disponible ]\n";
        } else {
            cout << "[ Ocupado ]\n";
        }
    }
}

// Función 3: Registra al usuario en la bitácora 2D y ocupa el equipo en el arreglo 1D
void registrarVisitante(int equipos[], string bitacora[][3], int &contador_registros) {
    if(contador_registros >= 10) {
        cout << "\nError: La bitacora de hoy esta llena (Max 10 registros diarios).\n";
        return;
    }

    int num_pc;
    cout << "\n--- REGISTRO DE VISITANTE ---\n";
    cout << "Ingrese el numero de PC a asignar (1-20): ";
    cin >> num_pc;

    // Validación de la PC
    if(num_pc < 1 || num_pc > 20) {
        cout << "Error: Numero de PC invalido.\n";
        return;
    }
    if(equipos[num_pc - 1] == 1) {
        cout << "Error: La PC #" << num_pc << " ya se encuentra ocupada.\n";
        return;
    }

    // Si la PC está libre, se procede a registrar en la matriz
    string id, nombre, hora;
    cout << "Ingrese ID del visitante: ";
    cin >> ws; // Limpia el buffer
    getline(cin, id);
    cout << "Ingrese el Nombre completo: ";
    getline(cin, nombre);
    cout << "Ingrese la Hora de entrada (ej. 14:30): ";
    getline(cin, hora);

    // Almacenando en el arreglo bidimensional
    bitacora[contador_registros][0] = id;
    bitacora[contador_registros][1] = nombre;
    bitacora[contador_registros][2] = hora;

    // Actualizacion del arreglo unidimensional (Se marca la PC como ocupada)
    equipos[num_pc - 1] = 1;

    // Se aumenta el contador de registros
    contador_registros++;

    cout << "\niRegistro exitoso! PC #" << num_pc << " asignada correctamente.\n";
}

// Función 4: Crea y escribe en el archivo .txt (Persistencia)
void generar_reporte(string bitacora[][3], int contador_registros) {
    if(contador_registros == 0) {
        cout << "\nAdvertencia: No hay registros para guardar el dia de hoy.\n";
        return;
    }

    // ofstream sirve para CREAR y ESCRIBIR en archivos
    ofstream archivo("reporte_dia.txt");

    if(archivo.is_open()) {
        archivo << "===================================================================================\n";
        archivo << "                        BITACORA DIARIA - SIG-CONECTA V3.0                         \n";
        archivo << "===================================================================================\n";
        archivo << "ID \t\t Nombre \t\t Hora\n";
        archivo << "-----------------------------------------------------------------------------------\n";
        
        for(int i = 0; i < contador_registros; i++) {
            archivo << bitacora[i][0] << " \t " << bitacora[i][1] << " \t " << bitacora[i][2] << "\n";
        }
        
        archivo.close(); // Siempre cerrar el archivo por seguridad
        cout << "\niReporte generado exitosamente! Archivo guardado como 'reporte_dia.txt'.\n";
    } else {
        cout << "\nError critico: No se pudo crear el archivo de reporte.\n";
    }
}

// Función 5: Lee el archivo .txt y lo muestra en consola
void consultar_reporte() {
    string linea;
    // ifstream sirve para LEER archivos existentes
    ifstream archivo("reporte_dia.txt");

    cout << "\n--- CONSULTANDO REPORTE DEL DIA ---\n";
            
    if(archivo.is_open()) {
        // Leemos línea por línea hasta llegar al final del archivo
        while(getline(archivo, linea)) {
            cout << linea << "\n";
        }
        archivo.close();
    } else {
        cout << "Error: No se encontro el archivo 'reporte_dia.txt'. iGenere el reporte primero!\n";
    }
}