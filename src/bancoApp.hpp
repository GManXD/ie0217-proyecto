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


enum subopciones{
    // Opciones disponibles para el menu
    REGISTRAR_CLIENTE = 1,
    VERIFICAR_CLIENTE, //2
    PRESTAMOS_ACTIVOS,  // 3
    SALDOS, // 4
    CUOTAS_PENTIENTES,  // 5
    DEPOSITOS_TRANSFERENCIAS,  // 6
    REGRESAR,  // 7
    OPCIONES_MAX_SUB
};

enum opcionesDeposito{
    DEPOSITAR = 1,
    TRANSFERENCIA, //2
    REGRESAR_DEPOSITO,  // Cambiado de REGRESAR a REGRESAR_DEPOSITO
    OPCIONES_MAX_DEP
};

class BancoApp {
private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

public:
    BancoApp();
    ~BancoApp();
    void mostrarInformacionGeneral();
    int generarIDCliente();
    int generarIDCuenta();
    bool clienteExiste(int IDCliente);
    bool cuentaExiste(int IDCuenta);
    void registrarCliente();
    void obtenerPrestamosActivos(int IDCliente);
    void obtenerSaldos(int IDCliente);
    void obtenerCuotasPendientes(int IDPrestamo);
    void realizarDeposito();
    void realizarTransferencia();
};

#endif // BANCOAPP_HPP
