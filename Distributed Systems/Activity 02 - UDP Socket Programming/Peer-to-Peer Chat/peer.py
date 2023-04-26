# This file handles the peer operations

import socket
import threading
import emoji
import emojis

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
PORTS = [6666, 7000]

DATAGRAM_SIZE = 1 + 1 + 64 + 1 + 255
NORMALMESSAGE = 1
EMOJI = 2
URL = 3
ECHO = 4

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
            createThreads(username)
            break
        else:
            print(f"{backgroundColors.FAIL}Invalid username. Please try again.{Style.RESET_ALL}")

def validateUsername(username):
    if (len(username) > 0 and len(username) < 65):
        return True
    return False
    
def createThreads(username):
    option = "undefined"
    while option != "server" and option != "client":
        print(f"{backgroundColors.OKGREEN}Will you be acting as a server or a client?{Style.RESET_ALL}")
        option = input().lower()
        if (option == "server"):
            threading.Thread(target=server, args=(HOST, PORTS[0])).start() 
            threading.Thread(target=client, args=(HOST, PORTS[1], username)).start()
        elif (option == "client"):
            threading.Thread(target=client, args=(HOST, PORTS[0], username)).start()
            threading.Thread(target=server, args=(HOST, PORTS[1])).start()
        else:
            print(f"{backgroundColors.FAIL}Invalid option. Please try again.{Style.RESET_ALL}")

def server(HOST, PORT):
    clientSocket.bind((HOST, PORT))
    while True:
        data, addr = clientSocket.recvfrom(DATAGRAM_SIZE)
        print('')
        messageType = int(data[0])
        nickSize = int(data[1])
        nick = data[2:nickSize+2].decode()
        messageSize = int(data[nickSize+2])
        messageContent = data[nickSize+3 : nickSize+3+messageSize].decode() 
        messageFormat(nick, messageType, messageContent, PORT)

def messageFormat(nick, messageType, messageContent, PORT):
    if messageType == NORMALMESSAGE:
        print(f"{backgroundColors.OKGREEN}{nick}{backgroundColors.OKCYAN}: {messageContent}{Style.RESET_ALL}")
    elif messageType == EMOJI:
        print(f"{backgroundColors.OKGREEN}{nick}{backgroundColors.OKCYAN}: {emoji.emojize(messageContent)}{Style.RESET_ALL}")
    elif messageType == URL:
        print(f"{backgroundColors.OKGREEN}{nick}{backgroundColors.OKCYAN}: {messageContent}{Style.RESET_ALL}")
    elif messageType == ECHO:
        clientSocket.sendto(createDatagram(nick, NORMALMESSAGE, messageContent), (HOST, PORT))
    else:
        print(f"{backgroundColors.FAIL}Invalid message type.{Style.RESET_ALL}")

def createDatagram(nick, messageType, messageContent):
    nickSize = len(nick)
    messageSize = len(messageContent)
    datagram = bytes([messageType, nickSize]) + nick.encode() + bytes([messageSize]) + messageContent.encode()
    return datagram

def client(HOST, PORT, username):
    while True:
        print(f"{backgroundColors.OKGREEN}Please enter your message:{Style.RESET_ALL}")
        message = input()
        if (message == "exit"):
            break
        elif (len(message) < 0 and len(message) > 256):
            print(f"{backgroundColors.FAIL}Invalid message. Please try again.{Style.RESET_ALL}")
        else:
            # TODO: Validate message type
            # TODO: Send message to server
            messageType = NORMALMESSAGE
            if (emojis.count(message) > 0):
                messageType = EMOJI
            elif (message.__contains__("http://") or message.__contains__("https://")):
                messageType = URL
            elif (message.__contains__("echo")):
                messageType = ECHO
            clientSocket.sendto(createDatagram(username, messageType, message), (HOST, PORT))
            
# This function is the one who calls the main functions of the program
if __name__ == "__main__":
    main()