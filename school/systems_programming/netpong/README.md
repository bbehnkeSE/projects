Netpong
Brian Behnke
Systems Programming - CS43203
May 9, 2022

Instructions:
	1. Compile program with included Makefile
	2. Run the program with a single argument denoting a port number
		Ex: ./netpong 5002
		    It will ask the user for their name and attempt to create a socket on port 5002, then wait for a client to attempt to connect
	3. Run the program in another terminal with two arguments, one for the hostname, and the other for the port.
		Ex: ./netpong localhost 5002
			It will ask for the client's name and attempt to connect to the host on the provided port (port number must be the same as the server waiting for a client)
	4. The program will prompt the server to set the max score the players will play to, after which the game will begin.

The current version is incomplete and will only generate the playing fields for each player without serving a ball. 