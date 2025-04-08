const express = require('express');
const mysql = require('mysql2');
const cors = require('cors');

const app = express();
app.use(cors()); // Habilita CORS para permitir solicitudes desde el frontend
app.use(express.json()); // Permite manejar datos en formato JSON

// Configuración de la base de datos
const pool = mysql.createPool({
  host: 'kernelbd.co9kcumk48i6.us-east-1.rds.amazonaws.com',
  user: 'admin',
  password: 'Jagerylia0306.,',
  database: 'kernel',
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0,
});

// Ruta para obtener los datos de la tabla `people`
app.get('/people', (req, res) => {
  const query = 'SELECT * FROM people';
  pool.query(query, (err, results) => {
    if (err) {
      console.error('Error al consultar la base de datos:', err.message); // Muestra el mensaje de error
      res.status(500).json({ error: 'Error al consultar la base de datos', details: err.message });
    } else {
      res.json(results);
    }
  });
});

// Ruta para probar la conexión a la base de datos
app.get('/test-connection', (req, res) => {
  pool.query('SELECT 1', (err) => {
    if (err) {
      console.error('Error al conectar con la base de datos:', err.message);
      res.status(500).json({ error: 'Error al conectar con la base de datos', details: err.message });
    } else {
      res.json({ message: 'Conexión exitosa a la base de datos' });
    }
  });
});

// Inicia el servidor
const PORT = 8080;
app.listen(PORT, () => {
  console.log(`Servidor corriendo en http://localhost:${PORT}`);
});