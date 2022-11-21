import zmq
import string
import random


utf = "utf-8"

# Sends username and password to server, returns usercode and list of filenames
def sendLoginInfo(socket, username, password):
	# Send initial request code
	socket.send('login'.encode(utf))

	# Wait for acknowledgement
	ack = socket.recv().decode(utf)
	if ack != 'login_ack':
		return None

	print('login ack received')

	# Send data
	socket.send(username.get().encode(utf))
	response1 = socket.recv().decode(utf)
	print(response1)

	socket.send(password.get().encode(utf))
	response2 = socket.recv().decode(utf)
	print(response2)


	socket.send(''.encode(utf))
	usercode = socket.recv().decode(utf)

	if usercode == 'error':
		print('Incorrect username or password')
		return None
	else:
		print('Usercode received.')

	socket.send(''.encode(utf))
	filesLen = int(socket.recv().decode(utf))

	filenames = []

	for i in range(filesLen):
		socket.send(''.encode(utf))
		filename = socket.recv().decode(utf)
		if filename == 'skip':
			continue
		else:
			filenames.append(filename)

	print(filenames)


def sendRegisterInfo(socket, username, password, passwordConfirm):
	if password.get() != passwordConfirm.get():
		print('Passwords do not match')
		return None

	# Send initial request code
	socket.send('register'.encode(utf))

	# Wait for acknowledgement
	ack = socket.recv().decode(utf)
	if ack != 'register_ack':
		return None

	print('register ack received')

	# Generate random usercode
	usercode = string.ascii_lowercase + string.ascii_uppercase + string.ascii_letters + string.digits + string.punctuation
	usercode = ''.join(random.choice(usercode) for i in range(len(usercode)))

	for i in range(random.randint(1, 3)):
		usercode += ''.join(random.choice(usercode) for i in range(len(usercode)))

	# Send data
	socket.send(username.get().encode(utf))
	print(socket.recv().decode(utf))

	socket.send(password.get().encode(utf))
	print(socket.recv().decode(utf))

	socket.send(usercode.encode())
	print(socket.recv().decode(utf))

	socket.send(''.encode(utf))
	print(socket.recv().decode(utf))


def storeFile(socket, usercode, filenames, fileBlobs):
	if usercode == '':
		print('Usercode is empty.')
		return None

	# Send initial request code
	socket.send('storefile'.encode(utf))

	# Wait for acknowledgement
	ack = socket.recv().decode(utf)
	if ack != 'storefile_ack':
		return None

	print('storefile ack received')


	# Send data
	socket.send(usercode.encode(utf))
	checkResponse = socket.recv().decode(utf)
	if checkResponse == 'error':
		print('Not signed in')
		return None
	
	print(checkResponse)

	# Get length of lists
	filesLen = len(filenames)

	# Send lengths of lists to be stored
	socket.send(str(filesLen).encode(utf))
	print(socket.recv().decode(utf))

	for i in range(filesLen):
		socket.send(filenames[i].encode(utf))
		print(socket.recv().decode(utf))

		socket.send(fileBlobs[i])
		print(socket.recv().decode(utf))

	socket.send(''.encode(utf))
	print(socket.recv().decode(utf))