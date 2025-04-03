from flask import Blueprint
from database.connection import log_process_state

simulate_routes = Blueprint('simulate', __name__)

@simulate_routes.route('/simulate', methods=['POST'])
def simulate():
    states = ["NEW", "READY", "RUNNING", "WAITING", "TERMINATED"]
    for state in states:
        log_process_state(state)
    return "Simulación de procesos completada", 200