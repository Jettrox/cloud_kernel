import './App.css';
import { useState } from 'react';

function App() {
  const [logs, setLogs] = useState([]); // Estado para almacenar los logs
  const [error, setError] = useState(''); // Estado para manejar errores

  // Función para consultar los datos (logs)
  const consultarDatos = async () => {
    try {
      const response = await fetch('http://localhost:8080/people'); // Solicita datos al backend
      if (!response.ok) {
        throw new Error('Error al consultar los datos');
      }
      const data = await response.json();
      setLogs(data); // Actualiza el estado con los logs obtenidos
      setError(''); // Limpia cualquier error previo
    } catch (error) {
      setError('Error al consultar los datos: ' + error.message);
    }
  };

  return (
    <div className="App">
      <header className="App-header">
        <h1>Simulador de Kernel</h1>
        <div className="terminal">
          {logs.map((log, index) => (
            <p key={index}>$ {log.name} - {log.age} años - {log.color}</p>
          ))}
          {error && <p className="error">$ {error}</p>} {/* Muestra el error si existe */}
        </div>
        <div className="buttons">
          <button onClick={consultarDatos}>
            Consultar datos
          </button>
        </div>
      </header>
    </div>
  );
}

export default App;
