#include "bancoApp.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

BancoApp::BancoApp() {
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("database-gestion-bancaria-proyecto.cfco6sequqsn.us-east-2.rds.amazonaws.com", "admin", "PBiKlEfqXUdOLsEskVJi");
    con->setSchema("gestion_bancaria");
    srand(time(0));
}

BancoApp::~BancoApp() {
    delete con;
}


int BancoApp::generarIDCliente() {
    int IDCliente;
    bool idExiste;

    do {
        IDCliente = rand() % 10000; // Generar un ID aleatorio entre 0 y 9999
        idExiste = clienteExiste(IDCliente);
    } while (idExiste);

    return IDCliente;
}

int BancoApp::generarIDPrestamo() {
    int IDPrestamo;
    bool idExiste;

    do {
        IDPrestamo = rand() % 10000; // Generar un ID aleatorio entre 0 y 9999
        idExiste = prestamoExiste(IDPrestamo);
    } while (idExiste);

    return IDPrestamo;
}

bool BancoApp::prestamoExiste(int IDPrestamo) {
    try {
        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM Prestamos WHERE IDPrestamo = ?");
        pstmt->setInt(1, IDPrestamo);
        sql::ResultSet *res = pstmt->executeQuery();

        bool existe = res->next();
        
        delete res;
        delete pstmt;
        return existe;
    } catch (sql::SQLException &e) {
        cout << "Error al verificar el prestamo: " << e.what() << endl;
        return false;  // Error al verificar el prestamo
    }
}




int BancoApp::generarIDCuenta() {
    int IDCuenta;
    bool idExiste;
    int intentos = 0;
    const int maxIntentos = 100000; // Aumentar el rango para reducir la probabilidad de colisión

    do {
        IDCuenta = rand() % maxIntentos; // Generar un ID aleatorio entre 0 y maxIntentos-1
        idExiste = cuentaExiste(IDCuenta);
        intentos++;
    } while (idExiste && intentos < maxIntentos);

    if (intentos == maxIntentos) {
        throw runtime_error("No se pudo generar un ID de cuenta único.");
    }

    return IDCuenta;
}


int BancoApp::generarIDTransaccion() {
    int IDTransaccion;
    bool idExiste;

    do {
        IDTransaccion = rand() % 100000; // Generar un ID aleatorio entre 0 y 99999
        idExiste = transaccionExiste(IDTransaccion);
    } while (idExiste);

    return IDTransaccion;
}

bool BancoApp::transaccionExiste(int IDTransaccion) {
    try {
        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM Transacciones WHERE IDTransaccion = ?");
        pstmt->setInt(1, IDTransaccion);
        sql::ResultSet *res = pstmt->executeQuery();

        bool existe = res->next();
        
        delete res;
        delete pstmt;
        return existe;
    } catch (sql::SQLException &e) {
        cout << "Error al verificar la transacción: " << e.what() << endl;
        return false;  // Error al verificar la transacción
    }
}


bool BancoApp::cuentaExiste(int IDCuenta) {
    try {
        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM Cuentas WHERE IDCuenta = ?");
        pstmt->setInt(1, IDCuenta);
        sql::ResultSet *res = pstmt->executeQuery();

        bool existe = res->next();
        
        delete res;
        delete pstmt;
        return existe;
    } catch (sql::SQLException &e) {
        cout << "Error al verificar la cuenta: " << e.what() << endl;
        return false;  // Error al verificar la cuenta
    }
}

