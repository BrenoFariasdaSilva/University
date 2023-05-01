import socket
import threading
import hashlib
from colorama import Style

# Macros:
class backgroundColors: # Colors for the terminal
	OKCYAN = "\033[96m"
	OKGREEN = "\033[92m"
	WARNING = "\033[93m"
	FAIL = "\033[91m"

def main():
	client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	server = ('localhost', 7000)

	while True:
		print(f"{backgroundColors.OKCYAN}Enter message to send to server: {Style.RESET_ALL}", end=' ')
		message = input('-> ')
		client_socket.sendto(message.encode('utf-8'), server)
		data, addr = client_socket.recvfrom(1024)
		print(Style.RESET_ALL + backgroundColors.OKGREEN + 'Received from server: ' + data.decode('utf-8'))



if __name__ == '__main__':
	main()