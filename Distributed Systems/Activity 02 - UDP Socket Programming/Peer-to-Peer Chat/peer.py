# This file handles the peer operations

import socket
import threading

from colorama import Style

# Macros:
## Colors for the terminal
class backgroundColors: 
    OKCYAN = "\033[96m"
    OKGREEN = "\033[92m"
    WARNING = "\033[93m"
    FAIL = "\033[91m"
## Host and port
HOST = "localhost"
PORTS = [5000, 6666]

# Create a socket object
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP socket

# This is the main function
# It receives the user input
def main():
    print(f"{backgroundColors.OKCYAN}Welcome to the P2P chat!{Style.RESET_ALL}")
    while True:
        print(f"{backgroundColors.OKCYAN}Please enter your username:{Style.RESET_ALL}")
        username = input()
        if (validateUsername(username)):
            print(f"{backgroundColors.OKGREEN}Welcome {username}!{Style.RESET_ALL}")
            createThreads()
            break
        else:
            print(f"{backgroundColors.FAIL}Invalid username. Please try again.{Style.RESET_ALL}")

def validateUsername(username):
    if (len(username) > 0 and len(username) < 65):
        return True
    return False
    
def createThreads():
    option = "undefined"
    while option != "server" and option != "client":
        print(f"{backgroundColors.OKGREEN}Will you be acting as a server or a client?{Style.RESET_ALL}")
        option = input().toLowerCase()
        if (option == "server"):
            threading.Thread(target=server, args=(HOST, PORTS[0])).start() # TODO: Create server function
            threading.Thread(target=client, args=(HOST, PORTS[1])).start() # TODO: Create client function
        elif (option == "client"):
            threading.Thread(target=client, args=(HOST, PORTS[0])).start()
            threading.Thread(target=server, args=(HOST, PORTS[1])).start()
        else:
            print(f"{backgroundColors.FAIL}Invalid option. Please try again.{Style.RESET_ALL}")

# This function is the one who calls the main functions of the program
if __name__ == "__main__":
    main()