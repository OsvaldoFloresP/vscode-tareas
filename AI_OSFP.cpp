#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// =========================================================================
// ESTRUCTURAS DE DATOS
// =========================================================================
struct RegistroBitacora {
    int idEquipo;
    string hora;
    string tipoIncidente;
    string descripcion;
};

// Constantes globales
const int TOTAL_EQUIPOS = 20;
const int MAX_REGISTROS = 100;

// =========================================================================
// PROTOTIPOS DE FUNCIONES
// =========================================================================
void mostrarBienvenida();
void cargarDatos(RegistroBitacora bitacora[], int &contador);
void guardarDatos(RegistroBitacora bitacora[], int contador);
void consultarEstado(int equipos[]);
void modificarEstado(int equipos[]);
void registrarIncidente(RegistroBitacora bitacora[], int &contador, int equipos[]);
void consultarHistorial(RegistroBitacora bitacora[], int contador);

// =========================================================================
// FUNCIÓN PRINCIPAL
// =========================================================================
int main() {
    // Arreglo unidimensional (0 = Libre, 1 = Ocupada, 2 = Mantenimiento)
    int estadoEquipos[TOTAL_EQUIPOS] = {0}; 
    
    // Arreglo de estructuras para almacenar la bitácora en memoria
    RegistroBitacora bitacora[MAX_REGISTROS];
    int contadorRegistros = 0;
    int opcion;

    mostrarBienvenida();
    
    // Cargar historial previo si existe el archivo (Persistencia de lectura)
    cargarDatos(bitacora, contadorRegistros);

    do {
        cout << "===================================================================================\n";
        cout << "                   CENTRO TECNOLOGICO 'SAN PEDRO DE LA MONTANA'                    \n";
        cout << "                              SIG-Conecta v4.0 (Final)                             \n";
        cout << "===================================================================================\n";
        cout << " 1. Consultar estado de las computadoras\n";
        cout << " 2. Modificar estado de un equipo\n";
        cout << " 3. Registrar un incidente\n";
        cout << " 4. Consultar historial de bitacora\n";
        cout << " 5. Guardar y Salir\n";
        cout << "-----------------------------------------------------------------------------------\n";
        cout << " Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                consultarEstado(estadoEquipos);
                break;
            case 2:
                modificarEstado(estadoEquipos);
                break;
            case 3:
                registrarIncidente(bitacora, contadorRegistros, estadoEquipos);
                break;
            case 4:
                consultarHistorial(bitacora, contadorRegistros);
                break;
            case 5:
                guardarDatos(bitacora, contadorRegistros);
                cout << "\nDatos guardados exitosamente. Cerrando sistema...\n";
                break;
            default:
                cout << "\nError: Opcion no valida.\n";
        }
    } while(opcion != 5);

    return 0;
}

// =========================================================================
// DEFINICIÓN DE FUNCIONES
// =========================================================================

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

// Persistencia: Lectura del archivo al iniciar
void cargarDatos(RegistroBitacora bitacora[], int &contador) {
    ifstream archivo("bitacora.txt");
    if(archivo.is_open()) {
        string linea;
        // Saltamos las 4 primeras lineas de encabezado
        for(int i=0; i<4; i++) getline(archivo, linea); 
        
        while(getline(archivo, linea) && contador < MAX_REGISTROS) {
            if(linea.empty() || linea.find("----") != string::npos) continue;
            
            // Parseo básico separando por el caracter '|'
            stringstream ss(linea);
            string temp;
            
            getline(ss, temp, '|'); bitacora[contador].idEquipo = stoi(temp);
            getline(ss, temp, '|'); bitacora[contador].hora = temp;
            getline(ss, temp, '|'); bitacora[contador].tipoIncidente = temp;
            getline(ss, temp, '|'); bitacora[contador].descripcion = temp;
            
            contador++;
        }
        archivo.close();
        cout << "\n[INFO] Se recuperaron " << contador << " registros previos de bitacora.txt\n";
    } else {
        cout << "\n[INFO] No se encontro historial previo. Se iniciara una bitacora nueva.\n";
    }
}

