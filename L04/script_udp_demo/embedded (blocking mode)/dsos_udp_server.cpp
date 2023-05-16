/**
  ******************************************************************************
  * @file    udp_socket_util.cpp
  * @author  AW         Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 May 2023
  * @brief   Digital second-order-system emulation with UDP communication
  * @note    USE WITH MATLAB SCRIPT
  * 
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
// standard C++ library
#include <iostream>
#include <iomanip>
// user headers
#include "udp_socket_util.h" // UDP socket utility
#include "time_util.h"       // Time utility (delay_ms)
#include "dsos.h"            // Discreate second-order-system

/* Private define ------------------------------------------------------------*/
#define DEFAULT_IP  "172.27.229.191"
#define DEFAULT_PORT 20000

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
    // Initialize dynamic system emulation
    DSOS_HandleTypeDef sys; 
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
    struct UDP_Socket sock;
    UDP_Socket_Init(&sock, &opt);

    /* Main loop */
	uint64_t iteration = 0;
    float u = 0.0f; // Input signal
    float y = 0.0f; // Output signal 
    const unsigned int SAMPLE_TIME = 50; // ms

	while(1)
	{
        // Receive control signal
        UDP_Socket_ReceiveFloatArray(&sock, &u, 1);

        // Read system response 
		y = DSOS_GetOutput(&sys, u);

		//if(iteration % 10 == 0) 
        {

            // Send system response 
            float txData[] = { timestamp_us(), u, y };
            UDP_Socket_SendFloatArray(&sock, txData, sizeof(txData)/sizeof(float));

            //std::cout << "t = " <<  std::setw(12) << std::right << (int)txData[0] << " us, ";
            //std::cout << "u = " << u << ", y = " << y << std::endl;

        }

        // Wait SAMPLE_TIME milliseconds 
    	delay_ms(SAMPLE_TIME);

		iteration++;
    }

    return 0;
}