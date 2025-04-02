import './App.css';

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <h1>Simulador de Kernel</h1>
        <div className="terminal">
          <p>$ Bienvenido al simulador de kernel</p>
          <p>$ Iniciando procesos...</p>
          <p>$ Proceso 1: RUNNING</p>
          <p>$ Proceso 2: WAITING</p>
          <p>$ Proceso 3: TERMINATED</p>
        </div>
      </header>
    </div>
  );
}

export default App;
