#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <json/json.h> // Biblioteca para manejar JSON

namespace beast = boost::beast;     // Alias para Boost.Beast
namespace http = beast::http;      // Alias para HTTP
namespace net = boost::asio;       // Alias para Boost.Asio
using tcp = boost::asio::ip::tcp;  // Alias para TCP

// Configuración de la base de datos
const std::string DB_HOST = "kernelbd.co9kcumk48i6.us-east-1.rds.amazonaws.com";
const std::string DB_USER = "admin";
const std::string DB_PASSWORD = "Jagerylia0306.,";
const std::string DB_NAME = "kernel";

// Estados del proceso
enum class ProcessState {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

// Función para convertir el estado del proceso a string
std::string stateToString(ProcessState state) {
    switch (state) {
        case ProcessState::NEW: return "NEW";
        case ProcessState::READY: return "READY";
        case ProcessState::RUNNING: return "RUNNING";
        case ProcessState::WAITING: return "WAITING";
        case ProcessState::TERMINATED: return "TERMINATED";
        default: return "UNKNOWN";
    }
}

// Función para registrar un log en la base de datos
void logProcessState(ProcessState state) {
    try {
        // Conexión a la base de datos
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> connection(driver->connect(DB_HOST, DB_USER, DB_PASSWORD));
        connection->setSchema(DB_NAME);

        // Insertar el log en la base de datos
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        std::string query = "INSERT INTO logs (message) VALUES ('Proceso en estado: " + stateToString(state) + "')";
        stmt->execute(query);

        std::cout << "Log registrado: " << stateToString(state) << std::endl;

    } catch (sql::SQLException& e) {
        std::cerr << "Error al registrar el log: " << e.what() << std::endl;
    }
}

// Simulador de procesos
void simulateProcess() {
    ProcessState state = ProcessState::NEW;
    logProcessState(state);

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simula tiempo de transición
    state = ProcessState::READY;
    logProcessState(state);

    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simula tiempo de ejecución
    state = ProcessState::RUNNING;
    logProcessState(state);

    std::this_thread::sleep_for(std::chrono::seconds(3)); // Simula espera
    state = ProcessState::WAITING;
    logProcessState(state);

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simula finalización
    state = ProcessState::TERMINATED;
    logProcessState(state);
}

// Función para obtener los logs desde la base de datos
std::string getLogsFromDatabase() {
    try {
        // Conexión a la base de datos
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> connection(driver->connect(DB_HOST, DB_USER, DB_PASSWORD));
        connection->setSchema(DB_NAME);

        // Ejecutar la consulta
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM logs"));

        // Convertir los resultados a JSON
        Json::Value logs(Json::arrayValue);
        while (res->next()) {
            Json::Value log;
            log["id"] = res->getInt("id");
            log["message"] = res->getString("message");
            log["timestamp"] = res->getString("timestamp");
            logs.append(log);
        }

        // Convertir el JSON a string
        Json::StreamWriterBuilder writer;
        return Json::writeString(writer, logs);

    } catch (sql::SQLException& e) {
        std::cerr << "Error al obtener los logs: " << e.what() << std::endl;
        return "{\"error\": \"Error al obtener los logs\"}";
    }
}

// Función para manejar las solicitudes HTTP
void handleRequest(http::request<http::string_body> req, http::response<http::string_body>& res) {
    if (req.method() == http::verb::get && req.target() == "/logs") {
        // Obtener los logs desde la base de datos
        std::string logs = getLogsFromDatabase();

        // Configurar la respuesta HTTP
        res.result(http::status::ok);
        res.set(http::field::content_type, "application/json");
        res.body() = logs;
        res.prepare_payload();
    } else if (req.method() == http::verb::post && req.target() == "/simulate") {
        // Iniciar la simulación de procesos
        simulateProcess();

        // Configurar la respuesta HTTP
        res.result(http::status::ok);
        res.set(http::field::content_type, "text/plain");
        res.body() = "Simulación de procesos completada";
        res.prepare_payload();
    } else {
        // Respuesta para rutas no encontradas
        res.result(http::status::not_found);
        res.set(http::field::content_type, "text/plain");
        res.body() = "Ruta no encontrada";
        res.prepare_payload();
    }
}

int main() {
    try {
        // Configuración del servidor
        const int port = 8080;
        net::io_context ioc;
        tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), port));

        std::cout << "Servidor iniciado en el puerto " << port << std::endl;

        while (true) {
            // Aceptar conexiones
            tcp::socket socket(ioc);
            acceptor.accept(socket);

            // Leer la solicitud HTTP
            beast::flat_buffer buffer;
            http::request<http::string_body> req;
            http::read(socket, buffer, req);

            // Crear la respuesta HTTP
            http::response<http::string_body> res;
            handleRequest(req, res);

            // Enviar la respuesta
            http::write(socket, res);
        }

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}