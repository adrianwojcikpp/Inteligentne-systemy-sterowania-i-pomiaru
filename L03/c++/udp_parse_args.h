/**
  ******************************************************************************
  * @file    udp_parse_args.h
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date    28-Mar-2024
  * @brief   Simple UDP CLI app argument parsing
  *
  ******************************************************************************
  */

#ifndef UDP_PARSE_ARGS_H
#define UDP_PARSE_ARGS_H

/**
 * @brief Command-line argument options
 */
struct argopt {
    int port;        /**< Port number */
    char ip[32];     /**< IP address in dotted-decimal notation */
};

/**
 * @brief Parse command-line arguments using getopt_long
 *
 * @param argc Number of arguments
 * @param argv Array of argument strings
 * @param opt Pointer to struct argopt to fill with parsed options
 */
void udp_parse_args(int argc, char* argv[], struct argopt* opt);

#endif /* UDP_PARSE_ARGS_H */