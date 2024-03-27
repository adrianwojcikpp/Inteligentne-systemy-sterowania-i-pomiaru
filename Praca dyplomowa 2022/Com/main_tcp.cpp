#include <stdio.h>
#include <stdlib.h> // exit()
#include <string.h> // memset()
#include <arpa/inet.h> // inet_pton()
#include <sys/socket.h>
#include <iostream>
#include <fstream>
#include <string>
#include "AS5600.h"
#include <wiringPi.h>
#include <unistd.h>
#include "uartSteval.h"
#include <ctype.h>
#include <math.h>

#define SERVER_PORT 6788
#define SERVER_IP "192.168.0.106" 
#define MAX_CONNECTION 10
using namespace std;


string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}


float normalize( const float value, const float start, const float end ) 
{
  const float width       = end - start   ;   // 
  const float offsetValue = value - start ;   // value relative to 0

  return ( offsetValue - ( floor( offsetValue / width ) * width ) ) + start ;
  // + start to reset back to start of original range
}

const int ScopeOutput= 25;

int main()
{

    // ENCODER
    int as5600;
    AS5600_Init(&as5600);
    //
    
    //GPIO
    wiringPiSetup();
    pinMode(25,OUTPUT);
    //

    // MOTOR
    UART uart;
    uart.baud = 38400;
    int speed=0;
    Frame f;
    //

    StartMotor(1,uart,&f);
    //
    struct sockaddr_in server =
    {
        .sin_family = AF_INET,
        .sin_port = htons( SERVER_PORT )
    };
    if( inet_pton( AF_INET, SERVER_IP, & server.sin_addr ) <= 0 )
    {
        perror( "inet_pton() ERROR" );
        exit( 1 );
    }
   
    const int socket_ = socket( AF_INET, SOCK_STREAM, 0 );
    if(( socket_ ) < 0 )
    {
        perror( "socket() ERROR" );
        exit( 2 );
    }
   
    char buffer[ 7 ] = { };
    char buffer2[ 4096] = {};
   
    socklen_t len = sizeof( server );
    if( bind( socket_,( struct sockaddr * ) & server, len ) < 0 )
    {
        perror( "bind() ERROR" );
        exit( 3 );
    }
   
    if( listen( socket_, MAX_CONNECTION ) < 0 )
    {
        perror( "listen() ERROR" );
        exit( 4 );
    }
    
    struct sockaddr_in client = { };
    string sUDPRetVal = "0.00000";
    int UDPRetVal = 0;
       
    
 
        //printf( "|Message from client|: %s \n", buffer );

     const int clientSocket = accept( socket_,( struct sockaddr * ) & client, & len );
        if( clientSocket < 0 )
            {
                perror( "accept() ERROR" );
            }

    while( 1 )
    {   
       

        memset( buffer, 0, sizeof( buffer ) );
        memset( buffer2, 0, sizeof( buffer2 ) );

        //////////////
        // ENKODER
        float unscaled_degrees = convertRawAngleToDegrees(getRawAngle());
        float degrees = normalize(unscaled_degrees,-180,180);
		//
        string s = to_string(degrees);
        const char *liniaChar = s.c_str();
        strncpy(buffer, liniaChar, sizeof(buffer));
        std::cout<< "BUFOR 1: " <<buffer << std::endl;
        if (send( clientSocket, buffer, strlen( buffer ), 0 ) <= 0)
        {
            perror("sendto() ERROR");
            exit(5);
        }
        //SCOPE
        digitalWrite(ScopeOutput, HIGH);
        //
        if (recv( clientSocket, buffer2, sizeof( buffer2 ), 0 ) <= 0)
        {
            perror("recvfrom() ERROR");
            exit(4);
        }
        //SCOPE
        digitalWrite(ScopeOutput, LOW);
        //
        std::cout<<buffer2 <<std::endl;
        sUDPRetVal = convertToString(buffer, 4); //TODO !
        speed = stoi(sUDPRetVal);

        printf("\n%d", speed);
        SetMotorRefSpeed(speed, 1, uart, &f);
        
         usleep(50);

        //////////////
    }
    
    shutdown( socket_, SHUT_RDWR );
}

//g++ main_tcp.cpp uartSteval.cpp uartSteval.h registers.h AS5600.cpp AS5600.h -lstdc++ -lwiringPi -o a
