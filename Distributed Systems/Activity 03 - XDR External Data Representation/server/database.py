import os
from pymongo.mongo_client import MongoClient
from pymongo.server_api import ServerApi
from dotenv import load_dotenv

# @brief: This is the main function of the server
# @param: None
# @return: None
def main():
	load_dotenv()

	uri = f"mongodb+srv://{os.getenv('USERNAME')}:{os.getenv('PASSWORD')}@{os.getenv('DATABASE_URL')}"

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