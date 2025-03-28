#ifndef CONNECTION_H
#define CONNECTION_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>
#include <string>

class DatabaseConnection {
private:
    std::string host;       // Dirección del host (RDS endpoint)
    std::string user;       // Usuario de la base de datos
    std::string password;   // Contraseña del usuario
    std::string database;   // Nombre de la base de datos
    sql::mysql::MySQL_Driver* driver; // Driver de MySQL
    sql::Connection* connection;      // Conexión a la base de datos

public:
    // Constructor
    DatabaseConnection(const std::string& host, const std::string& user, const std::string& password, const std::string& database);

    // Método para establecer la conexión
    void connect();

    // Método para ejecutar consultas
    sql::ResultSet* executeQuery(const std::string& query);

    // Método para cerrar la conexión
    void close();

    // Destructor
    ~DatabaseConnection();
};

#endif // CONNECTION_H