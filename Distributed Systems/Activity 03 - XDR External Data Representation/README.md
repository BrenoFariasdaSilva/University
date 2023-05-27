
# External Data Representation (XDR) Programming using Protobuffers
@author: Breno Farias da Silva    
@date: 07/05/2023  
@last update: 27/05/2021  
@[repository](https://github.com/BrenoFariasdaSilva/University/tree/main/Distributed%20Systems/Activity%2003%20-%20XDR%20External%20Data%20Representation)  
@TODO: Test multilpe clients and multiple values in a field.    
@TODO: Update README.md How to use and Example of usage

### ***Quick notes:*** 
Note that in the ```/server/database.py``` file we have the following code in the database constructor (```__init__```):

    load_dotenv()
    uri = f"mongodb+srv://{os.getenv('USERNAME')}:{os.getenv('PASSWORD')}@{os.getenv('DATABASE_URL')}"

Is used the ```os.getenv()``` function to get the environment variables, so you need to create a ```.env``` file in the ```'root'``` directory of the project (next to the Makefile), and inside it, you need to have the following variables:

    USERNAME=your_username
    PASSWORD=your_password
    DATABASE_URL=your_database_url

For obvious reasons, i'm not going to share my database credentials, so you need to create your own database and get your own credentials in your MongoDB account.

## Install dependencies
The dependency inside the makefile command are required to run this project so, before that, make sure you have makefile installed on your machine.
    ```bash
    sudo apt install make -y
    make setup
    ```
Also, you need to have [Maven](https://maven.apache.org/) installed on your computer, as we have lots of dependencies on the client side, inside the ```pom.xml``` file, like `protobuf` and `JUnit`.  

## How to run
In order to run this project, you need to open two terminals.
#### ***Important notes:*** The order of which terminal you open first is important, so make sure you follow the order below.  
Also, as i'm using MongoDB, you can install [MongoDB Compass](https://www.mongodb.com/try/download/compass) to see the database in a more friendly way.
* On the server terminal, type:  
    ```bash
    make server_run
    ```
* On the client terminal, type:  
    ```bash 
    make client_run
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
First, the python libraries (for the server side) used in this project are:
- **Socket**: The socket library provides low-level networking support in Python.
- **Threading**: The threading library provides high-level support for working with threads in Python.
- **MessageToJson**: This function is imported from the google.protobuf.json_format module. It provides the capability to convert Protocol Buffers messages to JSON format, making it easier to work with the data in a human-readable and interoperable format.
- **Decoder**: This module google.protobuf.internal.decoder likely provides functionality for decoding Protocol Buffers encoded data.
- **Colorama**: The colorama library provides cross-platform support for coloring and styling terminal output. It allows you to use ANSI escape sequences to change the color, style, and other formatting aspects of the text displayed in the terminal.
 
It's worth mentioning that some of the libraries mentioned are standard libraries that come bundled with Python, such as `socket`, `threading`, and `json`. Others, like `MongoDatabase` and `Movies_pb2`, are custom modules or external dependencies specific to this project, as they are importing local files.
Now the Java libraries (for the client side) used in this project are:

- **java.net**: This package provides classes and interfaces for networking operations in Java. It includes classes for handling URLs, sockets, server sockets, and network protocols.
- **java.io**: This package contains classes for performing input and output operations in Java. It includes classes for reading and writing data streams, files, and objects.
- **java.util.ArrayList**: This class is a part of the Java Collections Framework and provides an implementation of a dynamic array. It allows you to create and manipulate resizable arrays, which can grow or shrink as needed.
- **java.util.List**: The List interface is a part of the Java Collections Framework and provides a generic ordered collection of elements. It defines operations for adding, accessing, and removing elements from a list.
- **java.util.Objects**: This class provides utility methods for working with objects in Java. It includes methods for performing null-safe operations, comparing objects, generating hash codes, and more.
- **java.util.Scanner**: The Scanner class is a part of the Java API and provides methods for parsing input streams into tokens. It allows you to read input from various sources, such as files, strings, and system input, and break it into tokens based on specific delimiters.
- **org.example.client.structs.***: The import statement is used to import classes, interfaces, or packages from other packages into the current Java file. In this case, it imports all classes and interfaces from the org.example.client.structs package, denoted by the * wildcard.

## Useful Documentation
* [XDR - External Data Representation Documentation](https://tools.ietf.org/html/rfc4506)
* [Python Protobuffers](https://blog.gitnux.com/code/python-protobuf/)