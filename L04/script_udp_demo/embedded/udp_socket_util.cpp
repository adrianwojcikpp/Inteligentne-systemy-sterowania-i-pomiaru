/**
  ******************************************************************************
  * @file    udp_socket_util.cpp
  * @author  AW         Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 May 2023
  * @brief   Simple UDP socket utility: sending and receiving float data
  * 
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
// standard C++ library
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
// GNU C library
#include <getopt.h>
// user headers
#include "udp_socket_util.h"

/* Public functions ----------------------------------------------------------*/
/**
 * @brief Parse command-line arguments using getopt_long
 *
 * @param[in]  argc : Number of arguments
 * @param[in]  argv : Array of argument strings
 * @param[out] opt  : Pointer to struct argopt to fill with parsed options
 */
void UDP_Socket_ParseArgs(int argc, char* argv[], struct argopt* opt)
{
    int option;
    struct option longopts[] = {
        {"port", required_argument, NULL, 'p'},
        {"ip", required_argument, NULL, 'i'},
        {0, 0, 0, 0}
    };

    while ((option = getopt_long(argc, argv, "p:i:", longopts, NULL)) != -1) {
        switch (option) {
            case 'p':
                opt->port = atoi(optarg);
                break;
            case 'i':
                if (strlen(optarg) >= sizeof(opt->ip))
                {
                    std::cerr << "IP address too long" << std::endl;
                    exit(EXIT_FAILURE);
                }
                memcpy(opt->ip, optarg, strlen(optarg));
                break;
            case '?':
            default:
                std::cerr << "Usage: "<< argv[0] << " [-p local_port] [-i local_ip]" << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        std::cerr << "Unexpected arguments: ";
        while (optind < argc) 
            std::cerr << argv[optind++] << " ";
        std::cerr << std::endl << "Usage: "<< argv[0] << " [-p port] [-i ip]" << std::endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief UDP socket initialization: binding to given local port
 * 
 * @param[inout] sock : UDP socket handler for Linux machine
 * @param[in]    opt  : UDP socket options (local port and IP address)
 */
void UDP_Socket_Init(struct UDP_Socket* sock, struct argopt* opt)
{
    // Creating socket file descriptor
	if((sock->fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		std::cerr << "socket creation failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	std::memset(&(sock->local_address), 0, sizeof(sock->local_address));
	std::memset(&(sock->remote_address), 0, sizeof(sock->remote_address));

	// Filling server information
	sock->local_address.sin_family = AF_INET; // IPv4
	sock->local_address.sin_addr.s_addr = inet_addr(opt->ip);;
	sock->local_address.sin_port = htons(opt->port);

    // Bind the socket with the server address
	if(bind(sock->fd, (const struct sockaddr *)&(sock->local_address), sizeof(sock->local_address)) < 0 )
	{
		std::cerr << "bind failed" << std::endl;
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Reading float array form UDP socket.
 * @note Data decoded as ASCII character string with comma separated values.
 * 
 * @param[inout] sock      : UDP socket handler for Linux machine
 * @param[out]   array     : Received float array
 * @param[in]    array_len : Array length (number of elements)
 */
void UDP_Socket_ReceiveFloatArray(struct UDP_Socket* sock, float* array, unsigned int array_len)
{
	char buffer[1024] = { 0, };
	int len = sizeof(sock->remote_address);
	recvfrom(sock->fd, (char*)buffer, sizeof(buffer), 0, (struct sockaddr*)&(sock->remote_address), (socklen_t*)&len);

    csv_to_float : 
    {
        std::istringstream iss(buffer);
        std::string token;
        int index = 0;

        while (std::getline(iss, token, ',')) {
            array[index] = std::stof(token);
            index++;
        }

        if (index != array_len) 
            std::cerr << "text does not match the specified array size" << std::endl;
    }
}

/**
 * @brief Sending float array to UDP socket.
 * @note Data decoded as ASCII character string with comma separated values.
 * 
 * @param[inout] sock      : UDP socket handler for Linux machine
 * @param[in]    array     : Sended float array
 * @param[in]    array_len : Array length (number of elements)
 */
void UDP_Socket_SendFloatArray(struct UDP_Socket* sock, float* array, unsigned int array_len)
{
	char buffer[1024] = { 0, };

    float_to_csv : 
    {
        std::ostringstream oss;
        for (int i = 0; i < array_len; i++) 
        {
            oss << array[i];
            if (i < array_len - 1) 
                oss << ", ";
        }
        oss << std::endl;
        std::string result = oss.str();
        std::strncpy(buffer, result.c_str(), result.length());
    }

	sendto(sock->fd, (const char*)buffer, strlen(buffer), 0, (const struct sockaddr*)&(sock->remote_address), sizeof(sock->remote_address));
}
