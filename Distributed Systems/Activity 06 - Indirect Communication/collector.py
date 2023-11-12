import pika as pk # Import the pika library that is used for the Advanced Message Queuing Protocol (AMQP) used by RabbitMQ
import csv # Import the csv library that is used to read the csv file
from client import BackgroundColors, Database # Import the BackgroundColors and Database classes from client.py
from colorama import Style # For coloring the terminal

class CSVFile:
    folder = "./dataset/" # CSV file folder
    file = "Tweets.csv" # CSV file name

# #brief: This is the main collector.py function of the program
# #param: None
# #return: None
def main():
    # Connect to the RabbitMQ server
    connection = pk.BlockingConnection(pk.ConnectionParameters(host=Database.ipAddress)) 
    channel = connection.channel() # Create the communication channel

    file = open(CSVFile.folder + CSVFile.file, errors="ignore") # CSV file path
    dataAssets = csv.DictReader(file) # Read the csv file

    print(f"{BackgroundColors.GREEN}Tweets Read from {BackgroundColors.CYAN}{BackgroundColors.UNDERLINE}{CSVFile.folder}{CSVFile.file}{Style.RESET_ALL}{BackgroundColors.GREEN} file{Style.RESET_ALL}") # Print a message to the user
    for asset in dataAssets:
        user = "Username: " + asset["username"] # Store the username of the person who tweeted
        text = "Text: " + asset["tweet"] # Store the text of the tweet
        dataUser = user + " \n" + text + "\n" # Concatenate the username and the text of the tweet
        channel.exchange_declare(exchange="tweets", exchange_type="direct") # Exchange used for communication between client collector
        channel.basic_publish(exchange="", routing_key="tweets", body=dataUser) # Publish the tweet in the tweets queue

    print(f"{BackgroundColors.GREEN}Tweets sent to {BackgroundColors.CYAN}{BackgroundColors.UNDERLINE}classifier.py{Style.RESET_ALL}") # Print a message to the user
    connection.close() # Close the connection

# This is the standard boilerplate that calls the main() function.
if __name__ == "__main__":
   main() # Call the main function
