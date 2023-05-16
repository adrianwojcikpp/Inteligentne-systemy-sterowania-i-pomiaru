/**
  ******************************************************************************
  * @file    udp_socket_pair_util.h
  * @author  AW         Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 May 2023
  * @brief   Simple UDP socket pair utility: sending and receiving float data
  * 
  ******************************************************************************
  */

#ifndef __UDP_SOCKET_PAIR_UTIL_H__
#define __UDP_SOCKET_PAIR_UTIL_H__

/* Public includes -----------------------------------------------------------*/
// standard C++ library
#include <iostream>
// GNU C library
#include <sys/socket.h>
#include <arpa/inet.h>

/* Public typedef ------------------------------------------------------------*/
/**
 * @brief Command-line argument options
 */
struct argopt {
    int local_tx_port;  /**< Local port number for transmission  */
    int local_rx_port;  /**< Local port number for receiving  */
    int remote_tx_port; /**< Remote port number for transmission  */
    char local_ip[32];  /**< Local IP address in dotted-decimal notation */
    char remote_ip[32]; /**< Remote IP address in dotted-decimal notation */
};

/**
 * @brief UDP socket pair handler for Linux machine
 */
struct UDP_SocketPair {
    struct sockaddr_in local_tx_address; /**< Local address number for transmission  */
    struct sockaddr_in local_rx_address; /**< Local address number for receiving  */
    struct sockaddr_in remote_tx_address; /**< Remote address number for transmission  */
    struct sockaddr_in remote_rx_address; /**< Remote address number for receiving  */
    int txfd; /**< Transmission socket file descriptor */
    int rxfd; /**< Receiving socket file descriptor */
};

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Parse command-line arguments using getopt_long
 *
 * @param[in]  argc : Number of arguments
 * @param[in]  argv : Array of argument strings
 * @param[out] opt  : Pointer to struct argopt to fill with parsed options
 */
void UDP_SocketPair_ParseArgs(int argc, char* argv[], struct argopt* opt);

/**
 * @brief UDP socket pair initialization: binding to given local ports
 * 
 * @param[inout] sockp : UDP socket pair handler for Linux machine
 * @param[in]    opt   : UDP socket par options (local and remote ports and IP addresses)
 */
void UDP_SocketPair_Init(struct UDP_SocketPair* sockp, struct argopt* opt);
/**
 * @brief Reading float array form UDP socket pair.
 * @note Data decoded as raw single-precision floating point data array (little endian)
 * 
 * @param[inout] sockp     : UDP socket pair handler for Linux machine
 * @param[out]   array     : Received float array
 * @param[in]    array_len : Array length (number of elements)
 */
void UDP_SocketPair_ReceiveFloatArray(struct UDP_SocketPair* sockp, float* array, unsigned int array_len);

/**
 * @brief Sending float array to UDP socket pair.
 * @note Data decoded as ASCII character string with comma separated values.
 * 
 * @param[inout] sockp     : UDP socket par handler for Linux machine
 * @param[in]    array     : Sended float array
 * @param[in]    array_len : Array length (number of elements)
 */
void UDP_SocketPair_SendFloatArray(struct UDP_SocketPair* sockp, float* array, unsigned int array_len);

#endif // __UDP_SOCKET_PAIR_UTIL_H__