void BancoApp::mostrarInformacionGeneral() {
    string opcionPrestamo;
    string tipoMoneda;
    string generar;     // Generar prestamo o no
    int IDCliente;
    int monto;
    cout << "\n ------------------------------------------------------------------------\n\n";
    cout << "\nBienvenido al Banco UCR\n";
    cout << "Tipos de préstamos y certificados disponibles:\n";
    cout << "1. Préstamo Personal: \n";
    cout << "   Un préstamo personal puede ser utilizado para cualquier gasto personal. \n";
    cout << "2. Préstamo Hipotecario: \n";
    cout << "   Un préstamo hipotecario está destinado a la compra de bienes inmuebles.\n";
    cout << "3. Préstamo Prendario: \n";
    cout << "   Un préstamo prendario se garantiza con un bien mueble.\n";
    cout << "4. Certificado de Depósito a Plazo (CDP):\n";
    cout << "   Un CDP es un certificado de depósito a corto plazo que ofrece un retorno de interés fijo.\n";
    cout << "Si desea más información sobre un préstamo digite el numero de prestamo, de lo contrario digite 0";
    cout << "\n\n ------------------------------------------------------------------------\n\n";
    cin >> opcionPrestamo;
    if (opcionPrestamo == "1"){
        int interes = INTERES_PERSONAL
        int cuotas = CUOTAS_PERSONALES
        string personalizar;
        cout << "Un préstamo personal puede ser utilizado para cualquier gasto personal.\n";
        cout << "Opciones predefinidas para prestamos personales: \n";
        cout << "Tasa de interés fija: " << interes << "% mensual\n";
        cout << "Cantidad de cuotas: " << cuotas << "\n";
        cout << "Si desea personalizar estas opciones digite 1, de lo contrario digite 0: \n";
        cin >> personalizar;
        if (personalizar == "1"){
            cout << "Digite el tipo de moneda: ";
            cin >> tipoMoneda;
            cout << "Digite la taza de interes mensual: ";
            cin >> interes;
            cout << "Digite la cantidad de cuotas: ";
            cin >> cuotas;
            cout << "Digite el monto del prestamo: ";
            cin >> monto;

        }
        else if (personalizar == "0"){
            cout << "Digite el tipo de moneda: ";
            cin >> tipoMoneda;
            cout << "Digite el monto del prestamo: ";
            cin >> monto;
        }
        else{
            cout << "Opción no valida";
        }

        cout << "A continuación se muestra la tabla de pagos para el prestamo: " << endl;



        cout << "Si desea generar el prestamo digite 1, de lo contrario digite 0: ";
        cin >> generar;

        if (generar == "0"){
            cout << "De acuerdo, volviendo al menú principal.... " ;
        }

        else if (generar == "1"){
            string tipoPrestamo = "Personal";
            cout << "Digite su ID de cliente: ";
            cin >> IDCliente;
            // Verificar si el id del cliente existe
            if (clienteExiste(IDCliente)) {
                try {
                    
                    int IDPrestamo = generarIDPrestamo(); // Generar un ID de Prestamo único

                    sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Prestamos (IDPrestamo, IDCliente, TipoPrestamo, Monto, Moneda, TasaInteres, Periodo) VALUES (?, ?, ?, ?, ?, ?, ?)");
                    pstmt->setInt(1, IDPrestamo);
                    pstmt->setInt(2, IDCliente);
                    pstmt->setString(3, tipoPrestamo);
                    pstmt->setInt(4, monto);
                    pstmt->setString(5, tipoMoneda);
                    pstmt->setInt(6, interes);
                    pstmt->setInt(7, cuotas);
                    pstmt->execute();
                    delete pstmt;

                    
                    // Insertar tambien para DetallePrestamo
                    pstmt = con->prepareStatement("INSERT INTO DetallePrestamo (IDPrestamo, NumeroCuota, MontoCuota, FechaVencimiento, EstadoPago) VALUES (?, ?, ?, ?, ?)");
                    pstmt->setInt(1, IDPrestamo);
                    pstmt->setInt(2, cuotas);
                    pstmt->setInt(3, monto);
                    string periodo = to_string(cuotas) + "meses";
                    pstmt->setString(4, periodo);
                    pstmt->setString(5, "Pendiente");
                    pstmt->execute();

                    delete pstmt;

                    cout << "Registro exitoso, su ID de Prestamo es: " << IDPrestamo << endl;

                } catch (sql::SQLException &e) {
                    cout << "Error al registrar el prestamo: " << e.what() << endl;
                } catch (runtime_error &e) {
                    cout << "Error: " << e.what() << endl;
                }
            } else {
                cout << "El cliente con ID " << IDCliente << " no existe." << endl;
            }
        }



    }
    else if (opcionPrestamo == "2"){
        int interes = INTERES_HIPOTECARIO
        int cuotas = CUOTAS_HIPOTECARIO
        string personalizar;
        cout << "Un préstamo hipotecario está destinado a la compra de bienes inmuebles.\n";
        cout << "Opciones predefinidas para prestamos hipotecarios: \n";
        cout << "Tasa de interés fija: " << interes << "% mensual\n";
        cout << "Cantidad de cuotas: " << cuotas << "\n";
        cout << "Si desea personalizar estas opciones digite 1, de lo contrario digite 0: \n";
        cin >> personalizar;
        if (personalizar == "1"){
            cout << "Digite el tipo de moneda: ";
            cin >> tipoMoneda;
            cout << "Digite la taza de interes mensual: ";
            cin >> interes;
            cout << "Digite la cantidad de cuotas: ";
            cin >> cuotas;
            cout << "Digite el monto del prestamo: ";
            cin >> monto;
        }
        else if (personalizar == "0"){
            cout << "Digite el tipo de moneda: ";
            cin >> tipoMoneda;
            cout << "Digite el monto del prestamo: ";
            cin >> monto;
        }
        else{
            cout << "Opción no valida";
        }

        cout << "A continuación se muestra la tabla de pagos para el prestamo: " << endl;
        

        cout << "Si desea generar el prestamo digite 1, de lo contrario digite 0: ";
        cin >> generar;

        if (generar == "0"){
            cout << "De acuerdo, volviendo al menú principal.... " ;
        }

        else if (generar == "1"){
            string tipoPrestamo = "Hipotecario";
            cout << "Digite su ID de cliente: ";
            cin >> IDCliente;
            // Verificar si el id del cliente existe
            if (clienteExiste(IDCliente)) {
                try {
                    
                    int IDPrestamo = generarIDPrestamo(); // Generar un ID de Prestamo único

                    sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Prestamos (IDPrestamo, IDCliente, TipoPrestamo, Monto, Moneda, TasaInteres, Periodo) VALUES (?, ?, ?, ?, ?, ?, ?)");
                    pstmt->setInt(1, IDPrestamo);
                    pstmt->setInt(2, IDCliente);
                    pstmt->setString(3, tipoPrestamo);
                    pstmt->setInt(4, monto);
                    pstmt->setString(5, tipoMoneda);
                    pstmt->setInt(6, interes);
                    pstmt->setInt(7, cuotas);
                    pstmt->execute();
                    delete pstmt;

                    
                    // Insertar tambien para DetallePrestamo
                    pstmt = con->prepareStatement("INSERT INTO DetallePrestamo (IDPrestamo, NumeroCuota, MontoCuota, FechaVencimiento, EstadoPago) VALUES (?, ?, ?, ?, ?)");
                    pstmt->setInt(1, IDPrestamo);
                    pstmt->setInt(2, cuotas);
                    pstmt->setInt(3, monto);
                    string periodo = to_string(cuotas) + "meses";
                    pstmt->setString(4, periodo);
                    pstmt->setString(5, "Pendiente");
                    pstmt->execute();

                    delete pstmt;

                    cout << "Registro exitoso, su ID de Prestamo es: " << IDPrestamo << endl;

                } catch (sql::SQLException &e) {
                    cout << "Error al registrar el prestamo: " << e.what() << endl;
                } catch (runtime_error &e) {
                    cout << "Error: " << e.what() << endl;
                }
            } else {
                cout << "El cliente con ID " << IDCliente << " no existe." << endl;
            }
        }

    }
    else if (opcionPrestamo == "3"){
        int interes = INTERES_PRENDARIO
        int cuotas = CUOTAS_PRENDARIO
        string personalizar;
        cout << "Un préstamo prendario se garantiza con un bien mueble.\n";
        cout << "Opciones predefinidas para prestamos prendarios: \n";
        cout << "Tasa de interés fija: " << interes << "% mensual\n";
        cout << "Cantidad de cuotas: " << cuotas << "\n";
        cout << "Si desea personalizar estas opciones digite 1, de lo contrario digite 0: \n";
        cin >> personalizar;
        if (personalizar == "1"){
            cout << "Digite el tipo de moneda: ";
            cin >> tipoMoneda;
            cout << "Digite la taza de interes mensual: ";
            cin >> interes;
            cout <<"Digite la cantidad de cuotas: ";
            cin >> cuotas;
            cout <<"Digite el monto del prestamo: ";
            cin >> monto;
        }
        else if (personalizar == "0"){
            cout << "Digite el tipo de moneda: ";
            cin >> tipoMoneda;
            cout << "Digite el monto del prestamo: ";
            cin >> monto;
        }
        else{
            cout << "Opción no valida";
        }

        cout << "A continuación se muestra la tabla de pagos para el prestamo: " << endl;



        cout << "Si desea generar el prestamo digite 1, de lo contrario digite 0: ";
        cin >> generar;

        if (generar == "0"){
            cout << "De acuerdo, volviendo al menú principal.... " ;
        }

        else if (generar == "1"){
            string tipoPrestamo = "Prendario";
            cout << "Digite su ID de cliente: ";
            cin >> IDCliente;
            // Verificar si el id del cliente existe
            if (clienteExiste(IDCliente)) {
                try {
                    
                    int IDPrestamo = generarIDPrestamo(); // Generar un ID de Prestamo único

                    sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Prestamos (IDPrestamo, IDCliente, TipoPrestamo, Monto, Moneda, TasaInteres, Periodo) VALUES (?, ?, ?, ?, ?, ?, ?)");
                    pstmt->setInt(1, IDPrestamo);
                    pstmt->setInt(2, IDCliente);
                    pstmt->setString(3, tipoPrestamo);
                    pstmt->setInt(4, monto);
                    pstmt->setString(5, tipoMoneda);
                    pstmt->setInt(6, interes);
                    pstmt->setInt(7, cuotas);
                    pstmt->execute();
                    delete pstmt;

                    
                    // Insertar tambien para DetallePrestamo
                    pstmt = con->prepareStatement("INSERT INTO DetallePrestamo (IDPrestamo, NumeroCuota, MontoCuota, FechaVencimiento, EstadoPago) VALUES (?, ?, ?, ?, ?)");
                    pstmt->setInt(1, IDPrestamo);
                    pstmt->setInt(2, cuotas);
                    pstmt->setInt(3, monto);
                    string periodo = to_string(cuotas) + "meses";
                    pstmt->setString(4, periodo);
                    pstmt->setString(5, "Pendiente");
                    pstmt->execute();

                    delete pstmt;

                    cout << "Registro exitoso, su ID de Prestamo es: " << IDPrestamo << endl;

                } catch (sql::SQLException &e) {
                    cout << "Error al registrar el prestamo: " << e.what() << endl;
                } catch (runtime_error &e) {
                    cout << "Error: " << e.what() << endl;
                }
            } else {
                cout << "El cliente con ID " << IDCliente << " no existe." << endl;
            }
        }

    }
    else if (opcionPrestamo == "4"){
        int interes = INTERES_CERTIFICADO_PLAZO
        int cuotas = PLAZO_CERTIFICADO
        string personalizar;
        cout << "Un CDP es un certificado de depósito a corto plazo que ofrece un retorno de interés fijo.\n";
        cout << "Opciones predefinidas para certificados de depósito a corto plazo: \n";
        cout << "Tasa de interés : " << interes << "% anual\n";
        cout << "Plazo : " << cuotas << "\n";
        cout << "Si desea personalizar estas opciones digite 1, de lo contrario digite 0: \n";
        cin >> personalizar;
        if (personalizar == "1"){
            cout << "Digite el tipo de moneda: ";
            cin >> tipoMoneda;
            cout << "Digite la taza de interes anual: ";
            cin >> interes;
            cout << "Digite la cantidad de cuotas: ";
            cin >> cuotas;
            cout << "Digite el monto del certificado: ";
            cin >> monto;

        }
        else if (personalizar == "0"){
            cout << "Digite el tipo de moneda: ";
            cin >> tipoMoneda;
            cout << "Digite el monto del certificado: ";
            cin >> monto;
        }
        else{
            cout << "Opción no valida";
        }

        cout << "Al final del plazo de " << cuotas << " meses, recibirá un monto de : ";
    }
    else if (opcionPrestamo == "0"){
        cout << "Regresando al menú principal...\n"; 
    }
    else{
        cout << "Opcion no valida\n";
    }
}

