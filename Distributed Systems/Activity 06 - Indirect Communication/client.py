import pika as pk # Import the pika library that is used for the Advanced Message Queuing Protocol (AMQP) used by RabbitMQ
from colorama import Style # For coloring the terminal

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
 
class Categories: 
    CAR = "car"
    BITCOIN = "bitcoin"
    DOGECOIN = "dogecoin"
    TESLA = "tesla"
    SPACEX = "SpaceX"

def main(): 
    # Connect to the RabbitMQ server
    connection = pk.BlockingConnection(pk.ConnectionParameters(host="localhost")) 
    channel = connection.channel() # Create a communication channel
    channel.exchange_declare(exchange="direct_logs", exchange_type="direct") # Create an exchange of topic type

    result = channel.queue_declare(queue="", exclusive=True) # Create an exclusive queue
    queueName = result.method.queue # Catch the queue name

    # Get all the attributes of the Categories class
    category_attrs = [getattr(Categories, attr) for attr in dir(Categories) if not callable(getattr(Categories, attr)) and not attr.startswith("__")]

    # Filter the attributes to include only the desired categories
    categories = [attr for attr in category_attrs if isinstance(attr, str)]

    # Queues list
    queues = categories

    breakFlag = False # Flag to break the loop
    # Ask the user for the topics to subscribe
    print(f"{backgroundColors.GREEN} Register in one of the following topics: {queues}{Style.RESET_ALL}")
    while not breakFlag:
        topics = input("Enter the topics to subscribe (separated by spaces): ").split()
        if not topics: # If there is no topic
            print(f"{backgroundColors.YELLOW} You must enter at least one topic{Style.RESET_ALL}")
            continue
        for i in range(len(topics)): # For each topic
            if topics[i] not in queues: # If the topic is not in the queues list
                print(f"{backgroundColors.RED}Invalid topic. Register in one of the following topics: {queues}{Style.RESET_ALL}")
                break
            breakFlag = True # Break the loop
    
    # Create a queue for each topic
    for topic in topics:
        channel.queue_bind(exchange="direct_logs", queue=queueName, routing_key=topic) # Bind the queue to the topic

    print(backgroundColors.GREEN + backgroundColors.BOLD + "Waiting for messages..." + Style.RESET_ALL) # Print the waiting message

    def callback(ch, method, properties, body): # Callback function to show the results
        topic = body.decode() # Decode the data
        print(f"{backgroundColors.CYAN}Topic: {method.routing_key}{Style.RESET_ALL}") # Print the topic
        print(topic) # Print the data
        print()

    channel.basic_consume(queue=queueName, on_message_callback=callback, auto_ack=True) # Associate the callback function to the queue
    channel.start_consuming() # Start the communication 

# Directive to run the main function
if __name__ == "__main__":
        main()