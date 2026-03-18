#include <iostream>
#include <string>

using namespace std;

int main() {
    // Definición de variables solicitadas
    int id_usuario;
    int num_pc;
    int tiempo_minutos;
    string nivel_estudio;
    
    // Variables para el control del flujo del programa
    int opcion;
    char continuar;

    // Mensaje de bienvenida
    cout << "==========================================\n";
    cout << "   Sistema de Registro SIG-Conecta v1.0   \n";
    cout << "==========================================\n";

    // Ciclo de continuidad principal
    do {
        // Despliegue del menú de usuario
        cout << "\n--- MENU PRINCIPAL ---\n";
        cout << "1. Registrar ingreso\n";
        cout << "2. Consultar disponibilidad de equipos\n";
        cout << "3. Salir del sistema\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Estructura selectiva para el menú
        switch (opcion) {
            case 1:
                cout << "\n--- REGISTRO DE INGRESO ---\n";
                
                // Lógica de validación para ID de usuario (debe ser mayor a 0)
                do {
                    cout << "Ingrese el ID del usuario (mayor a 0): ";
                    cin >> id_usuario;
                    if (id_usuario <= 0) {
                        cout << "Error: El ID debe ser un numero positivo. Intente de nuevo.\n";
                    }
                } while (id_usuario <= 0);

                // Lógica de validación para número de PC (entre 1 y 20)
                do {
                    cout << "Ingrese el numero de PC asignada (1 - 20): ";
                    cin >> num_pc;
                    if (num_pc < 1 || num_pc > 20) {
                        cout << "Error: El numero de PC no es valido. Debe ser entre 1 y 20.\n";
                    }
                } while (num_pc < 1 || num_pc > 20);

                // Captura del resto de los datos sin validación estricta en esta versión
                cout << "Ingrese el tiempo de uso (en minutos): ";
                cin >> tiempo_minutos;
                
                cout << "Ingrese el nivel de estudios (ej. Primaria, Secundaria): ";
                cin >> nivel_estudio;

                cout << "\n¡Registro completado con exito!\n";
                break;

            case 2:
                // Consulta estática de disponibilidad
                cout << "\n--- DISPONIBILIDAD DE EQUIPOS ---\n";
                cout << "Actualmente hay equipos disponibles en el laboratorio.\n";
                cout << "Total de equipos: 20.\n";
                break;

            case 3:
                cout << "\nSaliendo del sistema de registro...\n";
                // Forzamos la salida asignando 'N' a continuar
                continuar = 'N'; 
                break;

            default:
                cout << "\nError: Opcion no valida. Seleccione 1, 2 o 3.\n";
                break;
        }

        // Si el usuario no eligió salir, preguntamos si desea hacer otra operación
        if (opcion != 3) {
            cout << "\n¿Desea realizar otra operacion en el sistema? (S/N): ";
            cin >> continuar;
        }

    } while (toupper(continuar) == 'S'); // toupper convierte la letra a mayúscula para aceptar 's' o 'S'

    cout << "Gracias por utilizar el sistema SIG-Conecta. Hasta pronto\n";

    return 0;
}