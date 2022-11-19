import tkinter.messagebox
import tkinter as tk

from client               import connectToServer
from connection_functions import sendLoginInfo, sendRegisterInfo


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
								command=lambda: sendLoginInfo(clientSocket,
									                          username,
									                          password))
		loginButton.pack(side='left')


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


class MainView(tk.Frame):
	def __init__(self, *args, **kwargs):
		tk.Frame.__init__(self, *args, **kwargs)
		loginPage = Login(self)
		registerPage = Register(self)

		buttonFrame = tk.Frame(self)
		container = tk.Frame(self)
		buttonFrame.pack(side='top', anchor='nw')
		container.pack(side='top', fill='both', expand=True)

		loginPage.place(in_=container, x=0, y=0, relwidth=1, relheight=1)
		registerPage.place(in_=container, x=0, y=0, relwidth=1, relheight=1)

		loginButton = tk.Button(buttonFrame, text='Login', command=loginPage.show)
		registerButton = tk.Button(buttonFrame, text='Sign up', command=registerPage.show)

		loginButton.pack(side='left')
		registerButton.pack(side='left')

		loginPage.show()


if __name__ == '__main__':
	root = tk.Tk()
	main = MainView(root)
	main.pack(side='top', fill='both', expand=True)
	root.wm_geometry('800x600')
	root.mainloop()







# # Create window
# window = Tk()

# background_color = '#28272B'
# active_background = '#9B97A7'
# white = '#FFFFFF'

# window.geometry('800x600')
# window.title('DSaP Project GUI')
# window.configure(bg=background_color)

# usernameLabel = Label(window, text='Username').grid(row=2, column=0)
# username = StringVar()
# usernameEntry = Entry(window, textvariable=username).grid(row=2, column=1)

# passwordLabel = Label(window, text='Password').grid(row=3, column=0)
# password = StringVar()
# passwordEntry = Entry(window, textvariable=password, show='*').grid(row=3, column=1)

# loginButton = Button(window, 
# 	                 text="Log In",
# 	                 width=8,
# 	                 height=1,
# 	                 fg=white, 
# 	                 bg=background_color,
# 	                 activebackground=active_background,
# 	                 command=lambda: sendLoginInfo(clientSocket, username, password)).grid(row=4, column=0)


# # Run GUI
# window.mainloop()