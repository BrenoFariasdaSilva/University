# [gRPC - Google Remote Procedure Call](https://github.com/BrenoFariasdaSilva/University/tree/main/Distributed%20Systems/Activity%2004%20-%20gRPC)
`@author: Breno Farias da Silva.`     
`@date: 27/05/2023.`    
`@last update: 31/05/2023.`    

### ***Quick notes:*** 
Note that in the ```/server/database.py``` file we have the following code in the database constructor (```__init__```):

    load_dotenv()
    uri = f"mongodb+srv://{os.getenv('USERNAME')}:{os.getenv('PASSWORD')}@{os.getenv('DATABASE_URL')}"
        
Is used the ```os.getenv()``` function to get the environment variables, so you need to create a ```.env``` file in the ```'root'``` directory of the project (next to the Makefile), and inside it, you need to have the following variables:

    USERNAME=your_username
    PASSWORD=your_password
    DATABASE_URL=your_database_url

For obvious reasons, i'm not going to share my database credentials, so you need to create your own database and get your own credentials in your MongoDB account.

Also, if you are trying to run "`make server_run`" and it shows this error:
```bash
ModuleNotFoundError: No module named 'movies_pb2'
```
Just open the `server/structs/movies_pb2_grpc.py` file update the import statement from:
```python
import movies_pb2 as movies__pb2
```
to:
```python
import structs.movies_pb2 as movies__pb2
```

