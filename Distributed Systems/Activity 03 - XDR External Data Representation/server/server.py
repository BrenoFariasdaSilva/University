import socket # For creating the TCP/STREAM socket
import threading # For creating the client thread
import movies_pb2 # For the movie protocol buffer
from database import MongoDatabase # For the database
from colorama import Style # For coloring the terminal

# Constants:
class backgroundColors: # Colors for the terminal
	OKCYAN = "\033[96m" # Cyan
	OKGREEN = "\033[92m" # Green
	WARNING = "\033[93m" # Yellow
	FAIL = "\033[91m" # Red

## Server:
SERVERADDRESS = ["localhost", 7000] # The server's address. The first element is the IP address, the second is the port.

## Client:
CLIENT_REQUEST_SIZE = 4 # The client request size is 4 byte

## Operations:
CREATE_MOVIE = 1 # The create movie command
GET_MOVIE = 2 # The get movie command
UPDATE_MOVIE = 3 # The update movie command
DELETE_MOVIE = 4 # The delete movie command
GET_ACTOR_BY_MOVIES = 5 # The get actor movies command
GET_CATEGORY_BY_MOVIES = 6 # The get category movies command

## Response codes:
SUCCESS = 1 # The success response code
FAILURE = 0 # The failure response code

# @brief: This function parses a list object from string
# @param list_object: The list object
# @return: The list object parsed
def parse_list_object(list_object):
	list = movies_pb2.ClientListOperation() # Create a list object
	list.ParseFromString(list_object) # Parse the list object
	return list

# @brief: This function parses a delete object from string
# @param delete_object: The delete object
# @return: The delete object parsed
def parse_delete_object(delete_object):
	delete = movies_pb2.DeleteMovieOperation() # Create a delete object
	delete.ParseFromString(delete_object) # Parse the delete object
	return delete

# @brief: This function parses a movie object from string
# @param movie_object: The movie object
# @return: The movie object parsed
def parse_movie_object(movie_object):
	movie = movies_pb2.Movie() # Create a movie object
	movie.ParseFromString(movie_object) # Parse the movie object
	return movie

# @brief: This function get a packet from the client
# @param client_socket: The client socket object
# @return: The packet
def get_client_packet(client_socket):
	packet_size = int.from_bytes(client_socket.recv(CLIENT_REQUEST_SIZE), "big") # Get the packet size
	packet = client_socket.recv(packet_size) # Get the packet
	return packet

# @brief: This function creates a movie
# @param client_socket: The client socket object
# @param database: The database object
# @return: Status code
def createMovie(client_socket, database):
	movie_string = get_client_packet(client_socket) # Get the movie object
	movie_object = parse_movie_object(movie_string) # Create a movie object
	print(f"Creating movie {backgroundColors.OKGREEN}{movie_object.name}{Style.RESET_ALL}")

	if database.createMovie(movie_object) is None:
		return FAILURE
	return SUCCESS

# @brief: This function gets a movie
# @param client_socket: The client socket object
# @param database: The database object
# @return: Status code or movie object
def geMovie(client_socket, database):
	movie_title = get_client_packet(client_socket) # Get the movie object
	get_movie_object = parse_movie_object(movie_title) # Create a movie object

	print(f"Getting movie {backgroundColors.OKGREEN}{get_movie_object.movie_title}{Style.RESET_ALL}")
	response_object = database.getMovieByTitle(get_movie_object.movie_title)
	if response_object is None:
		return FAILURE
	return response_object

# @brief: This function updates a movie
# @param client_socket: The client socket object
# @param database: The database object
# @return: Status code or movie object
def updateMovie(client_socket, database):
	old_movie_string = get_client_packet(client_socket) # Get the movie object
	old_movie_object = parse_movie_object(old_movie_string) # Create a movie object

	new_movie_string = get_client_packet(client_socket) # Get the movie object
	new_movie_object = parse_movie_object(new_movie_string) # Create a movie object

	print(f"Updating movie {backgroundColors.OKGREEN}{old_movie_object.title}{Style.RESET_ALL}")
	response_object = database.updateMovie(old_movie_object, new_movie_object)
	if response_object is None:
		return FAILURE
	return response_object

