# Indirect Communication
@author: Breno Farias da Silva    
@date: 29/05/2023  
@last update: 29/05/2021  
@[repository](https://github.com/BrenoFariasdaSilva/University/tree/main/Distributed%20Systems/Activity%2006%20-%20Indirect%20Communication)  

### ***Quick notes:*** 
Note that in this project uses RabbitMQ, so you need to install it first [here](https://www.rabbitmq.com/getstarted.html).  
Also, i try to simplify things by using `Makefile`, so you need to install it too [here](https://www.gnu.org/software/make/), or if you are running a Unix-based system, just run:
```bash
sudo apt install make -y
```

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
* On the client terminal, type:  
    ```bash
    
    ```
* On the client terminal, type:   
    ```bash

    ```
## Libraries
The python used libraries in this project are:
- **pika**: The `pika` library is a feature-rich Python client for RabbitMQ, a popular message broker. It provides a high-level API for interacting with RabbitMQ, allowing you to publish and consume messages, create and manage queues, and handle connections and channels. Pika makes it easier to build scalable and robust distributed systems using RabbitMQ.

- **csv**: The `csv` library in Python provides functionality for reading and writing Comma-Separated Values (CSV) files. It allows you to parse CSV data into Python data structures and write Python data structures back to CSV format. The csv module provides options for handling different CSV dialects, custom delimiters, quoting rules, and more. It is a convenient and efficient tool for working with tabular data in CSV files.

- **sys**: The `sys` library is a core module in Python that provides access to system-specific parameters and functions. It allows you to interact with the Python interpreter and the underlying operating system. The sys module provides functionality for accessing command-line arguments, interacting with the standard input and output streams, manipulating the import path, and more. It is often used for system-level programming and accessing runtime information.

- **colorama**: The `colorama` library provides cross-platform support for styling and coloring text output in the terminal. It simplifies the process of adding colored text to console applications. Colorama allows you to change the text color, background color, and other formatting aspects of the terminal output using ANSI escape sequences. It is a useful tool for enhancing the visual appeal and readability of command-line interfaces.

## Useful Documentation
* [RabbitMQ Tutorials](https://www.rabbitmq.com/getstarted.html)
* [RabbitMQ Installation](https://www.rabbitmq.com/download.html)