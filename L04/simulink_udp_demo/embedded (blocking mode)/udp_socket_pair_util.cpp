/**
  ******************************************************************************
  * @file    udp_socket_pair_util.cpp
  * @author  AW         Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 May 2023
  * @brief   Simple UDP socket pair utility: sending and receiving float data
  * 
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
// standard C++ library
#include <sstream>
#include <iomanip>
#include <cstring>
// GNU C library
#include <getopt.h>
#include <time.h>
// user headers
#include "udp_socket_pair_util.h"

/* Public functions ----------------------------------------------------------*/
/**
 * @brief Parse command-line arguments using getopt_long
 *
 * @param[in]  argc : Number of arguments
 * @param[in]  argv : Array of argument strings
 * @param[out] opt  : Pointer to struct argopt to fill with parsed options
 */
void UDP_SocketPair_ParseArgs(int argc, char* argv[], struct argopt* opt)
{
    int option;
    struct option longopts[] = {
        {"local_tx_port", required_argument, NULL, 't'},
        {"local_rx_port", required_argument, NULL, 'l'},
        {"local_ip", required_argument, NULL, 'i'},
        {"remote_tx_port", required_argument, NULL, 'r'},
        {"remote_ip", required_argument, NULL, 'a'},
        {0, 0, 0, 0}
    };

    while ((option = getopt_long(argc, argv, "t:l:i:r:a:", longopts, NULL)) != -1) {
        switch (option) {
            case 't':
                opt->local_tx_port = atoi(optarg);
                break;
            case 'l':
                opt->local_rx_port = atoi(optarg);
                break;
            case 'r':
                opt->remote_tx_port = atoi(optarg);
                break;
            case 'i':
                if (std::strlen(optarg) >= sizeof(opt->local_ip))
                {
                    std::cerr << "IP address too long" << std::endl;
                    exit(EXIT_FAILURE);
                }
                std::memcpy(opt->local_ip, optarg, std::strlen(optarg));
                break;
            case 'a':
                if (std::strlen(optarg) >= sizeof(opt->remote_ip))
                {
                    std::cerr << "IP address too long" << std::endl;
                    exit(EXIT_FAILURE);
                }
                std::memcpy(opt->remote_ip, optarg, std::strlen(optarg));
                break;
            case '?':
            default:
                std::cerr << "Usage: "<< argv[0] << " [--local_tx_port Local Tx port] [--local_rx_port Local Rx port]" ;
                std::cerr << " [--local_ip Local IP address] [--remot_Tx_port Remote Tx port] [--local_ip Local IP address]" << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        std::cerr << "Unexpected arguments: ";
        while (optind < argc) 
            std::cerr << argv[optind++] << " ";
        std::cerr << "Usage: "<< argv[0] << " [--local_tx_port Local Tx port] [--local_rx_port Local Rx port]" ;
        std::cerr << " [--local_ip Local IP address] [--remot_Tx_port Remote Tx port] [--local_ip Local IP address]" << std::endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief UDP socket pair initialization: binding to given local ports
 * 
 * @param[inout] sockp : UDP socket pair handler for Linux machine
 * @param[in]    opt   : UDP socket par options (local and remote ports and IP addresses)
 */
void UDP_SocketPair_Init(struct UDP_SocketPair* sockp, struct argopt* opt)
{
    // Creating socket file descriptor
	if((sockp->rxfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		std::cerr << "rx socket creation failed" << std::endl;
		exit(EXIT_FAILURE);
	}
    if((sockp->txfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		std::cerr << "tx socket creation failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	std::memset(&(sockp->local_rx_address), 0, sizeof(sockp->local_rx_address));
    std::memset(&(sockp->local_tx_address), 0, sizeof(sockp->local_tx_address));
	std::memset(&(sockp->remote_rx_address), 0, sizeof(sockp->remote_rx_address));
    std::memset(&(sockp->remote_tx_address), 0, sizeof(sockp->remote_tx_address));

	// Filling server informations
	sockp->local_rx_address.sin_family = AF_INET; // IPv4
	sockp->local_rx_address.sin_addr.s_addr = inet_addr(opt->local_ip);
	sockp->local_rx_address.sin_port = htons(opt->local_rx_port);

    // Bind the socket with the server address
	if(bind(sockp->rxfd, (const struct sockaddr *)&(sockp->local_rx_address), sizeof(sockp->local_rx_address)) < 0 )
	{
		std::cerr << "rx bind failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Filling server informations
	sockp->local_tx_address.sin_family = AF_INET; // IPv4
	sockp->local_tx_address.sin_addr.s_addr = inet_addr(opt->local_ip);
	sockp->local_tx_address.sin_port = htons(opt->local_tx_port);

    // Bind the socket with the server address
	if(bind(sockp->txfd, (const struct sockaddr *)&(sockp->local_tx_address), sizeof(sockp->local_tx_address)) < 0 )
	{
		std::cerr << "tx bind failed" << std::endl;
		exit(EXIT_FAILURE);
	}

    // Filling client informations
	sockp->remote_tx_address.sin_family = AF_INET; // IPv4
	sockp->remote_tx_address.sin_addr.s_addr = inet_addr(opt->remote_ip);
	sockp->remote_tx_address.sin_port = htons(opt->remote_tx_port);

    // Set socket timeout
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    setsockopt(sockp->rxfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
}

/**
 * @brief Reading float array form UDP socket pair.
 * @note Data decoded as raw single-precision floating point data array (little endian)
 * 
 * @param[inout] sockp     : UDP socket pair handler for Linux machine
 * @param[out]   array     : Received float array
 * @param[in]    array_len : Array length (number of elements)
 */
void UDP_SocketPair_ReceiveFloatArray(struct UDP_SocketPair* sockp, float* array, unsigned int array_len)
{
	char buffer[1024] = { 0, };
	int len = sizeof(sockp->remote_rx_address);
	recvfrom(sockp->rxfd, (char*)buffer, sizeof(buffer), 0, (struct sockaddr*)&(sockp->remote_rx_address), (socklen_t*)&len);

    std::memcpy((char*)array, buffer, array_len*sizeof(float));
}

/**
 * @brief Sending float array to UDP socket pair.
 * @note Data decoded as ASCII character string with comma separated values.
 * 
 * @param[inout] sockp     : UDP socket par handler for Linux machine
 * @param[in]    array     : Sended float array
 * @param[in]    array_len : Array length (number of elements)
 */
void UDP_SocketPair_SendFloatArray(struct UDP_SocketPair* sockp, float* array, unsigned int array_len)
{
	char buffer[1024] = { 0, };
    std::memcpy(buffer, (char*)array, array_len*sizeof(float));

	sendto(sockp->txfd, (const char*)buffer, array_len*sizeof(float), 0, (const struct sockaddr*)&(sockp->remote_tx_address), sizeof(sockp->remote_tx_address));
}