bool BancoApp::clienteExiste(int IDCliente) {
    try {
        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM Clientes WHERE IDCliente = ?");
        pstmt->setInt(1, IDCliente);
        sql::ResultSet *res = pstmt->executeQuery();

        if (res->next()) {
            cout << "Cliente encontrado:\n";
            cout << "ID: " << res->getInt("IDCliente") << "\n";
            cout << "Nombre: " << res->getString("Nombre") << "\n";
            cout << "Apellido: " << res->getString("Apellido") << "\n";
            cout << "Cedula: " << res->getString("NumeroCedula") << "\n";
            cout << "Telefono: " << res->getString("Telefono") << "\n";
            delete res;
            delete pstmt;
            return true;  // Cliente encontrado
        } else {
            delete res;
            delete pstmt;
            return false;  // Cliente no encontrado
        }
    } catch (sql::SQLException &e) {
        cout << "Error al verificar el cliente: " << e.what() << endl;
        return false;  // Error al verificar el cliente
}
}

//MODIFICADO PARA VER LOS PRESTAMOS ACTIVOS
void BancoApp::obtenerPrestamosActivos(int IDCliente) {
    try {
        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT dp.IDPrestamo, dp.NumeroCuota, dp.MontoCuota, dp.FechaVencimiento, dp.EstadoPago "
                                                              "FROM DetallePrestamo dp "
                                                              "JOIN Prestamos p ON dp.IDPrestamo = p.IDPrestamo "
                                                              "WHERE p.IDCliente = ? AND dp.EstadoPago = 'Pendiente'");
        pstmt->setInt(1, IDCliente);
        sql::ResultSet *res = pstmt->executeQuery();

        cout << "Préstamos activos para el cliente con ID " << IDCliente << ":\n";
        while (res->next()) {
            cout << "ID de Préstamo: " << res->getInt("IDPrestamo") << "\n";
            cout << "Número de Cuota: " << res->getInt("NumeroCuota") << "\n";
            cout << "Monto de Cuota: " << res->getDouble("MontoCuota") << "\n";
            cout << "Fecha de Vencimiento: " << res->getString("FechaVencimiento") << "\n";
            cout << "Estado de Pago: " << res->getString("EstadoPago") << "\n";
            cout << "------------------------\n";
        }

        delete res;
        delete pstmt;
    } catch (sql::SQLException &e) {
        cout << "Error al obtener los préstamos activos: " << e.what() << endl;
    }
} //HASTA ACA

