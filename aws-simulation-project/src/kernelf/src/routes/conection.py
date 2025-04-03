import pymysql

DB_HOST = "kernelbd.co9kcumk48i6.us-east-1.rds.amazonaws.com"
DB_USER = "admin"
DB_PASSWORD = "Jagerylia0306.,"
DB_NAME = "kernel"

def get_connection():
    return pymysql.connect(
        host=DB_HOST,
        user=DB_USER,
        password=DB_PASSWORD,
        database=DB_NAME
    )

def log_process_state(state):
    try:
        connection = get_connection()
        with connection.cursor() as cursor:
            query = "INSERT INTO logs (message) VALUES (%s)"
            cursor.execute(query, (f"Proceso en estado: {state}",))
            connection.commit()
    except Exception as e:
        print(f"Error al registrar el log: {e}")
    finally:
        connection.close()