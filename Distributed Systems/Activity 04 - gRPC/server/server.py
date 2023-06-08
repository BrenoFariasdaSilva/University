import grpc # For the gRPC
import structs.movies_pb2 as movies_pb2 # For the protocol buffer
import structs.movies_pb2_grpc as movies_pb2_grpc # For the protocol buffer
from concurrent import futures # For the maximum number of workers
from database.database import MongoDatabase # For the database. It is importing the database.py file from the database folder
from google.protobuf.json_format import MessageToJson # For converting the protocol buffer to JSON
from colorama import Style # For coloring the terminal

# TODO: Function to clean the database!

# Background colors:
class backgroundColors: # Colors for the terminal
	CYAN = "\033[96m" # Cyan
	GREEN = "\033[92m" # Green
	RED = "\033[91m" # Red
	YELLOW = "\033[93m" # Yellow
	BLACK = "\033[30m" # Black
	WHITE = "\033[97m" # White
	BOLD = "\033[1m" # Bold
	UNDERLINE = "\033[4m" # Underline

# Server:
SERVERADDRESS = ["localhost", 7070] # The server's address. The first element is the IP address, the second is the port.
MAX_WORKERS = 10 # The maximum number of workers

# Status messages:
SUCCESS = "1" # The success response code
FAILURE = "0" # The failure response code

# Empty Fields:
EMPTY_STRING_FIELD = "Undefined" # The empty field
EMPTY_INT_FIELD = -1 # The empty field
EMPTY_LIST_FIELD = [] # The empty field

# @brief: This class is the server class which inherits from the movies_pb2_grpc class
# @param: None
# @return: None
class MoviesServicer(movies_pb2_grpc.MovieServiceServicer):
	# @brief: This is the constructor of the class
	# @param: None
	# @return: MongoDatabase connection object
	def __init__(self):
		self.database = MongoDatabase()

	# @brief: This function creates a movie
	# @param request: The movie protocol buffer as an object
	# @param context: The context
	# @return: The message protocol buffer
	def CreateMovie(self, request, context):
		print(f"{backgroundColors.GREEN}Creating Movie: {backgroundColors.CYAN}{request.title}{Style.RESET_ALL}")
		movie = MessageToJson(request) # Convert the movie to JSON
		movie_document = self.database.createMovie(movie) # Create the movie
		status_message = FAILURE
		if movie_document == SUCCESS: # If the movie was created successfully
			print(f"{backgroundColors.GREEN}Movie {backgroundColors.CYAN}{request.title}{backgroundColors.GREEN} created successfully{Style.RESET_ALL}")
			status_message = SUCCESS
		else: # If the movie was not created successfully
			print(f"{backgroundColors.RED}Failed to create movie {backgroundColors.CYAN}{request.title}{Style.RESET_ALL}")
		print()
		return movies_pb2.Message(message=status_message) # Return the status message
	
	# @brief: This function gets a movie
	# @param request: The message protocol buffer containing the movie title
	# @param context: The context
	# @return: The movie protocol buffer
	def GetMovie(self, request, context):
		print(f"{backgroundColors.GREEN}Getting Movie: {backgroundColors.CYAN}{request.message}{Style.RESET_ALL}")
		movie_document = self.database.getMovieByTitle(request.message) # Get the movie by title
		if movie_document: # If the movie was found
			print(f"{backgroundColors.GREEN}Movie {backgroundColors.CYAN}{movie_document['title']}{backgroundColors.GREEN} found{Style.RESET_ALL}")
		else: # If the movie was not found
			print(f"{backgroundColors.RED}Movie {backgroundColors.CYAN}{movie_document['title']}{backgroundColors.RED} not found{Style.RESET_ALL}")
		print()
		movie_object = self.convert_document_to_protocol_buffer(movie_document) # Convert the movie document to a protocol buffer
		print(f"{backgroundColors.GREEN}movie_object.plot: {backgroundColors.CYAN}{movie_object.plot}{Style.RESET_ALL}")
		return movie_object
	
	# @brief: This function updates a movie
	# @param request: The movie protocol buffer as an object
	# @param context: The context
	# @return: The message protocol buffer
	# @note: This needs to be fixed
	def UpdateMovie(self, request, context):
		print(f"{backgroundColors.GREEN}Updating Movie: {backgroundColors.CYAN}{request.title}{Style.RESET_ALL}")
		movie_document = self.database.updateMovie(request) # Update the movie
		status_message = FAILURE
		if movie_document: # If the movie was found
			print(f"{backgroundColors.GREEN}Movie {backgroundColors.CYAN}{request.title}{backgroundColors.GREEN} updated successfully{Style.RESET_ALL}")
			status_message = SUCCESS
		else: # If the movie was not found
			print(f"{backgroundColors.RED}Movie {backgroundColors.CYAN}{request.title}{backgroundColors.RED} not found{Style.RESET_ALL}")
		print()
		return movies_pb2.Message(message=status_message)
	
	# @brief: This function deletes a movie
	# @param request: The message protocol buffer containing the movie title
	# @param context: The context
	# @return: The message protocol buffer
	def DeleteMovie(self, request, context):
		print(f"{backgroundColors.GREEN}Deleting Movie: {backgroundColors.CYAN}{request.message}{Style.RESET_ALL}")
		movie_document = self.database.deleteMovie(request.message)
		status_message = FAILURE
		if movie_document: # If the movie was found
			print(f"{backgroundColors.GREEN}Movie {backgroundColors.CYAN}{request.message}{backgroundColors.GREEN} deleted successfully{Style.RESET_ALL}")
			status_message = SUCCESS
		else: # If the movie was not found
			print(f"{backgroundColors.RED}Movie {backgroundColors.CYAN}{request.message}{backgroundColors.RED} not found{Style.RESET_ALL}")
		print()
		return movies_pb2.Message(message=status_message)

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

# @brief: This is the main function of the server
# @param: None
# @return: None
def main():
	print(f"{backgroundColors.GREEN}Server started{Style.RESET_ALL}")
	# Setup the server pool of threads
	server_pool = grpc.server(futures.ThreadPoolExecutor(max_workers=MAX_WORKERS))
	# Add the server to the pool
	movies_pb2_grpc.add_MovieServiceServicer_to_server(MoviesServicer(), server_pool)
	# Bind the server to the port
	server_pool.add_insecure_port(f"[::]:{SERVERADDRESS[1]}")
	# Start the server
	server_pool.start()
	# Wait for the server to terminate
	server_pool.wait_for_termination()

if __name__ == "__main__":
	main()