void BancoApp::registrarCliente() {
    string nombre, apellido, cedula, telefono;
    cout << "Ingrese Nombre: ";
    cin >> nombre;
    cout << "Ingrese Apellido: ";
    cin >> apellido;
    cout << "Ingrese Cedula: ";
    cin >> cedula;
    cout << "Ingrese Telefono: ";
    cin >> telefono;

    try {
        int IDCliente = generarIDCliente(); // Generar un ID de cliente único

        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Clientes (IDCliente, Nombre, Apellido, NumeroCedula, Telefono) VALUES (?, ?, ?, ?, ?)");
        pstmt->setInt(1, IDCliente);
        pstmt->setString(2, nombre);
        pstmt->setString(3, apellido);
        pstmt->setString(4, cedula);
        pstmt->setString(5, telefono);
        pstmt->execute();
        delete pstmt;

        // Generar IDs de cuenta únicos para las cuentas en dólares y colones
        int IDCuentaDolares = generarIDCuenta();
        int IDCuentaColones = generarIDCuenta();

        // Crear cuentas en dólares y colones para el nuevo cliente
        pstmt = con->prepareStatement("INSERT INTO Cuentas (IDCuenta, IDCliente, TipoCuenta, Saldo) VALUES (?, ?, ?, ?)");
        pstmt->setInt(1, IDCuentaDolares);
        pstmt->setInt(2, IDCliente);
        pstmt->setString(3, "Dolares");
        pstmt->setDouble(4, 0.0);
        pstmt->execute();

        pstmt->setInt(1, IDCuentaColones);
        pstmt->setString(3, "Colones");
        pstmt->execute();

        delete pstmt;

        cout << "Registro exitoso, su ID de cliente es: " << IDCliente << endl;
        cout << "ID de cuenta en Dolares: " << IDCuentaDolares << endl;
        cout << "ID de cuenta en Colones: " << IDCuentaColones << endl;
    } catch (sql::SQLException &e) {
        cout << "Error al registrar el cliente: " << e.what() << endl;
    } catch (runtime_error &e) {
        cout << "Error: " << e.what() << endl;
    }
}


