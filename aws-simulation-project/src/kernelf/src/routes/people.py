from flask import Blueprint, jsonify, request
from database.connection import get_connection

people_routes = Blueprint('people', __name__)

@people_routes.route('/people', methods=['GET'])
def get_people():
    limit = request.args.get('limit', default=None, type=int)
    try:
        connection = get_connection()
        with connection.cursor() as cursor:
            query = "SELECT * FROM people"
            if limit:
                query += f" LIMIT {limit}"
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
            return jsonify(people)
    except Exception as e:
        return jsonify({"error": str(e)})