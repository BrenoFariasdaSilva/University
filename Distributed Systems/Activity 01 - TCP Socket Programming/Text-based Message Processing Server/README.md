
# TCP Socket Programming
Programming a TCP socket server and client that communicates with each other using text-based commands in Java.
@author Breno Farias da Silva  
@date 24/04/2023  
@last update 28/04/2021  
@[repository](https://github.com/BrenoFariasdaSilva/University/tree/main/Distributed%20Systems/Activity%2001%20-%20TCP%20Socket%20Programming/Text-based%20Message%20Processing%20Server)  
## How to compile and run
In order to compile this project, you need to open two terminals inside this folder, one for the server and another for the client.
But, before that, make sure you have makefile installed on your machine.
```bash
sudo apt install make -y
```
- On the first terminal, type:  
    ```bash
    make server
    ```
- On the second terminal, type:  
    ```bash
    make client
    ```
## How to use
### Commands:
- **CONNECT** *user*,*password* -> Tries to establish a connection with the client
- **PWD** -> Shows the current directory
- **GETFILES** -> Shows all files in the current directory
- **CHDIR** *directoryName* -> Changes the current directory to the *directoryName*
- **GETDIRS** -> Shows all directories in the current directory
- **EXIT** -> Closes the client connection

## Example of usage
- Open the first terminal, type:
    ```bash
    make server
    ```
- Open the second terminal, type:
    ```bash
    make client
    ```
- On the client terminal, type:
    ```bash
    CONNECT guest,guest
    ```
- On the client terminal, type:
    ```bash
    PWD
    ```
- On the client terminal, type:
    ```bash
    GETFILES
    ```
- On the client terminal, type:
    ```bash
    GETDIRS
    ```
- On the client terminal, type:
    ```bash
    CHDIR {insert here a directory name that was shown in the GETDIRS command}
    ```
- On the client terminal, type:
    ```bash
    PWD
    ```
- On the client terminal, type:
    ```bash
    EXIT
    ```

## Libraries
* **java.io** -> Used to read and write files.
* **java.net** -> Used to create the server and client sockets.
* **java.util** -> Used to create the scanner and the arraylist.
* **java.math.BigInteger** -> Used to convert the hash to a string.
* **java.nio.file.Paths;** -> Used to get the current directory.
* **java.security.MessageDigest** -> Used to create the hash.
* **java.util.Scanner** -> Used to read the user input.