/**
  ******************************************************************************
  * @file    udp_client.cpp
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date    28-Mar-2024
  * @brief   Simple UDP client
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
// C++ standard libraries
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>

// POSIX libraries
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// Local files
#include "datetimestr.h"
#include "udp_parse_args.h"

/* Define --------------------------------------------------------------------*/
#define DEFAULT_IP		"172.27.224.1" // MATLAB / Python server [PC]
#define DEFAULT_PORT	20000
#define MAXLINE  		1024

/* Main function -------------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @param[in] argc : argument count; number of command-line arguments passed 
  *                   by the user including the name of the program.
  * @param[in] argv : argument vector; character pointers (C-strings) listing 
  *                   all the arguments.
  * @retval 0 
  */
int main(int argc, char* argv[])
{
	struct argopt opt = { DEFAULT_PORT, DEFAULT_IP };
	udp_parse_args(argc, argv, &opt);
	
	int sockfd;
	char rx_buffer[MAXLINE] = {0,};
	char tx_hello[] = "{\"dummy_data\":null}";
	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		std::cerr << "socket creation failed";
		std::exit(EXIT_FAILURE);
	}

	std::memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_port = htons(opt.port);
	servaddr.sin_addr.s_addr = inet_addr(opt.ip);
	
	// Send to socket
	sendto(sockfd, (const char *)tx_hello, strlen(tx_hello), 0, (const struct sockaddr*)&servaddr, sizeof(servaddr));
	std::cout << "Message sent. " << std::endl;
	
	// Receive from socket
	int len = sizeof(servaddr);
	recvfrom(sockfd, (char *)rx_buffer, MAXLINE, 0, (struct sockaddr*)&servaddr, (socklen_t*)&len);
	close(sockfd);
	std::cout << "Server response [" << datetimestr() << "]: " << rx_buffer << std::endl;

	return 0;
}
