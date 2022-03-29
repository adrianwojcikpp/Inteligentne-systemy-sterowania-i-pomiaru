default: client

client: udp_client.c 
	gcc udp_client.c -o udp_client --std=c18 -Wall -pedantic 

server: udp_server.c 
	gcc udp_server.c -o udp_server --std=c18 -Wall -pedantic 

clean:
	rm -f udp_client
	rm -f udp_server