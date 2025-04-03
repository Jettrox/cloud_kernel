import './App.css';
import { useState } from 'react';

function App() {
  const [logs, setLogs] = useState([]); // Estado para almacenar los logs
  const [error, setError] = useState(''); // Estado para manejar errores
  const [showWelcome, setShowWelcome] = useState(true); // Estado para mostrar/ocultar el mensaje de bienvenida

  // Función para iniciar la conexión con la base de datos
  const iniciarConexion = async () => {
    try {
      setShowWelcome(false); // Oculta el mensaje de bienvenida
      const response = await fetch('http://127.0.0.1:8080/simulate', {
        method: 'POST',
      });
      if (response.ok) {
        setError(''); // Limpia cualquier error previo
        consultarDatos(); // Llama a consultarDatos para obtener los logs después de la simulación
      } else {
        setError('Error al iniciar la conexión con la base de datos');
      }
    } catch (error) {
      setError('Error al conectar con la API: ' + error.message);
    }
  };

  // Función para consultar los datos (logs)
  const consultarDatos = async () => {
    try {
      setShowWelcome(false); // Oculta el mensaje de bienvenida
      const response = await fetch('http://127.0.0.1:8080/people');
      if (response.ok) {
        const data = await response.json();
        setLogs(data); // Actualiza el estado con los logs obtenidos
        setError(''); // Limpia cualquier error previo
      } else {
        setError('Error al consultar los datos');
      }
    } catch (error) {
      setError('Error al consultar los datos: ' + error.message);
    }
  };

  // Función para finalizar la conexión con la base de datos
  const finalizarConexion = async () => {
    try {
      const response = await fetch('http://127.0.0.1:8080/close', {
        method: 'POST',
      });
      if (response.ok) {
        setError('Conexión finalizada'); // Muestra un mensaje de conexión finalizada
        setLogs([]); // Limpia los logs
      } else {
        setError('Error al finalizar la conexión con la base de datos');
      }
    } catch (error) {
      setError('Error al finalizar la conexión: ' + error.message);
    }
  };

  return (
    <div className="App">
      <header className="App-header">
        <h1>Simulador de Kernel</h1>
        <div className="terminal">
          {showWelcome && <p>$ Bienvenido al simulador de kernel</p>} {/* Muestra el mensaje de bienvenida si showWelcome es true */}
          {logs.map((log, index) => (
            <p key={index}>$ {log.name} - {log.age} años - {log.color}</p>
          ))}
          {error && <p className="error">$ {error}</p>} {/* Muestra el error si existe */}
        </div>
        <div className="buttons">
          <button onClick={iniciarConexion}>
            Iniciar conexión con la base de datos
          </button>
          <button onClick={consultarDatos}>
            Consultar datos
          </button>
          <button onClick={finalizarConexion}>
            Finalizar conexión
          </button>
        </div>
      </header>
    </div>
  );
}

export default App;
