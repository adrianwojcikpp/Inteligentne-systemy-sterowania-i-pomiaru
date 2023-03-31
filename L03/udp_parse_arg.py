#!/usr/bin/python3
#*
#******************************************************************************
#* @file    udp_parse_args.py
#* @author  AW           Adrian.Wojcik@put.poznan.pl
#* @version 1.0
#* @date    30-Mar-2023
#* @brief   This file contains a command-line argument parsing function implemented in Python using the getopt module. 
#*          The function parses two optional arguments: a port number and an IP address.
#*          The port number is an integer, and the IP address is a string in dotted-decimal notation.
#* 
#******************************************************************************
#*
import getopt
import sys

"""
@brief Parse command-line arguments using getopt module.

@return: A tuple containing the port number and IP address parsed from the command-line arguments.
             If an argument is not specified, its value in the tuple will be None.
@rtype: tuple
"""
def parse_args():
    port = None
    ip = None

    try:
        opts, args = getopt.getopt(sys.argv[1:], "p:i:", ["port=", "ip="])
    except getopt.GetoptError as err:
        print(str(err))
        sys.exit(2)

    for opt, arg in opts:
        if opt in ("-p", "--port"):
            port = int(arg)
        elif opt in ("-i", "--ip"):
            ip = arg

    return port, ip
