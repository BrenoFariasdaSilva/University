import os
import socket
from colorama import Style

# Macros:
class backgroundColors:
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
standardResponseHeaderSize = 3 # Size of the standard response header
statusCodePosition = 2 # Position of the status code in the response header

# Valid commands for the client:
validCommands = ["ADDFILE", "DELETE", "GETFILESLIST", "GETFILE"]

# Header of the request message:
standardRequestHeader = bytearray(3) # 1 Byte for the message type, 1 Byte for the command and 1 Byte for the size of the filename
standardRequestHeader[0] = REQUEST # REQUEST in the header inside position 0

# Create a socket object
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Family: IPv4 e Type: Stream (TCP)
clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # Reuse the address
clientSocket.connect(serverAddress) # Connect to the server

# Validate the command inserted by the user
# Recieve the command from the user and a filename if it"s necessary
def switch(filename, command):
    if not os.path.exists("./client"): # If the directory doesn't exist
            os.makedirs("./client") # Create the directory
            
    if command == validCommands[0]: # ADDFILE
        standardRequestHeader[1] = ADDFILE # ADDFILE in the header inside position 1
        standardRequestHeader[2] = len(filename) # Size of the filename in the header inside position 2
        directoryFiles = os.listdir("./client") # List of files in the directory

        if (directoryFiles.__contains__(filename)):
            if (len(filename) < MAXFILENAMESIZE):
                clientSocket.send(standardRequestHeader + bytearray(filename.encode())) # Send the standard header and the filename
                fileSize = os.path.getsize("./client/" + filename) # Size of the file in bytes and in Big Endian
                clientSocket.send(fileSize.to_bytes(4, "big")) # Send the size of the file in bytes with a size of 4 bytes  
                
                OpenFile = open("./client/" + filename, "rb") # Open the file in binary mode
                fileBytes = OpenFile.read() # Read the file in bytes
                clientSocket.send(fileBytes) # Send the file in bytes to the serve

                confirmation = int(clientSocket.recv(standardResponseHeaderSize)[statusCodePosition]) # Confirmation if the file was added or not
                
                if (confirmation == SUCESS): # If the file was added
                    print(backgroundColors.OKGREEN + "File " + backgroundColors.OKCYAN + filename + "transfered!" + Style.RESET_ALL)
                else: # If the file was not added
                    print(backgroundColors.FAIL + "ERROR transfering the file " + backgroundColors.OKCYAN + filename + "!" + Style.RESET_ALL)

        else:
            print(backgroundColors.FAIL + "File " + backgroundColors.OKCYAN + filename + backgroundColors.FAIL + " not found!" + Style.RESET_ALL)
            
    elif command == validCommands[1]: # DELETE
        standardRequestHeader[1] = DELETE # DELETE in the header inside position 1
        standardRequestHeader[2] = len(filename) # Size of the filename in the header inside position 2
        clientSocket.send(standardRequestHeader + bytearray(filename.encode())) # Send the standard header and the filename

        if ((clientSocket.recv(3)[statusCodePosition]) == SUCESS): # If the file was deleted
            print(backgroundColors.OKGREEN + "File " + backgroundColors.OKCYAN + filename + backgroundColors.OKGREEN + " deleted!" + Style.RESET_ALL)
        else: # If the file was not deleted
            print(backgroundColors.FAIL + "ERROR deleting the file " + backgroundColors.OKCYAN + filename + "!" + Style.RESET_ALL)
            
    elif command == validCommands[2]: # GETFILESLIST
        standardRequestHeader[1] = GETFILESLIST # GETFILESLIST in the header inside position 1
        standardRequestHeader[2] = 0 # Size of the filename in the header inside position 2
        clientSocket.send(standardRequestHeader) # Send the standard header

        if (clientSocket.recv(standardResponseHeaderSize)[statusCodePosition] == SUCESS):
            quantityFiles = int.from_bytes(clientSocket.recv(2), "big") # Quantity of files in the server in Big Endian
            print(backgroundColors.OKGREEN + "Files in the server:" + Style.RESET_ALL)
            for i in range(quantityFiles): # Print the files in the server
                fileSize = int.from_bytes(clientSocket.recv(1), "big") # Size of the file in bytes in Big Endian
                print(backgroundColors.OKCYAN + clientSocket.recv(fileSize).decode() + Style.RESET_ALL) # Print the file name
        else:
            print(backgroundColors.FAIL + "ERROR getting the files list!" + Style.RESET_ALL)
            
    elif command == validCommands[3]: # GETFILE
        standardRequestHeader[1] = GETFILE # GETFILE in the header inside position 1
        standardRequestHeader[2] = len(filename) # Size of the filename in the header inside position 2
        clientSocket.send(standardRequestHeader + bytearray(filename.encode())) # Send the standard header and the filename

        if (clientSocket.recv(standardResponseHeaderSize)[statusCodePosition] == SUCESS): # If the file was found
            fileSize = int.from_bytes(clientSocket.recv(4), "big") # Size of the file in bytes in Big Endian
            directoryFiles = clientSocket.recv(fileSize.to_bytes) # File in bytes

            with open("./client/" + filename, "w+b") as files: # Create a file with the name of the file in the server
                files.write(directoryFiles) # Write the file in bytes in the file created
            print(backgroundColors.OKGREEN + "File " + backgroundColors.OKCYAN + filename + backgroundColors.OKGREEN + " transfered!" + Style.RESET_ALL)
        else:
            print(backgroundColors.FAIL + "ERROR recieving the file " + backgroundColors.OKCYAN + filename + "!" + Style.RESET_ALL)
            
    else:
        print(backgroundColors.FAIL + "Invalid command!" + Style.RESET_ALL)
        
def main():
    while True:
        userInput = input(backgroundColors.OKGREEN + "Enter a command: " + Style.RESET_ALL) # User input

        if (len(userInput.split())) > 1: # if the user input has more than one word
            command = userInput.split()[0] # command
            filename = userInput.split()[1] # filename

        switch(filename, command.upper())

if __name__ == "__main__":
    main()