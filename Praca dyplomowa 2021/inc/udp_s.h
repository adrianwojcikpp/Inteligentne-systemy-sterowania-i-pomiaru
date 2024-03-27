
#ifndef INC_UDP_S_H_
#define INC_UDP_S_H_

#include "./uartSteval.h"
int run();
/**
 * @brief UDP server star
 * 
 * @param u UART object for uart communication
 */
void server(UART u);
/**
 * @brief UDP sending process
 * 
 * @param socket_ socket handle
 * @param len socket lenght
 * @param u UART object for uart communication
 */
void send_data(const int socket_, socklen_t len, UART u);
/**
 * @brief UDP receiving process
 * 
 * @param socket_ socket handle
 * @param len socket lenght
 * @param u UART object for communiaction
 */
void recv_data(const int socket_, socklen_t len, UART u);
/**
 * @brief Check for errors in Steval in register STEVAL_REGISTERS::FLAGS
 * 
 * @param u UART object for communication
 */
void checkForErrors(UART u);
/**
 * @brief Start motor and set default ramp speed
 * 
 * @param u UART object for uart communication
 */
void Init_ScreSpin(UART u);
const char *getEthIp();
#endif /* INC_UDP_S_H_ */