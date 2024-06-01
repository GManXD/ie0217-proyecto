#include "bancoApp.hpp"
#include <iostream>

using namespace std;

int main() {
    BancoApp app;

    if (app.comprobarConexion()) {
        cout << "Conexión a la base de datos exitosa." << endl;
    } else {
        cout << "Error al conectar con la base de datos." << endl;
        return 1; // Salir si no se puede conectar
    }

    int opcion;

    do {
        cout << "1. Atención al Cliente\n";
        cout << "2. Información General\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (opcion == 1) {
            int subOpcion;
            int IDCliente;

            do {
                cout << "1. Registrar Cliente\n";
                cout << "2. Verificar Cliente\n";
                cout << "3. Obtener Prestamos Activos\n";
                cout << "4. Obtener Saldos\n";
                cout << "5. Obtener Cuotas Pendientes\n";
                cout << "6. Regresar al Menú Principal\n";
                cout << "Seleccione una opción: ";
                cout << "\n ------------------------------------------------------------------------\n\n";
                cin >> subOpcion;

                switch(subOpcion) {
                    case 1:
                        cout << "\nRegistrando Cliente... \n" << endl;
                    case 2:
                        cout << "\nIngrese el ID del Cliente: \n";
                        break;
                    case 3:
                        cout << "\nIngrese el ID del Cliente: \n";
                        break;
                    case 4:
                        cout << "\nIngrese el ID del Cliente: \n";
                        break;
                    case 5:
                        cout << "\nIngrese el ID del Prestamo: \n";
                    case 6:
                        cout << "\nRegresando al menú principal. \n" << endl;
                        break;
                    default:
                        cout << "\nOpción no válida. \n" << endl;
                        break;
                }
            } while(subOpcion != 6);
        } else if (opcion == 2) {
            app.mostrarInformacionGeneral();
        } else if (opcion != 3) {
            cout << "\nOpción no válida.\n" << endl;
        }
    } while(opcion != 3);

    cout << "\nSaliendo del programa.\n" << endl;

    return 0;
}