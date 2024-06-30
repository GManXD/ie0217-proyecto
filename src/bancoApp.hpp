/**
 * @file gestor.hpp
 * @version 1.0
 * @date 19/04/2024
 *  * @authors
 * - Jason Antonio Luna Vega
 * - María José Guevara Matarrita
 * - Óscar Francisco Rojas Rojas
 * @title Encabezados
 * @brief Declaraciones para la aplicación de Banco.
 * 
 * Este archivo contiene las declaraciones necesarias para la aplicación de Banco,
 * incluyendo las constantes para los tipos de préstamos, enums para las opciones del menú,
 * y la clase BancoApp que maneja las operaciones principales.
*/

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
#include <limits>
#include <iostream>

// Opciones predefinidas para los tipos de préstamos

// Préstamo personal
#define INTERES_PERSONAL 18;  // Taza de interés mensual
#define CUOTAS_PERSONALES 36;
// Préstamo Hipotecario
#define INTERES_HIPOTECARIO 7;    // Taza de interés mensual
#define CUOTAS_HIPOTECARIO 240 ;
// Préstamo Prendario
#define INTERES_PRENDARIO 5;  // Taza de interés mensual
#define CUOTAS_PRENDARIO 18;
// Certificado de deposito a plazo
#define INTERES_CERTIFICADO_PLAZO 2.0;  // Taza de interes anual
#define PLAZO_CERTIFICADO 8;

/**
 * @enum opcionesPrestamos
 * @brief Opciones disponibles para tipos de préstamos y certificados.
 */
enum opcionesPrestamos{
    
    REGRESAR_PRESTAMO = 0,
    PRESTAMO_PERSONAL = 1,
    PRESTAMO_HIPOTECARIO, //2
    PRESTAMO_PRENDARIO,
    CERTIFICADO_PLAZO, 
    OPCIONES_MAX_PRESAMOS
};
/**
 * @enum subopciones
 * @brief Opciones disponibles para el modulo de atención al cliente.
 */
enum subopciones{
    // Opciones disponibles para el modulo de atención al cliente
    REGISTRAR_CLIENTE = 1,
    VERIFICAR_CLIENTE, //2
    PRESTAMOS_ACTIVOS,  // 3
    SALDOS, // 4
    CUOTAS_PENTIENTES,  // 5
    DEPOSITOS_TRANSFERENCIAS,  // 6
    HISTORIAL_TRANSACCIONES,  // 7
    REGRESAR,  // 8
    OPCIONES_MAX_SUB
};

/**
 * @enum opcionesDeposito
 * @brief Opciones disponibles para depósitos, transferencias y abonos.
 */
enum opcionesDeposito{
    DEPOSITAR = 1,
    TRANSFERENCIA, //2
    ABONO,
    REGRESAR_DEPOSITO,  // Cambiado de REGRESAR a REGRESAR_DEPOSITO
    OPCIONES_MAX_DEP
};

/**
 * @brief Plantilla para validar una entrada.
 * 
 * Esta función plantilla valida la entrada del usuario.
 * 
 * @tparam T Tipo de la variable a validar
 * @param prompt Mensaje de solicitud para la entrada
 * @param variable Variable donde se almacenará la entrada válida
 */
template <typename T>
// Plantilla de la funcion de validar una entrada
void validarEntrada(const std::string &prompt, T &variable);

/**
 * @class BancoApp
 * @brief Clase principal para la aplicación del banco.
 * 
 * La clase BancoApp maneja las operaciones principales de la aplicación,
 * incluyendo la conexión a la base de datos y las operaciones de clientes y transacciones.
 */
class BancoApp {
private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

public:
    /**
     * @brief Constructor de la clase BancoApp.
     */
    BancoApp();

    /**
     * @brief Destructor de la clase BancoApp.
     */
    ~BancoApp();

    /**
     * @brief Muestra la información general sobre prestamos y certificados.
     * Incluye una tabla de pagos para prestamos y solicitud de prestamos o certificados
     */
    void mostrarInformacionGeneral();

    /**
     * @brief Genera un nuevo ID aleatorio para un cliente.
     * 
     * @return Nuevo ID de cliente
     */
    int generarIDCliente();

    /**
     * @brief Genera un nuevo ID aleatorio para una cuenta.
     * 
     * @return Nuevo ID de cuenta
     */
    int generarIDCuenta();

    /**
     * @brief Genera un nuevo ID aleatorio para un préstamo.
     * 
     * @return Nuevo ID de préstamo
     */
    int generarIDPrestamo();

    /**
     * @brief Genera un nuevo ID para una transacción.
     * 
     * @return Nuevo ID de transacción
     */
    int generarIDTransaccion();

    /**
     * @brief Verifica si un préstamo existe.
     * 
     * @param IDPrestamo ID del préstamo a verificar
     * @return true si el préstamo existe, false en caso contrario
     */
    bool prestamoExiste(int IDPrestamo);

    /**
     * @brief Verifica si un cliente existe.
     * 
     * @param IDCliente ID del cliente a verificar
     * @return true si el cliente existe, false en caso contrario
     */
    bool clienteExiste(int IDCliente);

    /**
     * @brief Verifica si una cuenta existe.
     * 
     * @param IDCuenta ID de la cuenta a verificar
     * @return true si la cuenta existe, false en caso contrario
     */
    bool cuentaExiste(int IDCuenta);

    /**
     * @brief Verifica si una transacción existe.
     * 
     * @param IDTransaccion ID de la transacción a verificar
     * @return true si la transacción existe, false en caso contrario
     */
    bool transaccionExiste(int IDTransaccion);

    /**
     * @brief Registra un nuevo cliente en el banco.
     */
    void registrarCliente();

    /**
     * @brief Obtiene los préstamos activos de un cliente.
     * 
     * @param IDCliente ID del cliente
     */
    void obtenerPrestamosActivos(int IDCliente);

    /**
     * @brief Obtiene los saldos de las cuentas de un cliente.
     * 
     * @param IDCliente ID del cliente
     */
    void obtenerSaldos(int IDCliente);

    /**
     * @brief Obtiene las cuotas pendientes de un préstamo.
     * 
     * @param IDPrestamo ID del préstamo
     */
    void obtenerCuotasPendientes(int IDPrestamo);

    /**
     * @brief Realiza un depósito en una cuenta.
     */
    void realizarDeposito();

    /**
     * @brief Realiza una transferencia entre cuentas.
     */
    void realizarTransferencia();

    /**
     * @brief Realiza un abono a un prestamo.
     */
    void realizarAbono();

    /**
     * @brief Imprime el historial de transacciones realizadas por un cliente.
     */
    void imprimirHistorialTransacciones();

    /**
     * @brief Inserta un certificado de depósito a plazo en la tabla certificados.
     */
    void insertarCertificado();

    /**
     * @brief Agrega un número específico de meses a la fecha actual.
     * 
     * @param meses Número de meses a agregar
     * @return Fecha actualizada en formato de cadena
     */
    std::string agregarMeses(int meses);
};

#endif // BANCOAPP_HPP
