# This file handles the peer operations

import socket # Library for using sockets
import threading # Library for using threads 
import emoji # Library for using emojis
import re # Library for using regular expressions

from emoji.core import emoji_count # Library for using emojis
from colorama import Style # Library for using colors in the terminal

# Macros:
## Colors for the terminal
class BackgroundColors: 
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
# As i never used Regex, i simply copied this one from the internet:
# https://uibakery.io/regex-library/url-regex-python

# Create a socket object
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP socket

# --------------------------------------------------------------- #
# TCP Server related macros
# # TCP_IP = "localhost" # IP address of the TCP server
# # TCP_PORT = 8000 # Port of the TCP server

# # # create a TCP socket
# # sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# This is the main function
# @param: None
# @return: None
# @logic: This function will read user input, validate it and call the functions to manage the threads
def main():
    print(f"{BackgroundColors.OKCYAN}Welcome to the P2P chat!{Style.RESET_ALL}")
    
    while True:
        print(f"{BackgroundColors.OKCYAN}Please enter your username:{Style.RESET_ALL}")
        username = input()
        if (validateUsername(username)):
            print(f"{BackgroundColors.OKGREEN}Welcome {username}!{Style.RESET_ALL}")
            createThreads(username)
            break
        else:
            print(f"{BackgroundColors.FAIL}Invalid username. Please try again.{Style.RESET_ALL}")

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
        print(f"{BackgroundColors.OKGREEN}Will you be acting as a server or a client?{Style.RESET_ALL}")
        option = input().lower()
        if (option == "server"):
            # # Aqui é feita a criação do "servidor" e do "cliente" em threads diferentes
            # # Como faço ou onde coloco o código que faz a conexão com o servidor TCP?   
            # # Esse daqui: sock.connect((TCP_IP, TCP_PORT)) ?
            # # Crio outra thread só para isso? Ou vou precisar de mais duas threads? Uma para envio de mensagens e outra para recebimento?
            # # Além disso, quando a conexão é feita, o peer precisa enviar um pacote com o seu nickname para o servidor tcp.
            # # Algo como: sock.send(nickname.encode())
            # # Além de, quando o client sair, ele precisa fecha a conexão com o servidor tcp: sock.close()
            threading.Thread(target=server, args=(HOST, PORTS[0])).start() 
            threading.Thread(target=client, args=(HOST, PORTS[1], username)).start()
            # # threading.Thread(target=tcp_server, args=(username)).start()
        elif (option == "client"):
            threading.Thread(target=client, args=(HOST, PORTS[0], username)).start()
            threading.Thread(target=server, args=(HOST, PORTS[1])).start()
            # # # threading.Thread(target=tcp_server, args=(username)).start()
        else:
            print(f"{BackgroundColors.FAIL}Invalid option. Please try again.{Style.RESET_ALL}")

# This function represents the connection with the TCP server
# @param username: The username of the peer
# @return: None
# @logic: This function will connect the peer with the TCP server and send the nickname,
# and wait for possible changes in the list or echo messages to validate if this peer is still connected
# # def tcp_server(username):
# #     sock.connect((TCP_IP, TCP_PORT))
# #     sock.send(username.encode())
# #     while True:
# #         data = sock.recv(1024)
# #         print(f"{BackgroundColors.OKGREEN}TCP-Server said: {data.decode()}{Style.RESET_ALL}")

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
        print(f"{BackgroundColors.OKGREEN}{nick} Normal Message{BackgroundColors.OKCYAN}: {messageContent}{Style.RESET_ALL}")
    elif messageType == EMOJI:
        print(f"{BackgroundColors.OKGREEN}{nick} EMOJI{BackgroundColors.OKCYAN}: {emoji.emojize(messageContent)}{Style.RESET_ALL}")
    elif messageType == URL:
        print(f"{BackgroundColors.OKGREEN}{nick} URL{BackgroundColors.OKCYAN}: {messageContent}{Style.RESET_ALL}")
    elif messageType == ECHO:
        print(f"{BackgroundColors.OKGREEN}{nick} ECHO{BackgroundColors.OKCYAN}: {messageContent}{Style.RESET_ALL}")
        emptyEcho(messageContent, nick)
        clientSocket.sendto(createDatagram(nick, NORMALMESSAGE, messageContent), (HOST, PORT))
    else:
        print(f"{BackgroundColors.FAIL}Invalid message type.{Style.RESET_ALL}", end=" ")

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
        return True
    return False

# This function verify if the ECHO message is empty 
# @param message: The message to verify
# @param username: The username of the peer
# @return: None
# @logic: This function will verify if the ECHO message is empty after removing the "ECHO" word. If it is empty, it will replace it with a default message
def emptyEcho(message, username):
    message = message[5:]
    if (len(message) == 0):
        message = username + " said ECHO"
    return message

# This function verify if the message is too long
# @param message: The message to verify
# @return: True if the message is too long, False otherwise
# @logic: This function will verify if the message is too long according to the length valid range for the datagram
def isMessageTooLong(message):
    if (len(message) > 256):
        return True
    return False

# This function sends the datagram
# @param message: The message to send
# @param messageType: The type of the message
# @param username: The username of the peer
# @param HOST: The host of the peer
# @param PORT: The port of the peer
# @return: None
# @logic: This function will send the datagram to the server if the message is not too long
def sendMessage(message, messageType, username, HOST, PORT):
    if (isMessageTooLong(message)):
            print(f"{BackgroundColors.FAIL}The message is too long. Please try again.{Style.RESET_ALL}")
            return
    clientSocket.sendto(createDatagram(username, messageType, message), (HOST, PORT))

# This function handles the client
# @param HOST: The host of the peer
# @param PORT: The port of the peer
# @param username: The username of the peer
# @return: None
# @logic: This function will send the messages to the server according to the user input
def client(HOST, PORT, username): # Send messages
    while True:
        print(f"{BackgroundColors.OKGREEN}Please enter your message:{Style.RESET_ALL}", end=" ")
        message = input()

        if (message.lower() == "exit"):
            break
        else:
            messageType = NORMALMESSAGE
            if (emoji_count(emoji.emojize(message)) > 0):
                messageType = EMOJI
            elif (re.search(URL_REGEX, message)):
                messageType = URL
            elif (isEcho(message)):
                messageType = ECHO
                message = emptyEcho(message, username)
            sendMessage(message, messageType, username, HOST, PORT)
      
# This is the standard boilerplate that calls the main() function.
if __name__ == "__main__":
	main() # Call the main function