# @brief: This function deletes a movie
# @param client_socket: The client socket object
# @param database: The database object
# @return: Status code
def deleteMovie(client_socket, database):
	movie_title = get_client_packet(client_socket) # Get the movie object
	delete_object = parse_delete_object(movie_title) # Create a delete object

	print(f"Deleting movie {backgroundColors.OKGREEN}{delete_object.movie_title}{Style.RESET_ALL}")
	response_object = database.deleteMovie(delete_object.movie_title)
	if response_object is None:
		return FAILURE
	return SUCCESS

# @brief: This function gets the movies made by an actor
# @param client_socket: The client socket object
# @param database: The database object
# @return: Movies List
def getMoviesByActor(client_socket, database):
	actor_name_string = get_client_packet(client_socket) # Get the actor name

	list_movies_object = parse_list_object(actor_name_string) # Create a list by object

	print(f"Getting actor {backgroundColors.OKGREEN}{list_movies_object.filter}{Style.RESET_ALL}'s movies")
	movies_list = database.listByActors(list_movies_object.filter)
	if movies_list is None:
		return FAILURE
	return movies_list

# @brief: This function gets a category's movies
# @param client_socket: The client socket object
# @param database: The database object
# @return: Movies List
def getMoviesByCategory(client_socket, database):
	movie_category = get_client_packet(client_socket) # Get the movie category5

	list_movies_object = parse_list_object(movie_category) # Create a list by object

	print(f"Getting category {backgroundColors.OKGREEN}{list_movies_object.filter}{Style.RESET_ALL}'s movies")
	movies = database.listByCategory(list_movies_object.filter)
	if movies is None:
		return FAILURE
	movies_list = ""
	for movie in movies:
		print(f"{backgroundColors.OKGREEN}{movie.title}{Style.RESET_ALL}")
		# append the movie marshalled to the movies list
		movies_list += movie.SerializeToString()
	return movies_list

# @brief: This function send the response to the client
# @param client_socket: The client socket object
# @param response: The response code
# @return: None
def send_response(client_socket, response):
	# Serialize the response to the protocol buffer
	response_object = movies_pb2.serverResponse()
	response_object.response = response
	# Send the response to the client
	client_socket.send(response_object.SerializeToString())

# @brief: This function handles the client input
# @param client_socket: The client socket object
# @param client_address: The client address
# @param database: The database object
# @param client_request: The client request protocol buffer containing the operation value
# @return: None
def handle_client_input(client_socket, client_address, database, client_request):
	client_data = movies_pb2.clientRequest() # Create a client request object.
	client_data.ParseFromString(client_request) # Parse the data

	match client_data.operation:
		case CREATE_MOVIE.__str__(): # If the operation is create movie: 1
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent create movie command")
			response = createMovie(client_socket, database) # Create the movie
			# send the response code to the client
		case GET_MOVIE.__str__: # If the operation is get movie: 2
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent get movie command")
			response = geMovie(client_socket, database) # Get the movie
		case UPDATE_MOVIE.__str__(): # If the operation is update movie: 3
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent update movie command")
			response = updateMovie(client_socket, database) # Update the movie
		case DELETE_MOVIE.__str__(): # If the operation is delete movie: 4
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent delete movie command")
			response = deleteMovie(client_socket, database) # Delete the movie
		case GET_ACTOR_BY_MOVIES.__str__: # If the operation is get actor movies: 5
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent get actor movies command")
			response = getMoviesByActor(client_socket, database) # Get the actor movies
		case GET_CATEGORY_BY_MOVIES.__str__: # If the operation is get category movies: 6
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent get category movies command")
			response = getMoviesByCategory(client_socket, database) # Get the category movies
		case _: # If the operation is unknown
			print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent unknown command")
	send_response(client_socket, response)

# @brief: This function handles the client input
# @param client_socket: The client socket
# @param client_address: The client address
# @return: None
def client_input(client_socket, client_address):
	database_connection = MongoDatabase() # Get a database connection object
	while True:
		try:
			next_package_size = client_socket.recv(CLIENT_REQUEST_SIZE) # Receive the next_package_size from the client
			client_request = client_socket.recv(next_package_size) # Receive the operation from the client
			if not client_request: # If the data is empty
				print(f"Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL} sent empty data")
				break
			handle_client_input(client_socket, client_address, database_connection, client_request) # Handle the client input
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