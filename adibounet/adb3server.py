# AdibouNet Server reimplementation
# Login Credentials:
# the maximum password length is only allowed to be 9 chars being long.

# Connection informations:
# When each new connection will be established to the server always an new temp port will be choice.

# WORKAROUND:
# If the Server can't be started and Adress is already in use message is being displayed, Restart Adibou3 or return into the Garden of Adibou.

import socket
import threading
import datetime
import sys
import logging
import subprocess

# Configure logging to output to both the console and a log file
log_filename = "adibounet.log"

# Setting up logging
logger = logging.getLogger("")
logger.setLevel(logging.DEBUG)  # Log everything (debug level and higher)

# Console handler (prints to the console)
console_handler = logging.StreamHandler(sys.stdout)
console_handler.setLevel(logging.DEBUG)

# File handler (writes to a log file)
file_handler = logging.FileHandler(log_filename)
file_handler.setLevel(logging.DEBUG)

# Create a formatter for timestamps and log levels
formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
console_handler.setFormatter(formatter)
file_handler.setFormatter(formatter)

# Add handlers to the logger
logger.addHandler(console_handler)
logger.addHandler(file_handler)

def current_timestamp():
    """Returns the current timestamp as a formatted string."""
    return datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')

def handle_connection(client_socket, client_address):
    logger.info(f"Connection established from: {client_address}")
    
    # Receive data from the client (up to 1024 bytes)
    data = client_socket.recv(1024)
    
    if data:
        # Attempt to decode the data, handle potential errors
        try:
            received_data = data.decode('utf-8')
            logger.info(f"Data received: {received_data}")  # Print received data with timestamp
        except UnicodeDecodeError:
            # If decoding fails, log a warning and the raw bytes
            logger.warning(f"Data received (non-UTF-8): {data}")
            received_data = "<non-UTF-8 data>"
        
        # Example response to the client (you could customize this)
        response = f"Received: {received_data}"
        
        # Send data back to the client
        client_socket.send(response.encode('utf-8'))
        logger.info(f"Data sent: {response}")  # Print sent data with timestamp
    
    # Close the connection after handling the data
    client_socket.close()

def run_server(port):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("", port))
    server.listen(5)  # Listen for incoming connections

    logger.info(f"Listening on port {port}...")
    
    while True:
        client_socket, client_address = server.accept()  # Accept a new connection
        threading.Thread(target=handle_connection, args=(client_socket, client_address)).start()

def start_console():
    """Starts the command-line console that accepts user input."""
    while True:
        command = input(f"[{current_timestamp()}] Enter command to navigate in the Server: \n").strip().lower()
        
        if command == "shutdown":
            logger.info("Shutting down the server.")
            sys.exit(0)  # Exit the program, shutting down the server
        
        elif command == "help":
            logger.info("Displaying help message.")
            print("\nAvailable commands:")
            print("  shutdown  - Stop the server")
            print("  openlog   - Open adibounet.log")
            print("  help      - Display this help message")
            print("\n")
        
        elif command == "openlog":
            logger.info("Opening adibounet.log over an Texteditor")
            logfile = 'adibounet.log'
            subprocess.call(['open', 'adibounet.log'])

        else:
            logger.warning(f"Unknown command: {command}. Type 'help' for a list of commands.")

# Define the ports you want the server to listen on
ports = [3000, 3100]  # 3000 (French server), 3100 (German server)

# Create and start a separate thread for each port
threads = []
for port in ports:
    thread = threading.Thread(target=run_server, args=(port,))
    thread.daemon = True  # Daemonize thread so it exits when the main program exits
    threads.append(thread)
    thread.start()

# Start the console input listener in the main thread
try:
    start_console()  # This will allow you to interact with the server via the console
except KeyboardInterrupt:
    logger.info("KeyboardInterrupt received. Shutting down the server.")
    sys.exit(0)
