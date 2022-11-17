import sqlite3

from db_functions import get_connection


def main():
	conn = get_connection('database.db')

	with open('schema.sql') as file:
	    conn.executescript(file.read())

	conn.commit()
	conn.close()
	print("Closed connection")


if __name__ == "__main__":
	main()