
# UDP Socket Programming
@author Breno Farias da Silva    
@date 29/04/2023  
@last update 29/04/2021  
@[repository](https://github.com/BrenoFariasdaSilva/University/tree/main/Distributed%20Systems/Activity%2002%20-%20UDP%20Socket%20Programming/UDP%20File%20Upload%20System)  
Programming a UDP socket which is used into a client-server connection to upload files from the client to the server. The server will receive the first datagram which contains the file size, filename and the file checksum. After that, the server receives fragments of the file into batches of 1024 bytes and then reassembles them into a single file using the fragment position as a reference. After that, the server will calculate the file checksum and then verify if it is equal to the checksum received from the client.
**Initial datagram**:
| File Size (4 bytes) | Filename (988 byte) | Checksum (32 bytes) |
|:-:|---|---|

**File fragments datagram**:
| File Fragment (1024 bytes)|
|--:|

## How to run
In order to run this project, you need to open at least two terminals inside this folder, one for client e another for the server.
But, before that, make sure you have makefile installed on your machine.
```bash
sudo apt install make -y
```
* On the first terminal, type:  
    ```bash
    make server
    ```
* On the second terminal, type:  
    ```bash 
    make client
    ```
## How to use
After running the make command on both terminals, you will be able to communicate between them.  

## Example of usage
* On the client terminal, type:  
    ```bash
    
    ```
* On the client terminal, type:  
    ```bash
    
    ```
* On the client terminal, type:   
    ```bash
    
    ```

## Libraries
- **socket** -> The socket library provides low-level networking support in Python. It allows Python programs to send and receive data across a network, using sockets to establish connections and transfer data. Sockets can be used to create servers and clients for a wide range of network protocols, including TCP/IP, UDP, and HTTP.
- **threading** -> The threading library provides high-level support for working with threads in Python. Threads are a way to run multiple tasks concurrently within a single process, allowing programs to take advantage of multiple CPU cores and improve performance. The threading library provides tools for creating and managing threads, including a Thread class, synchronization primitives like locks and semaphores, and tools for working with thread-local data.