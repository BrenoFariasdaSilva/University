# This file handles the peer operations

import socket
from colorama import Style

# Macros:
class backgroundColors: # Colors for the terminal
    OKCYAN = "\033[96m"
    OKGREEN = "\033[92m"
    WARNING = "\033[93m"
    FAIL = "\033[91m"

# Create a socket object
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP socket

# This is the main function
# It receives the user input
def main():
    global username                                                                                              
    global connectedPeer
    
    while True:
        print(f"{backgroundColors.OKCYAN}Welcome to the P2P chat!{Style.RESET_ALL}")
        print(f"{backgroundColors.OKCYAN}Please enter your username:{Style.RESET_ALL}")
        nickname = input()
        if (len(nickname) > 0 and len(nickname) < 65):
            username = nickname
        else:
            print(f"{backgroundColors.WARNING}Please enter a valid username!{Style.RESET_ALL}")

# This function is the one who calls the main functions of the program
if __name__ == "__main__":
    main()