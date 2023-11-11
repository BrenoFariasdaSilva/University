import os # For getting the environment variables
from pymongo.mongo_client import MongoClient # For connecting to the database
from pymongo.server_api import ServerApi # For connecting to the database
from dotenv import load_dotenv # For getting the environment variables
import json # For converting the movie object to JSON
from colorama import Style # For coloring the terminal

# Background colors:
class BackgroundColors: # Colors for the terminal
	OKCYAN = "\033[96m" # Cyan
	OKGREEN = "\033[92m" # Green
	WARNING = "\033[93m" # Yellow
	FAIL = "\033[91m" # Red

# Status messages:
SUCCESS = "1" # Success
FAILURE = "0" # Failure

# @brief: This class is used to connect to the database, as well as all the CRUD related methods.
class MongoDatabase:
	# Constructor:
	def __init__(self):
		load_dotenv()
		uri = f"mongodb+srv://{os.getenv('USERNAME')}:{os.getenv('PASSWORD')}@{os.getenv('DATABASE_URL')}"
		self.client = MongoClient(uri, server_api=ServerApi('1'))
		self.database = self.client["movies"]
		self.collection = self.database["movies"]
		database_name = os.getenv("DATABASE_URL")[:os.getenv("DATABASE_URL").find(".")]
		print(f"{BackgroundColors.OKGREEN}Server Connected to {BackgroundColors.OKCYAN}{database_name}{BackgroundColors.OKGREEN} MongoDB database using {BackgroundColors.OKCYAN}{os.getenv('USERNAME')} {BackgroundColors.OKGREEN}user{Style.RESET_ALL}")
		print("")

	## Methods:
	# @brief: This method gets the connection information
	# @return: A JSON object with the connection information
	def connectionInfo(self):
		return self.client.server_info()

	# @brief: This method creates a movie in the database
	# @param movie: A JSON object with the movie information
	# @return: SUCCESS if the movie was created, None if not
	def createMovie(self, movie):
		movie = json.loads(movie)
		if movie.get('id'):
			movie.pop('id')
		reponse_document = self.collection.insert_one(movie)
		print(f"{BackgroundColors.OKGREEN}Movie {BackgroundColors.OKCYAN}{movie['title']}{BackgroundColors.OKGREEN} created in the database{Style.RESET_ALL}")
		if reponse_document.acknowledged: # If the movie was created
			return SUCCESS
		return None
	
	# @brief: This method gets a movie in the database by its title
	# @param movie_title: The title of the movie
	# @return: The movie object if the movie was found, None if not
	def getMovieByTitle(self, movie_title):
		return self.collection.find_one({"title": movie_title})
	
	# @brief: This method gets a movie in the database by its id
	# @param movie_id: The id of the movie
	# @return: The movie object if the movie was found, None if not
	def getMovieById(self, movie_id):
		return self.collection.find_one({"id": movie_id})
	
	# @brief: This method updates a movie in the database
	# @param old_movie_object: The old movie object
	# @param new_movie_object: The new movie object
	# @return: The new movie object if the movie was updated, None if not
	def updateMovie(self, new_movie_object):
		movie = json.loads(new_movie_object) # Convert the movie object to JSON
		# delete the movie with the same id
		if self.collection.delete_one({"id": movie["id"]}).acknowledged:
			# Create the new movie
			if self.collection.insert_one(movie).acknowledged:
				return movie
		return None

	# @brief: This method deletes a movie in the database
	# @param movie_title: The title of the movie
	# @return: The number of movies deleted
	def deleteMovie(self, movie_title):
		reponse_document = self.collection.delete_one({"title": movie_title})
		if reponse_document.acknowledged: # If the movie was deleted
			return reponse_document.deleted_count
		return None
	
	# @brief: This method gets the movies in the database made by a specific actor/cast
	# @param actor_name: The name of the actor
	# @return: A list with all the movies in the database related to the actor
	def listByActor(self, actor_name):
		return list(self.collection.find({"cast": actor_name}))

	# @brief: This method gets the movies in the database made by a specific director
	# @param genre: The genre of the movie
	# @return: A list with all the movies in the database according to the genre
	def listByGenre(self, genre):
		return list(self.collection.find({"genre": genre}))
	
	# @brief: This method deletes all the movies in the database
	# @param: None
	# @return: The number of movies deleted
	def eraseAllMovies(self):
		response_document = self.collection.delete_many({})
		return response_document.deleted_count
	
# Main:
if __name__ == "__main__":
	database = MongoDatabase()