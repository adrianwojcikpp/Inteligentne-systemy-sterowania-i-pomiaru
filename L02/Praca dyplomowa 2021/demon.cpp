#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <cstdlib>
#include <fcntl.h>
#include <ctype.h>
#include <iostream>
#include "./inc/udp_s.h"
static void szatan()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* Set new file permissions */
    umask(0);

    // otwieramy devnulla
    int devnull = open("/dev/null", O_RDWR);
 
    // zamykamy standardowe strumienie
    close(0);
    close(1);
    close(2);
 
    dup2(devnull, 0);
    dup2(devnull, 1);
    dup2(devnull, 2);
 
    close(devnull);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }

    /* Open the log file */
    
}


int main()
{
    szatan();
    openlog("/var/log/screwspin/screwspin_demon", LOG_PID, LOG_DAEMON);
    syslog (LOG_NOTICE, "Screwspin daemon started.");
    run();
    syslog (LOG_NOTICE, "Screwspin daemon terminated.");
    closelog();
    
    return EXIT_SUCCESS;
}