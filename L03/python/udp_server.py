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
from udp_parse_arg import parse_args

if __name__ == '__main__':
    
    port, ip = parse_args()

    # Set default values if port or ip are not specified
    if port is None:
        port = 20000
    if ip is None:
        ip = "172.27.229.191" # C++ / Python server [RPi]
        #ip = "192.168.2.100" # MATLAB / Python server [PC]

    bufferSize = 1024

    msgFromServer = "ACK from [Python] server"
    bytesToSend   = str.encode(msgFromServer)

    # Create a datagram socket
    UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

    # Bind to address and ip
    UDPServerSocket.bind((ip, port))

    print("[Python] UDP server up and listening.")

    # Listen for incoming datagrams
    while(True):

        bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)

        message = bytesAddressPair[0]

        address = bytesAddressPair[1]

        clientMsg = "Client message [{}]: {}".format(datetimestr(), message)
        clientIP  = "Client IP Address:{}".format(address)
        
        print(clientMsg)
        #print(clientIP)

        # Sending a reply to client
        UDPServerSocket.sendto(bytesToSend, address)
        print("Response sent.")