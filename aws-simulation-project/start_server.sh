#!/bin/bash
# filepath: /path/to/your/repo/start_server.sh

echo "Actualizando el repositorio..."
git pull origin main

echo "Compilando el proyecto..."
mkdir -p build
cd build
cmake ..
make

echo "Iniciando el servidor..."
./simulator  # Reemplaza "simulator" con el nombre del ejecutable generado por tu proyecto

echo "Servidor iniciado correctamente."