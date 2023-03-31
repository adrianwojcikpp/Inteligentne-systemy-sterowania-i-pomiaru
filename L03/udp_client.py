#!/usr/bin/python3
#*
#******************************************************************************
#* @file    udp_client.py
#* @author  AW           Adrian.Wojcik@put.poznan.pl
#* @version 1.0
#* @date    29-Mar-2022
#* @brief   Simple UDP client
#* 
#******************************************************************************
#*
import socket
from datetimestr import datetimestr

msgFromClient       = "Hello from [Python] client"
bytesToSend         = str.encode(msgFromClient)
serverAddressPort   = ("172.27.229.191", 20000)   # C / Python server [RPi]
#serverAddressPort   = ("192.168.0.15", 20000)  # MATLAB server [PC]
bufferSize          = 1024

# Create a UDP socket at client side
UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# Send to server using created UDP socket
UDPClientSocket.sendto(bytesToSend, serverAddressPort)
print("Message sent.")

msgFromServer = UDPClientSocket.recvfrom(bufferSize)

msg = "Server response [{}]: {}".format(datetimestr(), msgFromServer[0])
print(msg)