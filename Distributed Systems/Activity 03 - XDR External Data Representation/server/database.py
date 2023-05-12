import os
from pymongo.mongo_client import MongoClient
from pymongo.server_api import ServerApi
from dotenv import load_dotenv

class database:
	def __init__(self):
		uri = f"mongodb+srv://{os.getenv('USERNAME')}:{os.getenv('PASSWORD')}@{os.getenv('DATABASE_URL')}"
		self.client = MongoClient(uri, server_api=ServerApi('1'))
		self.database = self.client["movies"]
		self.collection = self.database["movies"]
def main():
	load_dotenv()


	# Create a new client and connect to the server
	client = MongoClient(uri, server_api=ServerApi('1'))

	# Send a ping to confirm a successful connection
	try:
		client.admin.command('ping')
		print("Pinged your deployment. You successfully connected to MongoDB!")
	except Exception as e:
		print(e)
	
# @brief: This is what runs the main function when file is executed
if __name__ == "__main__":
	main()