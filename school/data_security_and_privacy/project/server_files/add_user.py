from db_functions import add_user

import random
import string
import sys

def main():
	args = sys.argv[1:]

	username = args[0]
	password = args[1]

	usercode = string.ascii_lowercase + string.ascii_uppercase + string.ascii_letters + string.digits + string.punctuation
	usercode = ''.join(random.choice(usercode) for i in range(len(usercode)))

	for i in range(random.randint(1, 4)):
		usercode += ''.join(random.choice(usercode) for i in range(len(usercode)))

	add_user(username, password, usercode)


if __name__ == '__main__':
	main()