from socket import *


serverPort = 9001


with socket(AF_INET, SOCK_STREAM) as socket:
	socket.bind(('', serverPort))
	socket.listen()
	print("Listening on port " + str(serverPort))
	conn, addr = socket.accept()

	with conn:
		print(f"Connected by {addr}")
		while True:
			data = conn.recv(1024)
			if not data:
				break

			conn.sendall(data)