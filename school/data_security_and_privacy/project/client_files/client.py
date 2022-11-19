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