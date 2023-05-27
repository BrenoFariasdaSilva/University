import socket # For creating the TCP/STREAM socket
import threading # For creating the client thread
from google.protobuf.json_format import MessageToJson # For converting the protocol buffer to a dictionary
import google.protobuf.internal.decoder as decoder # For decoding the protocol buffer
import structs.movies_pb2 as movies_pb2 # For the protocol buffers. It is importing the movies_pb2.py file from the structs folder
from database.database import MongoDatabase # For the database. It is importing the database.py file from the database folder
from colorama import Style # For coloring the terminal

# Background colors:
class backgroundColors: # Colors for the terminal
	OKCYAN = "\033[96m" # Cyan
	OKGREEN = "\033[92m" # Green
	WARNING = "\033[93m" # Yellow
	FAIL = "\033[91m" # Red

# Server:
SERVERADDRESS = ["localhost", 7070] # The server's address. The first element is the IP address, the second is the port.

# Client:
CLIENT_REQUEST_SIZE = 4 # The client request size is 4 byte

# Response codes:
SUCCESS = 1 # The success response code
FAILURE = 0 # The failure response code

# Empty Fields:
EMPTY_STRING_FIELD = "Undefined" # The empty field
EMPTY_INT_FIELD = -1 # The empty field
EMPTY_LIST_FIELD = [] # The empty field

# Erase Key:
ERASE_MOVIES = False # If the movies should be erased

# @brief: This function converts the document to a protocol buffer
# @param document: The movie document
# @return: The movie protocol buffer
def convert_document_to_protocol_buffer(document):
	movie = movies_pb2.Movie() # Create a movie object
	movie.id = str(document["_id"]) # Set the id
	movie.plot = document["plot"] if document["plot"] else EMPTY_STRING_FIELD # Set the plot
	movie.genre = document["genre"] if document["genre"] else EMPTY_STRING_FIELD # Set the genre
	movie.runtime = document["runtime"] if document["runtime"] else EMPTY_INT_FIELD # Set the runtime
	if document["cast"]:
		movie.cast.extend(document["cast"]) # Set the cast
	movie.num_mflix_comments = document["numMflixComments"] if document["numMflixComments"] else EMPTY_INT_FIELD # Set the num_mflix_comments
	movie.title = document["title"] if document["title"] else EMPTY_STRING_FIELD # Set the title
	movie.fullplot = document["fullplot"] if document["fullplot"] else EMPTY_STRING_FIELD # Set the fullplot
	if document["countries"]:
		movie.countries.extend(document["countries"])
	movie.released = document["released"] if document["released"] else EMPTY_STRING_FIELD # Set the released
	if document["directors"]:
		movie.directors.extend(document["directors"])
	movie.rated = document["rated"] if document["rated"] else EMPTY_STRING_FIELD # Set the rated
	movie.lastupdated = document["lastupdated"] if document["lastupdated"] else EMPTY_STRING_FIELD # Set the lastupdated
	movie.year = document["year"] if document["year"] else EMPTY_INT_FIELD # Set the year
	movie.type = document["type"] if document["type"] else EMPTY_STRING_FIELD # Set the type
	return movie # Return the movie object

