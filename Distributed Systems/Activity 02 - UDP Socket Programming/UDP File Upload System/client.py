# @brief: This file contains the client program that will send files to the server
# The sent datagrams will be in the following format:
# 1. The first datagram will be the file size (4 bytes), filename size (4 bytes), filename (956 bytes), and the file hash (64 bytes)
# 2. The rest of the datagrams will be the checksum (bytes) and the file data (1024 bytes)

import socket # For creating the UDP/Datagram socket
import threading # For creating the client thread
import hashlib # For getting the file hash (SHA256)
import math # For math operations, like ceil that was used
import logging # For logging the server actions
import time # For logging the server actions
from tqdm import tqdm # For showing the progress bar
from colorama import Style # For coloring the terminal

# Macros:
class backgroundColors: # Colors for the terminal
	OKCYAN = "\033[96m" # Cyan
	OKGREEN = "\033[92m" # Green
	WARNING = "\033[93m" # Yellow
	FAIL = "\033[91m" # Red

# Constants:
SERVER_ADDRESS = ('localhost', 7000) # The server to send the file to
DATAGRAM_SIZE = 1024 # The size of the data chunk to send
DATAGRAM_ORDER_SIZE = 4 # The size of the ack datagram
MAX_FILENAME_SIZE = 956 # The maximum size of the filename

# Commands
EXIT = "exit" # Exit command
HELP = "help" # Help command
UPLOAD = "upload" # Upload command

# Create a logger for the client
logger = logging.getLogger("client_logger") # Create a logger
logger.setLevel(logging.DEBUG) # Set the logger level to DEBUG

# Create a file handler
file_handler = logging.FileHandler("logs/client.log") # Create a file handler
file_handler.setLevel(logging.DEBUG) # Set the file handler level to DEBUG

# Create a formatter
formatter = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s") # Create a formatter
file_handler.setFormatter(formatter) # Set the formatter

# Add the file handler to the logger
logger.addHandler(file_handler) # Add the file handler to the logger

# @brief: This function waits for the server to send a datagram, related to "OK" or "ERROR" file upload
# @param client_socket: The socket to receive the datagram from
# @param filename: The name of the file to re-upload if the file upload failed
# @return: The datagram received from the server
def waitForServerResponse(client_socket, filename):
	datagram, server = client_socket.recvfrom(DATAGRAM_SIZE) # Wait for the server to send a datagram
	
	if datagram.decode() == "OK":
		print(f"{backgroundColors.OKGREEN}File {filename} uploaded successfully!{Style.RESET_ALL}")
		logger.info("File uploaded successfully!")
	elif datagram.decode() == "ERROR":
		print(f"{backgroundColors.FAIL}File {filename} upload failed{Style.RESET_ALL}")
		logger.error("File upload failed")
		clientThread(client_socket)
		# upload_file(filename, client_socket) # Re-upload the file
  
# @brief: This function verifies if the filename is less or equal to MAX_FILENAME_SIZE bytes
# @param: filename: The name of the file to verify
# @return: True if the filename is less or equal to MAX_FILENAME_SIZE bytes, False otherwise
def verify_filename_length(filename):
	return len(filename) <= MAX_FILENAME_SIZE
  
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

