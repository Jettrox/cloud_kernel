#include "routes/routes.h"
#include "database/connection.h"

int main() {
    start_server();

    // Configura las credenciales de la base de datos
    std::string host = "your-rds-endpoint.amazonaws.com";
    std::string user = "admin";
    std::string password = "yourpassword";
    std::string database = "yourdatabase";

    // Crea la conexión
    DatabaseConnection db(host, user, password, database);

    try {
        db.connect();

        // Ejecuta una consulta
        sql::ResultSet* res = db.executeQuery("SELECT * FROM your_table");
        while (res->next()) {
            std::cout << "ID: " << res->getInt("id") << ", Name: " << res->getString("name") << std::endl;
        }
        delete res;

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}