# @brief: This function updates a movie object fields
# @param updated_movie_object: The new movie object
# @param old_movie_object: The old movie object
# @return: The updated movie object
def updateMovieObjectFields(updated_movie_object, old_movie_object):
	# updated_movie_object.id = old_movie_object.id
	updated_movie_object.plot = old_movie_object.plot if updated_movie_object.plot else old_movie_object.plot
	updated_movie_object.genre = old_movie_object.genre if updated_movie_object.genre else old_movie_object.genre
	updated_movie_object.runtime = old_movie_object.runtime if updated_movie_object.runtime else old_movie_object.runtime
	if not updated_movie_object.cast:
		updated_movie_object.cast.extend(old_movie_object.cast) # Set the cast
	updated_movie_object.num_mflix_comments = old_movie_object.num_mflix_comments if updated_movie_object.num_mflix_comments else old_movie_object.num_mflix_comments
	updated_movie_object.title = old_movie_object.title if updated_movie_object.title else old_movie_object.title
	updated_movie_object.fullplot = old_movie_object.fullplot if updated_movie_object.fullplot else old_movie_object.fullplot
	if not updated_movie_object.countries:
		updated_movie_object.countries.extend(old_movie_object.countries)
	updated_movie_object.released = old_movie_object.released if updated_movie_object.released else old_movie_object.released
	if not updated_movie_object.directors:
		updated_movie_object.directors.extend(old_movie_object.directors)
	updated_movie_object.rated = old_movie_object.rated if updated_movie_object.rated else old_movie_object.rated
	updated_movie_object.lastupdated = old_movie_object.lastupdated if updated_movie_object.lastupdated else old_movie_object.lastupdated
	updated_movie_object.year = old_movie_object.year if updated_movie_object.year else old_movie_object.year
	updated_movie_object.type = old_movie_object.type if updated_movie_object.type else old_movie_object.type

	return updated_movie_object

# @brief: This function erases all of the movies inside the database
# @param database: The database object
# @return: Status code
def eraseAllMovies(database: MongoDatabase):
	return database.eraseAllMovies()

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

# @brief: This function parses a GetMovieOperation object from string
# @param get_movie_object: The GetMovieOperation object
# @return: The GetMovieOperation object parsed
def parse_get_movie_object(get_movie_object):
	get_movie = movies_pb2.GetMovieOperation() # Create a GetMovieOperation object
	get_movie.ParseFromString(get_movie_object) # Parse the GetMovieOperation object
	return get_movie

# @brief: This function parses a movie object from string
# @param serialized_movie: The movie object
# @return: The movie object parsed
def parse_movie_object(serialized_movie):
	deserialized_movie = movies_pb2.Movie() # Create a movie object
	deserialized_movie.ParseFromString(serialized_movie) # Parse the movie object
	return deserialized_movie

# @brief: This function get a packet from the client
# @param client_socket: The client socket object
# @return: The packet
def get_client_packet(client_socket):
	packet_size = int.from_bytes(client_socket.recv(CLIENT_REQUEST_SIZE), "big") # Get the packet size
	print(f"{backgroundColors.OKGREEN}	Parsed Packet size: {backgroundColors.OKCYAN}{packet_size}{Style.RESET_ALL}")
	serialized_packet = client_socket.recv(packet_size) # Get the packet
	print(f"{backgroundColors.OKGREEN}	Bytes Packet: {backgroundColors.OKCYAN}{serialized_packet}{Style.RESET_ALL}")
	return serialized_packet

# @brief: This function creates a movie
# @param client_socket: The client socket object
# @param database: The database object
# @return: Status code
def createMovie(client_socket, database: MongoDatabase):
	serialized_movie = get_client_packet(client_socket) # Get the movie object
	deserialized_movie = parse_movie_object(serialized_movie) # Create a movie object
	print(f"{backgroundColors.OKGREEN} deserialized_movie.title: {backgroundColors.OKCYAN}{deserialized_movie.title}{Style.RESET_ALL}")

	return database.createMovie(MessageToJson(deserialized_movie))

# @brief: This function gets a movie
# @param client_socket: The client socket object
# @param database: The database object
# @return: Status code or movie object
def getMovie(client_socket, database):
	serialized_get_movie = get_client_packet(client_socket) # Get the movie object
	deserialized_get_movie = parse_get_movie_object(serialized_get_movie) # Create a movie object

	print(f"{backgroundColors.OKGREEN}	Getting movie {backgroundColors.OKCYAN}{deserialized_get_movie.movie_title}{backgroundColors.OKGREEN} from database{Style.RESET_ALL}")
	movie_document = database.getMovieByTitle(deserialized_get_movie.movie_title)

	if movie_document is None:
		print(f"{backgroundColors.FAIL}	Movie {backgroundColors.OKCYAN}{deserialized_get_movie.movie_title}{backgroundColors.FAIL} not found{Style.RESET_ALL}")
		return None
	
	# Convert the movie object to a string and send it to the client
	movie_object = convert_document_to_protocol_buffer(movie_document)
	return movie_object

