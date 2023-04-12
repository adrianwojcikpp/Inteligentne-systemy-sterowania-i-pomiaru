default: example

example: object_emulation.c dsos.c
	gcc object_emulation.c dsos.c -o example.exe -std=c18 -Wall -pedantic	
	
server: udp_server.c dsos.c
	gcc udp_server.c dsos.c -o udp_server --std=c18 -Wall -pedantic -lpthread
	
server_sim: udp_server_sim.c dsos.c
	gcc udp_server_sim.c dsos.c -o udp_server_sim --std=c18 -Wall -pedantic -lpthread

clean:
	rm -f udp_server	
	rm -f udp_server_sim
	rm -f example.exe

