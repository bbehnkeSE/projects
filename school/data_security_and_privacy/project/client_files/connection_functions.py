import zmq
import string
import random


utf = "utf-8"


def sendLoginInfo(socket, username, password):
	# Send initial request code
	socket.send('login'.encode(utf))

	# Wait for acknowledgement
	ack = socket.recv().decode(utf)
	if ack != 'login_ack':
		return None

	print('login ack received')

	socket.send(username.get().encode(utf))
	response1 = socket.recv().decode(utf)
	print(response1)

	socket.send(password.get().encode(utf))
	response2 = socket.recv().decode(utf)
	print(response2)

	socket.send(''.encode(utf))
	response3 = socket.recv().decode(utf)
	if response3 == 'error':
		print('Incorrect username or password')
	else:
		print('Usercode received.')


def sendRegisterInfo(socket, username, password, passwordConfirm):
	if password.get() != passwordConfirm.get():
		print('Passwords do not match')
		return None

	# Send initial request code
	socket.send('register'.encode())

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

	socket.send(username.get().encode(utf))
	print(socket.recv().decode(utf))

	socket.send(password.get().encode(utf))
	print(socket.recv().decode(utf))

	socket.send(usercode.encode())
	print(socket.recv().decode(utf))

	socket.send(''.encode(utf))
	print(socket.recv().decode(utf))
