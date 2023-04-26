
# UDP Socket Programming
@author Breno Farias da Silva    
@date 24/04/2023  
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
- On the second terminal, type:  
    ```bash
    make
    ```
## How to use
### Commands:
- **Normal Message** -> Sends a message to all peers.
- **Emoji** -> Sends a emoji to all peers.
- **URL** -> Sends a URL to all peers.
- **ECHO** -> Sends a message to all peers and to itself to indicate that the user is active.

## Example of usage

## Libraries
