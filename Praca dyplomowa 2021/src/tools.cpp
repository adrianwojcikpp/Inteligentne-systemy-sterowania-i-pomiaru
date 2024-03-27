/**
 * @file tools.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
#include <iostream>
#include <string.h>
#include "../inc/tools.h"

void print_log_time()
{
    time_t my_time = time(NULL); 
    printf("[%s] ", strtok(ctime(&my_time), "\n"));
}

long start_log(char const *path)
{
    fflush(stdout);
    int fd;
    fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        perror("open failed");
        return -1;
    }
    int fd2 = dup(STDOUT_FILENO);
    if (dup2(fd, 1) == -1)
    {
        perror("dup2 failed");
        return -1;
    }
    print_log_time();
    return ((fd) << (8*2)) + fd2;
}

void stop_log(long fd12)
{
    int fd =(int)(fd12 >>(8*2));
    int fd2 =(int)(fd12 & 0xffff);
    close(fd);
    if (fd2 != -1)
    {
        fflush(stdout);
        if (dup2(fd2, STDOUT_FILENO) < 0)
        {
            perror("Failed to reinstate standard output\n");
            return;
        }
        close(fd2);
    }
    return;
}