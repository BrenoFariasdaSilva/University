# @brief: This file contains the server program that will send files to the server
# The received datagrams will be in the following format:
# 1. The first datagram will be the file size (4 bytes), filename size (4 bytes), filename (956 bytes), and the file hash (64 bytes)
# 2. The rest of the datagrams will be the checksum (bytes) and the file data (1024 bytes)

import socket # For creating the UDP/Datagram socket
import threading # For creating the client thread
import os # For manipulating the file system
import hashlib # For getting the file hash (SHA256)
import math # For math operations, like ceil that was used
import logging # For logging the server actions
from tqdm import tqdm # For showing the progress bar
from colorama import Style # For coloring the terminal

# Macros:
class backgroundColors: # Colors for the terminal
	OKCYAN = "\033[96m" # Cyan
	OKGREEN = "\033[92m" # Green
	WARNING = "\033[93m" # Yellow
	FAIL = "\033[91m" # Red

# Constants:
DATAGRAM_SIZE = 1024 # The size of the data chunk to send in bytes
HASH_SIZE = 64 # The size of the file hash in bytes
FILESIZE_OFFSET = 4 # The offset of the file size in the first datagram
FILENAME_SIZE_OFFSET = 8 # The offset of the filename size in the first datagram
DATAGRAM_ORDER_SIZE = 4 # The number of fragment received
HOST = "localhost" # The server's IP address
PORT = 7000 # The server's port

# Create a logger for the server
logger = logging.getLogger("server_logger") # Create a logger
logger.setLevel(logging.DEBUG) # Set the logger level to DEBUG

# Create a file handler
file_handler = logging.FileHandler("logs/server.log") # Create a file handler
file_handler.setLevel(logging.DEBUG) # Set the file handler level to DEBUG

# Create a formatter
formatter = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s") # Create a formatter
file_handler.setFormatter(formatter) # Set the formatter

# Add the file handler to the logger
logger.addHandler(file_handler) # Add the file handler to the logger

# brief: Validate file integrity
# @param filename: The name of the file to validate
# @param file_hash: The file hash to validate
# @return: True if the file is valid, False otherwise
def validate_file(filename, file_hash):
	file = open("./server_files/" + filename, 'rb') # Open the file in binary mode
	file_data = file.read() # Read the file data
	file.close() # Close the file

	file_hash_calculated = hashlib.sha256(file_data).hexdigest() # Get the file hash
 
	return file_hash == file_hash_calculated # Check if the file hash is correct
	
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
def printFirstDatagramData(file_size, filename_size, filename, file_hash):
	print(f"{backgroundColors.OKGREEN}File size: {file_size} bytes")
	print(f"Filename size: {filename_size} bytes")
	print(f"Filename: {filename}")
	print(f"File hash: {file_hash}{Style.RESET_ALL}")

# @brief: This function add the first datagram data to the log file
# @param file_size: The file size
# @param filename_size: The filename size
# @param filename: The filename
# @param file_hash: The file hash
# @return: None
def logFirstDatagramData(file_size, filename_size, filename, file_hash):
	logger.info(f"File size: {file_size} bytes")
	logger.info(f"Filename size: {filename_size} bytes")
	logger.info(f"Filename: {filename}")
	logger.info(f"File hash: {file_hash}")

# @brief: This function verifies if there is a file with the same name in the server, if so, it deletes it
# @param filename: The filename to check
# @return: None
def verifyRepeatedFilename(filename):
	if os.path.exists("./server_files/" + filename):
		os.remove("./server_files/" + filename)

# @brief: This function returns the file size, filename size, filename, and file hash from the first datagram
# @param datagram: The datagram to get the data from
# @return: The file size, filename size, filename, and file hash
def getFirstDatagramData(datagram):
	file_size:int = int.from_bytes(datagram[0 : FILESIZE_OFFSET], 'big') 
	# print(f"file_size: {file_size}")
	filename_size:int = int.from_bytes(datagram[FILESIZE_OFFSET : FILENAME_SIZE_OFFSET], 'big')
	# print(f"filename_size: {filename_size}")
	filename:str = datagram[FILENAME_SIZE_OFFSET : FILENAME_SIZE_OFFSET + filename_size].decode('utf-8')
	file_hash = datagram[FILENAME_SIZE_OFFSET + filename_size : FILENAME_SIZE_OFFSET + filename_size + HASH_SIZE].decode('utf-8')
	return file_size, filename_size, filename, file_hash

