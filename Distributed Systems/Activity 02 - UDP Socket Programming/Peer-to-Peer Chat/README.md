
# UDP Socket Programming
@author Breno Farias da Silva    
@date 24/04/2023  
@last update 28/04/2021  
@[repository](https://github.com/BrenoFariasdaSilva/University/tree/main/Distributed%20Systems/Activity%2002%20-%20UDP%20Socket%20Programming/Peer-to-Peer%20Chat)  
Programming a UDP socket peer-to-peer (P2P) connection to send messages between it's peers.  
As it is a UDP connection, a well-known header is needed to be implemented in order to make the communication possible.  
| Message Type (1 byte) | Nick Size (1 byte) | Nick (1-64 bytes) |
|:-:|---|---|

| Message Size (1 byte) | Message Content (0-255 bytes) | | |
|--:|---|---|---|  

Which for a datagram of 322 bytes (1 + 1 + 64 + 1 + 255).

## How to run
In order to run this project, you need to open at least two terminals inside this folder, one for each peer you wanna have.
But, before that, make sure you have makefile installed on your machine.
```bash
sudo apt install make -y
```
* On the first terminal, type:  
    ```bash
    make
    ```
* On the second terminal, type:  
    ```bash
    make
    ```
## How to use
After running the make command on both terminals, you will be able to communicate between them.  
There is not specific command to use, simply type the message you want to send and press enter and the algorithm will do the rest.

## Example of usage
* On the first terminal, type:  
    ```bash
    make
    ```
    It will ask for a nickname, type whatever you want and press enter.  
    Then, it will ask if you wanna act as a "server" or a "client", type client and press enter.
* On the second terminal, type:  
    ```bash
    make
    ```
    It will ask for a nickname, type whatever you want, but try not to have duplicated nicknames, and press enter.
    Then, it will ask if you wanna act as a "server" or a "client", type server and press enter.
* On any of the terminals, type:  
    ```bash
    Hello, how are you?
    ```
    And after pressing enter, you will see the message on the other terminal.  
    Then, you can type any message you want and press enter to send it to the other terminal.
    This message is configured as a normal message, so it will be sent to all the peers connected to the network.

    ### Quick Disclaimer:
    This is a **peer-to-peer (P2P) connection**, so the messages will be sent to all the peers connected to the network.   
    When prompted about whether you wanna act as a "client" or a "server", it **only affects which of the threads (the one who handles message sending or message receiving) it's in the background and which is in the foregroung**, alright? It doesn't affect the way the messages are received or the change it to a client-server connection.  
    When choosing the "client" option, the foreground thread will be the one who handles message sending, and the background thread will be the one who handles message receiving.  
    When choosing the "server" option, the foreground thread will be the one who handles message receiving, and the background thread will be the one who handles message sending.
### URL
* On the first terminal, type:  
    ```bash
    https://www.example.com
    ```
    This message is configured as an URL message, so it will be sent to all the peers connected to the network.
    The other peers (terminals) will receive this message and will be able to access the URL by clicking on it.
### Emoji
* On the first terminal, type:  
    ```bash
    :penguin:
    ```
    This message is configured as an emoji message, so it will be sent to all the peers connected to the network.
    The other peers (terminals) will receive this message and will be able to see the processed emoji on the message.
### Echo
* On the second terminal, type:  
    ```bash
    echo typeSomethingHereOrNot
    ```
    This message is configured as an echo message, so it will be sent to all the peers connected to the network.
    The other peers (terminals) will receive this message and will be able to see the processed echo on the message.


## Libraries
- **socket** -> The socket library provides low-level networking support in Python. It allows Python programs to send and receive data across a network, using sockets to establish connections and transfer data. Sockets can be used to create servers and clients for a wide range of network protocols, including TCP/IP, UDP, and HTTP.
- **threading** -> The threading library provides high-level support for working with threads in Python. Threads are a way to run multiple tasks concurrently within a single process, allowing programs to take advantage of multiple CPU cores and improve performance. The threading library provides tools for creating and managing threads, including a Thread class, synchronization primitives like locks and semaphores, and tools for working with thread-local data.
- **emoji** -> The emoji library provides tools for working with emoji characters in Python. Emoji are graphical symbols that are often used to represent emotions or ideas in text messages, social media posts, and other forms of online communication. The emoji library provides tools for working with emoji characters, including functions for encoding and decoding emoji characters, searching for emoji in text, and generating random emoji sequences.
- **re** -> The re library provides support for working with regular expressions in Python. Regular expressions are a powerful tool for searching and manipulating text, allowing programs to match patterns of characters and perform complex text processing tasks. The re library provides functions for compiling regular expressions, searching for patterns in text, and performing substitutions and other manipulations on text using regular expressions.
