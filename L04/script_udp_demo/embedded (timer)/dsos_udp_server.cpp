/**
  ******************************************************************************
  * @file    dsos_udp_server.cpp
  * @author  AW         Adrian.Wojcik@put.poznan.pl
  * @version 1.1
  * @date    10 May 2026
  * @brief   Digital second-order-system emulation with UDP communication
  * @note    USE WITH MATLAB SCRIPT
  * 
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
// standard C++ library
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
// user headers
#include "udp_socket_util.h" // UDP socket utility
#include "time_util.h"       // Time utility (delay_ms)
#include "dsos.h"            // Discreate second-order-system

/* Private define ------------------------------------------------------------*/
#define DEFAULT_IP  "192.168.137.118"
#define DEFAULT_PORT 20000

/* Private variables ---------------------------------------------------------*/
float u = 0.0f; // Input signal
float y = 0.0f; // Output signal 
const unsigned int SAMPLE_TIME = 50; // ms
struct UDP_Socket sock;

DSOS_HandleTypeDef sys; // Dynamic system emulation

static timer_t timerid; // Timer ID
uint64_t iteration = 0; // Iteration counter

/* Control loop  -------------------------------------------------------------*/
/**
  * @brief The application control loop - timer handler
  *  
  * @param[inout] arg : input arguments.
  */
void control_loop(int sig, siginfo_t *si, void *uc)
{
    y = DSOS_GetOutput(&sys, u);
    float txData[] = { timestamp_us(), u, y };
    UDP_Socket_SendFloatArray(&sock, txData, sizeof(txData)/sizeof(float));
    iteration++;
}

/* Main function -------------------------------------------------------------*/
/**
  * @brief The application entry point.
  * 
  * @param[in] argc : argument count; number of command-line arguments passed 
  *                   by the user including the name of the program.
  * @param[in] argv : argument vector; character pointers (C-strings) listing 
  *                   all the arguments.
  * @retval 0 
  */
int main(int argc, char* argv[])
{
    // Initialize dynamic system emulation
	uint64_t coeffs[] = {
        // MATLAB GENERATED VALUES	
		0x3FFFE62F08D2DDB4,   
		0xBFEFCCB099E06B4F,   
		0x3ED4A20EABF99825,  
		0x3EE4A20EABF99825,   
		0x3ED4A20EABF99825
	};	
	DSOS_Init(&sys, (double*)coeffs);

    // Read user options
    struct argopt opt = { DEFAULT_PORT, DEFAULT_IP };
	UDP_Socket_ParseArgs(argc, argv, &opt);

    // Create and bind UDP socket 
    UDP_Socket_Init(&sock, &opt);

    // Timer configuration
    struct sigaction sa;
    struct sigevent sev;
    struct itimerspec its;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = control_loop;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGRTMIN, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = &timerid;

    if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1) {
        perror("timer_create");
        return 1;
    }

    //> First expiration after SAMPLE_TIME ms, then every SAMPLE_TIME ms
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = SAMPLE_TIME * 1000000;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = SAMPLE_TIME * 1000000;

    if (timer_settime(timerid, 0, &its, NULL) == -1) {
        perror("timer_settime");
        return 1;
    }

    /* Main loop */
    while(1)
    {
        // Receive control signal
        UDP_Socket_ReceiveFloatArray(&sock, &u, 1);
    }

    return 0;
}