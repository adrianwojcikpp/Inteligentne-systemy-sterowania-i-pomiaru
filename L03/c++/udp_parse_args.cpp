/**
  ******************************************************************************
  * @file    udp_parse_args.cpp
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date    28-Mar-2024
  * @brief   Simple UDP CLI app argument parsing
  *
  ******************************************************************************
  */

// C++ standard libraries
#include <cstdio>
#include <cstring>
#include <cstdlib>

// POSIX libraries
#include <getopt.h>

// Local files
#include "udp_parse_args.h"

#define IP4_STR_MAX_LEN 16

/**
 * @brief Parse command-line arguments using getopt_long
 *
 * @param argc Number of arguments
 * @param argv Array of argument strings
 * @param opt Pointer to struct argopt to fill with parsed options
 */
void udp_parse_args(int argc, char* argv[], struct argopt* opt)
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
                if (strlen(optarg) >= IP4_STR_MAX_LEN)
                {
                    std::fprintf(stderr, "IP address too long\n");
                    std::exit(EXIT_FAILURE);
                }
                std::memcpy(opt->ip, optarg, strlen(optarg));
                break;
            case '?':
            default:
                std::fprintf(stderr, "Usage: %s [-p port] [-i ip]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        std::fprintf(stderr, "Unexpected arguments: ");
        while (optind < argc) {
            std::fprintf(stderr, "%s ", argv[optind++]);
        }
        std::fprintf(stderr, "\nUsage: %s [-p port] [-i ip]\n", argv[0]);
        std::exit(EXIT_FAILURE);
    }
}

