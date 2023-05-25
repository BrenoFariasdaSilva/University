import os
from pymongo.mongo_client import MongoClient
from pymongo.server_api import ServerApi
from dotenv import load_dotenv
import json
from colorama import Style # For coloring the terminal

# Background colors:
class backgroundColors: # Colors for the terminal
	OKCYAN = "\033[96m" # Cyan
	OKGREEN = "\033[92m" # Green
	WARNING = "\033[93m" # Yellow
	FAIL = "\033[91m" # Red

# Status messages:
SUCCESS = 1
FAILURE = 0

class MongoDatabase:
	def __init__(self):
		load_dotenv()
		uri = f"mongodb+srv://{os.getenv('USERNAME')}:{os.getenv('PASSWORD')}@{os.getenv('DATABASE_URL')}"
		self.client = MongoClient(uri, server_api=ServerApi('1'))
		self.database = self.client["movies"]
		self.collection = self.database["movies"]
		database_name = os.getenv("DATABASE_URL")[:os.getenv("DATABASE_URL").find(".")]
		print(f"{backgroundColors.OKGREEN}Client Connected to {backgroundColors.OKCYAN}{database_name}{backgroundColors.OKGREEN} server using {backgroundColors.OKCYAN}{os.getenv('USERNAME')} {backgroundColors.OKGREEN}user{Style.RESET_ALL}")
		print("")

	def connectionInfo(self):
		return self.client.server_info()

	def createMovie(self, movie):
		movie = json.loads(movie)
		if movie.get('id'):
			movie.pop('id')
		print(f"{backgroundColors.OKGREEN}Creating movie {backgroundColors.OKCYAN}{movie}{Style.RESET_ALL}")
		reponse_document = self.collection.insert_one(movie)
		if reponse_document.acknowledged: # If the movie was created
			return SUCCESS
		return None
	
	def getMovieByTitle(self, movie_title):
		return self.collection.find_one({"title": movie_title})
	
	def updateMovie(self, old_movie_object, new_movie_object):
		self.delete_one({"title": old_movie_object["title"]})
		return self.createMovie(new_movie_object)

	def deleteMovie(self, movie_title):
		reponse_document = self.collection.delete_one({"title": movie_title})
		if reponse_document.acknowledged: # If the movie was deleted
			return reponse_document.deleted_count
		return None
	
	def listByActor(self, actor_name):
		return list(self.collection.find({"cast": actor_name}))
	
	def listByGenre(self, genre):
		return list(self.collection.find({"genres": genre}))
	
	def eraseAllMovies(self):
		response_document = self.collection.delete_many({})
		return response_document.deleted_count
	
if __name__ == "__main__":
	database = MongoDatabase()