# @brief: This is the server thread that will handle the datagram
# @param datagram: The datagram to handle
# @param client: The client's address
# @param server_socket: The server socket
# @return: None
def serverThread(first_datagram, client, server_socket):
	# Get the file size, filename size, filename, and file hash from the first datagram
	file_size, filename_size, filename, file_hash = getFirstDatagramData(first_datagram)
	verifyRepeatedFilename(filename)

	# printFirstDatagramData(file_size, filename_size, filename, file_hash)
	logFirstDatagramData(file_size, filename_size, filename, file_hash)

	file_data = b'' # Initialize the file data
	file_datagram = b'' # Initialize the datagram
	
	# calculate math ceil of file_size / DATAGRAMSIZE
	iterations = math.ceil(file_size / DATAGRAM_SIZE)
	for i in tqdm(range(iterations), desc="File Data Upload Progress", unit="iteration", ncols=100): # Loop through the file data
		# if is not the last iteration, get full datagram
		if i == iterations - 1:
			file_datagram = server_socket.recvfrom(DATAGRAM_ORDER_SIZE + (file_size % DATAGRAM_SIZE))[0]
		else: # else get the remaining bytes
			file_datagram = server_socket.recvfrom(DATAGRAM_ORDER_SIZE + DATAGRAM_SIZE)[0] 

		# print(f"Recieved {int.from_bytes(datagram[:ACKDATAGRAMSIZE], 'big')}")
		file_data += file_datagram[DATAGRAM_ORDER_SIZE:]
		server_socket.sendto(file_datagram[:DATAGRAM_ORDER_SIZE], client)
		# print(f"Sending ACK {int.from_bytes(datagram[:ACKDATAGRAMSIZE], 'big')}")

	logger.info(f"File data recieved")
	write_file(filename, file_data) # Write the file data to the file

	if validate_file(filename, file_hash): # Check if the file is valid, send OK
		print(f"{backgroundColors.OKGREEN}File {filename} is valid. Operation was successful!{Style.RESET_ALL}")
		logger.info(f"File is valid. Operation was successful!")
		server_socket.sendto(b"OK", client)
	else:
		print(f"{backgroundColors.FAIL}File is invalid. Operation failed!{Style.RESET_ALL}")
		logger.info(f"File {filename} is invalid. Operation failed!")
		server_socket.sendto(b"ERROR", client)
		os.remove("./server_files/" + filename)

	print()
	logger.info("")

	# rerun the main function in order to wait for another "first datagram"
	waitForFirstDatagram(server_socket)

# brief: This function waits for the first datagram to be sent to the server
# @param server_socket: The server socket
# @return: None
def waitForFirstDatagram(server_socket):
	print(f"{backgroundColors.OKGREEN}Waiting for file information datagram...{Style.RESET_ALL}")
	logger.info("Waiting for file information datagram...")
	first_datagram, client = server_socket.recvfrom(DATAGRAM_SIZE) # Wait for the first datagram to be sent to the server
	print(f"{backgroundColors.OKGREEN}Client connected with address {client[0]}:{client[1]}{Style.RESET_ALL}")
	logger.info(f"Client connected with address {client[0]}:{client[1]}")
	serverThread(first_datagram, client, server_socket) # Create a server thread to handle the datagram
	print(f"{backgroundColors.OKGREEN}Recieved connection from {client[0]}:{client[1]}{Style.RESET_ALL}")
	logger.info(f"Recieved connection from {client[0]}:{client[1]}")

# @brief: This the main function that will be run when the program is executed
# This function creates the UDP/DGRAM socket and binds it to the host and port.
# Then it waits for a datagram to be sent to it and creates a server thread to handle the datagram.
# @param: None
# @return: None
def main():
	print(f"{backgroundColors.OKGREEN}Starting server...{Style.RESET_ALL}")
	logger.info("Starting server...")
	print(f"{backgroundColors.OKGREEN}Server waiting for connection...{Style.RESET_ALL}")
	logger.info("Server waiting for connection...")

	server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # Create the UDP/Datagram socket
	server_socket.bind((HOST, PORT)) # Bind the socket to the host and port

	waitForFirstDatagram(server_socket) # Wait for the first datagram to be sent to the server

if __name__ == '__main__':
	main()