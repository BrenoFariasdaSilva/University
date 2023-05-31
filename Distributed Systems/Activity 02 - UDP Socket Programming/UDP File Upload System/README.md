# UDP Socket Programming
@author Breno Farias da Silva    
@date 29/04/2023  
@last update 07/05/2023  
@[repository](https://github.com/BrenoFariasdaSilva/University/tree/main/Distributed%20Systems/Activity%2002%20-%20UDP%20Socket%20Programming/UDP%20File%20Upload%20System)   
@**ToDo**: Implement timeout in **client.py** at line 150 for the client not to be stuck infinty waiting in case some datagram fails.   
Programming a UDP socket which is used into a client-server connection to upload files from the client to the server. The server will receive the first datagram which contains the file size, filename size, filename and the file checksum. After that, the server receives fragments of the file into batches of 1028 bytes which contains the datagram_number and the file data. After all file data datagrams were sent, the server will reassemble them into a single file inside the `/server_files`. Subsequently, the server will calculate the file checksum and then verify if it is equal to the checksum received from the client in the first datagram. If the checksums are equal, the server will send an OK message to the client, otherwise, it will send an ERROR message.   

### ***Quick notes:***  
 - There is a progress bar on the client and server side, which is used to show the progress of the file upload/download. This progress bar is not required to run the project, but it is recommended to install it, because it will make the project more user friendly. Futhermore, the progress bar might run too fast, so it is recommended to upload a file with at least 1MB of size or uncomment the sleep function inside the client code in line 154. 
 - There are log files that are generated for each side of the application (client and server). The log files are stored inside the `/logs` folder. Feel free to read them in order to have a better understanding of the application flow.

**Initial Datagram**:
| File Size (4 bytes) | Filename Size (4 bytes) | Filename (956 byte) | Checksum (64 bytes) |
|:-:|---|---|---|

**File Fragments Datagram**:
| Datagram Number (4 Byte) | File Fragment (1024 bytes)|
|--:|---|

## Install dependencies
The dependency inside the makefile command are required to run this project, due to make the progress bar work properly. But, before that, make sure you have makefile installed on your machine and install the project dependencies.
```bash
sudo apt install make -y
make setup
```

## How to run
In order to run this project, you need to open at least two terminals inside this folder, one for client e another for the server.  
- On the first terminal, type:  
    ```bash  
    make server
    ```  
- On the second terminal, type:  
    ```bash 
    make client
    ```
## How to use
After running the make command on both terminals, you will be able to communicate between them.  
## Example of usage
* On the client terminal, type:  
    ```bash
    upload filename.extension
    # Example: upload test.pdf
    # If you have any doubts, type: help
    ```
    Now Wait for the server response, which can be:
    - OK - File is valid
    - ERROR - File is invalid  
    If the file was sent successfully, you can check the server folder to see if the file was uploaded correctly.
* On the client terminal, type:   
    ```bash
    exit
    ```
## Libraries
- **socket** -> The socket library provides low-level networking support in Python. It allows Python programs to send and receive data across a network, using sockets to establish connections and transfer data. Sockets can be used to create servers and clients for a wide range of network protocols, including TCP/IP, UDP, and HTTP.
- **threading** -> The threading library provides high-level support for working with threads in Python. Threads are a way to run multiple tasks concurrently within a single process, allowing programs to take advantage of multiple CPU cores and improve performance. The threading library provides tools for creating and managing threads, including a Thread class, synchronization primitives like locks and semaphores, and tools for working with thread-local data.
- **os** -> The os library provides a portable way to interact with the underlying operating system in Python. It provides functions for working with files, directories, and processes, as well as utilities for managing the environment, working with file paths, and more. The os library is particularly useful for writing cross-platform applications that need to interact with the file system or other low-level system resources.
- **hashlib** -> The hashlib library provides a set of cryptographic hash functions in Python. Hash functions are a way to transform input data into a fixed-length string of bytes, which can be used to verify the integrity of data or securely store passwords and other sensitive information. The hashlib library provides functions for computing a variety of hash functions, including MD5, SHA-1, SHA-256, and more.
- **math** -> The math library provides a set of mathematical functions in Python. It includes functions for performing basic arithmetic, trigonometry, logarithmic and exponential functions, and more. The math library is particularly useful for scientific computing and numerical analysis, and provides a wide range of tools for working with numbers in Python.