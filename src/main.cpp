#include "bancoApp.hpp"
#include <iostream>

using namespace std;

int main() {
    BancoApp app;

    if (app.comprobarConexion()) {
        cout << "Conexión a la base de datos exitosa." << endl;
    } else {
        cout << "Error al conectar con la base de datos." << endl;
        return 1; 
    }
    return 0;
}