
# TCP Socket Programming
```bash
Programming a TCP socket server and client that communicates with each other using binary commands in Python.
@author Breno Farias da Silva  
@date 24/04/2023
```
## How to run
In order to run this project, you need to open two terminals inside this folder, one for the server and another for the client.
But, before that, make sure you have makefile installed on your machine.
```bash
sudo apt install make -y
```
* On the first terminal, type:  
    ```bash
    make run-server
    ```
- On the second terminal, type:  
    ```bash
    make run-client
    ```
## How to use
### Commands:
- **ADDFILE** *fileName* -> Adds a file to the server
- **DELETE** *fileName* -> Deletes a file from the server
- **GETFILESLIST** -> Shows all files in the server
- **GETFILE** *fileName* -> Downloads a file from the server

## Example of usage
- Open the first terminal, type:
    ```bash
    make run-server
    ```
- Open the second terminal, type:
    ```bash
    make run-client
    ```
- On the client terminal, type:
    ```bash
    GETFILESLIST
    ```
- On the client terminal, type:
    ```bash
    GETFILE {insert here a filename that was shown in the GETFILESLIST command}
    # The command above will download the file to the client folder.
    # After that, you can check if the file was downloaded correctly by
    # looking at the client folder from your file explorer.
    ```
- On the client terminal, type:
    ```bash
    DELETE {insert here a filename that you used in the GETFILE command above}
    # The command above will delete the file from the server.
    # After that, you can check if the file was deleted correctly by
    # looking at the server folder from your file explorer.
    ```
- On the client terminal, type:
    ```bash
    # Before usinf the ADDFILE command, open the client folder and copy
    # the name of the file you want to send to the server
    ADDFILE {insert here a filename that you copied in the step above}
    # The command above will add the file to the server.
    ```
- On the client terminal, type:
    ```bash
    GETFILESLIST
    # The command above will show all files in the server.
    # The execution of this command should result in a output that includes
    # the name of the file you added in the ADDFILE command above. 
    ```
- On the client terminal, type:
    ```bash
    EXIT
    # The command above will close the client connection.
    ```

## Libraries
* **os** -> The os library provides a way to interact with the operating system in a platform-independent way. It includes functions for working with files and directories, manipulating the environment, and managing processes.
* **socket** -> The socket library provides low-level networking functionality in Python. It allows you to create and use sockets for communication over the network, including TCP/IP and UDP.
* **threading** -> The threading library provides a way to create and manage threads in Python. Threads allow you to run multiple parts of your program concurrently, which can be useful for improving performance and handling multiple tasks at the same time. With threading, you can create new threads, start and stop them, and synchronize their execution using locks and other synchronization primitives.
* **logging** -> The logging library provides a way to write log messages from your Python programs. Logging can be useful for debugging and troubleshooting, as well as for auditing and monitoring the behavior of your program.
