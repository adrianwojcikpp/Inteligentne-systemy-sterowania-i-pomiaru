#!/usr/bin/python
#*
#******************************************************************************
#* @file    udp_server.py
#* @author  AW           Adrian.Wojcik@put.poznan.pl
#* @version 1.0
#* @date    29-Mar-2022
#* @brief   Simple UDP server with main loop
#* 
#******************************************************************************
#*
import socket
from datetimestr import datetimestr

localIP    = "172.27.229.191"
localPort  = 20000
bufferSize = 1024

msgFromServer = "Hello from [Python] server"
bytesToSend   = str.encode(msgFromServer)

# Create a datagram socket
UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# Bind to address and ip
UDPServerSocket.bind((localIP, localPort))

print("[Python] UDP server up and listening.")

# Listen for incoming datagrams
while(True):

    bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)

    message = bytesAddressPair[0]

    address = bytesAddressPair[1]

    clientMsg = "Client message[{}]: {}".format(datetimestr(), message)
    clientIP  = "Client IP Address:{}".format(address)
    
    print(clientMsg)
    #print(clientIP)

    # Sending a reply to client
    UDPServerSocket.sendto(bytesToSend, address)
    print("Response sent.")