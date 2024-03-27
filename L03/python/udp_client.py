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
from udp_parse_arg import parse_args

if __name__ == '__main__':
    
    port, ip = parse_args()

    # Set default values if port or ip are not specified
    if port is None:
        port = 20000
    if ip is None:
        ip = "172.27.229.191" # C / Python server [RPi]
        #ip = "192.168.0.15" # MATLAB server [PC]

    msgFromClient       = "Hello from [Python] client"
    bytesToSend         = str.encode(msgFromClient)
    serverAddressPort   = (ip, port)   # C / Python server [RPi]
    bufferSize          = 1024

    # Create a UDP socket at client side
    UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

    # Send to server using created UDP socket
    UDPClientSocket.sendto(bytesToSend, serverAddressPort)
    print("Message sent.")

    msgFromServer = UDPClientSocket.recvfrom(bufferSize)

    msg = "Server response [{}]: {}".format(datetimestr(), msgFromServer[0])
    print(msg)