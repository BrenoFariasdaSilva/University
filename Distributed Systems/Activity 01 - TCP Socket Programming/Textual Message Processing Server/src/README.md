
# TCP Socket Programming
```bash
Programming a TCP socket server and client using Java.  
@author Breno Farias da Silva  
@date 24/04/2023
```
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
- CONNECT *user*,*password* -> Tries to establish a connection with the client
- PWD -> Shows the current directory
- GETFILES -> Shows all files in the current directory
- CHDIR *directoryName* -> Changes the current directory to the *directoryName*
- GETDIRS -> Shows all directories in the current directory
- EXIT -> Closes the client connection

## Example of usage
- On the server terminal, type:
```bash
    make server
```
- On the client terminal, type:
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
* java.io.*;
* java.net.*;
* java.util.*;
* java.math.BigInteger;
* java.nio.file.Paths;
* java.security.MessageDigest;
* java.util.Scanner;