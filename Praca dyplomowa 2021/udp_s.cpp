/**
 * @file udp_s.cpp
 * @author Jakub Walkowski
 * @brief 
 * @version 0.1
 * @date 2021-02-03
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <wiringPi.h>
#include <iostream>
#include "./inc/uartSteval.h"
#include "./inc/AS5600.h"
#include <unistd.h>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <cmath>

#include <sys/ioctl.h>
#include <net/if.h>

#include <unistd.h>

#include <arpa/inet.h>
#include <condition_variable>
#include "./inc/udp_s.h"
#include "./inc/tools.h"
#include "./inc/AS5600.h"


#define S_SERWER_PORT 8888
#define R_SERWER_PORT 8889
#define C_PORT 22000
#define UART_BAUD  38400
#define UART_DEVICE "/dev/ttyACM0"


struct sockaddr_in client = { };
bool clientIsSet = false;
int old;
std::mutex mtx;
std::mutex uart_mtx;
std::condition_variable cv_client;
const char* SERWER_IP;



int main()
{
    UART uart;
    uart.baud = UART_BAUD;
    uart.device = UART_DEVICE;
    int as5600;
    AS5600_Init(&as5600);
    printf("Serwer started\n");
    SERWER_IP = getEthIp();
    printf("Local eth ip:%s",SERWER_IP);
    Init_ScreSpin(uart);
    server(uart);
    return 0;
}

void server(UART u)
{
    #pragma region Init serwer
    struct sockaddr_in serwer =
    {
        .sin_family = AF_INET,
        .sin_port = htons( R_SERWER_PORT )
    };
    if( inet_pton( AF_INET, SERWER_IP, & serwer.sin_addr ) <= 0 )
    {
        long l = start_log(LOG_PATH);
        printf( "[SERVER ERROR] inet_pton() ERROR " );
        printf("%s\n",strerror(errno));
        stop_log(l);
        exit( 1 );
    }
   
    const int socket_ = socket( AF_INET, SOCK_DGRAM, 0 );
    if(( socket_ ) < 0 )
    {
        long l = start_log(LOG_PATH);
        printf( "[SERVER ERROR] socket() ERROR " );
        printf("%s\n",strerror(errno));
        stop_log(l);
        exit( 2 );
    }
   
    socklen_t len = sizeof( serwer );
    if( bind( socket_,( struct sockaddr * ) & serwer, len ) < 0 )
    {
        long l = start_log(LOG_PATH);
        printf( "[SERVER ERROR] bind() ERROR " );
        printf("%s\n",strerror(errno));
        stop_log(l);
        exit( 3 );
    }
    #pragma endregion 
    
    std::thread sending_thread(send_data,socket_,len, u);
    std::thread receiving_thread(recv_data,socket_,len, u);
    
    sending_thread.join();
    receiving_thread.join();
    
    shutdown( socket_, SHUT_RDWR );
}
void recv_data(const int socket_, socklen_t len, UART u)
{
    while (1)
    {
        double re;
        Frame f,f2;
        if (recvfrom(socket_, &re, sizeof(double), 0, (struct sockaddr *)&client, &len) < 0)
        {
            long l = start_log(LOG_PATH);
            printf("[SERVER ERROR] recvfrom() ERROR ");
            printf("%s\n", strerror(errno));
            stop_log(l);
            exit(4);
        }
        uart_mtx.lock();
        StartMotor(1,u,&f2);
        ExeRampSpeed(1,u,(int)(abs((int)re-old)),(int)re,&f);
        old = (int)re;
        uart_mtx.unlock();
        clientIsSet = true;
        cv_client.notify_one();
        //printf("|Message from client|: %f \n", re);

        char buffer_ip[128] = {};
        //printf("|Client ip: %s port: %d|\n", inet_ntop(AF_INET, &client.sin_addr, buffer_ip, sizeof(buffer_ip)), ntohs(client.sin_port));
    }
}
void send_data(const int socket_, socklen_t len, UART u)
{
    while (1)
    {
        Frame f;
        uart_mtx.lock();
        checkForErrors(u);
        GetRegistry(STEVAL_REGISTERS::SPEED_MEAS, STEVAL_REGISTERS_LEN::GET, 1, u, &f);
        uart_mtx.unlock();
        float d = convertRawAngleToDegrees(getRawAngle());
        
        // if (f.payload == 0)
        //     continue;
        int dd = (int)d;
        if(dd>180)
            dd= dd-360;
        
        int Amount[] = {(int)f.data, dd};
        
        std::unique_lock<std::mutex> ul(mtx);
        cv_client.wait(ul, [] { return clientIsSet; });
        client.sin_port = htons( C_PORT );
        //printf("SENDING\n");
        if (sendto(socket_, &Amount, sizeof(Amount), 0, (struct sockaddr *)&client, len) < 0)
        {
            long l = start_log(LOG_PATH);
            printf("[SERVER ERROR] sendto() ERROR ");
            printf("%s\n",strerror(errno));
            stop_log(l);
        }
    }
}
void Init_ScreSpin(UART u)
{
    Frame f, f2;
    ExeRampSpeed(1,u,5000,1000,&f2);
    StartMotor(1, u, &f);
}
void checkForErrors(UART u)
{

    //delay(5000);
    Frame f, f2, f3;
    GetRegistry(STEVAL_REGISTERS::FLAGS, STEVAL_REGISTERS_LEN::GET, 1, u, &f);
    long fd;
    switch ((int)f.data)
    {
    case 2:
        fd = start_log(LOG_PATH);
        printf("[ERROR] Over voltage\n");
        stop_log(fd);
        return;
    case 32:
        fd = start_log(LOG_PATH);
        printf("[ERROR] SpeedFeedback\n");
        stop_log(fd);
        FaultAck(1, u, &f2);
        StartMotor(1, u, &f3);
        return;
    default:
        return;
    }
}
const char *getEthIp()
{
    int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    //Get IPv4 IP address
    ifr.ifr_addr.sa_family = AF_INET;
    //Get "eth0"
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ - 1);
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);
    return inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
}
// gcc server.c -g -Wall -o server && ./server
//g++ src/tools.cpp src/registers.cpp src/AS5600.cpp src/uartSteval.cpp udp_s.cpp -lwiringPi -lpthread  -o serverUDP