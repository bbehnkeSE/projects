import zmq

def connectToServer():
	server_ip = "192.168.178.129"
	port = 9001

	try:
		context = zmq.Context()
		socket = context.socket(zmq.REQ)
		socket.connect(f"tcp://{server_ip}:{port}")
		print(f"Connected to {server_ip}:{port}")
		
		return socket

	except zmq.ZMQError as e:
		print(e)


	# clientSocket = socket(AF_INET, SOCK_STREAM)
	# serverAddress = (server_ip, port)

	# clientSocket.connect(serverAddress)

	# if clientSocket.fileno() != -1:
	# 	print("Connected to " + server_ip + ":" + str(port))
	# 	return clientSocket
	# else:
	# 	print('Unable to connect...')
	# 	clientSocket.close()
	# 	return