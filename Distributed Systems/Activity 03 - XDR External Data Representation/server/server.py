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
CLIENT_REQUEST_SIZE = 1 # The client request size is 1 byte
CREATE_MOVIE = 1 # The create movie command
GET_MOVIE = 2 # The get movie command
UPDATE_MOVIE = 3 # The update movie command
DELETE_MOVIE = 4 # The delete movie command
GET_ACTOR_MOVIES = 5 # The get actor movies command
GET_CATEGORY_MOVIES = 6 # The get category movies command

# @brief: This function creates a movie

# @brief: This function creates a movie
# @param movie: movie protocol buffer
# @return: Status code
def create_movie(movie):
	print(f"Creating movie {backgroundColors.OKGREEN}{movie.name}{Style.RESET_ALL}")
	# Get the crud_request, access it's movie attribute which contains a object of the Movie type.
	# Access the movie's attributes and print them.
	# Return the status code
	# movie_object = 




# @brief: This function gets a movie
# @param crud_request: The crud request protocol buffer
# @return: Status code
def get_movie(crud_request):
	print(f"Getting movie {backgroundColors.OKGREEN}{crud_request.movie.name}{Style.RESET_ALL}")

# @brief: This function updates a movie
# @param crud_request: The crud request protocol buffer
# @return: Status code
def update_movie(crud_request):
	print(f"Updating movie {backgroundColors.OKGREEN}{crud_request.movie.name}{Style.RESET_ALL}")

# @brief: This function deletes a movie
# @param crud_request: The crud request protocol buffer
# @return: Status code
def delete_movie(crud_request):
	print(f"Deleting movie {backgroundColors.OKGREEN}{crud_request.movie.name}{Style.RESET_ALL}")

# @brief: This function gets an actor's movies
# @param client_list_request: The client list request protocol buffer
# @return: Movies List
def get_actor_movies(client_list_request):
	print(f"Getting actor {backgroundColors.OKGREEN}{client_list_request.argument}{Style.RESET_ALL}'s movies")

# @brief: This function gets a category's movies
# @param movie: The movie protocol buffer
# @return: Movies List
def get_category_movies(client_list_request):
	print(f"Getting category {backgroundColors.OKGREEN}{client_list_request.argument}{Style.RESET_ALL}'s movies")

# @brief: This function send the response to the client
# @param client_socket: The client socket object
# @param response: The response code
# @return: None
def send_response(client_socket, response):
	client_socket.sendall(response) # Send the response to the client

# @brief: This function handles the client input
# @param data: The data the client sent to handled
# @param client_socket: The client socket object
# @param client_address: The client address
# @return: None
def handle_client_input(data, client_socket, client_address):
	client_data = movies_pb2.clientRequest() # Create a client request object.
	client_data.ParseFromString(data) # Parse the data

	match data.operation:
		case CREATE_MOVIE.__str__(): # If the operation is create movie: 1
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent create movie command")
			response = create_movie(data.movie) # Create the movie
			# send the response code to the client
		case GET_MOVIE.__str__: # If the operation is get movie: 2
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent get movie command")
		case UPDATE_MOVIE.__str__(): # If the operation is update movie: 3
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent update movie command")
		case DELETE_MOVIE.__str__(): # If the operation is delete movie: 4
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent delete movie command")
		case GET_ACTOR_MOVIES.__str__: # If the operation is get actor movies: 5
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent get actor movies command")
		case GET_CATEGORY_MOVIES.__str__: # If the operation is get category movies: 6
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent get category movies command")
		case _: # If the operation is unknown
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent unknown command")
	send_response(client_socket, response)

# @brief: This function handles the client input
# @param client_socket: The client socket
# @param client_address: The client address
# @return: None
def client_input(client_socket, client_address):
	# database_connection = 
	while True:
		try:
			# Receive the data from the client
			data = client_socket.recv(CLIENT_REQUEST_SIZE)
			if not data:
				print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent empty data")
				break
			handle_client_input(data, client_socket, client_address) # Handle the client input
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