from db_functions import add_file, get_usercode
import sys


def convert_to_binary_data(filename):
	with open(filename, 'rb') as file:
		binaryData = file.read()

	return binaryData


def main():
	args = sys.argv[1:]

	username = args[0]
	password = args[1]
	filename = args[2]

	usercode = get_usercode(username, password)
	fileblob = convert_to_binary_data(filename)

	add_file(usercode, filename, fileblob)


if __name__ == '__main__':
	main()