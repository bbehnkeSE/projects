import tkinter.messagebox
import tkinter     as tk
import tkinter.ttk as ttk

from tkinter.filedialog   import askopenfilenames
from client               import connectToServer
from connection_functions import *


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

		refreshButtonFrame = tk.Frame(self)
		serverFilesButtonFrame = tk.Frame(self)
		container = tk.Frame(self)
		refreshButtonFrame.pack(side='top', anchor='nw')
		serverFilesButtonFrame.pack(side='bottom')
		container.pack(side='bottom', anchor='se')

		vsb = tk.Scrollbar(self, orient="vertical")
		self.text = tk.Text(self, width=40, height=20, yscrollcommand=vsb.set)
		vsb.config(command=self.text.yview)
		vsb.pack(side="right", fill="y")
		self.text.pack(side="left", fill="both", expand=True)

		refreshButton = tk.Button(refreshButtonFrame,
		                          text='Refresh List',
								  command=lambda: self.displayFiles())
		refreshButton.pack(side='right')

		storeFilesButton = tk.Button(serverFilesButtonFrame,
								     text='Upload File',
									 command=lambda: storeFile(clientSocket,
									                           usercode,
															   self.localFilenames,
															   self.fileBlobs))
		storeFilesButton.pack(side='right', anchor='se')

		selectFileButton = tk.Button(serverFilesButtonFrame,
		                             text='Select File',
									 command=self.processFile)
		selectFileButton.pack(side='right', anchor='se')

		deleteFileButton = tk.Button(serverFilesButtonFrame,
		                             text='Delete Files',
									 command=self.guiDeleteFiles)
		deleteFileButton.pack(side='left', anchor='sw')

		downloadFileButton = tk.Button(serverFilesButtonFrame,
		                               text='Download Files',
									   command=self.guiDownloadFiles)
		downloadFileButton.pack(side='left', anchor='sw')


	def processFile(self):
		filePaths = askopenfilenames()
		self.fileBlobs = []
		self.localFilenames = []

		# Prune path from filename
		for i in range(len(filePaths)):
			pos = filePaths[i].rfind('/') + 1
			self.localFilenames.append(filePaths[i][pos::1])

			# Open file and convert to binary data
			with open(filePaths[i], 'rb') as file:
				binaryData = file.read()

			self.fileBlobs.append(binaryData)

	def displayFiles(self):
		self.ids, self.remoteFilenames = requestFilenames(clientSocket, usercode)
		
		try:
			self.text.delete('1.0', 'end')
		except:
			pass

		self.cbIntVar= []
		for filename in self.remoteFilenames:
			self.cbIntVar.append(tk.IntVar())
			cb = tk.Checkbutton(self, 
			                    text=filename,
						        bg='white',
						        variable=self.cbIntVar[-1],
						        command=self.cbChecked)
			self.text.window_create("end", window=cb)
			self.text.insert("end", "\n")


	def cbChecked(self):
		self.filesToManage= {}
		for index, intVar in enumerate(self.cbIntVar):
			if intVar.get():
				self.filesToManage[self.ids[index]] = self.remoteFilenames[index]


	def guiDownloadFiles(self):
		downloadFiles(clientSocket, self.filesToManage)

	def guiDeleteFiles(self):
		deleteFiles(clientSocket, self.filesToManage)
			


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