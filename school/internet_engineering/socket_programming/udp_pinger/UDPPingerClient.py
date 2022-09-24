from   socket import *
import time
import sys

def main():
    if(len(sys.argv) == 3):
        ip = sys.argv[1]
        port = int(sys.argv[2])
    else:
        print("Please provide IP address and port number. (Ex. UDPPingerClient.py 127.0.0.1 5000")
        exit(1)

    clientSocket = socket(AF_INET, SOCK_DGRAM)
    clientSocket.settimeout(1)      # Set 1 second timeout

    numberOfPings = 10
    message = "test message"
    lostPackets = 0
    pingTimes = []                  # Empty list to store RTTs and calculate min/max/avg.

    serverAddress = (ip, port)

    for i in range(0, numberOfPings):
        startTime = time.time()
        clientSocket.sendto(message.encode(), serverAddress)
        try:
            response = clientSocket.recvfrom(1024)
            ping = (time.time() - startTime)
            print(response[0], " RTT: %.5f seconds" %ping)
            pingTimes.append(ping)
        except timeout:
            print("Request timed out")
            lostPackets += 1

    print("\nMinimum RTT: %.5f" %min(pingTimes))
    print("Maximum RTT: %.5f" %max(pingTimes))
    print("Average RTT: %.5f" %(sum(pingTimes) / len(pingTimes)))

    print("Packet loss: %d%%" %((lostPackets / numberOfPings) * 100))


if __name__ == "__main__":
    main()