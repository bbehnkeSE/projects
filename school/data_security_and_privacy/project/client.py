from socket import *

server_ip = "192.168.178.129"
port = 9001

clientSocket = socket(AF_INET, SOCK_STREAM)
serverAddress = (server_ip, port)

message = "Test message"

clientSocket.connect(serverAddress)
clientSocket.sendall(message.encode())

response = clientSocket.recv(2048).decode()

print(response)

clientSocket.close()