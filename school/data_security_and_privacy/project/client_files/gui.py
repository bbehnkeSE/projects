import tkinter as tk


background_color = '#28272B'
active_background = '#9B97A7'
white = '#FFFFFF'

Large_Font = ('Verdana', 24)


class GUI(tk.Tk):
	def __init__(self, *args, **kwargs):
		tk.Tk.__init__(self, *args, **kwargs)

		container = tk.Frame(self)
		#container.pack(side='top', fill='both', expand=True)
		container.grid_rowconfigure(0, weight=1)
		container.grid_columnconfigure(0, weight=1)

		self.frames = {}

		for f in (Login, Register, UserPage):
			frame = f(container, self)
			self.frames[f] = frame
			frame.grid(row=0, column=0, sticky='nw')

		self.show_frame(Login)

	def show_frame(self, cont):
		frame = self.frames[cont]
		frame.tkraise()


class Login(tk.Frame):
	def __init__(self, parent, controller):
		tk.Frame.__init__(self, parent)
		label = tk.Label(self, text='Login', font=Large_Font)
		#label.pack(pady=10, padx=10)

		usernameLabel = tk.Label(self, text='Username')
		passwordLabel = tk.Label(self, text='Password')

		usernameEntry = tk.Entry(self)
		passwordEntry = tk.Entry(self)

		usernameLabel.grid(row=5)
		passwordLabel.grid(row=6)

		usernameEntry.grid(row=5, column=1)
		passwordEntry.grid(row=6, column=1)

		regButton = ttk.Button(self, text="Sign Up",
			                  command=lambda: controller.show_frame(Register))

		userPageButton = ttk.Button(self, text="Login",
			                       command=lambda: controller.show_frame(UserPage))


class Register(tk.Frame):
	def __init__(self, parent, controller):
		tk.Frame.__init__(self, parent)
		label = tk.Label(self, text='Sign Up', font=Large_Font)
		#label.pack(pady=10, padx=10)

		usernameLabel = tk.Label(self, text='Username')
		passwordLabel = tk.Label(self, text='Password')
		passConfLabel = tk.Label(self, text='Confirm Password')

		usernameEntry = tk.Entry(self)
		passwordEntry = tk.Entry(self)
		passConfEntry = tk.Entry(self)

		usernameLabel.grid(row=5)
		passwordLabel.grid(row=6)
		passConfLabel.grid(row=7)

		usernameEntry.grid(row=5, column=1)
		passwordEntry.grid(row=6, column=1)
		passConfEntry.grid(row=7, column=1)

		registerButton = ttk.Button(self, text='Register',
			                     command=lambda: controller.show_frame(Login))

		backButton = ttk.Button(self, text='Back',
			                   command=lambda: controller.show_frame(Login))


class UserPage(tk.Frame):
	def __init__(self, parent, controller):
		tk.Frame.__init__(self, parent)
		label = tk.Label(self, text='username', font=Large_Font)
		#label.pack(pady=10, padx=10)

		logoutButton = ttk.Button(self, text='Logout',
			                     command=lambda: controller.show_frame(Login))


app = GUI()
app.mainloop()






# import tkinter
# import tkinter.messagebox


# def clicked_button():
# 	tkinter.messagebox.showinfo("Button prompt", "You clicked the button")


# def main():
# 	# Create window
# 	window = tkinter.Tk()

# 	background_color = '#28272B'
# 	active_background = '#9B97A7'
# 	white = '#FFFFFF'

# 	window.geometry('800x600')
# 	window.title('DSaP Project GUI')
# 	window.configure(bg=background_color)

# 	button = tkinter.Button(window, 
# 		                    text="Sign Up", 
# 		                    width=8, 
# 		                    height=1,
# 		                    fg=white, 
# 		                    bg=background_color,
# 		                    activebackground=active_background,
# 		                    command=clicked_button)

# 	button.place(x=680, y=20)

# 	# Run GUI
# 	window.mainloop()


# if __name__ == '__main__':
# 	main()