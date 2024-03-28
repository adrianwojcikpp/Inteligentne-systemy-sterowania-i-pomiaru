#!/usr/bin/python3
#*
#******************************************************************************
#* @file    datetimestr.py
#* @author  AW           Adrian.Wojcik@put.poznan.pl
#* @version 2.0
#* @date    28-Mar-2024
#* @brief   Returns a string with the current date and time, up to milliseconds precision.
#* 
#******************************************************************************
#*
from datetime import datetime

def datetimestr():
    return datetime.now().strftime("%d.%m.%Y %H:%M:%S.%f")[:-3]
