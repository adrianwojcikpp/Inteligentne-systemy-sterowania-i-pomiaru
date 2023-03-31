/**
  ******************************************************************************
  * @file    udp_server.cpp
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    29-Mar-2022
  * @brief   Simple UDP server with main loop
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "datetimestr.h"
#include "udp_parse_args.h"

/* Define --------------------------------------------------------------------*/
#define DEFAULT_IP		"172.27.229.191"
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
	parse_args(argc, argv, &opt);

	int sockfd;
	char buffer[MAXLINE] = {0,};
	char hello[] = "Hello from [C] server";
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_port = htons(opt.port);
	servaddr.sin_addr.s_addr = inet_addr(opt.ip);
	
	// Bind the socket with the server address
	if(bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	printf("[C] UDP server up and listening.\n");
	while(1)
	{
		// Receive from socket
		int len = sizeof(cliaddr);
		recvfrom(sockfd, (char*)buffer, MAXLINE, 0, (struct sockaddr*)&cliaddr, (socklen_t*)&len);
		printf("Client message [%s]: %s\n", datetimestr(), buffer);
		
		// Send to socket
		sendto(sockfd, (const char *)hello, strlen(hello), 0, (const struct sockaddr*)&cliaddr, len);
		printf("Response sent.\n");
	}
	
	return 0;
}
