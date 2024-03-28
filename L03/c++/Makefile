default: client

client: udp_client.cpp udp_parse_args.cpp datetimestr.cpp
	g++ udp_client.cpp udp_parse_args.cpp datetimestr.cpp -o udp_client -Wall -pedantic 

server: udp_server.cpp udp_parse_args.cpp datetimestr.cpp
	g++ udp_server.cpp udp_parse_args.cpp datetimestr.cpp -o udp_server -Wall -pedantic 

clean:
	rm -f udp_client
	rm -f udp_server