## Install dependencies
The dependency inside the makefile command are required to run this project so, before that, make sure you have makefile installed on your machine.
```bash
sudo apt install make -y
make setup
```
Also, you need to have [Maven](https://maven.apache.org/) installed on your computer, as we have lots of dependencies on the client side, inside the ```pom.xml``` file, like `grpc-protobuf`, `grpc-stub` and `grpc-netty`.  When developing this project, the `protocol buffer compiler` was version `libprotoc 23.0`, and Maven was version `Apache Maven 3.6.3`.  If you have any problems with the dependencies, try to update them to the same version as mine or update them to the latest version. The `pom.xml` file is inside the `client` directory already contains the version of the dependencies that i used, so you don't need to worry about that.

## How to use
The avaliable commands are:
- ***`HELP`*** : Show all available commands
- ***`CREATE`*** : Create a new movie, which will ask you to fill every movie field.
- ***`GET`*** : Get a movie by title
- ***`UPDATE`*** : Update a movie (New ID must be the same as old ID!)
- ***`DELETE`*** : Delete a movie by title
- ***`LISTBYACTOR`*** : List all movies by an actor
- ***`LISTBYGENRE`*** : List all movies by a genre
- ***`EXIT`*** : Exit the program

The movie fields are specified in the `movies.proto` file, which are:
- ***`ID`*** : The movie ID as a `string`.
- ***`plot`*** : The movie plot as a `string`.
- ***`genre`*** : The movie genre as a `string`.
- ***`runtime`*** : The movie runtime as a `integer`.
- ***`cast`*** : The movie cast as a `array`.
- ***`num_mflix_comments`*** : The movie num_mflix_comments as a `integer`.
- ***`title`*** : The movie title as a `string`.
- ***`fullplot`*** : The movie fullplot as a `string`.
- ***`countries`*** : The movie countries as a `array`.
- ***`released`*** : The movie released as a `string`.
- ***`directors`*** : The movie directors as a `array`.
- ***`rated`*** : The movie rated as a `string`.
- ***`lastupdated`*** : The movie lastupdated as a `string`.
- ***`year`*** : The movie year as a `integer`.
- ***`type`*** : The movie type as a `string`.

## How to run
In order to run this project, you need to open two terminals.
#### ***Important notes:*** The order of which terminal you open first is important, so make sure you follow the order below.  In a client-server architecture, the server needs to be running before the client, otherwise, the client will not be able to connect to the server. From my personal experience, I recommend you to open the server (`Python`) on `Visual Studio Code` and the client (`Java`) on `IntelliJ IDEA`.
* On the server terminal, type:  
    ```bash
    make server_run
    ```
* On the client terminal, type:  
    ```bash 
    make client_run
    ```
## Example of usage
* On the server terminal, type:  
    ```bash
    make server_run
    ```
* On the client terminal, type:   
    ```bash
    make client_run
    # In my case, i simply click on "run" button on IntelliJ IDEA
    ```

Now the client must have connected to the server, and you can start to send requests to the server, giving you something like this:
```bash
Server started
Server Connected to distributedsystems MongoDB database using brenofarias user
```
And the client will be asking for a user input, like this:
```bash
Type a message: (String)
```
Now type the help command on the client, so you can see all the available commands:
```bash
help
```
Now type a operation, like `GET`, and follow the instructions:
```bash
get
```
Now type the movie title, and you will get the movie information:
```bash
title
```
It create a request to the server, which will return the movie information, like this:
```bash
id: "6472338bd2dca46e62b59403"
plot: "plot"
genre: "genre"
runtime: 1
cast: "actor1"
num_mflix_comments: 1
title: "title"
fullplot: "fullplot"
countries: "country1"
released: "released"
directors: "director1"
rated: "rated"
lastupdated: "lastupdated"
year: 2023
type: "type"
```
Or not, if the movie doesn't exist.
You could also delete the returned movie, by typing the `DELETE` command, and following the instructions:
```bash
delete
```
Now type the movie title, and you will delete the movie:
```bash
title
```
If the operation was successful, you will get a message like this:
```bash
Operation DELETE SUCCESS!
```
Now, in order to close the connection, you need to type the `EXIT` command.

## Libraries
First, the python libraries (for the server side) used in this project are:
- **grpc**: This is a Python implementation of gRPC, a high-performance, open-source framework for remote procedure calls (RPC). gRPC enables communication between distributed systems and provides features like authentication, load balancing, and bidirectional streaming. The grpc library allows you to create gRPC servers and clients, define service interfaces using Protocol Buffers, and perform remote method invocations.
- **concurrent.futures**: This module provides a high-level interface for asynchronously executing callables (functions or methods) using threads or processes. It provides the Executor class, which allows you to submit callables for execution and manage the execution of multiple tasks concurrently. This module is particularly useful for parallelizing and asynchronously executing tasks, such as when you want to perform multiple operations concurrently without blocking the main thread.
- **MessageToJson**: This function is imported from the google.protobuf.json_format module. It provides the capability to convert Protocol Buffers messages to JSON format, making it easier to work with the data in a human-readable and interoperable format.
- **Colorama**: The colorama library provides cross-platform support for coloring and styling terminal output. It allows you to use ANSI escape sequences to change the color, style, and other formatting aspects of the text displayed in the terminal.
 
It's worth mentioning that some of the libraries mentioned are standard libraries that come bundled with Python, such as `grpc` and `concurrent`. .Others like `MongoDatabase`, `structs.movies_pb2` and `structs.movies_pb2_grpc` are custom modules or external dependencies specific to this project, as they are importing local files.
Now the Java libraries (for the client side) used in this project are:

- **java.net**: This package provides classes and interfaces for networking operations in Java. It includes classes for handling URLs, sockets, server sockets, and network protocols.
- **java.io**: This package contains classes for performing input and output operations in Java. It includes classes for reading and writing data streams, files, and objects.
- **java.util.ArrayList**: This class is a part of the Java Collections Framework and provides an implementation of a dynamic array. It allows you to create and manipulate resizable arrays, which can grow or shrink as needed.
- **java.util.List**: The List interface is a part of the Java Collections Framework and provides a generic ordered collection of elements. It defines operations for adding, accessing, and removing elements from a list.
- **java.util.Objects**: This class provides utility methods for working with objects in Java. It includes methods for performing null-safe operations, comparing objects, generating hash codes, and more.
- **java.util.Scanner**: The Scanner class is a part of the Java API and provides methods for parsing input streams into tokens. It allows you to read input from various sources, such as files, strings, and system input, and break it into tokens based on specific delimiters.
- **org.example.client.structs.***: The import statement is used to import classes, interfaces, or packages from other packages into the current Java file. In this case, it imports all classes and interfaces from the org.example.client.structs package, denoted by the * wildcard.

## Useful Documentation
* [Introduction to gRPC](https://grpc.io/docs/what-is-grpc/introduction/)
* [gRPC Basics Tutorial - Python](https://grpc.io/docs/languages/python/basics/)
* [gRPC Quick Start - Java](https://grpc.io/docs/languages/java/quickstart/)