import socket
import random
import time

localIP = "192.168.56.102"
clientIP = "192.168.56.1"
receivePort = 8893
sendPort = 8881
bufferSize = 1024

#Config
UDPServerSend = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
UDPServerReceive = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

UDPServerReceive.bind((localIP,sendPort))
UDPServerSend.connect((clientIP,receivePort))


print("Server up")

ToC = [1,2,3,5,8,12]


while 1:
    answer = UDPServerReceive.recvfrom(bufferSize)
    address = answer[1]
    print(address)
    

    msgFromServer= random.choice(ToC)
    bytesToSend = msgFromServer.to_bytes(2,'big')#str.encode(msgFromServer)
    UDPServerSend.send(bytesToSend)