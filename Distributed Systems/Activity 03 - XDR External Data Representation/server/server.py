import socket # For creating the TCP/STREAM socket
import threading # For creating the client thread
import movies_pb2 # For the movie protocol buffer
from colorama import Style # For coloring the terminal

# Constants:
class backgroundColors: # Colors for the terminal
	OKCYAN = "\033[96m" # Cyan
	OKGREEN = "\033[92m" # Green
	WARNING = "\033[93m" # Yellow
	FAIL = "\033[91m" # Red

SERVERADDRESS = ["localhost", 7000] # The server's address. The first element is the IP address, the second is the port.
PACKAGESIZE = 1024 # The size of the data chunk to send in bytes

# @brief: This function handles the client input
# @param client_socket: The client socket
# @param client_address: The client address
# @return: None
def client_input(client_socket, client_address):
	while True:
		try:
			# Receive the data from the client
			data = client_socket.recv(PACKAGESIZE)
			if not data:
				break
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent: {data.decode()}")
			client_socket.sendall(data)
		except ConnectionResetError:
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} disconnected")
			break

# @brief: This is the main function of the server
# @param: None
# @return: None
def main():
	server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Create a TCP/STREAM socket
	server_socket.bind((SERVERADDRESS[0], SERVERADDRESS[1])) # Bind the socket to the server address
	server_socket.listen() # Listen for connections
 
	while True:
		client_socket, client_address = server_socket.accept() # Accept the client connection
		print(f"Client connected with address {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL}")
		client_thread = threading.Thread(target=client_input, args=(client_socket, client_address)) # Create a thread for the client
		client_thread.start() # Start the client thread
		

if __name__ == "__main__":
	main()