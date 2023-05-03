# @brief: This file contains the server program that will send files to the server
# The received datagrams will be in the following format:
# 1. The first datagram will be the file size (4 bytes), filename size (4 bytes), filename (984 bytes), and the file hash (32 bytes)
# 2. The rest of the datagrams will be the file data (1024 bytes)

import socket # For creating the UDP/Datagram socket
import threading # For creating the server thread
import hashlib # For getting the file hash (SHA256)
import math
from colorama import Style # For coloring the terminal

# Macros:
class backgroundColors: # Colors for the terminal
	OKCYAN = "\033[96m" # Cyan
	OKGREEN = "\033[92m" # Green
	WARNING = "\033[93m" # Yellow
	FAIL = "\033[91m" # Red

# Constants:
DATAGRAMSIZE = 1024 # The size of the data chunk to send
HOST = "localhost" # The server's IP address
PORT = 7000 # The server's port

# brief: Validate file integrity
# @param filename: The name of the file to validate
# @param file_hash: The file hash to validate
# @return: True if the file is valid, False otherwise
def validate_file(filename, file_hash):
	file = open("./server_files/" + filename, 'rb') # Open the file in binary mode
	file_data = file.read() # Read the file data
	file.close() # Close the file

	file_hash_calculated = hashlib.sha256(file_data).hexdigest() # Get the file hash
	print(f"Calculated File hash: {file_hash_calculated}")

	if file_hash == file_hash_calculated: # Check if the file hash is correct
		return True
	else:
		return False
	
# @brief: This function wwrites the file data to the file
# @param filename: The name of the file to write to
# @param file_data: The file data to write to the file
# @return: None
def write_file(filename, file_data):
	file = open("./server_files/" + filename, 'wb') # Open the file in binary mode
	file.write(file_data) # Write the file data to the file
	file.close() # Close the file

# @brief: This function prints the file info from the first datagram
# @param file_size: The file size
# @param filename_size: The filename size
# @param filename: The filename
# @param file_hash: The file hash
# @return: None
def printFirstDatagram(file_size, filename_size, filename, file_hash):
	print(f"{backgroundColors.OKGREEN}File size: {file_size} bytes")
	print(f"Filename size: {filename_size} bytes")
	print(f"Filename: {filename}")
	print(f"File hash: {file_hash}{Style.RESET_ALL}")

# @brief: This function returns the file size, filename size, filename, and file hash from the first datagram
# @param datagram: The datagram to get the data from
# @return: The file size, filename size, filename, and file hash
def getFirstDatagramData(datagram):
	file_size = int.from_bytes(datagram[0:4], 'big')
	filename_size = int.from_bytes(datagram[4:8], 'big')
	filename = datagram[8:8+filename_size].decode('utf-8')
	file_hash = datagram[8+filename_size:8+filename_size+32].decode('utf-8')
	print("File Hash: " + file_hash)
	return file_size, filename_size, filename, file_hash

# @brief: This is the server thread that will handle the datagram
# @param datagram: The datagram to handle
# @param client: The client's address
# @param server_socket: The server socket
# @return: None
def serverThread(datagram, client, server_socket):
	# Get the file size, filename size, filename, and file hash from the first datagram
	file_size, filename_size, filename, file_hash = getFirstDatagramData(datagram)

	# printFirstDatagram(file_size, filename_size, filename, file_hash)

	file_data = b'' # Initialize the file data
	# calculate math ceil of file_size / DATAGRAMSIZE
	iterations = math.ceil(file_size / DATAGRAMSIZE)
	for i in range(iterations):
		# if is not the last iteration, get full datagram
		if i != iterations - 1:
			file_data += server_socket.recvfrom(DATAGRAMSIZE)[0]
		else: # else get the remaining bytes
			file_data += server_socket.recvfrom(file_size % DATAGRAMSIZE)[0]
	
	print(f"{backgroundColors.OKGREEN}File data recieved{Style.RESET_ALL}")
	write_file(filename, file_data) # Write the file data to the file

	if validate_file(filename, file_hash): # Check if the file is valid, send OK
		print(f"{backgroundColors.OKGREEN}File is valid{Style.RESET_ALL}")
		server_socket.sendto(b"OK", client)
	else:
		print(f"{backgroundColors.FAIL}File is invalid{Style.RESET_ALL}")
		server_socket.sendto(b"ERROR", client)
		# TODO: Delete the file from the server

# @brief: This the main function that will be run when the program is executed
# This function creates the UDP/DGRAM socket and binds it to the host and port.
# Then it waits for a datagram to be sent to it and creates a server thread to handle the datagram.
# @param: None
# @return: None
def main():
	print(f"{backgroundColors.OKGREEN}Starting server...{Style.RESET_ALL}")
	server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # Create the UDP/Datagram socket
	server_socket.bind((HOST, PORT)) # Bind the socket to the host and port
	# print that the user is waiting for a connection
	print(f"{backgroundColors.OKGREEN}Waiting for connection...{Style.RESET_ALL}")

	# while True:
		# The server is waiting for a datagram to be sent to it.
		# When it receives a datagram, it stores the datagram in the variable datagram and the client's address in the variable client.
		# The client's address is a tuple containing the client's IP address and port.
	[datagram, client] = server_socket.recvfrom(DATAGRAMSIZE)
	
	print(f"{backgroundColors.OKGREEN}Recieved connection from {client[0]}:{client[1]}{Style.RESET_ALL}")
	serverThread(datagram, client, server_socket) # Create the server thread
		# server_thread = threading.Thread(target=serverThread, args=(datagram, client, server_socket)) # Create the server thread
		# server_thread.start() # Start the server thread


if __name__ == '__main__':
	main()