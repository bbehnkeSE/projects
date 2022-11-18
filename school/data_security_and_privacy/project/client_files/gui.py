import tkinter.messagebox

from tkinter import *
from socket  import *

from client import connectToServer, closeConnection


def sendLoginInfo(socket, username, password):
	print(str(socket) + username.get() + password.get())
	socket.send(username.get().encode())
	socket.send(password.get().encode())


clientSocket = connectToServer()


# Create window
window = Tk()

background_color = '#28272B'
active_background = '#9B97A7'
white = '#FFFFFF'

window.geometry('800x600')
window.title('DSaP Project GUI')
window.configure(bg=background_color)

usernameLabel = Label(window, text='Username').grid(row=2, column=0)
username = StringVar()
usernameEntry = Entry(window, textvariable=username).grid(row=2, column=1)

passwordLabel = Label(window, text='Password').grid(row=3, column=0)
password = StringVar()
passwordEntry = Entry(window, textvariable=password, show='*').grid(row=3, column=1)

loginButton = Button(window, 
	                 text="Log In",
	                 width=8,
	                 height=1,
	                 fg=white, 
	                 bg=background_color,
	                 activebackground=active_background,
	                 command=lambda: sendLoginInfo(clientSocket, username, password)).grid(row=4, column=0)


# Run GUI
window.mainloop()