import zmq
from db_functions import get_usercode, add_user, add_file, usercode_in_files


serverPort = 9001
utf = "utf-8"


def loginRequest(socket):
	# Acknowledge login request has been received
	socket.send('login_ack'.encode(utf))

	# Get required data
	username = socket.recv().decode(utf)
	socket.send('username received'.encode(utf))

	password = socket.recv().decode(utf)
	socket.send('password received'.encode(utf))

	socket.recv()
	usercode = get_usercode(username, password)

	# Check for error
	if usercode == None:
		socket.send('error'.encode(utf))
	else:
		socket.send(usercode.encode(utf))


def registerRequest(socket):
	# Acknowledge register user request has been received
	socket.send('register_ack'.encode(utf))

	# Get required data
	username = socket.recv().decode(utf)
	socket.send('username received'.encode(utf))

	password = socket.recv().decode(utf)
	socket.send('password received'.encode(utf))

	usercode = socket.recv().decode(utf)
	socket.send('usercode received'.encode(utf))

	add_user(username, password, usercode, usercode)

	socket.recv()
	socket.send('New user created'.encode(utf))


def storeFilesRequest(socket):
	# Acknowledge storefile request
	socket.send('storefile_ack'.encode(utf))

	# Get required data
	usercode = socket.recv().decode(utf)
	if not usercode_in_files(usercode):
		socket.send('error'.encode(utf))
		pass

	socket.send('usercode received'.encode(utf))

	filename = socket.recv().decode(utf)
	socket.send('filename received'.encode(utf))

	file = socket.recv()
	socket.send('file received'.encode(utf))

	add_file(usercode, filename, file)

	socket.recv()
	socket.send('File added'.encode(utf))


if __name__ == '__main__':
	context = zmq.Context()

	with context.socket(zmq.REP) as socket:
		socket.bind("tcp://*:9001")
		print("Listening on port " + str(serverPort))

		while True:
			request = socket.recv().decode(utf)

			if request == 'login':
				loginRequest(socket)
			elif request == 'register':
				registerRequest(socket)
			elif request == 'storefile':
				storeFilesRequest(socket)