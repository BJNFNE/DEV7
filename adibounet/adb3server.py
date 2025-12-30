# AdibouNet Server reimplementation
# Login Credentials:
# the maximum password length is only allowed to be 9 chars being long.

# Connection informations:
# When each new connection will be established to the server always an new temp port will be choice.

# Wireshark:
# Set the filter there to either tcp.port == 3100 or tcp.port == 3000

# WORKAROUND:
# If the Server can't be started and Adress is already in use message is being displayed, Restart Adibou3 or return into the Garden of Adibou.

# Setup custom Server:
# Modify b3i_url.ini can be found in b3_internet.itk, In the section called [SERVER] change the domain of PortalServerIp to the IP of your custom Server.

# Status:
# Currently can only be comunicated with the Server to the Client to bring up the Login screen and display Username and Password.
# Non printable data will be also shown in the Console. (Maybe useful for further debugging)

# Used Functions:
# netOpenIPConnection() loaded from CkNet.dll

# Requests:
# When leaving AdibouNet and return to Adibou's Garden an Request will be sended after leaving called "Bye"

# Callbacks:
# CallbackConnection checks if the connection is working if so it prints OK and shows the Portal Server with IP

# Christophe Delouche:
# It seems to be loaded Unencrypted (0 --> 0)
# netGetProviderList() checks which internet connection / provider could be used to connect.
# ConnectionRetry retrys to connect to Portal Server and to the Connection Manager (9 times)
# If the Connection is abort the Portal Server is not found

# B3I_ModemLaunch:
# Connect after choosing the provider to AdibouNet's Portal Server

# B3I_PortalServer:
# Send AccountIdentiftication (AccountCode also known as the Username you entered) and the password

# B3I_Bulletin_Board:
# If you go to the Applications/Adibou's Garden the messsage "return to adibou..." is shown.

# AFK:
# If you are do nothing in the main screen of AdibouNet Adibou asks you to connect to AdibouNet

# Subscription:
# Onclic : B3I_HP_SubscriptionButton is used for when you click on the paper were you can login.
# Opens then the https://www.subscription.de.adibouland.com/index.asp?origin=2 URL (Stored in b3i_url.ini can be replaced)

import socket
import threading
import datetime
import os
import sys
import logging
import subprocess

# AdibouNet defines
versionNumber = "v0.2alpha"

# Configure logging to output to both the console and a log file
logfile = "adibounet.log"

# Setting up logging
logger = logging.getLogger()
logger.setLevel(logging.DEBUG)  # Log everything (debug level and higher)

# Console handler (prints to the console)
console_handler = logging.StreamHandler(sys.stdout)
console_handler.setLevel(logging.DEBUG)

# File handler (writes to a log file)
file_handler = logging.FileHandler(logfile)
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
        
        if command == "restart":
            logger.info("Restarts the server.")
            os.execl(sys.executable, *sys.orig_argv)  # Exit the program, restarting the server

        elif command == "help":
            logger.info("Displaying help message.")
            print("\nAvailable commands:")
            print("  shutdown - Stop the server")
            print("  restart -  Restarts the server")
            print("  clear - Clear the Console")
            print("  openlog - Open adibounet.log")
            print("  deletelog - Delete old adibounet.log")
            print("  showip - Display Server IP")
            print("  pythonversion - Display python version")
            print("  poweroff_server - Shutdown the server (Physical Server)")
            print("  reboot_server - Reboot the server (Physical Server)")
            print("  help - Display this help message")
            print("  version - Display version of AdibouNet")
            print("\n")
        
        elif command == "openlog":
            logger.info("Opening adibounet.log over an Texteditor")
            os.system('notepad adibounet.log' if os.name=='nt' else 'open adibounet.log')

        elif command == "deletelog":
            os.system('del adiboulog.txt' if os.name=='nt' else 'rm adibounet.log')
            logger.info("Deleting old adibou3.log\n Restart AdibouNet Server with 'restart' to generate an new Logfile.")

        elif command == "clear":
            os.system('cls' if os.name=='nt' else 'clear')

        elif command == "showip":
            os.system('ipconfig | findstr "IPv4"' if os.name=='nt' else 'ifconfig | grep "255.255.255.0"') # Search for submask on Linux

        elif command == "poweroff_server":
            os.system('poweroff' if os.name=='nt' else 'shutdown -s -t 0')

        elif command == "pythonversion":
            os.system('python --version' if os.name=='nt' else 'python3 --version"') # Show python version under Linux

        elif command == "version":
            print("AdibouNet", versionNumber)
            
        elif command == "gameports":
            print("Ports: ", ports)

        else:
            logger.warning(f"Unknown command: {command}. Type 'help' for a list of commands.")

# Define the ports you want the server to listen on
ports = [3000, 3100]  # 3000 (French/English server), 3100 (German server)

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

except MemoryError:
    logger.info("Out of memory!")
    sys.exit(0)
