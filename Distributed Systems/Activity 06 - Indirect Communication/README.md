# [Indirect Communication](https://github.com/BrenoFariasdaSilva/University/tree/main/Distributed%20Systems/Activity%2006%20-%20Indirect%20Communication)
`@author: Breno Farias da Silva.`     
`@date: 29/05/2023.`    
`@last update: 05/06/2023.`  
### ***Quick notes:*** 
I usually try to simplify things by using `Makefile`, so you need to install it too [here](https://www.gnu.org/software/make/), or if you are running a Unix-based system, just run:
```bash
sudo apt install make -y
```
Also, the [`Tweets.csv`](https://www.kaggle.com/datasets/andradaolteanu/all-elon-musks-tweets?resource=download) file has downloaded from [Kaggle](https://www.kaggle.com/), so you can also download yours (and paste it into `/datasets`) and modify this code to work with it.  
Note that in this project uses [RabbitMQ](https://www.rabbitmq.com/), so you need to install it [locally](https://www.rabbitmq.com/download.html), or just use a [docker container](https://hub.docker.com/_/rabbitmq).  If you decide to use the docker container (which is easier), you need to [install docker](https://docs.docker.com/get-docker/) first, and use the `make docker_run` to , both pull the rabbitmq image and create a container with it named as `rabbitmq-tweets`.
So, as you are using a docker container, when you create the container, it will automatically start the rabbitmq server, so you don't need to start it manually, but, more importantly, it will get a random available `IP Address` and `port` so, in order for the `client.py` to connect with the container, you must update the `ipAddress` attribute that is inside the `Database` class in the `client.py` file. To get the `IP Address` of the container, you can run:
```bash
docker inspect rabbitmq-tweets | grep "IPAddress"
```
Now get the value of the field named `"IpAddress":` and update the `ipAddress` attribute in the `Database` class in the `client.py` file!

## Install dependencies
The dependency inside the makefile command are required to run this project so, before that, make sure you have makefile installed on your machine.
```bash
make setup
```

## How to run
In order to run this project, you need to open three terminals, one for the client, one for the classifier and one for the collector.
* On the first terminal (client), type:  
    ```bash 
    make client_run
    ```
* On the second terminal (classifier), type:   
    ```bash
    make classifier_run
    ```
* On the third terminal (collector), type:   
    ```bash
    make collector_run
    ```
## How to use

## Example of usage
After openning the three terminals, the client terminal will be asking for the topic you want to subscribe of the available topics, which are:  
  - `tesla`
  - `SpaceX`
  - `car`
  - `bitcoin`
  - `dogecoin`  
  
So, just type the topic you want to subscribe, but separated by spaces
* On the client terminal, type:  
    ```bash
    tesla SpaceX
    ```
Now you need to wait for the `collector.py` to read the `/dataset/Tweets.csv` file and send the tweets to the `classifier.py` to classify them, and then send the classified tweets to the `client.py`, where inside the `/processed_tweets` folder, will have a file for each of the tweet topics you were subscribed.  

## Libraries
The python used libraries in this project are:
- **pika**: The `pika` library is a feature-rich Python client for RabbitMQ, a popular message broker. It provides a high-level API for interacting with RabbitMQ, allowing you to publish and consume messages, create and manage queues, and handle connections and channels. Pika makes it easier to build scalable and robust distributed systems using RabbitMQ.

- **csv**: The `csv` library in Python provides functionality for reading and writing Comma-Separated Values (CSV) files. It allows you to parse CSV data into Python data structures and write Python data structures back to CSV format. The csv module provides options for handling different CSV dialects, custom delimiters, quoting rules, and more. It is a convenient and efficient tool for working with tabular data in CSV files.

- **sys**: The `sys` library is a core module in Python that provides access to system-specific parameters and functions. It allows you to interact with the Python interpreter and the underlying operating system. The sys module provides functionality for accessing command-line arguments, interacting with the standard input and output streams, manipulating the import path, and more. It is often used for system-level programming and accessing runtime information.

- **colorama**: The `colorama` library provides cross-platform support for styling and coloring text output in the terminal. It simplifies the process of adding colored text to console applications. Colorama allows you to change the text color, background color, and other formatting aspects of the terminal output using ANSI escape sequences. It is a useful tool for enhancing the visual appeal and readability of command-line interfaces.

## Useful Documentation
* [RabbitMQ Tutorials](https://www.rabbitmq.com/getstarted.html)
* [RabbitMQ Installation](https://www.rabbitmq.com/download.html)