# @brief: This function updates a movie
# @param client_socket: The client socket object
# @param database: The database object
# @return: Status code or movie object
def updateMovie(client_socket, database: MongoDatabase):
	old_movie_document = getMovie(client_socket, database)
	if old_movie_document is None:
		send_response_code(client_socket, FAILURE) # Send the response to the client
		return None
	
	send_response_code(client_socket, SUCCESS) # Send the response to the client
	send_movie(client_socket, old_movie_document) # Send the response to the client

	new_movie_string = get_client_packet(client_socket) # Get the movie object
	new_movie_object = parse_movie_object(new_movie_string) # Create a movie object

	# now delete the old movie from the database
	response_delete_object = database.deleteMovie(old_movie_document.title)

	if response_delete_object is None:
		print(f"{backgroundColors.FAIL}	Failed to delete movie {backgroundColors.OKCYAN}{old_movie_document['title']}{backgroundColors.FAIL} from database{Style.RESET_ALL}")
		return FAILURE

	print(f"{backgroundColors.OKGREEN}	Updated movie name {backgroundColors.OKCYAN}{new_movie_object.title}{backgroundColors.OKGREEN} in database{Style.RESET_ALL}")

	# now add the new movie object and return the status code
	return database.createMovie(MessageToJson(new_movie_object))

# @brief: This function deletes a movie
# @param client_socket: The client socket object
# @param database: The database object
# @return: Status code
def deleteMovie(client_socket, database):
	serialized_delete_movie = get_client_packet(client_socket) # Get the movie object
	deserialized_delete_movie = parse_delete_object(serialized_delete_movie) # Create a delete object

	if (ERASE_MOVIES): # If the erase movies flag is set, erase all movies
		return eraseAllMovies() # Erase all movies and return the deleted movies count

	print(f"{backgroundColors.OKGREEN} Deleting movie {backgroundColors.OKCYAN}{deserialized_delete_movie.movie_title}{Style.RESET_ALL}")
	response_object = database.deleteMovie(deserialized_delete_movie.movie_title)
	if response_object is None: # If the response object is None, return FAILURE
		return FAILURE
	return response_object 

# @brief: This function gets the movies made by an actor
# @param client_socket: The client socket object
# @param database: The database object
# @return: Movies List
def getMoviesByActor(client_socket, database):
	actor_name_string = get_client_packet(client_socket) # Get the actor name

	list_movies_object = parse_list_object(actor_name_string) # Create a list by object

	print(f"{backgroundColors.OKGREEN} Getting movies from {backgroundColors.OKCYAN}{list_movies_object.filter}{backgroundColors.OKGREEN} actor{Style.RESET_ALL}")
	movies_list_document = database.listByActor(list_movies_object.filter) # Get the movies list from the database
	movies_list = movies_pb2.ServerListBy() # Create a movies list object
	for movie in movies_list_document: # For each movie in the movies list
		# append the movie marshalled to the movies list
		movies_list.movies.append(convert_document_to_protocol_buffer(movie))

	print(f"{backgroundColors.OKGREEN} Movies list Count: {backgroundColors.OKCYAN}{len(movies_list.movies)}{Style.RESET_ALL}")
	return movies_list # Return the movies list