void BancoApp::realizarDeposito() {
    try {
        int IDCliente;
        string tipoCuenta;
        double monto;

        cout << "Ingrese el ID del Cliente: ";
        cin >> IDCliente;
        if (!clienteExiste(IDCliente)) {
            cout << "Cliente no encontrado. Operación cancelada." << endl;
            return;
        }

        cout << "Ingrese el tipo de cuenta (Dolares/Colones): ";
        cin >> tipoCuenta;
        cout << "Ingrese el monto a depositar: ";
        cin >> monto;

        sql::PreparedStatement *pstmt = con->prepareStatement("UPDATE Cuentas SET Saldo = Saldo + ? WHERE IDCliente = ? AND TipoCuenta = ?");
        pstmt->setDouble(1, monto);
        pstmt->setInt(2, IDCliente);
        pstmt->setString(3, tipoCuenta);
        pstmt->execute();

        delete pstmt;


        int IDTransaccion = generarIDTransaccion();
        pstmt = con->prepareStatement("INSERT INTO Transacciones (IDTransaccion, IDCliente, TipoTransaccion, Monto, FechaTransaccion, IDCuentaDestino) VALUES (?, ?, ?, ?, CURRENT_TIMESTAMP, ?)");
        pstmt->setInt(1, IDTransaccion);
        pstmt->setInt(2, IDCliente);
        pstmt->setString(3, "Depósito");
        pstmt->setDouble(4, monto);
        pstmt->setInt(5, IDCliente);
        pstmt->execute();
        delete pstmt;


        cout << "Depósito realizado exitosamente." << endl;
    } catch (sql::SQLException &e) {
        cout << "Error al realizar el depósito: " << e.what() << endl;
    }
}

