default: example

example: object_emulation.c dsos.c
	gcc object_emulation.c dsos.c -o example.exe -std=c18 -Wall -pedantic	
	
server: udp_server.c dsos.c
	gcc udp_server.c dsos.c -o udp_server --std=c18 -Wall -pedantic -lpthread

clean:
	rm -f udp_server	
	rm -f example.exe