# @brief: This function add the first datagram data to the log file
# @param file_size: The file size
# @param filename_size: The filename size
# @param filename: The filename
# @param file_hash: The file hash
# @return: None
def logFirstDatagramData(file_size, filename_size, filename, file_hash):
	logger.info(f"File size: {file_size} bytes")
	logger.info(f"Filename size: {filename_size} bytes")
	logger.info(f"Filename: {filename.encode('utf-8')}")
	logger.info(f"File hash: {file_hash}")

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
		print(f"{backgroundColors.FAIL}Filename must be less than {MAX_FILENAME_SIZE} bytes!{Style.RESET_ALL}")
		logger.error(f"Filename must be less than {MAX_FILENAME_SIZE} bytes!")
		return
 
	# printFirstDatagramData(file_size, filename_size, filename, file_hash)
	logFirstDatagramData(file_size, filename_size, filename, file_hash)

	# Convert the file size, filename size, filename, and file hash to bytes
	first_datagram = file_size.to_bytes(4, 'big') + filename_size.to_bytes(4, 'big') + str.encode(filename, 'utf-8') + str.encode(file_hash, 'utf-8' )
	# print(f"Filename size: {int.from_bytes(file_size.to_bytes(4, 'big'), 'big')}")
	client_socket.sendto(first_datagram, SERVER_ADDRESS) # Send the first datagram

	# Send the filedata datagrams
	iterations = math.ceil(file_size / DATAGRAM_SIZE)
	for i in tqdm(range(iterations), desc="File Data Upload Progress", unit="iteration", ncols=100, bar_format="{desc}: {percentage:3.0f}%|{bar}|  elapsed time: {elapsed}"): # Loop through the file data
		datagram_number = i.to_bytes(DATAGRAM_ORDER_SIZE, 'big') # Convert the sequence number to bytes
		if i == iterations - 1:
			file_data_datagram = datagram_number + file_data[(i * DATAGRAM_SIZE) : (i * DATAGRAM_SIZE) + (file_size % DATAGRAM_SIZE)]
		else:
			file_data_datagram = datagram_number + file_data[(i * DATAGRAM_SIZE) : (i + 1) * DATAGRAM_SIZE]
		# print(f"Sending: {int.from_bytes(datagram[:ACKDATAGRAMSIZE], 'big')}")
  
		client_socket.sendto(file_data_datagram, SERVER_ADDRESS) # Send the datagram
		while True:
			ack_datagram = client_socket.recvfrom(DATAGRAM_ORDER_SIZE)[0] # Wait for the server to send an ack datagram
			# print(f"Received: {int.from_bytes(ack_datagram, 'big')}")
			if int.from_bytes(ack_datagram, 'big') == i: # If the sequence number is the same as the one sent,
				break
			else:
				print(f"{backgroundColors.FAIL}Error in sending datagram {i}. Received {ack_datagram.decode()}!{Style.RESET_ALL}")
				logger.error(f"Error in sending datagram {i}. Received {ack_datagram.decode()}!")

		# Uncomment the following line to slow down the upload so you can see the progress bar move if it is going too fast
		# time.sleep(0.1)

	waitForServerResponse(client_socket, filename) # Wait for the server to send a datagram

# @brief: Uploads the file to the server
# @param client_socket: The socket to send the file to the server
# @return: None
def clientThread(client_socket):
	while True:
		print(f"{backgroundColors.OKGREEN}Type your command here: {Style.RESET_ALL}", end="")
		logger.info("Type your command here: ")
		userInput = input().split(" ") # Split the input by spaces
		logger.info(userInput)

		if userInput[0].lower() == EXIT: # Exit command
			return
		elif userInput[0].lower() == HELP: # Help command
			printHelpCommands()
		elif userInput[0].lower() == UPLOAD: # Upload command
			if verify_filename(userInput[1]): # File exists
				upload_file(userInput[1], client_socket) # Upload the file
			else: # File does not exist
				print(f"{backgroundColors.FAIL}File \"{userInput[1]}\" does not exist!{Style.RESET_ALL}")
			print()
			logger.info("")
		else:
			print(f"{backgroundColors.FAIL}Invalid command!{Style.RESET_ALL}")

# @brief: Prints the help commands
# @param: None
# @return: None
def printHelpCommands():
	print(f"{backgroundColors.OKCYAN}Valid commands:\n1. {EXIT}\n2. {UPLOAD} filenameHere\n3. {HELP}{Style.RESET_ALL}")
	print(f"{backgroundColors.WARNING}Note: {UPLOAD} command only works with files in the client_files folder!{Style.RESET_ALL}")

# @brief: Main function that runs the client program
# @param: None
# @return: None
def main():
	print(f"{backgroundColors.OKGREEN}Starting client...{Style.RESET_ALL}")
	logger.info("Starting client...")
	client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # Create the UDP/Datagram socket
	printHelpCommands() # Print the help commands
	client_thread = threading.Thread(target=clientThread, args=(client_socket,)) # Create the client thread
	client_thread.start() # Start the client thread

if __name__ == '__main__':
	main()