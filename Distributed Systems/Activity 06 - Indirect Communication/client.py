import pika as pk # Import the pika library that is used for the Advanced Message Queuing Protocol (AMQP) used by RabbitMQ
import os # Import the os library that is used to delete files
from colorama import Style # For coloring the terminal

# Background colors:
class BackgroundColors: # Colors for the terminal
	CYAN = "\033[96m" # Cyan
	GREEN = "\033[92m" # Green
	RED = "\033[91m" # Red
	YELLOW = "\033[93m" # Yellow
	BLACK = "\033[30m" # Black
	WHITE = "\033[97m" # White
	BOLD = "\033[1m" # Bold
	UNDERLINE = "\033[4m" # Underline
 
# This is the Categories class of the program which stores the topics
class Topics: 
    CAR = "car"
    BITCOIN = "bitcoin"
    DOGECOIN = "dogecoin"
    TESLA = "tesla"
    SPACEX = "SpaceX"

# This is the Database class of the program which stores the database information
class Database:
    ipAddress = "172.17.0.2"

# This is the CSVFile class of the program which stores the CSV file information
class ProcessedTweets:
    folder = "./processed_tweets/"
    file_extension = ".txt"

# @brief: This is the function asks the user for the topics to be used
# @param: available_topics: List of available_topics
# @return: topics_list: List of topics to be used
def askTopics(available_topics):
    valid_input = False # Flag to break the loop
    # Ask the user for the topics to subscribe
    print(f"{BackgroundColors.GREEN}Register in one of the following topics: {BackgroundColors.CYAN}{available_topics}{Style.RESET_ALL}")
    while not valid_input:
        topics = input(f"{BackgroundColors.GREEN}Enter the topics you want to subscribe {BackgroundColors.RED}(separated by space): {Style.RESET_ALL}").split()
        valid_input = validateTopics(topics, available_topics)
    print(f"{BackgroundColors.GREEN}User subscribed to the following topics: {BackgroundColors.CYAN}{topics}{Style.RESET_ALL}")
    return topics

# @brief: This is the function validates the topics from the user input
# @param: topics: List of topics to be used
# @param: available_topics: List of available_topics
# @return: if topics are valid, return True, else return False
def validateTopics(topics, available_topics):
    if not topics: # If there is no topic
        print(f"{BackgroundColors.YELLOW} You must enter at least one topic{Style.RESET_ALL}")
        return False
    for i in range(len(topics)): # For each topic
        if topics[i] not in available_topics: # If the topic is not in the available_topics
            print(f"{BackgroundColors.RED}Invalid topic. Register in one of the following topics: {BackgroundColors.CYAN}{available_topics}{Style.RESET_ALL}")
            return False
    return True

# @brief: This is the function gets the available topics
# @param: None
# @return: available_topics: List of available_topics
def getAvailableTopics():
    # Get all the attributes of the Topics class
    category_attrs = [getattr(Topics, attr) for attr in dir(Topics) if not callable(getattr(Topics, attr)) and not attr.startswith("__")]

    # Filter the attributes to include only the desired topics
    available_topics = [attr for attr in category_attrs if isinstance(attr, str)]
    return available_topics

# @brief: This is the function deletes all files in the ProcessedTweets.folder
# @param: None
# @return: None
def deleteFiles():
    # Delete all files in the ProcessedTweets.folder
    for filename in os.listdir(ProcessedTweets.folder):
        os.remove(os.path.join(ProcessedTweets.folder, filename))

# @brief: This is the function creates a file for the specified topics
# @param: topics_list: List of topics to create files
# @return: None
def createFiles(topics_list):
    for topic in topics_list:
        file = open(ProcessedTweets.folder + topic + ProcessedTweets.file_extension, "w")
        file.close()

# @brief: This is the main client.py function of the program
# @param: None
# @return: None
def main(): 
    # Connect to the RabbitMQ server
    connection = pk.BlockingConnection(pk.ConnectionParameters(host=Database.ipAddress)) 
    channel = connection.channel() # Create a communication channel
    channel.exchange_declare(exchange="direct_logs", exchange_type="direct") # Create an exchange of topic type

    result = channel.queue_declare(queue="", exclusive=True) # Create an exclusive queue
    queueName = result.method.queue # Catch the queue name

    # Ask the user for the topics to subscribe
    topics = askTopics(getAvailableTopics())
    
    # Create a queue for each topic
    for topic in topics:
        channel.queue_bind(exchange="direct_logs", queue=queueName, routing_key=topic) # Bind the queue to the topic

    print(f"{BackgroundColors.GREEN}Waiting the tweets from the {BackgroundColors.CYAN}{BackgroundColors.UNDERLINE}collector.py{BackgroundColors.GREEN}{Style.RESET_ALL}{BackgroundColors.GREEN}...{Style.RESET_ALL}")

    deleteFiles() # Delete all files in the ProcessedTweets.folder
    list_topics = " ".join(topics).split() # Convert the topics into a list of topics
    createFiles(list_topics) # Create a file for each topic

    def callback(ch, method, properties, body): # Callback function to show the results
        topic = body.decode() # Decode the data
        # print(f"{BackgroundColors.CYAN}Topic: {method.routing_key}{Style.RESET_ALL}") # Print the topic
        # print(topic) # Print the data
        # save the tweet in the corresponding file
        file = open(ProcessedTweets.folder + method.routing_key + ProcessedTweets.file_extension, "a")
        file.write(topic + "\n")
        file.close()

    channel.basic_consume(queue=queueName, on_message_callback=callback, auto_ack=True) # Associate the callback function to the queue
    channel.start_consuming() # Start the communication 
    connection.close()
    print(f"{BackgroundColors.GREEN}Finished processing tweets{Style.RESET_ALL}")

# Directive to run the main function
if __name__ == "__main__":
        main()