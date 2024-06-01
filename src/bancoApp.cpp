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

bool BancoApp::comprobarConexion() {
    try {
        sql::Statement *stmt;
        stmt = con->createStatement();
        stmt->execute("SELECT 1");
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        cout << "Error al conectar con la base de datos: " << e.what() << endl;
        return false;
    }

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