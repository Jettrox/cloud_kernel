from flask import Flask, jsonify, request
import pymysql
import time

app = Flask(__name__)

# Configuración de la base de datos
DB_HOST = "kernelbd.co9kcumk48i6.us-east-1.rds.amazonaws.com"
DB_USER = "admin"
DB_PASSWORD = "Jagerylia0306.,"
DB_NAME = "kernel"  # Cambiado a "kernel" para que coincida con tu base de datos

# Estados del proceso
class ProcessState:
    NEW = "NEW"
    READY = "READY"
    RUNNING = "RUNNING"
    WAITING = "WAITING"
    TERMINATED = "TERMINATED"

# Función para registrar un log en la base de datos
def log_process_state(state):
    try:
        connection = pymysql.connect(
            host=DB_HOST,
            user=DB_USER,
            password=DB_PASSWORD,
            database=DB_NAME
        )
        with connection.cursor() as cursor:
            query = "INSERT INTO logs (message) VALUES (%s)"
            cursor.execute(query, (f"Proceso en estado: {state}",))
            connection.commit()
        print(f"Log registrado: {state}")
    except Exception as e:
        print(f"Error al registrar el log: {e}")
    finally:
        connection.close()

# Simulador de procesos
def simulate_process():
    states = [
        ProcessState.NEW,
        ProcessState.READY,
        ProcessState.RUNNING,
        ProcessState.WAITING,
        ProcessState.TERMINATED
    ]
    for state in states:
        log_process_state(state)
        time.sleep(1)  # Simula tiempo de transición

# Función para obtener los datos de la tabla people
def get_people_from_database():
    try:
        connection = pymysql.connect(
            host=DB_HOST,
            user=DB_USER,
            password=DB_PASSWORD,
            database=DB_NAME
        )
        with connection.cursor() as cursor:
            query = "SELECT * FROM people"
            cursor.execute(query)
            rows = cursor.fetchall()
            people = []
            for row in rows:
                people.append({
                    "id": row[0],
                    "name": row[1],
                    "age": row[2],
                    "color": row[3]
                })
            return people
    except Exception as e:
        print(f"Error al obtener los datos de la tabla people: {e}")
        return {"error": "Error al obtener los datos de la tabla people"}
    finally:
        connection.close()

# Ruta para obtener los datos de la tabla people
@app.route('/people', methods=['GET'])
def people():
    people = get_people_from_database()
    return jsonify(people)

# Ruta para iniciar la simulación de procesos
@app.route('/simulate', methods=['POST'])
def simulate():
    simulate_process()
    return "Simulación de procesos completada", 200

# Iniciar el servidor
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)