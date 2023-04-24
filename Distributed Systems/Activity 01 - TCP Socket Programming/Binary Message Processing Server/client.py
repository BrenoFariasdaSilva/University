# This file handles the client side of the application. 

import os
import socket
from colorama import Style

# Macros:
class backgroundColors: # Colors for the terminal
    OKCYAN = "\033[96m"
    OKGREEN = "\033[92m"
    WARNING = "\033[93m"
    FAIL = "\033[91m"

serverAddress = ("localhost", 6666) # Server address
REQUEST = 1 # Request message
SUCESS = 1 # Sucess message
ERROR = 2 # Error message
MAXFILENAMESIZE = 256 # Max size of the filename
ADDFILE = 1 # ADDFILE command
DELETE = 2 # DELETE command
GETFILESLIST = 3 # GETFILESLIST command
GETFILE = 4 # GETFILE command
EXIT = 5 # EXIT command
CLIENTDIRECTORY = "./client" # Client directory
standardResponseHeaderSize = 3 # Size of the standard response header
statusCodePosition = 2 # Position of the status code in the response header

# Valid commands for the client:
validCommands = ["ADDFILE", "DELETE", "GETFILESLIST", "GETFILE", "EXIT"]

# Header of the request message:
standardRequestHeader = bytearray(3) # 1 Byte for the message type, 1 Byte for the command and 1 Byte for the size of the filename
standardRequestHeader[0] = REQUEST # REQUEST in the header inside position 0

# Create a socket object
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Family: IPv4 e Type: Stream (TCP)
clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # Reuse the address
clientSocket.connect(serverAddress) # Connect to the server

# This is the main function
# It receives the user input and calls the switch function for handling user input as it should 
def main():
    while True:
        userInput = input(backgroundColors.OKGREEN + "Enter a command: " + Style.RESET_ALL) # User input

        if (len(userInput.split())) > 1: # if the user input has more than one word
            command = userInput.split()[0].upper() # command
            filename = userInput.split()[1] # filename
            switch(command, filename)
        else:
            command = userInput.upper()
            switch(command, "")
                                                                                              
# This function validates the command inserted by the user, as well as creating the directory for the operations
# It recieves the command from the user and a filename if it's necessary
def switch(command, filename):
    if not os.path.exists(CLIENTDIRECTORY): # If the directory doesn't exist
        os.makedirs(CLIENTDIRECTORY) # Create the directory
        
    if (command == validCommands[4]): # EXIT
        client_exit()
    elif command == validCommands[0]: # ADDFILE
        addfile(filename)
    elif command == validCommands[1]: # DELETE
        delete(filename)
    elif command == validCommands[2]: # GETFILESLIST
        getfileslist()
    elif command == validCommands[3]: # GETFILE
        getfile(filename)
    else:
        print(backgroundColors.FAIL + "Invalid command!" + Style.RESET_ALL)

# This function handles the EXIT command
# This is done by sending the standard header with the EXIT command and closing the socket    
def client_exit():
    standardRequestHeader[1] = EXIT # EXIT in the header inside position 1
    standardRequestHeader[2] = 0 # Size of the filename in the header inside position 2
    clientSocket.send(standardRequestHeader) # Send the standard header
    clientSocket.close() # Close the socket
    print(backgroundColors.OKGREEN + "Connection closed!" + Style.RESET_ALL)
    exit(0) # Exit the program
   
# This functions handles the ADDFILE command
# It receives the filename and sends the standard header with the ADDFILE command, the size of the filename and the filename    
def addfile(filename):
    standardRequestHeader[1] = ADDFILE # ADDFILE in the header inside position 1
    standardRequestHeader[2] = len(filename) # Size of the filename in the header inside position 2
    directoryFiles = os.listdir(CLIENTDIRECTORY) # List of files in the client directory

    if ((directoryFiles.__contains__(filename)) and (len(filename) < MAXFILENAMESIZE)):
        clientSocket.send(standardRequestHeader + bytearray(filename.encode())) # Send the standard header and the filename
        fileSize = os.path.getsize(CLIENTDIRECTORY + "/" + filename) # Size of the file in bytes
        clientSocket.send(fileSize.to_bytes(4, "big")) # Send the size of the file in bytes with a size of 4 bytes  
        
        OpenFile = open(CLIENTDIRECTORY + "/" + filename, "rb") # Open the file in bytes
        fileBytes = OpenFile.read() # Read the file in bytes
        clientSocket.send(fileBytes) # Send the file in bytes to the server

        confirmation = int(clientSocket.recv(standardResponseHeaderSize)[statusCodePosition]) # Confirmation if the file was added or not
        
        if (confirmation == SUCESS): # If the file was added
            print(backgroundColors.OKGREEN + "File " + backgroundColors.OKCYAN + filename + backgroundColors.OKGREEN + " transfered!" + Style.RESET_ALL)
        else: # If the file was not added
            print(backgroundColors.FAIL + "ERROR transfering the file " + backgroundColors.OKCYAN + filename + "!" + Style.RESET_ALL)

    else:
        print(backgroundColors.FAIL + "File " + backgroundColors.OKCYAN + filename + backgroundColors.FAIL + " not found!" + Style.RESET_ALL)
   