void BancoApp::realizarTransferencia() {
    try {
        int IDClienteOrigen, IDClienteDestino;
        string tipoCuentaOrigen, tipoCuentaDestino;
        double monto;
        double tasaCambioDolaresAColones = 600.0; // Ejemplo de tasa de cambio (1 dólar = 600 colones)
        double tasaCambioColonesADolares = 1 / tasaCambioDolaresAColones;

        cout << "Ingrese el ID del Cliente origen: ";
        cin >> IDClienteOrigen;
        if (!clienteExiste(IDClienteOrigen)) {
            cout << "Cliente origen no encontrado. Operación cancelada." << endl;
            return;
        }

        cout << "Ingrese el tipo de cuenta origen (Dolares/Colones): ";
        cin >> tipoCuentaOrigen;

        cout << "Ingrese el ID del Cliente destino: ";
        cin >> IDClienteDestino;
        if (!clienteExiste(IDClienteDestino)) {
            cout << "Cliente destino no encontrado. Operación cancelada." << endl;
            return;
        }

        cout << "Ingrese el tipo de cuenta destino (Dolares/Colones): ";
        cin >> tipoCuentaDestino;

        cout << "Ingrese el monto a transferir: ";
        cin >> monto;

        // Verificar que la cuenta origen tenga suficiente saldo
        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT Saldo FROM Cuentas WHERE IDCliente = ? AND TipoCuenta = ?");
        pstmt->setInt(1, IDClienteOrigen);
        pstmt->setString(2, tipoCuentaOrigen);
        sql::ResultSet *res = pstmt->executeQuery();

        if (res->next()) {
            double saldoOrigen = res->getDouble("Saldo");
            if (saldoOrigen < monto) {
                cout << "Saldo insuficiente en la cuenta origen. Operación cancelada." << endl;
                delete res;
                delete pstmt;
                return;
            }
        } else {
            cout << "Cuenta origen no encontrada. Operación cancelada." << endl;
            delete res;
            delete pstmt;
            return;
        }

        delete res;
        delete pstmt;

        // Realizar la transferencia
        pstmt = con->prepareStatement("UPDATE Cuentas SET Saldo = Saldo - ? WHERE IDCliente = ? AND TipoCuenta = ?");
        pstmt->setDouble(1, monto);
        pstmt->setInt(2, IDClienteOrigen);
        pstmt->setString(3, tipoCuentaOrigen);
        pstmt->execute();

        // Convertir el monto si las cuentas son de tipos diferentes
        if (tipoCuentaOrigen != tipoCuentaDestino) {
            if (tipoCuentaOrigen == "Dolares" && tipoCuentaDestino == "Colones") {
                monto *= tasaCambioDolaresAColones;
            } else if (tipoCuentaOrigen == "Colones" && tipoCuentaDestino == "Dolares") {
                monto *= tasaCambioColonesADolares;
            } else {
                cout << "Tipo de cuenta no válido. Operación cancelada." << endl;
                return;
            }
        }

        pstmt = con->prepareStatement("UPDATE Cuentas SET Saldo = Saldo + ? WHERE IDCliente = ? AND TipoCuenta = ?");
        pstmt->setDouble(1, monto);
        pstmt->setInt(2, IDClienteDestino);
        pstmt->setString(3, tipoCuentaDestino);
        pstmt->execute();

        int IDTransaccion = generarIDTransaccion();
        cout << "Insertando transacción con los siguientes datos:" << endl;
        cout << "IDTransaccion: " << IDTransaccion << endl;
        cout << "IDCliente: " << IDClienteOrigen << endl;
        cout << "TipoTransaccion: Transferencia" << endl;
        cout << "Monto: " << monto << endl;
        cout << "IDCuentaDestino: " << IDClienteDestino << endl;

        pstmt = con->prepareStatement("INSERT INTO Transacciones (IDTransaccion, IDCliente, TipoTransaccion, Monto, FechaTransaccion, IDCuentaDestino) VALUES (?, ?, ?, ?, CURRENT_TIMESTAMP, ?)");
        pstmt->setInt(1, IDTransaccion);
        pstmt->setInt(2, IDClienteOrigen);
        pstmt->setString(3, "Transferencia");
        pstmt->setDouble(4, monto);
        pstmt->setInt(5, IDClienteDestino);
        pstmt->execute();
        cout << "Transferencia realizada exitosamente." << endl;
    } catch (sql::SQLException &e) {
        cout << "Error al realizar la transferencia: " << e.what() << endl;
    }
}
void BancoApp::obtenerSaldos(int IDCliente) {
    try {
        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT TipoCuenta, Saldo FROM Cuentas WHERE IDCliente = ?");
        pstmt->setInt(1, IDCliente);
        sql::ResultSet *res = pstmt->executeQuery();

        cout << "Saldos de las cuentas del cliente con ID " << IDCliente << ":\n";
        while (res->next()) {
            string tipoCuenta = res->getString("TipoCuenta");
            double saldo = res->getDouble("Saldo");
            cout << "Tipo de cuenta: " << tipoCuenta << ", Saldo: " << saldo << endl;
        }

        delete res;
        delete pstmt;
    } catch (sql::SQLException &e) {
        cout << "Error al obtener los saldos: " << e.what() << endl;
    }
}

