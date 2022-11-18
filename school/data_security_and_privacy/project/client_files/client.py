from socket import *

def connectToServer():
	server_ip = "192.168.178.129"
	port = 9001

	clientSocket = socket(AF_INET, SOCK_STREAM)
	serverAddress = (server_ip, port)

	clientSocket.connect(serverAddress)

	if clientSocket.fileno() != -1:
		print("Connected")
		return clientSocket
	else:
		print('Unable to connect...')
		clientSocket.close()
		return


def closeConnection(socket):
	socket.sendall('Exit.')
	socket.close()