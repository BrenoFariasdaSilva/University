# Create a tcp server that waits for a connection from peers in the network
# The connection is made through the port 5000 and the server is a peer list server
# It holds the nickname and IP address of all the peers in the network
# It also check if the peers are still connected to the network every 2 seconds
# If a peer is not connected anymore, it removes it from the list

import socket # Library for using sockets
import threading # Library for using threads
import time # Library for using threads

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
PORT = 7000 # Port

# Peers dictionary that holds the nickname and IP address of the peers
# Example: peers = {"nickname": "IP address"}
peers = {}

# Create a socket object
serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # TCP socket

# This is the main function
# @param: None
# @return: None
# @logic: This function will wait for a connection from peers in the network
def main():
    print(f"{backgroundColors.OKCYAN}Welcome to the Peer List Server!{Style.RESET_ALL}")
    serverSocket.bind((HOST, PORT)) # Bind to the port
    serverSocket.listen() # Now wait for client connection.
    while True:
        conn, address = serverSocket.accept()
        # address is a tuple with the IP address and the port of the peer
        threading.Thread(target=handleConnection, args=(conn, address)).start()
        # This create a thread for each peer that connects to the server

# This function will handle the connection with the peer
# @param: connection: The connection object of the peer
# @param: peerAddress: The IP address of the peer, a tuple with the IP address and the port
# @return: None
# @logic: This function will receive the nickname of the peer and add it to the list, and add the IP address of the peer to the list
# It will also check if the peer is still connected to the network every 2 seconds
def handleConnection(connection, peerAddress):
    nickname = connection.recv(64).decode("utf-8") # Receive the nickname of the peer
    peers[nickname] = peerAddress[0] # Add the nickname and IP address of the peer to the list
    print(f"{backgroundColors.OKGREEN}Added {nickname} to the list{Style.RESET_ALL}")
    while True:
        try:
            connection.sendall(bytes("OK", "utf-8")) # Send OK to the peer
            connection.recv(1) # Receive the OK from the peer
            notifyPeers(nickname, peerAddress[0], True) # Notify the peers that the peer has joined the network
        except:
            print(f"{backgroundColors.FAIL}{nickname} disconnected{Style.RESET_ALL}")
            del peers[nickname] # Remove the peer from the list
            notifyPeers(nickname, peerAddress[0], False) # Notify the peers that the peer has left the network
            break
        time.sleep(2) # Wait 2 seconds
    connection.close() # Close the connection

# This function will notify the peers that a peer has joined or left the network
# @param: nickname of the peer
# @param: IP address of the peer
# @param: joined, if the peer has joined or left the network
# @return: None
# @logic: This function will notify the peers that a peer has joined or left the network
def notifyPeers(nickname, IPAddress, joined):
    for peer in peers:
        if (peer != nickname):
            if (joined):
                print(f"{backgroundColors.OKGREEN}{nickname} with IP address {IPAddress} has joined the network{Style.RESET_ALL}")
            else:
                print(f"{backgroundColors.FAIL}{nickname} with IP address {IPAddress} has left the network{Style.RESET_ALL}")