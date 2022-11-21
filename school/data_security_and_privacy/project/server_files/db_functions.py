import sqlite3

from password import encode_password, verify_password

def get_connection(database):
	try:
		conn = sqlite3.connect(database)
		print('Connected to ' + database)
		return conn

	except sqlite3.Error as e:
		print(e)

	return conn


################## Insert data ##################

def add_user(username, password, usercodeEnc, usercode):
	try:
		conn = get_connection('database.db')
		cur = conn.cursor()

		# Add user info to users table
		userTableQuery = """INSERT INTO users(username, password, usercode) VALUES(?,?,?)"""
		userData = (username, encode_password(password), usercodeEnc)

		cur.execute(userTableQuery, userData)

		print("Added to users table")

		# Add usercode to files table
		filesTableQuery = """INSERT INTO files(usercode) VALUES(?)"""
		filesData = (usercode,)

		cur.execute(filesTableQuery, filesData)

		print("Added usercode to files table")

		conn.commit()

		cur.close()
		conn.close()
		print("Closed connection")

	except sqlite3.Error as e:
		print(e)


def add_file(usercode, filename, file):
	try:
		conn = get_connection('database.db')
		cur = conn.cursor()

		updateQuery = """INSERT INTO files(usercode, filename, file) VALUES(?,?,?)"""
		updateData = (usercode, filename, file)

		cur.execute(updateQuery, updateData)

		conn.commit()

		cur.close()
		conn.close()
		print("Connection closed")

	except sqlite3.Error as e:
		print(e)


################## Retrieve data ##################

def get_usercode(username, password):
	try:
		conn = get_connection('database.db')
		cur = conn.cursor()

		getUserQuery = """SELECT * FROM users WHERE username=?"""
		rows = cur.execute(getUserQuery, (username,)).fetchall()
		
		cur.close()
		conn.close()
		print("Connection closed")

		if len(rows) == 0:
			return None
		else:
			userInfo = rows[0]


		if verify_password(password, userInfo[1]):
			return userInfo[2]

		else:
			return None


	except sqlite3.Error as e:
		print(e)


def usercode_in_files(usercode):
	try:
		conn = get_connection('database.db')
		cur = conn.cursor()

		query = """SELECT * FROM files WHERE usercode=?"""
		row = cur.execute(query, (usercode,)).fetchall()

		cur.close()
		conn.close()
		print("Connection closed")

		# Current usercode does not belong to active user
		if len(row) == 0:
			return False

		return True

	except sqlite3.Error as e:
		print(e)


def get_id(usercode):
	try:
		conn = get_connection('database.db')
		cur = conn.cursor()

		query = """SELECT id FROM files WHERE usercode=?"""
		data = (usercode,)

		ids = cur.execute(query, data).fetchall()

		cur.close()
		conn.close()
		print("Connection closed")

		return ids

	except sqlite3.Error as e:
		print(e)


def get_filenames(usercode):
	try:
		conn = get_connection('database.db')
		cur = conn.cursor()

		query = """SELECT filename FROM files WHERE usercode=?"""
		data = (usercode,)

		rows = cur.execute(query, data).fetchall()

		cur.close()
		conn.close()
		print("Connection closed")

		if len(rows) == 0:
			return None
		else:
			filenames = []
			for row in rows:
				filenames.append(row[0])

		return filenames

	except sqlite3.Error as e:
		print(e)


def get_file(id):
	try:
		conn = get_connection('database.db')
		cur = conn.cursor()

		query = """SELECT file FROM files WHERE id=?"""
		data = (id,)

		file = cur.execute(query, data).fetchall()

		cur.close()
		conn.close()
		print("Connection closed")

		return file

	except sqlite3.Error as e:
		print(e)
		

################## Remove data ##################

def remove_user(username, password):
	try:
		conn = get_connection('database.db')
		cur = conn.cursor()

		getUserQuery = """SELECT * FROM users WHERE username=?"""
		userInfo = cur.execute(getUserQuery, (username,)).fetchall()[0]

		if verify_password(password, userInfo[1]):
			usercode = userInfo[2]
			removeUserQuery = """DELETE FROM users WHERE username=?"""
			
			cur.execute(removeUserQuery, (username,))

		else:
			print("Incorrect password")
			return

		removeFilesQuery = """DELETE FROM files WHERE usercode=?"""

		cur.execute(removeFilesQuery, (usercode,))

		conn.commit()

		cur.close()
		conn.close()
		print("Connection closed")

	except sqlite3.Error as e:
		print(e)


def remove_file(filename):
	try:
		conn = get_connection('database.db')
		cur = conn.cursor()

		query = """DELETE FROM files WHERE filename=?"""
		cur.execute(query, (filename,))

		conn.commit()

		cur.close()
		conn.close()
		print("Connection closed")

	except sqlite3.Error as e:
		print(e)