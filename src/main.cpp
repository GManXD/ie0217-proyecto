#include "bancoApp.hpp"
#include <iostream>
#include <limits> 

using namespace std;

int main() {
    BancoApp app;

    int opcion;

    do {
        cout << "\n1. Atención al Cliente\n";
        cout << "2. Información General\n";
        cout << "3. Salir\n";
        validarEntrada("Seleccione una opción: ", opcion);

        if (opcion == 1) {
            int subOpcion;
            int IDCliente;

            do {
                cout << "\n1. Registrar Cliente\n";
                cout << "2. Verificar Cliente\n";
                cout << "3. Obtener Prestamos Activos\n";
                cout << "4. Obtener Saldos\n";
                cout << "5. Depositos, transferencias y abonos\n";
                cout << "6. Historial de transacciones\n";
                cout << "7. Regresar al Menú Principal\n";
                validarEntrada("Seleccione una opción: ", subOpcion);
                cout << "\n ------------------------------------------------------------------------\n\n";
                

                switch(subOpcion) {
                    case REGISTRAR_CLIENTE:
                        app.registrarCliente();
                        break;
                    case VERIFICAR_CLIENTE:
                        validarEntrada("\nIngrese el ID del Cliente: \n", IDCliente);
                        if (app.clienteExiste(IDCliente)) {
                            cout << "El cliente con ID " << IDCliente << " existe." << endl;
                        } else {
                            cout << "El cliente con ID " << IDCliente << " no existe." << endl;
                        }
                        break;
                    case PRESTAMOS_ACTIVOS:
                        validarEntrada("\nIngrese el ID del Cliente: \n", IDCliente);
                        if (!app.clienteExiste(IDCliente)) {
                            cout << "Cliente no encontrado. Operación cancelada." << endl;
                            break;
                        }

                        app.obtenerPrestamosActivos(IDCliente);
                        break;

                    case SALDOS:
                        validarEntrada("\nIngrese el ID del Cliente: \n", IDCliente);
                        if (!app.clienteExiste(IDCliente)) {
                            cout << "Cliente no encontrado. Operación cancelada." << endl;
                            break;
                        }

                        app.obtenerSaldos(IDCliente);
                        break;
                    case DEPOSITOS_TRANSFERENCIAS:
                        int opcionDeposito;
                        do {
                            cout << "\n1. Realizar depósito\n";
                            cout << "2. Realizar transferencia\n";
                            cout << "3. Abono a un prestamo\n";
                            cout << "4. Regresar al menú anterior\n";
                            validarEntrada("Seleccione una opción: ", opcionDeposito);

                            switch (opcionDeposito) {
                                case DEPOSITAR:
                                    app.realizarDeposito();
                                    break;
                                case TRANSFERENCIA:
                                    app.realizarTransferencia();
                                    break;
                                case ABONO:
                                    app.realizarAbono();
                                    break;
                                case REGRESAR_DEPOSITO:
                                    cout << "Regresando al menú anterior" << endl;
                                    break;
                                default:
                                    cout << "Opción no válida. Intente de nuevo." << endl;
                                    break;
                            }
                        } while (opcionDeposito != 4);
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
            } while(subOpcion != REGRESAR);
        } else if (opcion == 2) {
            app.mostrarInformacionGeneral();
        } else if (opcion != 3) {
            cout << "\nOpción no válida.\n" << endl;
        }
    } while(opcion != 3);

    cout << "\nSaliendo del programa.\n" << endl;

    return 0;
}
