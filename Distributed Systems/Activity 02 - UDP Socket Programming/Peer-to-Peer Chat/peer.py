# This file handles the peer operations
# TODO: Validate the size of each field of the datagram -> nick, message, etc.

import socket # Library for using sockets
import threading # Library for using threads 
import emoji # Library for using emojis
import re # Library for using regular expressions

from emoji.core import emoji_count # Library for using emojis
from colorama import Style # Library for using colors in the terminal

# Macros:
## Colors for the terminal
class backgroundColors: 
    OKCYAN = "\033[96m" # Cyan color
    OKGREEN = "\033[92m" # Green color
    WARNING = "\033[93m" # Yellow color
    FAIL = "\033[91m" # Red color

## Host and port
HOST = "localhost" # Localhost
PORTS = [6666, 7000] # Ports, first for "server", second for "client"

# Datagram size
DATAGRAM_SIZE = 1 + 1 + 64 + 1 + 255
# 1 byte for the message type,
# 1 byte for the nickname size,
# 64 bytes for the nickname,
# 1 byte for the message size,
# 255 bytes for the message

# Message types
NORMALMESSAGE = 1 # Normal message
EMOJI = 2 # Emoji
URL = 3 # URL
ECHO = 4 # Echo

# Regex for the URLs
URL_REGEX = r"(http|https)://[a-zA-Z0-9\./]+" 

# Create a socket object
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP socket

# This is the main function
# @param: None
# @return: None
# @logic: This function will read user input, validate it and call the functions to manage the threads
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


# This function validates the username
# @param username: The username to validate
# @return: True if the username is valid, False otherwise
# @logic: This function will validate the username according to the length valid range for the datagram
def validateUsername(username):
    if (len(username) > 0 and len(username) < 65):
        return True
    return False

# This function creates the threads 
# @param username: The username of the peer
# @return: None
# @logic: This function will create the threads for the server and the client according to the user input
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

# This function represents the server
# @param HOST: The host of the peer
# @param PORT: The port of the peer
# @return: None
# @logic: This function will receive the messages and call the function to format them
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

# This function formats the messages
# @param nick: The nickname of the peer
# @param messageType: The type of the message
# @param messageContent: The content of the message
# @param PORT: The port of the peer
# @return: None
# @logic: This function will format the messages according to the type of the message
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

# This function creates the datagram
# @param nick: The nickname of the peer
# @param messageType: The type of the message
# @param messageContent: The content of the message
# @return: The datagram
# @logic: This function will create the datagram according to protocol specifications
def createDatagram(nick, messageType, messageContent):
    nickSize = len(nick)
    messageSize = len(messageContent)
    datagram = bytes([messageType, nickSize]) + nick.encode() + bytes([messageSize]) + messageContent.encode()
    return datagram

# This function verify if the message is an echo
# @param message: The message to verify
# @return: True if the message is an echo, False otherwise
# @logic: This function will verify if the message is an echo by splitting the message and checking if the first word is "ECHO"
def isEcho(message):
    command = message.split(" ")[0]
    if (command.upper() == "ECHO"):
        message = message[5:]
        return True
    return False

# This function handles the client
# @param HOST: The host of the peer
# @param PORT: The port of the peer
# @param username: The username of the peer
# @return: None
# @logic: This function will send the messages to the server according to the user input
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
# @param: None
# @return: None
# @logic: This function will call the main functions of the program
if __name__ == "__main__":
    main()