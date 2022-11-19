from db_functions import remove_user
import sys


def main():
	args = sys.argv[1:]

	username = args[0]
	password = args[1]

	remove_user(username, password)


if __name__ == '__main__':
	main()