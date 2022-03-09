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

#define MAX_MSG_LEN 4096
#define SERWER_PORT_S 8888
#define SERWER_PORT_R 8889
#define SERWER_IP "192.168.0.15"
#define MAX_CONNECTION 10

std::mutex uart_mtx;
int iii = 0;
int &oldSpeed = iii;

void sending(int, UART, int &);
void receiving(int, UART, int &);
void server_sending(UART u);
void server_recev(UART u);
void checkForErrors(UART u);
void Init_ScreSpin(UART u);
int main()
{
    //Init screwspin
    iii = 0;
    UART uart;
    uart.baud = 9600;

    UART uart2;
    uart2.baud = 9600;

    int as5600;
    AS5600_Init(&as5600);

    std::thread sending_thread(server_sending, uart);
    std::thread receiving_thread(server_recev, uart2);
    //std::thread error_check_thread(checkForErrors, uart2);
    Init_ScreSpin(uart);
    while (1)
    {
        sending_thread.join();
        receiving_thread.join();
        //error_check_thread.join();
    }
}

void Init_ScreSpin(UART u)
{
    Frame f, f2;

    //SetMotorRefSpeed(2000, 1, u, &f2);
    ExeRampSpeed(1,u,1000,2000,&f2);
    StartMotor(1, u, &f);
}

void sending(int soc, UART u, int &last)
{

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    Frame f;
    //printf("Przed registry \n");
    uart_mtx.lock();
    checkForErrors(u);
    GetRegistry(STEVAL_REGISTERS::SPEED_MEAS, STEVAL_REGISTERS_LEN::GET, 1, u, &f);
    uart_mtx.unlock();
    int d = (int)convertRawAngleToDegrees(getRawAngle());

    if (f.payload == 0)
        return;
    int Amount[] = {f.data, d};
    if (send(soc, &Amount, sizeof(Amount), 0) <= 0)
    {
        perror("send() ERROR");
    }

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> ela = end - start;
    printf("Send Time: %f\n", ela.count());
}
void receiving(int soc, UART u, int &old)
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    double re;
    Frame f, f2;
    recv(soc, &re, sizeof(double), 0);
    printf("REEEEE: %f\n", re);
    uart_mtx.lock();
    //SetRegistry(STEVAL_REGISTERS::RAMP_DUR,STEVAL_REGISTERS_LEN::RAMP_DUR,1,u,(int)(abs((int)re-old)/5),&f2);
    //SetMotorRefSpeed((int)re, 1, u, &f);
    ExeRampSpeed(1,u,(int)(abs((int)re-old)),(int)re,&f);
    old = (int)re;
    uart_mtx.unlock();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> ela = end - start;
    printf("Receaving Time: %f\n", ela.count());
}
void server_sending(UART u)
{
    struct sockaddr_in serwer =
        {
            .sin_family = AF_INET,
            .sin_port = htons(SERWER_PORT_S)};
    if (inet_pton(AF_INET, SERWER_IP, &serwer.sin_addr) <= 0)
    {
        perror("inet_pton() ERROR");
        exit(1);
    }

    const int socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ < 0)
    {
        perror("socket() ERROR");
        exit(2);
    }

    socklen_t len = sizeof(serwer);
    if (bind(socket_, (struct sockaddr *)&serwer, len) < 0)
    {
        perror("bind() ERROR");
        exit(3);
    }

    if (listen(socket_, MAX_CONNECTION) < 0)
    {
        perror("listen() ERROR");
        exit(4);
    }

    printf("Server send waiting for connection...\n");

    struct sockaddr_in client = {};
    int clientSocket = accept(socket_, (struct sockaddr *)&client, &len);
    if (clientSocket < 0)
    {
        perror("accept() ERROR");
    }
    int last = 0;
    while (1)
    {
        sending(clientSocket, u, last);
    }
    shutdown(socket_, SHUT_RDWR);
}
void server_recev(UART u)
{
    struct sockaddr_in serwer =
        {
            .sin_family = AF_INET,
            .sin_port = htons(SERWER_PORT_R)};
    if (inet_pton(AF_INET, SERWER_IP, &serwer.sin_addr) <= 0)
    {
        perror("inet_pton() ERROR");
        exit(1);
    }

    const int socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ < 0)
    {
        perror("socket() ERROR");
        exit(2);
    }

    socklen_t len = sizeof(serwer);
    if (bind(socket_, (struct sockaddr *)&serwer, len) < 0)
    {
        perror("bind() ERROR");
        exit(3);
    }

    if (listen(socket_, MAX_CONNECTION) < 0)
    {
        perror("listen() ERROR");
        exit(4);
    }

    printf("Server recev waiting for connection...\n");

    struct sockaddr_in client = {};
    int clientSocket = accept(socket_, (struct sockaddr *)&client, &len);
    if (clientSocket < 0)
    {
        perror("accept() ERROR");
    }
    int i = 2000;
    while (1)
    {
        if (i > 3000)
            i = 2000;
        receiving(clientSocket, u, oldSpeed);
    }
    shutdown(socket_, SHUT_RDWR);
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
//   g++ src/tools.cpp src/registers.cpp src/AS5600.cpp src/uartSteval.cpp tcp_s.cpp -lwiringPi -lpthread  -o server
