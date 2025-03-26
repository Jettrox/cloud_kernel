#include <iostream>
#include <boost/asio.hpp> // Si usas Boost para el servidor

void start_server() {
    const std::string host = "0.0.0.0"; // Escucha en todas las interfaces
    const int port = 8080;              // Puerto público

    // Aquí configuras tu servidor (puedes usar Boost.Asio, sockets, etc.)
    std::cout << "Starting server on " << host << ":" << port << std::endl;

    // Ejemplo con Boost.Asio
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host), port));
    boost::asio::ip::tcp::socket socket(io_context);

    acceptor.accept(socket);
    std::cout << "Client connected!" << std::endl;

    // Aquí manejarías las solicitudes del cliente
}