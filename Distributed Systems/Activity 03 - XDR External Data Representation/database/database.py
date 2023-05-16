import os
from pymongo.mongo_client import MongoClient
from pymongo.server_api import ServerApi
from dotenv import load_dotenv
import json

class MongoDatabase:
	def __init__(self):
		load_dotenv()
		uri = f"mongodb+srv://{os.getenv('USERNAME')}:{os.getenv('PASSWORD')}@{os.getenv('DATABASE_URL')}"
		self.client = MongoClient(uri, server_api=ServerApi('1'))
		self.database = self.client["movies"]
		self.collection = self.database["movies"]

	def createMovie(self, movie):
		movie = json.loads(movie)
		reponse_document = self.collection.insert_one(movie)
		if reponse_document.acknowledged: # If the movie was created
			return reponse_document.inserted_id # Return the movie id
		return None
	
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