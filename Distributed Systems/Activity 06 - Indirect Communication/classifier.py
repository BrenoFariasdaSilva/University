import pika as pk # Import the pika library that is used for the Advanced Message Queuing Protocol (AMQP) used by RabbitMQ

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

        # Verify if the has a topic related word
        if "people" in dataset:
            topic = "people"
        elif "beautiful" in dataset:
            topic = "beautiful"
        elif "Fasting" in dataset:
            topic = "Fasting"
        elif "innovation" in dataset:
            topic = "innovation"
        elif "saudade" in dataset:
            topic = "saudade"
        elif "house" in dataset:
            topic = "house"
        elif "alone" in dataset:
            topic = "alone"

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