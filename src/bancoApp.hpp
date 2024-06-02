#ifndef BANCOAPP_HPP
#define BANCOAPP_HPP

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>

class BancoApp {
private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

    

public:
    BancoApp();
    ~BancoApp();
    void mostrarInformacionGeneral();
    bool clienteExiste(int IDCliente);
    void registrarCliente();
    void obtenerPrestamosActivos(int IDCliente);
    void obtenerSaldos(int IDCliente);
    void obtenerCuotasPendientes(int IDPrestamo);
};

#endif // BANCOAPP_HPP
