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
    cout << "1. Préstamo Personal: Tasa de interés 3%\n";
    cout << "   Un préstamo personal puede ser utilizado para cualquier gasto personal.\n";
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
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM Clientes WHERE IDCliente = ?");
        pstmt->setInt(1, IDCliente);
        sql::ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            cout << "Cliente encontrado:" << endl;
            cout << "ID: " << res->getInt("IDCliente") << endl;
            cout << "Nombre: " << res->getString("Nombre") << endl;
            cout << "Apellido: " << res->getString("Apellido") << endl;
            cout << "Cedula: " << res->getString("NumeroCedula") << endl;
            cout << "Telefono: " << res->getString("Telefono") << endl;
        } else {
            cout <<"Cliente no encontrado" << endl;
        }

        delete pstmt;
        
        
        return res->next();
    } catch (sql::SQLException &e) {
        cout << "Error al verificar la existencia del cliente: " << e.what() << endl;
        return false;
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