# This function handles the DELETE command
# It receives the file filename to be deleted and sends the standard header with the DELETE command, the size of the filename and the filename 
def delete(filename):
    standardRequestHeader[1] = DELETE # DELETE in the header inside position 1
    standardRequestHeader[2] = len(filename) # Size of the filename in the header inside position 2
    clientSocket.send(standardRequestHeader + bytearray(filename.encode())) # Send the standard header and the filename
    
    confirmation = clientSocket.recv(standardResponseHeaderSize)[statusCodePosition]

    if (confirmation == SUCESS): # If the file was deleted
        print(backgroundColors.OKGREEN + "File " + backgroundColors.OKCYAN + filename + backgroundColors.OKGREEN + " deleted!" + Style.RESET_ALL)
    else: # If the file was not deleted
        print(backgroundColors.FAIL + "ERROR deleting the file " + backgroundColors.OKCYAN + filename + "!" + Style.RESET_ALL)
       
# This function handles the GETFILESLIST command
# It sends the standard header with the GETFILESLIST command and waits for the server to confirm the operation
# If the server answers as the operation was successful, it receives the quantity of files in the server and prints them        
def getfileslist():
    standardRequestHeader[1] = GETFILESLIST # GETFILESLIST in the header inside position 1
    standardRequestHeader[2] = 0 # Size of the filename in the header inside position 2
    clientSocket.send(standardRequestHeader) # Send the standard header
    
    confirmation = clientSocket.recv(standardResponseHeaderSize)[statusCodePosition] # 

    if (confirmation == SUCESS):
        quantityFiles = int.from_bytes(clientSocket.recv(2), "big") # Quantity of files in the server in Big Endian
        print(f"{backgroundColors.OKGREEN}Files in the server: {backgroundColors.OKCYAN}{quantityFiles}{Style.RESET_ALL}")
        for i in range(quantityFiles): # Print the files in the server
            filenameSize = int.from_bytes(clientSocket.recv(1), "big") # Size of the file in bytes in Big Endian
            print(backgroundColors.OKCYAN + clientSocket.recv(filenameSize).decode() + Style.RESET_ALL) # Print the file name
    else:
        print(backgroundColors.FAIL + "ERROR getting the files list: Empty Directory!" + Style.RESET_ALL)
  
# This function handles the GETFILE command
# It receives the file filename to be downloaded and sends the standard header with the GETFILE command, the size of the filename and the filename
# If the server confirms the operation, it receives the size of the file in bytes and the file in bytes and creates a file with the same name in the client directory
def getfile(filename):
    standardRequestHeader[1] = GETFILE # GETFILE in the header inside position 1
    standardRequestHeader[2] = len(filename) # Size of the filename in the header inside position 2
    clientSocket.send(standardRequestHeader + bytearray(filename.encode())) # Send the standard header and the filename

    if (clientSocket.recv(standardResponseHeaderSize)[statusCodePosition] == SUCESS): # If the file was found
        fileSize = int.from_bytes(clientSocket.recv(4), byteorder="big") # Size of the file in bytes in Big Endian
        file = b'' # File in bytes
        file = clientSocket.recv(fileSize) # Recieve the file in bytes

        with open(CLIENTDIRECTORY + "/" + filename, "w+b") as files:
            files.write(file) # Write the file in bytes in the file created
        print(backgroundColors.OKGREEN + "File " + backgroundColors.OKCYAN + filename + backgroundColors.OKGREEN + " transfered!" + Style.RESET_ALL)
    else:
        print(backgroundColors.FAIL + "ERROR recieving the file " + backgroundColors.OKCYAN + filename + "!" + Style.RESET_ALL)

# This function is the one who calls the main functions of the program
if __name__ == "__main__":
    main()