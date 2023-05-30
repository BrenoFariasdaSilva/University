import pika as pk # Import the pika library that is used for the Advanced Message Queuing Protocol (AMQP) used by RabbitMQ
import sys # For system calls

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

def main(): 
    # Connect to the RabbitMQ server
    connection = pk.BlockingConnection(pk.ConnectionParameters(host="localhost")) 
    channel = connection.channel() # Create a communication channel
    channel.exchange_declare(exchange="direct_logs", exchange_type="direct") # Create an exchange of topic type

    result = channel.queue_declare(queue="", exclusive=True) # Create an exclusive queue
    queueName = result.method.queue # Catch the queue name

    queues = ["people", "beautiful", "actor", "Fasting", "innovation", "house", "alone"] # Queues list
    topics = sys.argv[1:] # Topics list

    if not topics: # If there is no topic
        print(f"{backgroundColors.YELLOW} Register in one of the following topics: people, beautiful, actor, Fasting, innovation, lesson, alone{Style.RESET_ALL}")
        exit(1) # Exit the program

    for i in range(len(topics)): # For each topic
        if topics[i] not in queues: # If the topic is not in the queues list
            print(f"{backgroundColors.RED}Invalid topic. Register in one of the following topics: people, beautiful, actor, Fasting, innovation, lesson, alone{Style.RESET_ALL}")
            exit(1) # Exit the program
    
    # Create a queue for each topic
    for topico in topics:
        channel.queue_bind(exchange="direct_logs", queue=queueName, routing_key=topico) # Bind the queue to the topic

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