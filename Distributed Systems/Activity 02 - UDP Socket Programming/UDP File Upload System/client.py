# @brief: This file contains the client program that will send files to the server
# The sent datagrams will be in the following format:
# 1. The first datagram will be the file size (4 bytes), filename size (4 bytes), filename (984 bytes), and the file hash (32 bytes)
# 2. The rest of the datagrams will be the file data (1024 bytes)

import socket # For creating the UDP/Datagram socket
import threading # For creating the client thread
import hashlib # For getting the file hash (SHA256)
from colorama import Style # For coloring the terminal

# Macros:
class backgroundColors: # Colors for the terminal
	OKCYAN = "\033[96m" # Cyan
	OKGREEN = "\033[92m" # Green
	WARNING = "\033[93m" # Yellow
	FAIL = "\033[91m" # Red

# Constants:
DATAGRAMSIZE = 1024 # The size of the data chunk to send

# Commands
EXIT = "exit" # Exit command
UPLOAD = "upload" # Upload command

# @brief: Verifies that the file exists
# @param filename: The name of the file to verify
# @return: True if the file exists, False otherwise
def verify_filename(filename):
	try:
		file = open(filename, 'rb')
		file.close()
		return True
	except:
		return False
	
# @brief: Processes the file and send the first datagram, then send the rest of the datagrams in a loop until the file is sent.
# @param filename: The name of the file to upload
# @param client_socket: The socket to send the file to the server
# @param server: The server to send the file to
# @return: None
def upload_file(filename, client_socket, server):
	file = open(filename, 'rb') # Open the file in binary mode
	file_data = file.read() # Read the file data
	file.close() # Close the file

	file_hash = hashlib.sha256(file_data).hexdigest() # Get the file hash

	file_size = len(file_data) # Get the file size
	filename_size = len(filename) # Get the filename size

	# Convert the file size, filename size, filename, and file hash to bytes
	first_datagram = file_size.to_bytes(4, 'big') + filename_size.to_bytes(4, 'big') + filename.encode() + file_hash.encode() 
	client_socket.sendto(first_datagram, server) # Send the first datagram

	# Send the rest of the datagrams
	for i in range(0, file_size, DATAGRAMSIZE): # Loop through the file data
		client_socket.sendto(file_data[i:i+DATAGRAMSIZE], server) # Send the file data in 1024 byte chunks

# @brief: Uploads the file to the server
# @param client_socket: The socket to send the file to the server
# @param server: The server to send the file to
# @return: None
def clientThread(client_socket, server):
	while True:
		print(f"{backgroundColors.OKCYAN}Type your command here: {Style.RESET_ALL}", end=" ")
		userInput = input().split(" ") # Split the input by spaces

		if userInput[0].lower() == EXIT: # Exit command
			return
		elif userInput[0].lower() == UPLOAD: # Upload command
			if verify_filename(userInput[1]): # File exists
				upload_file(userInput[1], client_socket, server) # Upload the file
				print(f"{backgroundColors.OKGREEN}File \"{userInput[1]}\" sent successfully!{Style.RESET_ALL}") 
			else: # File does not exist
				print(f"{backgroundColors.FAIL}File \"{userInput[1]}\" does not exist!{Style.RESET_ALL}")
		else:
			print(f"{backgroundColors.FAIL}Invalid command!{Style.RESET_ALL}")

# @brief: Main function that runs the client program
# @param: None
# @return: None
def main():
	print(f"{backgroundColors.OKCYAN}Starting client...{Style.RESET_ALL}")
	client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # Create the UDP/Datagram socket
	server = ('localhost', 7000) # The server to send the file to

	print(f"{backgroundColors.OKCYAN}Valid commands: 1. {EXIT}\n2. {UPLOAD} filenameHere{Style.RESET_ALL}")
	client_thread = threading.Thread(target=clientThread, args=(client_socket, server)) # Create the client thread
	client_thread.start() # Start the client thread

if __name__ == '__main__':
	main()