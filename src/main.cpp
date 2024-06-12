#include "bancoApp.hpp"
#include <iostream>

using namespace std;

int main() {
    BancoApp app;

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
                cout << "\n1. Registrar Cliente\n";
                cout << "2. Verificar Cliente\n";
                cout << "3. Obtener Prestamos Activos\n";
                cout << "4. Obtener Saldos\n";
                cout << "5. Obtener Cuotas Pendientes\n";
                cout << "6. Depositos y transferencias\n";
                cout << "7. Historial de transacciones\n";
                cout << "8. Regresar al Menú Principal\n";
                cout << "Seleccione una opción: ";
                cout << "\n ------------------------------------------------------------------------\n\n";
                cin >> subOpcion;

                switch(subOpcion) {
                    case REGISTRAR_CLIENTE:
                    app.registrarCliente();
                    break;
                    case VERIFICAR_CLIENTE:
                        cout << "Ingrese el ID del Cliente: ";
                        cin >> IDCliente;
                        if (app.clienteExiste(IDCliente)) {
                            cout << "El cliente con ID " << IDCliente << " existe." << endl;
                        } else {
                            cout << "El cliente con ID " << IDCliente << " no existe." << endl;
                        }
                        break;
                    case PRESTAMOS_ACTIVOS:
                        cout << "\nIngrese el ID del Cliente: \n";
                        // Lógica para obtener préstamos activos
                        break;
                    case SALDOS:
                        cout << "\nIngrese el ID del Cliente: \n";
                        cin >> IDCliente;
                        app.obtenerSaldos(IDCliente);
                        break;
                    case CUOTAS_PENTIENTES:
                        cout << "\nIngrese el ID del Prestamo: \n";
                    case DEPOSITOS_TRANSFERENCIAS:
                        int opcionDeposito;
                        do {
                            cout << "\n1. Realizar depósito\n";
                            cout << "2. Realizar transferencia\n";
                            cout << "3. Regresar al menú anterior\n";
                            cout << "Seleccione una opción: ";
                            cin >> opcionDeposito;

                            switch (opcionDeposito) {
                                case DEPOSITAR:
                                    app.realizarDeposito();
                                    break;
                                case TRANSFERENCIA:
                                    app.realizarTransferencia();
                                    break;
                                case REGRESAR_DEPOSITO:
                                    cout << "Regresando al menú anterior" << endl;
                                    break;
                                default:
                                    cout << "Opción no válida. Intente de nuevo." << endl;
                                    break;
                            }
                        } while (opcionDeposito != 3);
                        break;

                    case HISTORIAL_TRANSACCIONES:
                        app.imprimirHistorialTransacciones();
                        break;
                    case REGRESAR:
                        cout << "\nRegresando al menú principal. \n" << endl;
                        break;
                    default:
                        cout << "\nOpción no válida. \n" << endl;
                        break;
                }
            } while(subOpcion != 8);
        } else if (opcion == 2) {
            app.mostrarInformacionGeneral();
        } else if (opcion != 3) {
            cout << "\nOpción no válida.\n" << endl;
        }
    } while(opcion != 3);

    cout << "\nSaliendo del programa.\n" << endl;

    return 0;
}