from socket import *
import sys


serverPort = 9001
serverSocket = socket(AF_INET, SOCK_STREAM)

serverSocket.bind(('', serverPort))
serverSocket.listen(1)

print("Listening on port " + str(serverPort))

message = ''

while message != 'Exit.':
	connectionSocket, addr = serverSocket.accept()

	message = connectionSocket.recv(1024).decode()
	connectionSocket.send("Message received.".encode())

	print(message)


connectionSocket.close()
serverSocket.close()
sys.exit()