// Persistencia: Escritura al salir
void guardarDatos(RegistroBitacora bitacora[], int contador) {
    ofstream archivo("bitacora.txt");
    if(archivo.is_open()) {
        archivo << "===================================================================================\n";
        archivo << "                        BITACORA DE INCIDENTES - SIG-CONECTA                       \n";
        archivo << "===================================================================================\n";
        archivo << "PC\t| HORA\t| TIPO\t\t| DESCRIPCION\n";
        archivo << "-----------------------------------------------------------------------------------\n";
        
        for(int i = 0; i < contador; i++) {
            archivo << bitacora[i].idEquipo << "\t| " 
                    << bitacora[i].hora << "\t| " 
                    << bitacora[i].tipoIncidente << "\t| " 
                    << bitacora[i].descripcion << "\n";
        }
        archivo.close();
    } else {
        cout << "\n[ERROR CRITICO] No se pudo escribir en el archivo bitacora.txt\n";
    }
}

void consultarEstado(int equipos[]) {
    cout << "\n--- ESTADO DE COMPUTADORAS ---\n";
    for(int i = 0; i < TOTAL_EQUIPOS; i++) {
        cout << "PC #" << (i + 1) << ": ";
        if(equipos[i] == 0) cout << "[ LIBRE ]\n";
        else if(equipos[i] == 1) cout << "[ OCUPADA ]\n";
        else cout << "[ MANTENIMIENTO ]\n";
    }
}

void modificarEstado(int equipos[]) {
    int id, nuevoEstado;
    cout << "\nIngrese el ID de la PC a modificar (1-20): ";
    cin >> id;
    if(id >= 1 && id <= 20) {
        cout << "Seleccione el nuevo estado (0=Libre, 1=Ocupada, 2=Mantenimiento): ";
        cin >> nuevoEstado;
        if(nuevoEstado >= 0 && nuevoEstado <= 2) {
            equipos[id-1] = nuevoEstado;
            cout << "Estado de la PC #" << id << " actualizado correctamente.\n";
        } else {
            cout << "Estado invalido.\n";
        }
    } else {
        cout << "ID de equipo invalido.\n";
    }
}

void registrarIncidente(RegistroBitacora bitacora[], int &contador, int equipos[]) {
    if(contador >= MAX_REGISTROS) {
        cout << "\nError: La bitacora de memoria esta llena.\n";
        return;
    }
    
    int id;
    cout << "\n--- REGISTRAR INCIDENTE ---\n";
    cout << "ID del equipo (1-20): ";
    cin >> id;
    
    if(id >= 1 && id <= 20) {
        bitacora[contador].idEquipo = id;
        equipos[id-1] = 2; // Al reportar incidente, pasa a mantenimiento por seguridad
        
        cout << "Hora del incidente (ej. 14:30): ";
        cin >> ws; getline(cin, bitacora[contador].hora);
        
        cout << "Tipo de incidente (Hardware/Software/Red): ";
        getline(cin, bitacora[contador].tipoIncidente);
        
        cout << "Descripcion breve: ";
        getline(cin, bitacora[contador].descripcion);
        
        contador++;
        cout << "iIncidente registrado! La PC #" << id << " ha sido puesta en MANTENIMIENTO.\n";
    } else {
        cout << "ID invalido.\n";
    }
}

void consultarHistorial(RegistroBitacora bitacora[], int contador) {
    cout << "\n--- HISTORIAL DE INCIDENTES ---\n";
    if(contador == 0) {
        cout << "No hay registros actualmente.\n";
        return;
    }
    for(int i = 0; i < contador; i++) {
        cout << "PC #" << bitacora[i].idEquipo 
             << " | Hora: " << bitacora[i].hora 
             << " | Tipo: " << bitacora[i].tipoIncidente 
             << " | Detalle: " << bitacora[i].descripcion << "\n";
    }
}