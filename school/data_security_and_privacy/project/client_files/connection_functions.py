import os

from encrypt import AESEncrypt, generateUsercode


utf = "utf-8"


def getKey(username):
	with open(f'secret_keys/{username}/key.txt', 'rb') as file:
		key = file.read()

	return key


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

	socket.send_string('')
	usercode = socket.recv().decode(utf)

	if usercode == 'error':
		print('Incorrect username or password')
		return None
	else:
		print('usercode received')

		aesObj = AESEncrypt(getKey(username.get()))
		usercode = aesObj.decrypt(usercode)
		return usercode


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
	encryptedUsercode, usercode = generateUsercode(username.get())

	# Send data
	socket.send(username.get().encode(utf))
	print(socket.recv().decode(utf))

	socket.send(password.get().encode(utf))
	print(socket.recv().decode(utf))

	socket.send(encryptedUsercode.encode())
	print(socket.recv().decode(utf))

	socket.send(usercode.encode())
	print(socket.recv().decode(utf))

	socket.send_string('')
	print(socket.recv().decode(utf))


def storeFile(socket, username, usercode, filenames, fileBlobs):
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

	aesObj = AESEncrypt(getKey(username.get()))

	for i in range(filesLen):
		socket.send_string(aesObj.encrypt(filenames[i].encode()))
		print(socket.recv().decode(utf))

		socket.send_string(aesObj.encrypt(fileBlobs[i]))
		print(socket.recv().decode(utf))

	socket.send_string('')
	print(socket.recv().decode(utf))


def requestFilenames(socket, username, usercode):
	if usercode == None:
		return None

	# Send initial request
	socket.send('filename request'.encode(utf))

	ack = socket.recv().decode(utf)
	if ack != 'requestfile_ack':
		return None

	socket.send(usercode.encode(utf))
	print(socket.recv().decode(utf))

	socket.send_string('')
	filenamesLen = socket.recv().decode(utf)

	if filenamesLen == 'no files':
		print(filenamesLen)
		return [], []

	filenamesLen = int(filenamesLen)

	filenames = []
	ids = []

	aesObj = AESEncrypt(getKey(username.get()))

	socket.send_string('')
	for _ in range(filenamesLen):
		filename = socket.recv().decode(utf)
		socket.send_string('')
		id = socket.recv().decode(utf)
		socket.send_string('')

		if filename == 'skip':
			continue

		filename = aesObj.decrypt(filename)

		filenames.append(filename)
		ids.append(int(id))

	print(socket.recv().decode(utf))
	return ids, filenames


def downloadFiles(socket, username, filesDict):
	filesLen = len(filesDict)
	if filesLen == 0:
		return None
	
	socket.send('download request'.encode())

	ack = socket.recv().decode(utf)
	if ack != 'download_ack':
		return None

	socket.send(str(filesLen).encode(utf))
	socket.recv()

	aesObj = AESEncrypt(getKey(username.get()))

	for id, filename in filesDict.items():
		socket.send(str(id).encode(utf))
		response = socket.recv().decode(utf)

		if response == 'error':
			print('There was an error')
			continue
		else:
			try:
				os.mkdir('downloads/')
			except:
				print('Downloads directory already exists')
			try:
				os.mkdir(f'downloads/{username.get()}')
			except:
				print(f'\'downloads/{username.get()}\' directory already exists')

			file = aesObj.decrypt(response)

			with open(f'downloads/{username.get()}/{filename.decode(utf)}', 'wb') as f:
				f.write(file)


def deleteFiles(socket, filesDict):
	filesLen = len(filesDict)
	if filesLen == 0:
		return None
	
	socket.send('delete files request'.encode())

	ack = socket.recv().decode(utf)
	if ack != 'delete_files_ack':
		return None

	socket.send(str(filesLen).encode(utf))
	socket.recv()

	for id in filesDict:
		socket.send(str(id).encode(utf))
		response = socket.recv().decode(utf)

		if response == 'error':
			print('There was an error')
			continue
		else:
			print(response)
