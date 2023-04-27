# This file handles the peer operations

import socket
import threading
import emoji
import re

from emoji.core import emoji_count
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

# Datagram size
DATAGRAM_SIZE = 1 + 1 + 64 + 1 + 255

# Message types
NORMALMESSAGE = 1
EMOJI = 2
URL = 3
ECHO = 4

# Regex for the URLs
URL_REGEX = r"(http|https)://[a-zA-Z0-9\./]+"

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

def server(HOST, PORT): # Receive messages
    clientSocket.bind((HOST, PORT))
    while True:
        datagram, peerAddress = clientSocket.recvfrom(DATAGRAM_SIZE)
        print('')
        messageType = int(datagram[0])
        nickSize = int(datagram[1])
        nick = datagram[2:nickSize+2].decode()
        messageSize = int(datagram[nickSize+2])
        messageContent = datagram[nickSize+3 : nickSize+3+messageSize].decode() 
        messageFormat(nick, messageType, messageContent, peerAddress[1])

def messageFormat(nick, messageType, messageContent, PORT):
    if messageType == NORMALMESSAGE:
        print(f"{backgroundColors.OKGREEN}{nick} Normal Message{backgroundColors.OKCYAN}: {messageContent}{Style.RESET_ALL}")
    elif messageType == EMOJI:
        print(f"{backgroundColors.OKGREEN}{nick} EMOJI{backgroundColors.OKCYAN}: {emoji.emojize(messageContent)}{Style.RESET_ALL}")
    elif messageType == URL:
        print(f"{backgroundColors.OKGREEN}{nick} URL{backgroundColors.OKCYAN}: {messageContent}{Style.RESET_ALL}")
    elif messageType == ECHO:
        print(f"{backgroundColors.OKGREEN}{nick} ECHO{backgroundColors.OKCYAN}: {messageContent}{Style.RESET_ALL}")
        clientSocket.sendto(createDatagram(nick, NORMALMESSAGE, messageContent), (HOST, PORT))
    else:
        print(f"{backgroundColors.FAIL}Invalid message type.{Style.RESET_ALL}", end=" ")

def createDatagram(nick, messageType, messageContent):
    nickSize = len(nick)
    messageSize = len(messageContent)
    datagram = bytes([messageType, nickSize]) + nick.encode() + bytes([messageSize]) + messageContent.encode()
    return datagram

def isEcho(message):
    command = message.split(" ")[0]
    if (command.upper() == "ECHO"):
        message = message[5:]
        return True
    return False

def client(HOST, PORT, username): # Send messages
    while True:
        print(f"{backgroundColors.OKGREEN}Please enter your message:{Style.RESET_ALL}", end=" ")
        message = input()

        if (message.lower() == "exit"):
            break
        elif (len(message) < 0 and len(message) > 256):
            print(f"{backgroundColors.FAIL}Invalid message. Please try again.{Style.RESET_ALL}")
        else:
            messageType = NORMALMESSAGE
            if (emoji_count(emoji.emojize(message)) > 0):
                messageType = EMOJI
            elif (re.search(URL_REGEX, message)):
                messageType = URL
            elif (isEcho(message)):
                messageType = ECHO
            clientSocket.sendto(createDatagram(username, messageType, message), (HOST, PORT))
      
# This function is the one who calls the main functions of the program
if __name__ == "__main__":
    main()