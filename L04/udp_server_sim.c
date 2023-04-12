/**
  ******************************************************************************
  * @file    udp_server_sim.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    12-Apr-2023
  * @brief   Simple UDP server with main loop for Simulink model
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
#define SERVER_IP 		 "192.168.1.248"
#define CLIENT_IP 		 "192.168.1.181"

#define TxPORT	 20001	   // UDP Receive Blok 'Remote Port' 
#define RxPORT   20002 	   // UDP Send Blok 'Remote Port' 
#define CLIENT_PORT 25000  // UDP Receive Blok 'Local Port' 

#define MAXLINE  1024

#define SAMPLE_TIME 50 // [ms]

/* Public variables ----------------------------------------------------------*/
DSOS_HandleTypeDef sys;
double u = 0.0, y = 0.0;
double flag = 1.0;

int rx_sockfd, tx_sockfd;
struct sockaddr_in rx_servaddr, tx_servaddr, rx_cliaddr, tx_cliaddr;

/* Private function ----------------------------------------------------------*/

/**
 * @brief Reverses the byte order of an 8-byte variable.
 * @param[in/out] value_ptr A pointer to the uint64_t variable whose byte order should be reversed.
 * @return None.
 */
void reverse_bytes(uint64_t *value_ptr) {
    uint64_t value = *value_ptr;
    uint64_t result = 0;
    int i;

    for (i = 0; i < 8; i++) {
        result = (result << 8) | (value & 0xFF);
        value >>= 8;
    }

    *value_ptr = result;
}

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
		y = DSOS_GetOutput(&sys, u);
    	delay_ms(SAMPLE_TIME);

		if(iteration % 10 == 0)
		{
			char response[64];
			memcpy(&response[0], &y, sizeof(y));
			memcpy(&response[8], &flag, sizeof(flag));

			printf("Server message: [%02x%02x%02x%02x%02x%02x%02x%02x] %lf\n", response[0], response[1], response[2], response[3], response[4], response[5], response[6], response[7], y);

			int len = sizeof(tx_cliaddr);
			sendto(tx_sockfd, (const char*)response, 2*sizeof(double), 0, (const struct sockaddr*)&tx_cliaddr, len);
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
	if((rx_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		perror("rx socket creation failed");
		exit(EXIT_FAILURE);
	}
	if((tx_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		perror("tx socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&tx_servaddr, 0, sizeof(tx_servaddr));
	memset(&tx_cliaddr, 0, sizeof(tx_cliaddr));
	memset(&rx_servaddr, 0, sizeof(rx_servaddr));
	memset(&rx_cliaddr, 0, sizeof(rx_cliaddr));
	
	// Filling server information
	rx_servaddr.sin_family = AF_INET; // IPv4
	rx_servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	rx_servaddr.sin_port = htons(RxPORT);

	tx_servaddr.sin_family = AF_INET; // IPv4
	tx_servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	tx_servaddr.sin_port = htons(TxPORT);
	
	// Bind the socket with the server address
	if(bind(rx_sockfd, (const struct sockaddr *)&rx_servaddr, sizeof(rx_servaddr)) < 0 )
	{
		perror("rx bind failed");
		exit(EXIT_FAILURE);
	}

	if(bind(tx_sockfd, (const struct sockaddr *)&tx_servaddr, sizeof(tx_servaddr)) < 0 )
	{
		perror("tx bind failed");
		exit(EXIT_FAILURE);
	}

	// Fillint client infromation
	tx_cliaddr.sin_family = AF_INET; // IPv4
	tx_cliaddr.sin_addr.s_addr = inet_addr(CLIENT_IP);
	tx_cliaddr.sin_port = htons(CLIENT_PORT);

    // Initialize dynamic system emulation
	uint64_t coeffs[] = {	
		0x3FFFE62F08D2DDB4,   
		0xBFEFCCB099E06B4F,   
		0x3ED4A20EABF99825,  
		0x3EE4A20EABF99825,   
		0x3ED4A20EABF99825
	};	

	DSOS_Init(&sys, (double*)coeffs);

    // Create a new thread
	pthread_t ptid;
	pthread_create(&ptid, NULL, &control_loop, NULL);
	
	printf("[C] UDP server up and listening.\n");
	while(1)
	{
		// Receive from socket
		int len = sizeof(rx_cliaddr);
		recvfrom(rx_sockfd, (char*)buffer, MAXLINE, 0, (struct sockaddr*)&rx_cliaddr, (socklen_t*)&len);

		memcpy(&u, buffer, sizeof(u));
		reverse_bytes((uint64_t*)&u);
		
		printf("Client message: [%02x%02x%02x%02x%02x%02x%02x%02x] %lf\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7], u);

		memset(buffer, '\0', sizeof(u));	
	}
	
	return 0;
}
