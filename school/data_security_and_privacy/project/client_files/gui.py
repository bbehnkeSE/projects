import tkinter.messagebox
import tkinter     as tk
import tkinter.ttk as ttk

from tkinter.filedialog   import askopenfilename
from client               import connectToServer
from connection_functions import sendLoginInfo, sendRegisterInfo, storeFile


clientSocket = connectToServer()


class Page(tk.Frame):
	def __init__(self, *args, **kwargs):
		tk.Frame.__init__(self, *args, **kwargs)
	def show(self):
		self.lift()


class Login(Page):
	def __init__(self, *args, **kwargs):
		Page.__init__(self, *args, **kwargs)
		label = tk.Label(self, text='Login', font=("TkDefaultFont", 20, 'bold'))
		label.pack(side='top', anchor='nw')

		usernameLabel = tk.Label(self, text='Username')
		username = tk.StringVar()
		usernameEntry = tk.Entry(self, textvariable=username)

		usernameLabel.pack(side='top', anchor='nw')
		usernameEntry.pack(side='top', anchor='nw')

		passwordLabel = tk.Label(self, text='Password')
		password = tk.StringVar()
		passwordEntry = tk.Entry(self, textvariable=password, show='*')

		passwordLabel.pack(side='top', anchor='nw')
		passwordEntry.pack(side='top', anchor='nw')

		buttonFrame = tk.Frame(self)
		container = tk.Frame(self)
		buttonFrame.pack(side='top', anchor='nw')
		container.pack(side='top', anchor='nw')

		loginButton = tk.Button(buttonFrame, 
								text='Submit',
								command=lambda: self.setUsercode(username, password))
		loginButton.pack(side='left')


	def setUsercode(self, username, password):
		global usercode 
		usercode = sendLoginInfo(clientSocket, username, password)


	def getUsercode(self):
		return self.usercode


class Register(Page):
	def __init__(self, *args, **kwargs):
		Page.__init__(self, *args, **kwargs)
		label = tk.Label(self, text='Register', font=("TkDefaultFont", 20, 'bold'))
		label.pack(side='top', anchor='nw')

		usernameLabel = tk.Label(self, text='Username')
		username = tk.StringVar()
		usernameEntry = tk.Entry(self, textvariable=username)

		usernameLabel.pack(side='top', anchor='nw')
		usernameEntry.pack(side='top', anchor='nw')

		passwordLabel = tk.Label(self, text='Password')
		password = tk.StringVar()
		passwordEntry = tk.Entry(self, textvariable=password, show='*')

		passwordLabel.pack(side='top', anchor='nw')
		passwordEntry.pack(side='top', anchor='nw')

		passwordConfirmLabel = tk.Label(self, text='Confirm Password')
		passwordConfirm = tk.StringVar()
		passwordConfirmEntry = tk.Entry(self, textvariable=passwordConfirm, show='*')

		passwordConfirmLabel.pack(side='top', anchor='nw')
		passwordConfirmEntry.pack(side='top', anchor='nw')

		buttonFrame = tk.Frame(self)
		container = tk.Frame(self)
		buttonFrame.pack(side='top', anchor='nw')
		container.pack(side='top', anchor='nw')

		registerButton = tk.Button(buttonFrame,
								   text='Submit',
								   command=lambda: sendRegisterInfo(clientSocket, 
								   	                                username, 
								   	                                password,
								   	                                passwordConfirm))
		registerButton.pack(side='left')


class MyFiles(Page):
	def __init__(self, *args, **kwargs):
		Page.__init__(self, *args, **kwargs)
		label = tk.Label(self, text='My Files', font=("TkDefaultFont", 20, 'bold'))
		label.pack(side='top', anchor='nw')

		buttonFrame = tk.Frame(self)
		container = tk.Frame(self)
		buttonFrame.pack(side='bottom', anchor='sw')
		container.pack(side='bottom', anchor='sw')

		selectFileButton = tk.Button(buttonFrame,
		                             text='Select File',
									 command=self.processFile)
		selectFileButton.pack(side='left')

		storeFilesButton = tk.Button(buttonFrame,
								     text='Store File',
									 command=lambda: storeFile(clientSocket,
									                           usercode,
															   self.filename,
															   self.fileBlob))
		storeFilesButton.pack(side='left')


	def processFile(self):
		filePath = askopenfilename()

		# Prune path from filename
		pos = filePath.rfind('/') + 1
		self.filename = filePath[pos::1]

		# Open file and convert to binary data
		with open(filePath, 'rb') as file:
			binaryData = file.read()

		self.fileBlob = binaryData


class MainView(tk.Frame):
	def __init__(self, *args, **kwargs):
		tk.Frame.__init__(self, *args, **kwargs)
		loginPage = Login(self)
		registerPage = Register(self)
		myFilesPage = MyFiles(self)

		buttonFrame = tk.Frame(self)
		container = tk.Frame(self)
		buttonFrame.pack(side='top', anchor='nw')
		container.pack(side='top', fill='both', expand=True)

		loginPage.place(in_=container, x=0, y=0, relwidth=1, relheight=1)
		registerPage.place(in_=container, x=0, y=0, relwidth=1, relheight=1)
		myFilesPage.place(in_=container, x=0, y=0, relwidth=1, relheight=1)

		loginButton = tk.Button(buttonFrame, text='Login', command=loginPage.show)
		registerButton = tk.Button(buttonFrame, text='Sign up', command=registerPage.show)
		myFilesButton = tk.Button(buttonFrame, text='My Files', command=myFilesPage.show)

		loginButton.pack(side='left')
		registerButton.pack(side='left')
		myFilesButton.pack(side='left')

		loginPage.show()


if __name__ == '__main__':
	root = tk.Tk()
	main = MainView(root)
	main.pack(side='top', fill='both', expand=True)
	root.wm_geometry('800x600')
	root.mainloop()