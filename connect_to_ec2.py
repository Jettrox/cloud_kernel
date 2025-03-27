import paramiko

def connect_to_ec2(hostname, username, key_file, commands):
    try:
        # Crea un cliente SSH
        ssh_client = paramiko.SSHClient()
        ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())

        # Conéctate a la instancia EC2
        print(f"Conectando a {hostname}...")
        ssh_client.connect(hostname=hostname, username=username, key_filename=key_file)
        print("Conexión exitosa.")

        # Ejecuta los comandos
        for command in commands:
            print(f"Ejecutando: {command}")
            stdin, stdout, stderr = ssh_client.exec_command(command)
            print("Salida:")
            print(stdout.read().decode())
            print("Errores:")
            print(stderr.read().decode())

        # Cierra la conexión
        ssh_client.close()
        print("Conexión cerrada.")

    except Exception as e:
        print(f"Error al conectar: {e}")

if __name__ == "__main__":
    
    HOSTNAME = "34.228.32.207"  
    USERNAME = "ec2-user"  
    KEY_FILE = "c:/Users/juanp/OneDrive/Documents/cloud_kernel/aws-simulation-project/key.pem"  
    COMMANDS = [
        "cd /path/to/your/repo",  
        "git pull origin main",  
        "chmod +x start_server.sh",  
        "./start_server.sh" 
    ]

    # Conecta y ejecuta los comandos
    connect_to_ec2(HOSTNAME, USERNAME, KEY_FILE, COMMANDS)