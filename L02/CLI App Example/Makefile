CC      = g++ 
CFLAGS  = -g -Wall -pedantic
RM      = rm -f 

default: all

all: build

build: cpp_args.cpp
		$(CC) $(CFLAGS) -o cpp_args cpp_args.cpp

clean:
		$(RM) cpp_args