# @brief: This function gets a category's movies
# @param client_socket: The client socket object
# @param database: The database object
# @return: Movies List
def getMoviesByGenre(client_socket, database):
	category_name_string = get_client_packet(client_socket) # Get the actor name

	list_movies_object = parse_list_object(category_name_string) # Create a list by object

	print(f"{backgroundColors.OKGREEN} Getting movies from {backgroundColors.OKCYAN}{list_movies_object.filter}{backgroundColors.OKGREEN} category{Style.RESET_ALL}")
	movies_list_document = database.listByGenre(list_movies_object.filter) # Get the movies list from the database
	movies_list = movies_pb2.ServerListBy() # Create a movies list object
	for movie in movies_list_document: # For each movie in the movies list
		# append the movie marshalled to the movies list
		movies_list.movies.append(convert_document_to_protocol_buffer(movie))
	return movies_list # Return the movies list

# @brief: This function send the response to the client
# @param client_socket: The client socket object
# @param response: The response code
# @return: None
def send_response_code(client_socket, response):
	# Serialize the response to the protocol buffer
	response_object = movies_pb2.ResponseCode() # Create a response object
	response_object.response = str(response) # Set the response code
	print(f"{backgroundColors.OKGREEN}	Sending Response: {backgroundColors.OKCYAN}{response_object.response}{Style.RESET_ALL}")
	# Send the response length to the client
	client_socket.send(len(response_object.SerializeToString()).to_bytes(4, byteorder='big'))
	# Send the response to the client
	client_socket.send(response_object.SerializeToString())
	print(f"{backgroundColors.OKGREEN}	Response sent successfully{Style.RESET_ALL}")

# @brief: This function sends the movies list to the client by sending the length of the list and then the list
# @param client_socket: The client socket object
# @param movies: The movie object
# @return: None
def send_movie(client_socket, movie):
	movie_length = len(movie.SerializeToString())
	# Send the movie length to the client
	client_socket.send(movie_length.to_bytes(4, byteorder='big'))
	# Send the movie to the client
	client_socket.send(movie.SerializeToString())
	print(f"{backgroundColors.OKGREEN}	Movie sent successfully{Style.RESET_ALL}")

# @brief: This function handles the client input
# @param client_socket: The client socket object
# @param client_address: The client address
# @param database: The database object
# @param client_request: The client request protocol buffer containing the operation value
# @return: None
def handle_client_input(client_socket, client_address, database, client_request):
	parsed_client_request = movies_pb2.ClientRequest() # Create a client request object.
	print(f"{backgroundColors.OKGREEN}	Client request: {backgroundColors.OKCYAN}{client_request}{Style.RESET_ALL}")
	parsed_client_request.ParseFromString(client_request) # Parse the data
	print(f"{backgroundColors.OKGREEN}	Parsed Client Request Operation: {backgroundColors.OKCYAN}{parsed_client_request.operation}{Style.RESET_ALL}")

	match parsed_client_request.operation:
		case movies_pb2.Operations.Create: # If the operation is create movie: 1
			print(f"{backgroundColors.OKGREEN}	Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]} {backgroundColors.OKGREEN}sent create movie command{Style.RESET_ALL}")
			response_code = createMovie(client_socket, database) # Create the movie
			send_response_code(client_socket, response_code) # Send the response to the client
		case movies_pb2.Operations.Read: # If the operation is get movie: 2
			print(f"{backgroundColors.OKGREEN}	Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{backgroundColors.OKGREEN} sent get movie command{Style.RESET_ALL}")
			response_movie = getMovie(client_socket, database) # Get the movie
			if not response_movie is None:
				send_response_code(client_socket, SUCCESS) # Send the response to the client
				send_movie(client_socket, response_movie) # Send the response to the client
			else:
				send_response_code(client_socket, FAILURE) # Send the response to the client
		case movies_pb2.Operations.Update: # If the operation is update movie: 3
			print(f"{backgroundColors.OKGREEN}	Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{backgroundColors.OKGREEN} sent update movie command{Style.RESET_ALL}")
			response_code = updateMovie(client_socket, database) # Update the movie
			send_response_code(client_socket, response_code) # Send the response to the client
		case movies_pb2.Operations.Delete: # If the operation is delete movie: 4
			print(f"{backgroundColors.OKGREEN}	Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{backgroundColors.OKGREEN} sent delete movie command{Style.RESET_ALL}")
			response_code = deleteMovie(client_socket, database) # Delete the movie
			send_response_code(client_socket, response_code) # Send the response to the client
		case movies_pb2.Operations.ListByActor: # If the operation is get actor movies: 5
			print(f"{backgroundColors.OKGREEN}	Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{backgroundColors.OKGREEN} sent get actor movies command{Style.RESET_ALL}")
			movies_list = getMoviesByActor(client_socket, database) # Get the movies of some specific actor
			if not movies_list is None:
				send_response_code(client_socket, SUCCESS) # Send the response to the client
				send_movie(client_socket, movies_list) # Send the response to the client
		case movies_pb2.Operations.ListByGenre: # If the operation is get category movies: 6
			print(f"{backgroundColors.OKGREEN}	Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{backgroundColors.OKGREEN} sent get category movies command{Style.RESET_ALL}")
			movies_list = getMoviesByGenre(client_socket, database) # Get the category movies
			if not movies_list is None:
				send_response_code(client_socket, SUCCESS) # Send the response to the client
				send_movie(client_socket, movies_list) # Send the response to the client
		case _: # If the operation is unknown
			print(f"{backgroundColors.OKGREEN}	Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{backgroundColors.OKGREEN} sent unknown command{Style.RESET_ALL}")

