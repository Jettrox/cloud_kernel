from flask import Blueprint, jsonify
from database.connection import get_connection

logs_routes = Blueprint('logs', __name__)

@logs_routes.route('/logs', methods=['GET'])
def get_logs():
    try:
        connection = get_connection()
        with connection.cursor() as cursor:
            query = "SELECT * FROM logs"
            cursor.execute(query)
            rows = cursor.fetchall()
            logs = []
            for row in rows:
                logs.append({
                    "id": row[0],
                    "message": row[1],
                    "timestamp": row[2].strftime("%Y-%m-%d %H:%M:%S")
                })
            return jsonify(logs)
    except Exception as e:
        return jsonify({"error": str(e)})