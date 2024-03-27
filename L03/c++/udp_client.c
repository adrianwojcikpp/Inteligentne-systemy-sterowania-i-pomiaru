/**
  ******************************************************************************
  * @file    udp_client.cpp
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    29-Mar-2022
  * @brief   Simple UDP client
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "datetimestr.h"
#include "udp_parse_args.h"

/* Define --------------------------------------------------------------------*/
#define DEFAULT_IP		"172.27.229.191" // C / Python server [Linux server]
//#define DEFAULT_IP		"192.168.0.15" // MATLAB server [Windows PC]
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
	char hello[] = "Hello from [C] client";
	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_port = htons(opt.port);
	servaddr.sin_addr.s_addr = inet_addr(opt.ip);
	
	// Send to socket
	sendto(sockfd, (const char *)hello, strlen(hello), 0, (const struct sockaddr*)&servaddr, sizeof(servaddr));
	printf("Message sent.\n");
	
	// Receive from socket
	int len = sizeof(servaddr);
	recvfrom(sockfd, (char *)buffer, MAXLINE, 0, (struct sockaddr*)&servaddr, (socklen_t*)&len);
	printf("Server response [%s]: %s\n", datetimestr(), buffer);

	close(sockfd);
	return 0;
}
