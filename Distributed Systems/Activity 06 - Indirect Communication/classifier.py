import pika as pk # Impo1rt the pika library that is used for the Advanced Message Queuing Protocol (AMQP) used by RabbitMQ
from client import Categories # Import the Categories class from client.py

# #brief: This is the main classifier.py function of the program
# #param: None
# #return: None
def main():
    # Open a connection to RabbitMQ server
    connection = pk.BlockingConnection(pk.ConnectionParameters(host="localhost"))

    # Connect to a communication channel
    channel = connection.channel()

    # Create a queue called tweets
    channel.queue_declare(queue="tweets")

    # Function to receive messages
    def callback(ch, method, properties, body):
        # Variable to store the topic
        topic = ""

        # Decode the dataset
        dataset = body.decode()

        # @TODO: Make this dinamic, so it doesn't need to be hardcoded, and the user can add more topics
        # Verify if the has a topic related word
        if Categories.PEOPLE in dataset.lower():
            topic = Categories.PEOPLE
        elif Categories.BEAUTIFUL in dataset.lower():
            topic = Categories.BEAUTIFUL
        elif Categories.FAST in dataset.lower():
            topic = Categories.FAST
        elif Categories.INNOVATION in dataset.lower():
            topic = Categories.INNOVATION
        elif Categories.SAUDADE in dataset.lower():
            topic = Categories.SAUDADE
        elif Categories.HOUSE in dataset.lower():
            topic = Categories.HOUSE
        elif Categories.ALONE in dataset.lower():
            topic = Categories.ALONE

        # Channel used for communication between client classifier
        channel.exchange_declare(exchange="direct_logs", exchange_type="direct")
        # Send the topic to the tweet queue
        channel.basic_publish(exchange="direct_logs", routing_key=str(topic), body=body) # Publica a mensagem no topico
    
    # Create a database connection
    channel.basic_consume(queue = "tweets", on_message_callback = callback, auto_ack = True)
    # Iniciate the communication
    channel.start_consuming() 

# Directive to run the main function
if __name__ == "__main__":
    main()