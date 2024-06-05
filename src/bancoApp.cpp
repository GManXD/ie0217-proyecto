#include "bancoApp.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

BancoApp::BancoApp() {
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("database-gestion-bancaria-proyecto.cfco6sequqsn.us-east-2.rds.amazonaws.com", "admin", "PBiKlEfqXUdOLsEskVJi");
    con->setSchema("gestion_bancaria");
}

BancoApp::~BancoApp() {
    delete con;
}

void BancoApp::mostrarInformacionGeneral() {
    cout << "\n ------------------------------------------------------------------------\n\n";
    cout << "\nBienvenido al Banco UCR\n";
    cout << "Tipos de préstamos disponibles:\n";
    cout << "1. Préstamo Personal: Tasa de interés 18%\n";
    cout << "   Un préstamo personal puede ser utilizado para cualquier gasto personal. Desde $400 hasta $20000 con una tasa de interés entre el 18% al 26%\n";
    cout << "2. Préstamo Hipotecario: Tasa de interés 7%\n";
    cout << "   Un préstamo hipotecario está destinado a la compra de bienes inmuebles.\n";
    cout << "3. Préstamo Prendario: Tasa de interés 5%\n";
    cout << "   Un préstamo prendario se garantiza con un bien mueble.\n";
    cout << "4. Certificado de Depósito a Plazo (CDP):\n";
    cout << "   Un CDP es un certificado de depósito a corto plazo que ofrece un retorno de interés fijo.\n";
    cout << "\n ------------------------------------------------------------------------\n\n";
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
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Clientes (Nombre, Apellido, NumeroCedula, Telefono) VALUES (?, ?, ?, ?)");
        pstmt->setString(1, nombre);
        pstmt->setString(2, apellido);
        pstmt->setString(3, cedula);
        pstmt->setString(4, telefono);
        pstmt->execute();

        delete pstmt; // Cerrar el PreparedStatement antes de ejecutar la siguiente consulta

        // Obtener el ID del cliente recién registrado
        pstmt = con->prepareStatement("SELECT LAST_INSERT_ID()");
        sql::ResultSet* res = pstmt->executeQuery();
        res->next();
        int IDCliente = res->getInt(1);

        cout << "Registro exitoso, su ID de cliente es: " << IDCliente << endl;

        delete res;
        delete pstmt;
    } catch (sql::SQLException &e) {
        cout << "Error al registrar el cliente: " << e.what() << endl;
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

        pstmt = con->prepareStatement("UPDATE Cuentas SET Saldo = Saldo + ? WHERE IDCliente = ? AND TipoCuenta = ?");
        pstmt->setDouble(1, monto);
        pstmt->setInt(2, IDClienteDestino);
        pstmt->setString(3, tipoCuentaDestino);
        pstmt->execute();

        delete pstmt;
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
