#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "udp_parse_args.h"

#define IP4_STR_MAX_LEN 16

void parse_args(int argc, char* argv[], struct argopt* opt)
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
                    fprintf(stderr, "IP address too long\n");
                    exit(EXIT_FAILURE);
                }
                memcpy(opt->ip, optarg, strlen(optarg));
                break;
            case '?':
            default:
                fprintf(stderr, "Usage: %s [-p port] [-i ip]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        fprintf(stderr, "Unexpected arguments: ");
        while (optind < argc) {
            fprintf(stderr, "%s ", argv[optind++]);
        }
        fprintf(stderr, "\nUsage: %s [-p port] [-i ip]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

