/**
 * @file tools.h
 * @author Jakub Walkowski
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef INC_TOOLS_H_
#define INC_TOOLS_H_

#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
#include <iostream>
#include <string.h>

#define LOG_PATH "/var/log/screwspin/log"

/**
 * @brief Print actual server time
 * 
 */
void print_log_time();
/**
 * @brief Start printing to log file
 * 
 * @param path Path to log file
 * @return long two fd int
 */
long start_log(char const *path);
/**
 * @brief Stop printing to log file
 * 
 * @param fd12 long two int fd
 */
void stop_log(long fd12);
#endif /* INC_TOOLS_H_ */