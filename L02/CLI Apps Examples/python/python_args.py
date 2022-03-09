#!/usr/bin/python3
#**
#******************************************************************************
#* @file    /cli_examples/python/python_args.py
#* @author  Adrian Wojcik
#* @version V1.0
#* @date    14-Mar-2020
#* @brief   Raspberry Pi CLI apps example: Python 3 with getopt
#******************************************************************************

import sys
import getopt

print("Python 3 CLI example")

flagstate = ["RESET", "SET"]
aflag = 0
bflag = 0
cvalue = ''

sysarg = sys.argv[1:]

# standard try/exept/for procedure for 'getopt' function 
try:
    opts, args = getopt.getopt(sysarg, ':abc:')
except getopt.GetoptError as err:
	print(err)
	sys.exit(1)

for opt, arg in opts:
    if opt in '-a':
        aflag = 1
    elif opt in '-b':
        bflag = 1
    elif opt in '-c':
        cvalue = arg

# Printing results 		
print('a (flag) =',flagstate[aflag])
print('b (flag) =',flagstate[bflag])
if cvalue:
	print('c (value) =',cvalue)

for arg in opts:
	sysarg.remove(arg[0])
	if arg[1]:
		sysarg.remove(arg[1])

index = 1	
for arg in sysarg:
	print('Non-option argument #', index, " = ", arg, sep="")
	index = index + 1
