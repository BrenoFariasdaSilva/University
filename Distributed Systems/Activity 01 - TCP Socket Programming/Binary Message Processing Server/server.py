import os
import socket
import threading
import logging

from colorama import Style

# Macros:
class backgroundColors:
    OKCYAN = "\033[96m"
    OKGREEN = "\033[92m"
    WARNING = "\033[93m"
    FAIL = "\033[91m"

serverAddress = ("", 6666) # Server address
maxNumberOfConnections = 3 # Max number of connections
SUCESS = 1 # Sucess message
ERROR = 2 # Error message
RESPONSE = 2 # Response message
ADDFILE = 1 # ADDFILE command
DELETE = 2 # DELETE command
GETFILESLIST = 3 # GETFILESLIST command
GETFILE = 4 # GETFILE command
EXIT = 5 # EXIT command
MAXFILENAMESIZE = 256 # Max size of the filename

# Create a socket object
serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Family: IPv4 e Type: Stream (TCP)
serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # Reuse the address
serverSocket.bind(serverAddress) # Bind the socket to the address

# Define o formato do log
formatLog = '%(asctime)-1s %(userIP)s %(userPort)s %(message)s'
logging.basicConfig(format=formatLog, level=20)
nameLog = logging.getLogger('TCP_Server')

def main():
    threads = [] # Vector of threads

    while True:
        serverSocket.listen(maxNumberOfConnections) # Listen for connections
        (connection, (ip, port)) = serverSocket.accept() # Accept the connection
        data = {'userIP': ip, 'userPort': port} # Define the format of the log
        nameLog.info('Protocol info: %s','connection established', extra=data) # Log the connection

        thread = threading.Thread(target=connectionClient, args=(ip, port, connection, )) # Create a thread
        thread.start() # Start the thread
        threads.append(thread) # Add the thread to the vector

def connectionClient(ip, port, connection):
    data = {'userIP': ip, 'userPort': port}
    
    if not os.path.exists("./server"): # If the directory doesn't exist
        os.makedirs("./server") # Create the directory

    while True:
        responseHeader = bytearray(3) # 1 Byte for the message type, 1 Byte for the command and 1 Byte for the status code
        responseHeader[0] = RESPONSE # RESPONSE in the header inside position 0

        # Receive the message
        messageReceived = bytearray(connection.recv(1024))
        messageType = int(messageReceived[0]) # Message type
        commandId = int(messageReceived[1]) # Command ID
        fileNameSize = int(messageReceived[2]) # Size of the filename
        filename = messageReceived[3:].decode('utf-8') # Filename
        
        if (commandId == EXIT):
            nameLog.info('Protocol: %s', 'Received EXIT request', extra=data)
            nameLog.info('Protocol: %s', 'Connection closed', extra=data)
            break
        
        if (commandId == ADDFILE):
            nameLog.info('Protocol: %s', 'Received ADDFILE request', extra=data)
            archiveSize = int.from_bytes(connection.recv(4), byteorder='big')
            archive = b'' # Archive received from the client (byte array)
            archive = connection.recv(archiveSize)
            nameLog.info('Protocol: %s', 'Download finished', extra=data)

            with open('./server/' + filename, 'w+b') as archiveFile:
                archiveFile.write(archive)

            archive = os.listdir(path='./server/')
            if filename in archive:
                responseHeader[2] = SUCESS
                nameLog.info('Protocol: %s','Successfully ADDFILE', extra=data)
            else:
                responseHeader[2] = ERROR
                nameLog.info('Protocol: %s','Unsuccessfully ADDFILE', extra=data)

            responseHeader[1] = ADDFILE
            connection.send(responseHeader)
            nameLog.info('Protocol: %s','Response ADDFILE sent', extra=data)

        elif (commandId == DELETE):
            nameLog.info('Protocol: %s','Received DELETE request', extra=data)
            if os.path.isfile('./server/' + filename):
                os.remove('./server/' + filename)

                if os.path.isfile('./server/' + filename):
                    responseHeader[2] = ERROR
                    nameLog.info('Protocol: %s','Unsuccessfully DELETE ', extra=data)
                else:
                    responseHeader[2] = SUCESS
                    nameLog.info('Protocol: %s','Successfully DELETE ', extra=data)

            connection.send(responseHeader)
            nameLog.info('Protocol: %s','Response DELETE sent ', extra=data)

        elif (commandId == GETFILESLIST):

            nameLog.info('Protocol: %s','Received GETFILESLIST request', extra=data)
            quantityFiles = 0
            files: list[str] = []
            directory = os.listdir('./server/')
            responseHeader[1] = GETFILESLIST
            filenameSizeResponseHeader = 0

            for filename in directory:
                if os.path.isfile(str('./server/' + filename)):
                    quantityFiles = quantityFiles + 1
                    files.append(str(filename))

            if quantityFiles > 0:
                responseHeader[2] = SUCESS
                connection.send(responseHeader)
                connection.send(quantityFiles.to_bytes(2, byteorder="big"))
                for filename in files:
                    filenameSizeResponseHeader = len(filename)
                    connection.send(filenameSizeResponseHeader.to_bytes(1, byteorder="big"))
                    connection.send(filename.encode())
                    nameLog.info('Protocol: %s','Response GETFILESLIST sent', extra=data)

            else:
                nameLog.info('Protocol: %s','Unsucessfully GETFILESLIST: Empty Directory', extra=data)
                responseHeader[2] = ERROR
                connection.send(responseHeader)
                nameLog.info('Protocol: %s','Response GETFILESLIST sent', extra=data)

        elif (commandId == GETFILE):
            nameLog.info('Protocol: %s','Received GETFILE request', extra=data)
            responseHeader[1] = GETFILE
            archive = os.listdir('./server/')

            if len(filename) <= MAXFILENAMESIZE and filename in archive:
                responseHeader[2] = SUCESS
                connection.send(responseHeader)
                nameLog.info('Protocol: %s','Response GETFILE sent', extra=data)
                fileSize = (os.stat('./server/' + filename).st_size).to_bytes(4, byteorder="big")
                connection.send(fileSize)
                fileOpen = open('./server/' + filename, 'rb')
                file = fileOpen.read()
                nameLog.info('Protocol: %s','Starting upload', extra=data)
                connection.send(file)
                nameLog.info('Protocol: %s','Upload finished', extra=data)
                fileOpen.close()

            else:
                nameLog.info('Protocol: %s','Unsuccessfully GETFILE', extra=data)
                responseHeader[2] = ERROR
                connection.send(responseHeader)
                nameLog.info('Protocol: %s','Response GETFILE sent', extra=data)

if __name__ == "__main__":
    main()