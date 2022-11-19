from tkinter.filedialog import askopenfilename

def processUsercode(usercode):
    return usercode


def convert_to_binary_data(filename):
	with open(filename, 'rb') as file:
		binaryData = file.read()

	return binaryData