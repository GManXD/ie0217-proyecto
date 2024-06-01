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