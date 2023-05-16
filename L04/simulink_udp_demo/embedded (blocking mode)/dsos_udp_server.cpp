/**
  ******************************************************************************
  * @file    udp_socket_util.cpp
  * @author  AW         Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 May 2023
  * @brief   Digital second-order-system emulation with UDP communication
  * @note    USE WITH SIMULINK MODEL
  * 
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
// standard C++ library
#include <iostream>
#include <iomanip>
// user headers
#include "udp_socket_pair_util.h" // UDP socket pair utility
#include "time_util.h"       // Time utility (delay_ms)
#include "dsos.h"            // Discreate second-order-system

/* Private define ------------------------------------------------------------*/
#define DEFAULT_LOCAL_IP   "172.27.229.191"
#define DEFAULT_REMOTE_IP  "172.27.224.1"

#define DEFAULT_LOCAL_TX_PORT	20001	// UDP Receive Blok 'Remote Port' 
#define DEFAULT_LOCAL_RX_PORT   20002 	// UDP Send Blok 'Remote Port' 
#define DEFAULT_REMOTE_TX_PORT  25000   // UDP Receive Blok 'Local Port' 

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
    DSOS_HandleTypeDef sys; // Dynamic system emulation
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
    struct argopt opt = { 
        DEFAULT_LOCAL_TX_PORT, 
        DEFAULT_LOCAL_RX_PORT, 
        DEFAULT_REMOTE_TX_PORT, 
        DEFAULT_LOCAL_IP, 
        DEFAULT_REMOTE_IP 
    };
	UDP_SocketPair_ParseArgs(argc, argv, &opt);

    // Create and bind UDP socket 
    struct UDP_SocketPair sockp; 
    UDP_SocketPair_Init(&sockp, &opt);

    /* Main loop */       
    float u = 0.0f; // Input signal
    float y = 0.0f; // Output signal 
    const unsigned int SAMPLE_TIME = 50; // ms

    while(1)
    {
        // Receive control signal
        UDP_SocketPair_ReceiveFloatArray(&sockp, &u, 1);

        // Read system resposne 
		y = DSOS_GetOutput(&sys, u);

        // Send system response 
		float txData[] = { timestamp_us(), u, y, 1.0f }; 
		UDP_SocketPair_SendFloatArray(&sockp, txData, sizeof(txData)/sizeof(float));

        // Wait SAMPLE_TIME milliseconds 
    	delay_ms(SAMPLE_TIME);
    }

    return 0;
}