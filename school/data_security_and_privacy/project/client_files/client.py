from socket import *

def connectToServer():
	server_ip = "192.168.178.129"
	port = 9001

	clientSocket = socket(AF_INET, SOCK_STREAM)
	serverAddress = (server_ip, port)

	message = "Connection test"

	clientSocket.connect(serverAddress)
	clientSocket.sendall(message.encode())

	response = clientSocket.recv(1024).decode()

	if response == "Message received.":
		print(response)
		return clientSocket
	else:
		print('Unable to connect...')
		clientSocket.close()


def closeConnection(socket):
	socket.sendall('Exit.')
	socket.close()