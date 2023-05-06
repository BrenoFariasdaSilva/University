# @brief: This file contains the client program that will send files to the server
# The sent datagrams will be in the following format:
# 1. The first datagram will be the file size (4 bytes), filename size (4 bytes), filename (984 bytes), and the file hash (32 bytes)
# 2. The rest of the datagrams will be the file data (1024 bytes)

# TODO: Adding ack_datagram confirmation

import socket # For creating the UDP/Datagram socket
import threading # For creating the client thread
import hashlib # For getting the file hash (SHA256)
import math # For math operations, like ceil that was used
from colorama import Style # For coloring the terminal

# Macros:
class backgroundColors: # Colors for the terminal
	OKCYAN = "\033[96m" # Cyan
	OKGREEN = "\033[92m" # Green
	WARNING = "\033[93m" # Yellow
	FAIL = "\033[91m" # Red

# Constants:
SERVERADDRESS = ('localhost', 7000) # The server to send the file to
DATAGRAMSIZE = 1024 # The size of the data chunk to send
ACKDATAGRAMSIZE = 4 # The size of the ack datagram

# Commands
EXIT = "exit" # Exit command
HELP = "help" # Help command
UPLOAD = "upload" # Upload command

# @brief: This function waits for the server to send a datagram, related to "OK" or "ERROR" file upload
# @param client_socket: The socket to receive the datagram from
# @param filename: The name of the file to re-upload if the file upload failed
# @return: The datagram received from the server
def waitForServerResponse(client_socket, filename):
	datagram, server = client_socket.recvfrom(DATAGRAMSIZE) # Wait for the server to send a datagram
	
	if datagram.decode() == "OK":
		print(f"{backgroundColors.OKGREEN}File uploaded successfully!{Style.RESET_ALL}")
	elif datagram.decode() == "ERROR":
		print(f"{backgroundColors.FAIL}File upload failed{Style.RESET_ALL}")
		clientThread(client_socket)
		# upload_file(filename, client_socket) # Re-upload the file
  
# @brief: This function verifies if the filename is less or equal to 956 bytes
# @param: filename: The name of the file to verify
# @return: True if the filename is less or equal to 956 bytes, False otherwise
def verify_filename_length(filename):
	return len(filename) <= 956
  
# @brief: This function prints the file info from the first datagram
# @param file_size: The file size
# @param filename_size: The filename size
# @param filename: The filename
# @param file_hash: The file hash
# @return: None
def printFirstDatagramData(file_size, filename_size, filename, file_hash):
	print(f"{backgroundColors.OKGREEN}File size: {file_size} bytes")
	print(f"Filename size: {filename_size} bytes")
	print(f"Filename: {filename.encode('utf-8')}")
	print(f"File hash: {file_hash}{Style.RESET_ALL}")

# @brief: Verifies that the file exists
# @param filename: The name of the file to verify
# @return: True if the file exists, False otherwise
def verify_filename(filename):
	try:
		file = open("./client_files/" + filename, 'rb') # Open the file in binary mode
		file.close() # Close the file
		return True
	except:
		return False
	
# @brief: Processes the file and send the first datagram, then send the rest of the datagrams in a loop until the file is sent.
# @param filename: The name of the file to upload
# @param client_socket: The socket to send the file to the server
# @return: None
def upload_file(filename, client_socket):
	file = open("./client_files/" + filename, 'rb') # Open the file in binary mode
	file_data = file.read() # Read the file data
	file.close() # Close the file

	file_hash = hashlib.sha256(file_data).hexdigest() # Get the file hash

	file_size = len(file_data) # Get the file size
	filename_size = len(filename) # Get the filename size
 
 	# filename must be less than 956 bytes
	if not verify_filename_length(filename):
		print(f"{backgroundColors.FAIL}Filename must be less than 956 bytes!{Style.RESET_ALL}")
		return
 
	# printFirstDatagramData(file_size, filename_size, filename, file_hash)

	# Convert the file size, filename size, filename, and file hash to bytes
	first_datagram = file_size.to_bytes(4, 'big') + filename_size.to_bytes(4, 'big') + str.encode(filename, 'utf-8') + str.encode(file_hash, 'utf-8' )
	# print(f"Filename size: {int.from_bytes(file_size.to_bytes(4, 'big'), 'big')}")
	client_socket.sendto(first_datagram, SERVERADDRESS) # Send the first datagram

	# Send the filedata datagrams
	iterations = math.ceil(file_size / DATAGRAMSIZE)
	for i in range(iterations): # Loop through the file data
		sequence_number = i.to_bytes(ACKDATAGRAMSIZE, 'big') # Convert the sequence number to bytes
		if i == iterations - 1:
			datagram = sequence_number + file_data[(i * DATAGRAMSIZE) : (i * DATAGRAMSIZE) + (file_size % DATAGRAMSIZE)]
		else:
			datagram = sequence_number + file_data[(i * DATAGRAMSIZE) : (i + 1) * DATAGRAMSIZE]
		# print(f"Sending: {int.from_bytes(datagram[:ACKDATAGRAMSIZE], 'big')}")
  
		client_socket.sendto(datagram, SERVERADDRESS) # Send the datagram
		while True:
			ack_datagram = client_socket.recvfrom(ACKDATAGRAMSIZE)[0] # Wait for the server to send an ack datagram
			# print(f"Received: {int.from_bytes(ack_datagram, 'big')}")
			if int.from_bytes(ack_datagram, 'big') == i: # If the sequence number is the same as the one sent,
				break
			else:
				print(f"{backgroundColors.FAIL}Error in sending datagram {i}. Received {ack_datagram.decode()}!{Style.RESET_ALL}")

	waitForServerResponse(client_socket, filename) # Wait for the server to send a datagram

# @brief: Uploads the file to the server
# @param client_socket: The socket to send the file to the server
# @return: None
def clientThread(client_socket):
	while True:
		print(f"{backgroundColors.OKGREEN}Type your command here: {Style.RESET_ALL}", end=" ")
		userInput = input().split(" ") # Split the input by spaces

		if userInput[0].lower() == EXIT: # Exit command
			return
		elif userInput[0].lower() == HELP: # Help command
			printHelpCommands()
		elif userInput[0].lower() == UPLOAD: # Upload command
			if verify_filename(userInput[1]): # File exists
				upload_file(userInput[1], client_socket) # Upload the file
				print(f"{backgroundColors.OKGREEN}File \"{userInput[1]}\" sent successfully!{Style.RESET_ALL}") 
			else: # File does not exist
				print(f"{backgroundColors.FAIL}File \"{userInput[1]}\" does not exist!{Style.RESET_ALL}")
		else:
			print(f"{backgroundColors.FAIL}Invalid command!{Style.RESET_ALL}")

# @brief: Prints the help commands
# @param: None
# @return: None
def printHelpCommands():
	print(f"{backgroundColors.OKCYAN}Valid commands:\n1. {EXIT}\n2. {UPLOAD} filenameHere\n3. {HELP}{Style.RESET_ALL}")

# @brief: Main function that runs the client program
# @param: None
# @return: None
def main():
	print(f"{backgroundColors.OKGREEN}Starting client...{Style.RESET_ALL}")
	client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # Create the UDP/Datagram socket
	printHelpCommands() # Print the help commands
	client_thread = threading.Thread(target=clientThread, args=(client_socket,)) # Create the client thread
	client_thread.start() # Start the client thread

if __name__ == '__main__':
	main()