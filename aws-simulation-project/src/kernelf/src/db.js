import mysql from 'mysql2/promise';

// Configuración de la conexión a la base de datos
const pool = mysql.createPool({
  host: 'kernelbd.co9kcumk48i6.us-east-1.rds.amazonaws.com',
  user: 'admin',
  password: 'Jagerylia0306.,',
  database: 'kernel',
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0,
});

export default pool;