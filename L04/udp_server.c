/**
  ******************************************************************************
  * @file    udp_server.cpp
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    29-Mar-2022
  * @brief   Simple UDP server with main loop
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
int nanosleep(const struct timespec *req, struct timespec *rem);
#include <errno.h>

#include "dsos.h" // Simple second order section implementation

/* Define --------------------------------------------------------------------*/
#define IP 		 "192.168.0.25"
#define PORT	 20000
#define MAXLINE  1024

#define SAMPLE_TIME 50 // [ms]

/* Public variables ----------------------------------------------------------*/
struct dsos sys;
double u = 0.0, y = 0.0;

int sockfd;
struct sockaddr_in servaddr, cliaddr;

/* Private function ----------------------------------------------------------*/
/**
  * @brief Standard delay function based on 'nanosleep'
  * @param[in] msec : delay time in millisecond 
  * @retval    0 if success 
  *         != 0 otherwise
  */
int delay_ms(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

/**
  * @brief The application control loop - thread with fixed delay time.
  * @param[in/out] arg : input arguments.
  * @retval None
  */
void* control_loop(void* arg)
{
	uint64_t iteration = 0;
	while(1)
	{
		y = lsim_step(&sys, u);
    	delay_ms(SAMPLE_TIME);

		if(iteration % 10 == 0)
		{
			char response[64];
			sprintf(response, "u = %.6lf, y = %.6lf", u, y);
			puts(response);
			int len = sizeof(cliaddr);
			sendto(sockfd, (const char*)response, strlen(response), 0, (const struct sockaddr*)&cliaddr, len);
		}

		iteration++;
	}
}

/* Main function -------------------------------------------------------------*/

/**
  * @brief The application entry point.
  * @param[in] argc : argument count; number of command-line arguments passed 
  *                   by the user including the name of the program.
  * @param[in] argv : argument vector; character pointers (C-strings) listing 
  *                   all the arguments.
  * @retval 0 
  */
int main(int argc, char* argv[])
{
	char buffer[MAXLINE] = {0,};
	char hello[] = "Hello from [C] server";
	
	// Creating socket file descriptor
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = inet_addr(IP);;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if(bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

    // Initialize dynamic system emulation
	uint64_t coeffs[] = {	
							0x3FFFE62F08D2DDB4,   
							0xBFEFCCB099E06B4F,   
							0x3ED4A20EABF99825,  
							0x3EE4A20EABF99825,   
							0x3ED4A20EABF99825
						};	

	dsos_init(&sys, (double*)coeffs);

    // Create a new thread
	pthread_t ptid;
	pthread_create(&ptid, NULL, &control_loop, NULL);
	
	printf("[C] UDP server up and listening.\n");
	while(1)
	{
		// Receive from socket
		int len = sizeof(cliaddr);
		recvfrom(sockfd, (char*)buffer, MAXLINE, 0, (struct sockaddr*)&cliaddr, (socklen_t*)&len);
		printf("Client message: %s\n", buffer);

		// Parse buffer
		sscanf((char*)buffer, "%lf", &u);

		// Clear buffer 
		memset(buffer, '\0', strlen(buffer));
		
		// Send to socket
		sendto(sockfd, (const char *)hello, strlen(hello), 0, (const struct sockaddr*)&cliaddr, len);
		printf("Response sent.\n");
	}
	
	return 0;
}
