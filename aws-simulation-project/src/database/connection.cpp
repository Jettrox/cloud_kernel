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

#include "connection.h"

// Constructor
DatabaseConnection::DatabaseConnection(const std::string& host, const std::string& user, const std::string& password, const std::string& database)
    : host(host), user(user), password(password), database(database), driver(nullptr), connection(nullptr) {}

// Método para establecer la conexión
void DatabaseConnection::connect() {
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        connection = driver->connect(host, user, password);
        connection->setSchema(database);
        std::cout << "Conexión exitosa a la base de datos: " << database << std::endl;
    } catch (sql::SQLException& e) {
        std::cerr << "Error al conectar a la base de datos: " << e.what() << std::endl;
        throw;
    }
}

// Método para ejecutar consultas
sql::ResultSet* DatabaseConnection::executeQuery(const std::string& query) {
    try {
        sql::Statement* stmt = connection->createStatement();
        sql::ResultSet* res = stmt->executeQuery(query);
        return res;
    } catch (sql::SQLException& e) {
        std::cerr << "Error al ejecutar la consulta: " << e.what() << std::endl;
        throw;
    }
}

// Método para cerrar la conexión
void DatabaseConnection::close() {
    if (connection) {
        delete connection;
        connection = nullptr;
        std::cout << "Conexión cerrada." << std::endl;
    }
}

// Destructor
DatabaseConnection::~DatabaseConnection() {
    close();
}