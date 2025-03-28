#ifndef PROCESS_CONTROLLER_H
#define PROCESS_CONTROLLER_H

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>

// Definimos los estados del proceso
enum class ProcessState {
    NEW,        // Proceso recién creado
    READY,      // Proceso listo para ejecutarse
    RUNNING,    // Proceso en ejecución
    WAITING,    // Proceso esperando respuesta de la base de datos
    TERMINATED  // Proceso terminado
};

class ProcessController {
private:
    ProcessState state;  // Estado actual del proceso
    std::string logFile; // Archivo de log

    // Método para registrar eventos en el log
    void logEvent(const std::string& message) {
        std::ofstream logStream(logFile, std::ios::app);
        if (logStream.is_open()) {
            logStream << "[" << getCurrentTime() << "] " << message << std::endl;
            logStream.close();
        } else {
            std::cerr << "Error: No se pudo abrir el archivo de log." << std::endl;
        }
    }

    // Método para obtener la hora actual como string
    std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        return std::ctime(&time);
    }

public:
    // Constructor
    ProcessController(const std::string& logFileName) : state(ProcessState::NEW), logFile(logFileName) {
        logEvent("Proceso creado en estado NEW.");
    }

    // Cambiar el estado del proceso
    void changeState(ProcessState newState) {
        state = newState;
        logEvent("Estado cambiado a " + getStateName(state) + ".");
    }

    // Ejecutar el proceso
    void executeProcess() {
        changeState(ProcessState::READY);
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simula tiempo de preparación

        changeState(ProcessState::RUNNING);
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Simula tiempo de ejecución

        changeState(ProcessState::WAITING);
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Simula espera de respuesta de la base de datos

        changeState(ProcessState::TERMINATED);
    }

    // Obtener el nombre del estado como string
    std::string getStateName(ProcessState state) {
        switch (state) {
            case ProcessState::NEW: return "NEW";
            case ProcessState::READY: return "READY";
            case ProcessState::RUNNING: return "RUNNING";
            case ProcessState::WAITING: return "WAITING";
            case ProcessState::TERMINATED: return "TERMINATED";
            default: return "UNKNOWN";
        }
    }
};

#endif // PROCESS_CONTROLLER_H