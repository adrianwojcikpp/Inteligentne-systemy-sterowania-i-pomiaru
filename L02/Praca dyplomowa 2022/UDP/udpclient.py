
import socket

 

msgFromClient       = "Hello UDP Server"

bytesToSend         = str.encode(msgFromClient)

serverAddressPort   = ("192.168.56.102", 20001)

bufferSize          = 1024

 

# Create a UDP socket at client side

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

 

# Send to server using created UDP socket

UDPClientSocket.sendto(bytesToSend, serverAddressPort)

f = open("sine_from_server.csv", "w")
f.close()
 
for i in range(100):

    msgFromServer = UDPClientSocket.recvfrom(bufferSize)

    

    msg = "Message from Server {}".format(msgFromServer[0])
    f = open("sine_from_server.csv", "a")
    f.write(str(msgFromServer[0])[2:-1])
    if i < 99:
        f.write('\n')
    f.close()

    print(msg)