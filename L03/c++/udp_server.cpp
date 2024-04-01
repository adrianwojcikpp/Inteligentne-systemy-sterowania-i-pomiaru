/**
  ******************************************************************************
  * @file    udp_server.cpp
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date    28-Mar-2024
  * @brief   Simple UDP server with main loop
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
#define DEFAULT_IP		"172.27.229.191" // C++ / Python server [RPi]
#define DEFAULT_PORT	20000
#define MAXLINE  		  1024

/* Macro ---------------------------------------------------------------------*/

/* Typedef -------------------------------------------------------------------*/

/**
 * Application options structure.
 */
struct options
{
  // USER CODE BEGIN
  bool flag_a;
  bool flag_b;
  double value_c;
  bool flag_h;
  options() : flag_a(false), flag_b(false), value_c(0.0), flag_h(false) { }
  // USER CODE END
};

/* Global variables ----------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* Function definitions ------------------------------------------------------*/

/**
  * @brief Converts text into space-separated tokens and counts them. 
  * @param[in]  str         : input text
  * @param[out] tok_cnt     : number of tokes: space-separated words
  * @param[out] tok_vec     : vector of tokes (array of C-strings)
  * @param[in]  tok_cnt_max : max. number of tokens
  * @retval 0 
  */
void cstr_to_tok(char* str, int* tok_cnt, char** tok_vec, const int tok_cnt_max)
{
  *tok_cnt = 1; 
  const char* filename = "./apc";
  tok_vec[0] = (char*)std::malloc(std::strlen(filename)+1); 
  std::strcpy(tok_vec[0], filename);

  //*tok_cnt = 0; 

  char* token = std::strtok(str, " "); 

  while(token != NULL && *tok_cnt < tok_cnt_max) {
    tok_vec[*tok_cnt] = (char*)std::malloc(std::strlen(token)+1); 
    std::strcpy(tok_vec[*tok_cnt], token);                     
    (*tok_cnt)++;                                          
    token = std::strtok(NULL, " ");
  }
}

/**
  * @brief Command-line arguments parsing.
  * @param[in]  command : user arguments
  * @param[out] op      : application options structure.
  * @retval 0 
  */
void abc_parse_args(char* command, options* op)
{	
  const int argc_max = 32;
  int argc;
  char* argv[argc_max]; 

  //! Allocates memory for local argv 
  cstr_to_tok(command, &argc, argv, argc_max); 

  int arg;
  optind = 0;
  while((arg = getopt(argc, argv, "abc:h")) != -1)
  {
    switch(arg)
    {
      // USER CODE BEGIN
      case 'a':
      {
        op->flag_a = true;
        break;
      }
      case 'b':
      {
        op->flag_b = true;
        break;
      }
      case 'c':
      {
        op->value_c = std::stod(optarg);
        break;
      }
      case 'h':
      {
        op->flag_h= true;
        break;
      }
      // USER CODE END
      default:
        break;
    }
  }

  for(int i = 0; i < argc; ++i)
    std::free(argv[i]);
}

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
	char tx_buffer[MAXLINE] = {0,};
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		std::cerr << "socket creation failed";
		std::exit(EXIT_FAILURE);
	}
	
	std::memset(&servaddr, 0, sizeof(servaddr));
	std::memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_port = htons(opt.port);
	servaddr.sin_addr.s_addr = inet_addr(opt.ip);
	
	// Bind the socket with the server address
	if(bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0 )
	{
		std::cerr << "bind failed";
		std::exit(EXIT_FAILURE);
	}

	std::cout << "[C++] UDP server up and listening." << std::endl;
	while(1)
	{
		// Receive from socket
    std::memset(rx_buffer, 0, MAXLINE);
		int len = sizeof(cliaddr);
		recvfrom(sockfd, (char*)rx_buffer, MAXLINE, 0, (struct sockaddr*)&cliaddr, (socklen_t*)&len);
		std::cout <<  "Client message [" << datetimestr() << "]: " << rx_buffer << std::endl;

		// USER CODE BEGIN
		options op;
		abc_parse_args(rx_buffer, &op);

    std::ostringstream oss;
		oss << "Options: a=" << op.flag_a 
				<< ", b=" << op.flag_b 
				<< ", c=" << op.value_c << std::endl;
    
    if(op.flag_h)
      oss << std::endl  << "Usage: app [options]" << std::endl
          << "Options:" << std::endl
          << "-h            Display help message." << std::endl
          << "-a            [TODO]" << std::endl
          << "-b            [TODO]" << std::endl
          << "-c <numeric>  [TODO]" << std::endl;

    std::strcpy(tx_buffer, oss.str().c_str());
		// USER CODE END
			
		// Send to socket
		sendto(sockfd, (const char *)tx_buffer, strlen(tx_buffer), 0, (const struct sockaddr*)&cliaddr, len);
		std::cout <<  "Response sent." << std::endl;
	}
	
	return 0;
}
