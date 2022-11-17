from socket import *
import sys


serverPort = 9001
serverSocket = socket(AF_INET, SOCK_STREAM)

serverSocket.bind(('', serverPort))
serverSocket.listen(1)

print("Listening on port " + str(serverPort))

while True:
	connectionSocket, addr = serverSocket.accept()

	try:
		message = connectionSocket.recv(2048).decode()
		connectionSocket.send("Message received.".encode())

		connectionSocket.close()

	except:
		print("Fuck if I know.")
		connectionSocket.close()

	serverSocket.close()
	sys.exit()