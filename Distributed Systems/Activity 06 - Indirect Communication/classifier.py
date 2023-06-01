import pika as pk # Impo1rt the pika library that is used for the Advanced Message Queuing Protocol (AMQP) used by RabbitMQ
from client import BackgroundColors, Topics, Database # Import the BackgroundColors, Topics and Database classes from client.py
from colorama import Style # For coloring the terminal

# #brief: This is the main classifier.py function of the program
# #param: None
# #return: None
def main():
    # Open a connection to RabbitMQ server
    connection = pk.BlockingConnection(pk.ConnectionParameters(host=Database.ipAddress))

    # Connect to a communication channel
    channel = connection.channel()

    # Create a queue called tweets
    channel.queue_declare(queue="tweets")

    print(f"{BackgroundColors.GREEN}Waiting for tweets from the {BackgroundColors.CYAN}{BackgroundColors.UNDERLINE}collector.py{Style.RESET_ALL}")

    # Function to receive messages
    def callback(ch, method, properties, body):
        # Variable to store the topic
        topic = ""

        # Decode the dataset
        dataset = body.decode()

        # @TODO: Make this dinamic, so it doesn't need to be hardcoded, and the user can add more topics
        # Verify if the has a topic related word
        if Topics.CAR in dataset.lower():
            topic = Topics.CAR
        elif Topics.BITCOIN in dataset.lower():
            topic = Topics.BITCOIN
        elif Topics.DOGECOIN in dataset.lower():
            topic = Topics.DOGECOIN
        elif Topics.TESLA in dataset.lower():
            topic = Topics.TESLA
        elif Topics.SPACEX in dataset.lower():
            topic = Topics.SPACEX

        # Channel used for communication between client classifier
        channel.exchange_declare(exchange="direct_logs", exchange_type="direct")
        # Send the topic to the tweet queue
        channel.basic_publish(exchange="direct_logs", routing_key=str(topic), body=body) # Publica a mensagem no topico
    
    # Create a database connection
    channel.basic_consume(queue = "tweets", on_message_callback = callback, auto_ack = True)
    # Iniciate the communication
    channel.start_consuming() 
    print(f"{BackgroundColors.GREEN}Tweets sent to the {BackgroundColors.CYAN}{BackgroundColors.UNDERLINE}client.py{Style.RESET_ALL}") # Print a message to the user
    # Close the connection
    connection.close()

# Directive to run the main function
if __name__ == "__main__":
    main()