# import socket module
from   socket import *
import sys              # In order to terminate the program

serverPort = 6789
serverSocket = socket(AF_INET, SOCK_STREAM)
#Prepare a sever socket
serverSocket.bind(('', serverPort))
serverSocket.listen(1)
print("Listening...")

while True:
    #Establish the connection
    print('Ready to serve...')
    connectionSocket, addr = serverSocket.accept()

    try:
        message = connectionSocket.recv(1024).decode()
        filename = message.split()[1]
        f = open(filename[1:])
        outputdata = f.read()
        #Send one HTTP header line into socket
        connectionSocket.send("HTTP/1.1 200 OK\nContent-Type: text/html\n\n".encode())
        #Send the content of the requested file to the client
        for i in range(0, len(outputdata)):
            connectionSocket.send(outputdata[i].encode())

        connectionSocket.send("\r\n".encode())
        connectionSocket.close()

    except IOError:
        #Send response message for file not found
        connectionSocket.send("404 Not Found".encode())
        #Close client socket
        connectionSocket.close()

    serverSocket.close()
    sys.exit()      #Terminate the program after sending the corresponding data