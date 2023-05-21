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

class MongoDatabase:
	def __init__(self):
		load_dotenv()
		uri = f"mongodb+srv://{os.getenv('USERNAME')}:{os.getenv('PASSWORD')}@{os.getenv('DATABASE_URL')}"
		self.client = MongoClient(uri, server_api=ServerApi('1'))
		self.database = self.client["movies"]
		self.collection = self.database["movies"]
		database_name = os.getenv("DATABASE_URL")[:os.getenv("DATABASE_URL").find(".")]
		print(f"{backgroundColors.OKGREEN}Client Connected to {backgroundColors.OKCYAN}{database_name}{backgroundColors.OKGREEN} server using {backgroundColors.OKCYAN}{os.getenv('USERNAME')} {backgroundColors.OKGREEN}user{Style.RESET_ALL}")

	def connectionInfo(self):
		return self.client.server_info()

	def createMovie(self, movie):
		movie = json.loads(movie)
		if movie.get('id'):
			movie.pop('id')
		print(f"Creating movie: {movie}")
		reponse_document = self.collection.insert_one(movie)
		return reponse_document
		# print(f"Movie created with id: {reponse_document.inserted_id}")
		# print(f"Movie acknowledged: {reponse_document.acknowledged}")
		# if reponse_document.acknowledged: # If the movie was created
		# 	return reponse_document.inserted_id # Return the movie id
		# return None
	
	def getMovieByTitle(self, movie_title):
		return self.collection.find_one({"title": movie_title})
	
	def updateMovie(self, old_movie_object, new_movie_object):
		self.deleteMovie(old_movie_object["title"])
		return self.createMovie(new_movie_object)

	def deleteMovie(self, movie_title):
		return self.collection.delete_one({"title": movie_title})
	
	def listByActors(self, actor_name):
		return self.collection.find({"actors": actor_name})
	
	def listByCategory(self, category):
		return self.collection.find({"category": category})
	
if __name__ == "__main__":
	database = MongoDatabase()