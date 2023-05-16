/**
  ******************************************************************************
  * @file    udp_socket_util.h
  * @author  AW         Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 May 2023
  * @brief   Simple UDP socket utility: sending and receiving float data
  * 
  ******************************************************************************
  */

#ifndef __UDP_SOCKET_UTIL_H__
#define __UDP_SOCKET_UTIL_H__

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
    int port;        /**< Port number */
    char ip[32];     /**< IP address in dotted-decimal notation */
};

/**
 * @brief UDP socket handler for Linux machine
 */
struct UDP_Socket {
    struct sockaddr_in local_address;   /**< Local address */
    struct sockaddr_in remote_address;  /**< Remote address */
    int fd; /**< Socket file descriptor */
};

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Parse command-line arguments using getopt_long
 *
 * @param[in]  argc : Number of arguments
 * @param[in]  argv : Array of argument strings
 * @param[out] opt  : Pointer to struct argopt to fill with parsed options
 */
void UDP_Socket_ParseArgs(int argc, char* argv[], struct argopt* opt);

/**
 * @brief UDP socket initialization: binding to given local port
 * 
 * @param[inout] sock : UDP socket handler for Linux machine
 * @param[in]    opt  : UDP socket options (local port and IP address)
 */
void UDP_Socket_Init(struct UDP_Socket* sock, struct argopt* opt);

/**
 * @brief Reading float array form UDP socket.
 * @note Data decoded as ASCII character string with comma separated values.
 * 
 * @param[inout] sock      : UDP socket handler for Linux machine
 * @param[out]   array     : Received float array
 * @param[in]    array_len : Array length (number of elements)
 */
void UDP_Socket_ReceiveFloatArray(struct UDP_Socket* sock, float* array, unsigned int array_len);

/**
 * @brief Sending float array to UDP socket.
 * @note Data decoded as ASCII character string with comma separated values.
 * 
 * @param[inout] sock      : UDP socket handler for Linux machine
 * @param[in]    array     : Sended float array
 * @param[in]    array_len : Array length (number of elements)
 */
void UDP_Socket_SendFloatArray(struct UDP_Socket* sock, float* array, unsigned int array_len);

#endif // __UDP_SOCKET_UTIL_H__