void BancoApp::imprimirHistorialTransacciones() {
    try {
        int IDCliente;
        
        cout << "Ingrese el ID del Cliente: ";
        cin >> IDCliente;
        if (!clienteExiste(IDCliente)) {
            cout << "Cliente no encontrado. Operación cancelada." << endl;
            return;
        }

        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT IDTransaccion, TipoTransaccion, Monto, FechaTransaccion, IDCuentaDestino FROM Transacciones WHERE IDCliente = ?");
        pstmt->setInt(1, IDCliente);
        sql::ResultSet *res = pstmt->executeQuery();

        cout << "Historial de Transacciones para el Cliente con ID " << IDCliente << ":" << endl;
        cout << "IDTransaccion | TipoTransaccion | Monto | FechaTransaccion | IDCuentaDestino" << endl;
        cout << "-------------------------------------------------------------" << endl;
        
        while (res->next()) {
            int IDTransaccion = res->getInt("IDTransaccion");
            string TipoTransaccion = res->getString("TipoTransaccion");
            double Monto = res->getDouble("Monto");
            string FechaTransaccion = res->getString("FechaTransaccion");
            int IDCuentaDestino = res->getInt("IDCuentaDestino");

            cout << IDTransaccion << " | " << TipoTransaccion << " | " << Monto << " | " << FechaTransaccion << " | " << IDCuentaDestino << endl;
        }

        delete res;
        delete pstmt;

    } catch (sql::SQLException &e) {
        cout << "Error al obtener el historial de transacciones: " << e.what() << endl;
    }
}