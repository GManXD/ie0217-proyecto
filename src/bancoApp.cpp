#include "bancoApp.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

// Plantilla de función para manejar la entrada de diferentes tipos de datos
template <typename T>
void validarEntrada(const std::string &prompt, T &variable) {
    static_assert(std::is_arithmetic<T>::value, "Se requiere un tipo de dato numérico");
    while (true) {
        std::cout << prompt;
        std::cin >> variable;

        if (std::cin.fail()) {
            std::cin.clear(); // Limpia el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora el resto de la línea
            std::cout << "Entrada inválida. Por favor, intente nuevamente." << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el búfer de entrada
            break; // Sal del bucle si la entrada es válida
        }
    }
}

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

int BancoApp::generarIDCertificado() {
    int IDCertificado;
    bool idExiste;

    do {
        IDCertificado = rand() % 10000; // Generar un ID aleatorio entre 0 y 9999
        idExiste = certificadoExiste(IDCertificado);
    } while (idExiste);

    return IDCertificado;
}

bool BancoApp::certificadoExiste(int IDCertificado) {
    try {
        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM Certificados WHERE IDCertificado = ?");
        pstmt->setInt(1, IDCertificado);
        sql::ResultSet *res = pstmt->executeQuery();

        bool existe = res->next();
        
        delete res;
        delete pstmt;
        return existe;
    } catch (sql::SQLException &e) {
        cout << "Error al verificar el certificado: " << e.what() << endl;
        return false;  // Error al verificar el certificado
    }
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
    int opcionPrestamo;
    string tipoMoneda;
    string generar;     // Generar prestamo o no
    int IDCliente;
    int monto;
    do{
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
        validarEntrada("Si desea más información sobre un préstamo digite el numero de prestamo, de lo contrario digite 0: ", opcionPrestamo);
        cout << "\n\n ------------------------------------------------------------------------\n\n";

        int interes, cuotas, personalizar;
        switch (opcionPrestamo) {
            case PRESTAMO_PERSONAL:
                interes = INTERES_PERSONAL
                cuotas = CUOTAS_PERSONALES
                cout << "Un préstamo personal puede ser utilizado para cualquier gasto personal.\n";
                cout << "Opciones predefinidas para prestamos personales: \n";
                cout << "Tasa de interés fija: " << interes << "% mensual\n";
                cout << "Cantidad de cuotas: " << cuotas << "\n";
                while (true){
                    validarEntrada("Si desea personalizar estas opciones digite 1, de lo contrario digite 0: \n", personalizar);
                    if (personalizar == 0 || personalizar == 1){
                        string opcionMoneda;
                        while (true){
                            cout << "Digite el tipo de moneda -> 1: Colones 2: Dolares \n";
                            cin >> opcionMoneda;
                            if (opcionMoneda == "1"){
                                tipoMoneda = "Colones";
                                break;
                            }
                            else if (opcionMoneda == "2"){
                                tipoMoneda = "Dolares";
                                break;
                            }
                            else{
                                cout << "Opcion no valida\n";
                            }
                        }
                    }
                    if (personalizar == 1){
                        validarEntrada("Digite la taza de interes mensual: ", interes);
                        validarEntrada("Digite la cantidad de cuotas: ", cuotas);
                        validarEntrada("Digite el monto del prestamo: ", monto);
                        break;
                    }
                    else if (personalizar == 0){
                        validarEntrada("Digite el monto del prestamo: ", monto);
                        break;
                    }
                    else{
                        cout << "Opción no valida\n";
                    }
                }
                cout << "A continuación se muestra la tabla de pagos para el prestamo: " << endl;


                while (true){
                    cout << "Si desea generar el prestamo digite 1, de lo contrario digite 0: ";
                    cin >> generar;

                    if (generar == "0"){
                        cout << "De acuerdo, volviendo al menú principal.... " ;
                        break;
                    }
                    else if (generar == "1"){
                        string tipoPrestamo = "Personal";
                        validarEntrada("Digite su ID de cliente: ", IDCliente);
                        // Verificar si el id del cliente existe
                        if (clienteExiste(IDCliente)) {
                            try {
                                
                                int IDPrestamo = generarIDPrestamo(); // Generar un ID de Prestamo único

                                sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Prestamos (IDPrestamo, IDCliente, TipoPrestamo, MontoPagar, Moneda, TasaInteres, Periodo, MontoInicial) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
                                pstmt->setInt(1, IDPrestamo);
                                pstmt->setInt(2, IDCliente);
                                pstmt->setString(3, tipoPrestamo);
                                pstmt->setInt(4, monto);
                                pstmt->setString(5, tipoMoneda);
                                pstmt->setInt(6, interes);
                                pstmt->setInt(7, cuotas);
                                pstmt->setInt(8, monto);
                                pstmt->execute();
                                delete pstmt;

                                
                                // Insertar tambien para DetallePrestamo
                                pstmt = con->prepareStatement("INSERT INTO DetallePrestamo (IDPrestamo, NumeroCuota, MontoCuota, PeriodoVencimiento, EstadoPago) VALUES (?, ?, ?, ?, ?)");
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
                        break;
                    } else {
                        cout << "Opcion no valida\n";
                    }
                }
                break;

            case PRESTAMO_HIPOTECARIO:
                interes = INTERES_HIPOTECARIO
                cuotas = CUOTAS_HIPOTECARIO
                cout << "Un préstamo hipotecario está destinado a la compra de bienes inmuebles.\n";
                cout << "Opciones predefinidas para prestamos hipotecarios: \n";
                cout << "Tasa de interés fija: " << interes << "% mensual\n";
                cout << "Cantidad de cuotas: " << cuotas << "\n";
                while (true){
                    validarEntrada("Si desea personalizar estas opciones digite 1, de lo contrario digite 0: \n", personalizar);
                    if (personalizar == 0 || personalizar == 1){
                        string opcionMoneda;
                        while (true){
                            cout << "Digite el tipo de moneda -> 1: Colones 2: Dolares \n";
                            cin >> opcionMoneda;
                            if (opcionMoneda == "1"){
                                tipoMoneda = "Colones";
                                break;
                            }
                            else if (opcionMoneda == "2"){
                                tipoMoneda = "Dolares";
                                break;
                            }
                            else{
                                cout << "Opcion no valida\n";
                            }
                        }
                    }
                    if (personalizar == 1){
                        validarEntrada("Digite la taza de interes mensual: ", interes);
                        validarEntrada("Digite la cantidad de cuotas: ", cuotas);
                        validarEntrada("Digite el monto del prestamo: ", monto);
                        break;
                    }
                    else if (personalizar == 0){
                        validarEntrada("Digite el monto del prestamo: ", monto);
                        break;
                    }
                    else{
                        cout << "Opción no valida\n";
                    }
                }
                cout << "A continuación se muestra la tabla de pagos para el prestamo: " << endl;
                
                while (true){
                    cout << "Si desea generar el prestamo digite 1, de lo contrario digite 0: ";
                    cin >> generar;

                    if (generar == "0"){
                        cout << "De acuerdo, volviendo al menú principal.... " ;
                        break;
                    }

                    else if (generar == "1"){
                        string tipoPrestamo = "Hipotecario";
                        validarEntrada("Digite su ID de cliente: ", IDCliente);
                        // Verificar si el id del cliente existe
                        if (clienteExiste(IDCliente)) {
                            try {
                                
                                int IDPrestamo = generarIDPrestamo(); // Generar un ID de Prestamo único

                                sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Prestamos (IDPrestamo, IDCliente, TipoPrestamo, MontoPagar, Moneda, TasaInteres, Periodo, MontoInicial) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
                                pstmt->setInt(1, IDPrestamo);
                                pstmt->setInt(2, IDCliente);
                                pstmt->setString(3, tipoPrestamo);
                                pstmt->setInt(4, monto);
                                pstmt->setString(5, tipoMoneda);
                                pstmt->setInt(6, interes);
                                pstmt->setInt(7, cuotas);
                                pstmt->setInt(8, monto);
                                pstmt->execute();
                                delete pstmt;

                                
                                // Insertar tambien para DetallePrestamo
                                pstmt = con->prepareStatement("INSERT INTO DetallePrestamo (IDPrestamo, NumeroCuota, MontoCuota, PeriodoVencimiento, EstadoPago) VALUES (?, ?, ?, ?, ?)");
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
                        break;
                    } else{
                        cout << "Opcion no valida\n";
                    }   
                }
                break;
            
            case PRESTAMO_PRENDARIO:
                interes = INTERES_PRENDARIO
                cuotas = CUOTAS_PRENDARIO
                cout << "Un préstamo prendario se garantiza con un bien mueble.\n";
                cout << "Opciones predefinidas para prestamos prendarios: \n";
                cout << "Tasa de interés fija: " << interes << "% mensual\n";
                cout << "Cantidad de cuotas: " << cuotas << "\n";
                while (true){
                    validarEntrada("Si desea personalizar estas opciones digite 1, de lo contrario digite 0: \n", personalizar);
                    if (personalizar == 0 || personalizar == 1){
                        string opcionMoneda;
                        while (true){
                            cout << "Digite el tipo de moneda -> 1: Colones 2: Dolares \n";
                            cin >> opcionMoneda;
                            if (opcionMoneda == "1"){
                                tipoMoneda = "Colones";
                                break;
                            }
                            else if (opcionMoneda == "2"){
                                tipoMoneda = "Dolares";
                                break;
                            }
                            else{
                                cout << "Opcion no valida\n";
                            }
                        }
                    }
                    if (personalizar == 1){
                        validarEntrada("Digite la taza de interes mensual: ", interes);
                        validarEntrada("Digite la cantidad de cuotas: ", cuotas);
                        validarEntrada("Digite el monto del prestamo: ", monto);
                        break;
                    }
                    else if (personalizar == 0){
                        validarEntrada("Digite el monto del prestamo: ", monto);
                        break;
                    }
                    else{
                        cout << "Opción no valida\n";
                    }
                }

                cout << "A continuación se muestra la tabla de pagos para el prestamo: " << endl;


                while(true){
                    cout << "Si desea generar el prestamo digite 1, de lo contrario digite 0: ";
                    cin >> generar;

                    if (generar == "0"){
                        cout << "De acuerdo, volviendo al menú principal.... " ;
                        break;
                    }

                    else if (generar == "1"){
                        string tipoPrestamo = "Prendario";
                        validarEntrada("Digite su ID de cliente: ", IDCliente);
                        // Verificar si el id del cliente existe
                        if (clienteExiste(IDCliente)) {
                            try {
                                
                                int IDPrestamo = generarIDPrestamo(); // Generar un ID de Prestamo único

                                sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Prestamos (IDPrestamo, IDCliente, TipoPrestamo, MontoPagar, Moneda, TasaInteres, Periodo, MontoInicial) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
                                pstmt->setInt(1, IDPrestamo);
                                pstmt->setInt(2, IDCliente);
                                pstmt->setString(3, tipoPrestamo);
                                pstmt->setInt(4, monto);
                                pstmt->setString(5, tipoMoneda);
                                pstmt->setInt(6, interes);
                                pstmt->setInt(7, cuotas);
                                pstmt->setInt(8, monto);
                                pstmt->execute();
                                delete pstmt;

                                
                                // Insertar tambien para DetallePrestamo
                                pstmt = con->prepareStatement("INSERT INTO DetallePrestamo (IDPrestamo, NumeroCuota, MontoCuota, PeriodoVencimiento, EstadoPago) VALUES (?, ?, ?, ?, ?)");
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
                        break;
                    } else {
                        cout << "Opcion no valida\n";
                    }
                }
                break;
            
            case CERTIFICADO_PLAZO:
                interes = INTERES_CERTIFICADO_PLAZO
                cuotas = PLAZO_CERTIFICADO
                cout << "Un CDP es un certificado de depósito a corto plazo que ofrece un retorno de interés fijo.\n";
                cout << "Opciones predefinidas para certificados de depósito a corto plazo: \n";
                cout << "Tasa de interés : " << interes << "% anual\n";
                cout << "Plazo : " << cuotas << "\n";
                cout << "Si desea personalizar estas opciones digite 1, si desea crear un certificado digite 0: \n";
                cin >> personalizar;
                if (personalizar == 1){
                    cout << "Digite el tipo de moneda: ";
                    cin >> tipoMoneda;
                    cout << "Digite la taza de interes anual: ";
                    cin >> interes;
                    cout << "Digite la cantidad de cuotas: ";
                    cin >> cuotas;
                    cout << "Digite el monto del certificado: ";
                    cin >> monto;

                }
                else if (personalizar == 0){
                    this->insertarCertificado();
                }
                else{
                    cout << "Opción no valida";
                }

                cout << "Al final del plazo de " << cuotas << " meses, recibirá un monto de : \n";

                break;

            case REGRESAR_PRESTAMO:
                cout << "Regresando al menú principal...\n"; 
                break;
            
            default:
                cout << "Opcion no valida\n";
                break;
        }
    } while (opcionPrestamo != REGRESAR_PRESTAMO);
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
        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT dp.IDPrestamo, dp.NumeroCuota, dp.MontoCuota, dp.PeriodoVencimiento, dp.EstadoPago "
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
            cout << "Periodo de Vencimiento: " << res->getString("PeriodoVencimiento") << "\n";
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
    string nombre, apellido;
    int cedula, telefono;
    cout << "Ingrese Nombre: ";
    cin >> nombre;
    cout << "Ingrese Apellido: ";
    cin >> apellido;
    validarEntrada("Ingrese Cedula: ", cedula);
    validarEntrada("Ingrese Telefono: ", telefono);

    try {
        int IDCliente = generarIDCliente(); // Generar un ID de cliente único

        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Clientes (IDCliente, Nombre, Apellido, NumeroCedula, Telefono) VALUES (?, ?, ?, ?, ?)");
        pstmt->setInt(1, IDCliente);
        pstmt->setString(2, nombre);
        pstmt->setString(3, apellido);
        pstmt->setString(4, to_string(cedula));
        pstmt->setString(5, to_string(telefono));
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
        string tipoCuenta, opcionMoneda;
        double monto;
        validarEntrada("Ingrese el ID del Cliente: ", IDCliente);
        if (!clienteExiste(IDCliente)) {
            cout << "Cliente no encontrado. Operación cancelada." << endl;
            return;
        }
        while (true){
            cout << "Digite el tipo de cuenta -> 1: Colones 2: Dolares \n";
            cin >> opcionMoneda;
            if (opcionMoneda == "1"){
                tipoCuenta = "Colones";
                break;
            }
            else if (opcionMoneda == "2"){
                tipoCuenta = "Dolares";
                break;
            }
            else{
                cout << "Opcion no valida\n";
            }
        }

        validarEntrada("Ingrese el monto a depositar: ", monto);

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
        string tipoCuentaOrigen, tipoCuentaDestino, opcionMoneda;
        double monto;
        double tasaCambioDolaresAColones = 600.0; // Ejemplo de tasa de cambio (1 dólar = 600 colones)
        double tasaCambioColonesADolares = 1 / tasaCambioDolaresAColones;

        validarEntrada("Ingrese el ID del Cliente origen: ", IDClienteOrigen);
        if (!clienteExiste(IDClienteOrigen)) {
            cout << "Cliente origen no encontrado. Operación cancelada." << endl;
            return;
        }
        while (true){
            cout << "Digite el tipo de cuenta origen -> 1: Colones 2: Dolares \n";
            cin >> opcionMoneda;
            if (opcionMoneda == "1"){
                tipoCuentaOrigen = "Colones";
                break;
            }
            else if (opcionMoneda == "2"){
                tipoCuentaOrigen = "Dolares";
                break;
            }
            else{
                cout << "Opcion no valida\n";
            }
        }

        validarEntrada("Ingrese el ID del Cliente destino: ", IDClienteDestino);
        if (!clienteExiste(IDClienteDestino)) {
            cout << "Cliente destino no encontrado. Operación cancelada." << endl;
            return;
        }

        while (true){
            cout << "Digite el tipo de cuenta destino -> 1: Colones 2: Dolares \n";
            cin >> opcionMoneda;
            if (opcionMoneda == "1"){
                tipoCuentaDestino = "Colones";
                break;
            }
            else if (opcionMoneda == "2"){
                tipoCuentaDestino = "Dolares";
                break;
            }
            else{
                cout << "Opcion no valida\n";
            }
        }

        validarEntrada("Ingrese el monto a transferir: ", monto);

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

void BancoApp::realizarAbono() {
    try {
        int IDClienteOrigen, IDPrestamo;
        string tipoCuentaOrigen, tipoMonedaPrestamo, opcionMoneda;
        double monto;
        double tasaCambioDolaresAColones = 600.0; // Ejemplo de tasa de cambio (1 dólar = 600 colones)
        double tasaCambioColonesADolares = 1 / tasaCambioDolaresAColones;

        validarEntrada("Ingrese el ID del Cliente origen: ", IDClienteOrigen);
        if (!clienteExiste(IDClienteOrigen)) {
            cout << "Cliente origen no encontrado. Operación cancelada." << endl;
            return;
        }

        while (true){
            cout << "Digite el tipo de cuenta origen -> 1: Colones 2: Dolares \n";
            cin >> opcionMoneda;
            if (opcionMoneda == "1"){
                tipoCuentaOrigen = "Colones";
                break;
            }
            else if (opcionMoneda == "2"){
                tipoCuentaOrigen = "Dolares";
                break;
            }
            else{
                cout << "Opcion no valida\n";
            }
        }

        validarEntrada("Ingrese el ID del Prestamo al cual desea abonar: ", IDPrestamo);
        if (!prestamoExiste(IDPrestamo)) {
            cout << "Prestamo no encontrado. Operación cancelada." << endl;
            return;
        }

        // Obtener el tipo de moneda del prestamo
        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT Moneda FROM Prestamos WHERE IDPrestamo = ?");
        pstmt->setInt(1, IDPrestamo);
        sql::ResultSet *res = pstmt->executeQuery();
        if (res->next()) {
            tipoMonedaPrestamo = res->getString("Moneda");
        } else {
            cout << "No se pudo encontrar el tipo de moneda del prestamo. Operación cancelada." << endl;
            delete res;
            delete pstmt;
            return;
        }

        validarEntrada("Ingrese el monto a abonar: ", monto);

        // Verificar que la cuenta origen tenga suficiente saldo
        pstmt = con->prepareStatement("SELECT Saldo FROM Cuentas WHERE IDCliente = ? AND TipoCuenta = ?");
        pstmt->setInt(1, IDClienteOrigen);
        pstmt->setString(2, tipoCuentaOrigen);
        res = pstmt->executeQuery();

        if (res->next()) {
            double saldoOrigen = res->getDouble("Saldo");
            if (saldoOrigen < monto) {
                cout << "Saldo insuficiente en la cuenta origen. Operación cancelada." << endl;
                delete res;
                delete pstmt;
                return;
            }
        } else {
            cout << "Error al obtener el saldo de la cuenta origen. Operación cancelada." << endl;
            delete res;
            delete pstmt;
            return;
        }
        delete res;
        delete pstmt;

        // Actualizar el saldo de la cuenta origen
        pstmt = con->prepareStatement("UPDATE Cuentas SET Saldo = Saldo - ? WHERE IDCliente = ? AND TipoCuenta = ?");
        pstmt->setDouble(1, monto);
        pstmt->setInt(2, IDClienteOrigen);
        pstmt->setString(3, tipoCuentaOrigen);
        pstmt->execute();


        // Convertir el monto si las cuentas son de tipos diferentes
        if (tipoCuentaOrigen != tipoMonedaPrestamo) {
            if (tipoCuentaOrigen == "Dolares" && tipoMonedaPrestamo == "Colones") {
                monto *= tasaCambioDolaresAColones;
            } else if (tipoCuentaOrigen == "Colones" && tipoMonedaPrestamo == "Dolares") {
                monto *= tasaCambioColonesADolares;
            } else {
                cout << "Tipo de cuenta no válido. Operación cancelada." << endl;
                return;
            }
        }

        // Realizar el abono
        pstmt = con->prepareStatement("UPDATE Prestamos SET MontoPagar = MontoPagar - ? WHERE IDPrestamo = ?");
        pstmt->setDouble(1, monto);
        pstmt->setInt(2, IDPrestamo);
        pstmt->execute();

        int IDTransaccion = generarIDTransaccion();
        cout << "Insertando transacción con los siguientes datos:" << endl;
        cout << "IDTransaccion: " << IDTransaccion << endl;
        cout << "IDCliente: " << IDClienteOrigen << endl;
        cout << "TipoTransaccion: Abono" << endl;
        cout << "Monto: " << monto << endl;
        cout << "IDPrestamo: " << IDPrestamo << endl;

        // Registrar la transaccion
        pstmt = con->prepareStatement("INSERT INTO Transacciones (IDTransaccion, IDCliente, TipoTransaccion, Monto, FechaTransaccion, IDCuentaDestino) VALUES (?, ?, ?, ?, CURRENT_TIMESTAMP, ?)");
        pstmt->setInt(1, IDTransaccion);
        pstmt->setInt(2, IDClienteOrigen);
        pstmt->setString(3, "Abono");
        pstmt->setDouble(4, monto);
        pstmt->setInt(5, IDPrestamo);
        pstmt->execute();
        cout << "Abono realizado exitosamente." << endl;
    } catch (sql::SQLException &e) {
        cout << "Error al realizar el abono: " << e.what() << endl;
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
        validarEntrada("Ingrese el ID del Cliente: ", IDCliente);
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

void BancoApp::insertarCertificado() {
    try {
        int idCertificado, idCliente, plazo_cert;
        string fechaEmisionStr, fechaVencimientoStr, estado, tipoCuenta, opcionMoneda;
        double monto, interes_plazo_cert;

        time_t now = time(0);
        tm *ltm = localtime(&now);
        char buffer[11];
        strftime(buffer, 11, "%Y-%m-%d", ltm);
        fechaEmisionStr = string(buffer);

        plazo_cert = PLAZO_CERTIFICADO
        interes_plazo_cert = INTERES_CERTIFICADO_PLAZO
        fechaVencimientoStr = agregarMeses(plazo_cert);

        idCertificado = generarIDCertificado(); // Generar un ID de certificado único

        validarEntrada("Ingrese el ID del Cliente: ", idCliente);
        cout << endl;
        if (!clienteExiste(idCliente)) {
            cout << "Cliente no encontrado. Operación cancelada." << endl;
            return;
        }

        while (true){
            cout << "Digite el tipo de moneda -> 1: Colones 2: Dolares \n";
            cin >> opcionMoneda;
            if (opcionMoneda == "1"){
                tipoCuenta = "Colones";
                break;
            }
            else if (opcionMoneda == "2"){
                tipoCuenta = "Dolares";
                break;
            }
            else{
                cout << "Opcion no valida\n";
            }
        }
        cout << endl;

        validarEntrada("Ingrese el monto del certificado: ", monto);
        cout << endl;

        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT Saldo FROM Cuentas WHERE IDCliente = ? AND TipoCuenta = ?");
        pstmt->setInt(1, idCliente);
        pstmt->setString(2, tipoCuenta);
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


        pstmt = con->prepareStatement("UPDATE Cuentas SET Saldo = Saldo - ? WHERE IDCliente = ? AND TipoCuenta = ?");
        pstmt->setDouble(1, monto);
        pstmt->setInt(2, idCliente);
        pstmt->setString(3, tipoCuenta);
        pstmt->execute();

        pstmt = con->prepareStatement("INSERT INTO Certificados(IDCertificado, IDCliente, Monto, Moneda, TasaInteres, Plazo, FechaEmision, FechaVencimiento, Estado) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
        pstmt->setInt(1, idCertificado);
        pstmt->setInt(2, idCliente);
        pstmt->setDouble(3, monto);
        pstmt->setString(4, tipoCuenta);
        pstmt->setDouble(5, interes_plazo_cert);
        pstmt->setInt(6, plazo_cert);
        pstmt->setString(7, fechaEmisionStr);
        pstmt->setString(8, fechaVencimientoStr);
        pstmt->setString(9, "Activo");
        pstmt->execute();
        delete(pstmt);

        cout << "Certificado realizado correctamente." << endl;
        return;

    } catch(sql::SQLException &e) {
        cout << "Error al crear el certificado: " << e.what() << endl;
    } catch(runtime_error &e) {
        cout << "Ocurrio un error : " << e.what() << endl;
    }
}

string BancoApp::agregarMeses(int meses) {
    time_t now = time(0);  // Current system time
    tm *ltm = localtime(&now);  // Convert to local time

    ltm->tm_mon += meses;  // Add months

    // Handle year increment if month exceeds 12
    while (ltm->tm_mon > 11) {  // Months in tm are 0-11
        ltm->tm_mon -= 12;  // Reduce month by 12
        ltm->tm_year += 1;  // Increment year
    }

    // Normalize the tm structure (important if day exceeds month's day capacity)
    mktime(ltm);

    // Format the date as YYYY-MM-DD
    stringstream dateStream;
    dateStream << (ltm->tm_year + 1900) << '-'  // tm_year is years since 1900
               << setw(2) << setfill('0') << (ltm->tm_mon + 1) << '-'  // tm_mon is month from 0-11
               << setw(2) << setfill('0') << ltm->tm_mday;  // tm_mday is day of the month

    return dateStream.str();
}