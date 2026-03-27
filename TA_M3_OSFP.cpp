#include <iostream>
#include <string>
#include <cctype> // Para la funcion toupper()

using namespace std;

// =========================================================================
// DECLARACIÓN DE PROTOTIPOS DE FUNCIONES
// =========================================================================
void mostrarBienvenida();
bool validarHorario(int hora);
bool validarID_Estudiante(int id_estudiante);
void asignarEquipo(int &totalEquipos); // Uso del operador & para paso por referencia

// =========================================================================
// FUNCIÓN PRINCIPAL
// =========================================================================
int main() {
    // Variables locales
    int totalEquipos = 20; // Actúa como nuestra variable principal de conteo
    int opcion;
    char continuar;

    // 1. Llamada a la función de bienvenida
    mostrarBienvenida();

    do {
        cout << "------------------------- MENU PRINCIPAL SIG-Conecta v2.0 -------------------------\n";
        cout << "1. Registrar ingreso\n";
        cout << "2. Consultar disponibilidad de equipos\n";
        cout << "3. Salir del sistema\n";
        cout << "===================================================================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                int id_usuario, hora_ingreso;
                
                // --- VALIDACIÓN DE HORARIO ---
                cout << "\nIngrese la hora de registro en formato 24h (0-23): ";
                cin >> hora_ingreso;
                
                // Si la función devuelve false, rompemos el caso y volvemos al menú
                if (!validarHorario(hora_ingreso)) {
                    break; 
                }

                // --- VALIDACIÓN DE ID ---
                do {
                    cout << "Ingrese el ID del usuario (1 - 1000): ";
                    cin >> id_usuario;
                    
                    if (!validarID_Estudiante(id_usuario)) {
                        cout << "Error: El ID ingresado no es valido.\n";
                    }
                } while (!validarID_Estudiante(id_usuario));

                // --- ASIGNACIÓN DE EQUIPO ---
                if (totalEquipos > 0) {
                    // Pasamos la variable por referencia. Se modificará permanentemente.
                    asignarEquipo(totalEquipos);
                    cout << "iRegistro completado con exito!\n";
                    cout << "Equipos restantes en el laboratorio: " << totalEquipos << "\n";
                } else {
                    cout << "Error: No hay equipos disponibles en este momento.\n";
                }
                break;
            }
            case 2:
                cout << "\n--- DISPONIBILIDAD DE EQUIPOS ---\n";
                cout << "Actualmente hay " << totalEquipos << " equipos disponibles.\n";
                break;
            case 3:
                cout << "\nSaliendo del sistema. iHasta pronto!\n";
                continuar = 'N'; // Forzamos la salida
                break;
            default:
                cout << "\nError: Opcion no valida. Seleccione 1, 2 o 3.\n";
                break;
        }

        // Evitar preguntar si el usuario ya eligió salir
        if (opcion != 3) {
            cout << "\n¿Desea realizar otra operacion en el sistema? (S/N): ";
            cin >> continuar;
        }

    } while (toupper(continuar) == 'S');

    return 0;
}

// =========================================================================
// DEFINICIÓN DE FUNCIONES
// =========================================================================

// Función 1: Muestra el banner institucional y reglas (No retorna nada)
void mostrarBienvenida() {
    cout << "===================================================================================\n";
    cout << "...................................................................................\n";
    cout << "..........@@@.......%%%%..%%%.%%%%...%%..%%%%%%%.....%%%%%.........................\n";
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
    cout << "                 Bienvenido al Sistema de Registro SIG-Conecta v2.0                \n";
    cout << "-----------------------------------------------------------------------------------\n";
    cout << "                          REGLAS DE USO DEL LABORATORIO:                           \n";
    cout << "                      1. No introducir alimentos ni bebidas.                       \n";
    cout << "               2. El uso de los equipos es estrictamente educativo.                \n";
    cout << "               3. Respetar el horario de operacion (08:00 - 20:00).                \n";
    cout << "===================================================================================\n";
}

// Función 2: Valida que la hora esté en el rango de operación (Retorna booleano)
bool validarHorario(int hora) {
    // Validar primero que el formato de hora exista
    if (hora < 0 || hora > 23) {
        cout << "Error: Formato de hora invalido.\n";
        return false;
    }
    // Validar que esté dentro del horario de servicio
    if (hora >= 8 && hora <= 20) {
        return true;
    } else {
        cout << "Aviso: No se permite el uso de equipos fuera del horario establecido (08:00 a 20:00 hrs).\n";
        return false;
    }
}

// Función 3: Valida el ID del estudiante usando paso por valor (Retorna booleano)
bool validarID_Estudiante(int id_estudiante) {
    // El id_estudiante es una copia del valor original
    if (id_estudiante > 0 && id_estudiante <= 1000) {
        return true; // Es válido
    } else {
        return false; // Es inválido
    }
}

// Función 4: Resta un equipo disponible usando paso por referencia (No retorna nada)
void asignarEquipo(int &totalEquipos) {
    // Al usar '&', estamos modificando directamente la variable de la función main()
    totalEquipos = totalEquipos - 1;
}