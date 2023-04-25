
# UDP Socket Programming
```
Programming a UDP socket peer-to-peer (P2P) connection to send messages between it's peers.
+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
| Message Type | Nick Size | Nick [Nick Size] (1-64 bytes) |
+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
| Message Size | Message [Message Size] (0-255 bytes)      |
+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
```
@author Breno Farias da Silva  
@date 24/04/2023
```
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
