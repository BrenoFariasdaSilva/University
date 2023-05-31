import pika as pk # Import the pika library that is used for the Advanced Message Queuing Protocol (AMQP) used by RabbitMQ
import csv # Import the csv library that is used to read the csv file

class CSVFile:
    folder = "./dataset/" # CSV file folder
    file = "TweetsData.csv" # CSV file name

# #brief: This is the main collector.py function of the program
# #param: None
# #return: None
def main():
    # Connect to the RabbitMQ server
    connection = pk.BlockingConnection(pk.ConnectionParameters("localhost")) 
    channel = connection.channel() # Create the communication channel

    file = open(CSVFile.folder + CSVFile.file, errors="ignore") # CSV file path
    dataAssets = csv.DictReader(file) # Read the csv file

    for asset in dataAssets:
        user = "Username: " + asset["Username"] # Store the username of the person who tweeted
        text = "Text: " + asset["Text"] # Store the text of the tweet
        dataUser = user + " \n" + text + "\n\n" # Concatenate the username and the text of the tweet
        channel.exchange_declare(exchange="tweets", exchange_type="direct") # Exchange used for communication between client collector
        channel.basic_publish(exchange="", routing_key="tweets", body=dataUser) # Publish the tweet in the tweets queue

    connection.close() # Close the connection

# Directive to run the main function
if __name__ == "__main__":
    main()