# @brief: This function handles the client input
# @param client_socket: The client socket
# @param client_address: The client address
# @return: None
def client_input(client_socket, client_address):
	database_connection = MongoDatabase() # Get a database connection object
	while True:
		try:
			print(f"{backgroundColors.OKGREEN}Waiting for client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{backgroundColors.OKGREEN} message{Style.RESET_ALL}")
			next_package_size = client_socket.recv(CLIENT_REQUEST_SIZE) # Receive the next_package_size from the client
			print(f"{backgroundColors.OKGREEN}	Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{backgroundColors.OKGREEN} sent next_package_size: {backgroundColors.OKCYAN}{next_package_size}{backgroundColors.OKGREEN} bytes{Style.RESET_ALL}")
			next_package_size = int.from_bytes(next_package_size, byteorder="big")
			print(f"{backgroundColors.OKGREEN}	Parsed Client next_package_size: {backgroundColors.OKCYAN}{next_package_size}{backgroundColors.OKGREEN} bytes{Style.RESET_ALL}")
			client_request = client_socket.recv(next_package_size) # Receive the operation from the client
			if not client_request: # If the data is empty
				print(f"{backgroundColors.OKGREEN}	Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{backgroundColors.FAIL} sent empty data{Style.RESET_ALL} ")
				break
			handle_client_input(client_socket, client_address, database_connection, client_request) # Handle the client input
			print("")
		except ConnectionResetError:
			print(f"{backgroundColors.OKGREEN}	Client {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{backgroundColors.FAIL} disconnected{Style.RESET_ALL}")
			break

# @brief: This is the main function of the server
# @param: None
# @return: None
def main():
	print(f"{backgroundColors.OKGREEN}Server started{Style.RESET_ALL}")
	server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Create a TCP/STREAM socket
	server_socket.bind((SERVERADDRESS[0], SERVERADDRESS[1])) # Bind the socket to the server address
	server_socket.listen() # Listen for connections
 
	while True:
		client_socket, client_address = server_socket.accept() # Accept the client connection
		print(f"{backgroundColors.OKGREEN}Client connected with address {backgroundColors.OKCYAN}{client_address[0]}:{client_address[1]}{Style.RESET_ALL}")
		client_thread = threading.Thread(target=client_input, args=(client_socket, client_address)) # Create a thread for the client
		client_thread.start() # Start the client thread

if __name__ == "__main__":
	main()