#include <stdio.h>
#include <stdlib.h> // exit()
#include <string.h> // memset()
#include <arpa/inet.h> // inet_pton()
#include <sys/socket.h>
#include <iostream>
#include <fstream>
#include <string>

#define SERVER_PORT 8888
#define SERVER_IP "192.168.56.102"

using namespace std;

int main()
{
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
   
    const int socket_ = socket( AF_INET, SOCK_DGRAM, 0 );
    if(( socket_ ) < 0 )
    {
        perror( "socket() ERROR" );
        exit( 2 );
    }
   
    char buffer[ 4096 ] = { };
   
    socklen_t len = sizeof( server );
    if( bind( socket_,( struct sockaddr * ) & server, len ) < 0 )
    {
        perror( "bind() ERROR" );
        exit( 3 );
    }
   
    while( 1 )
    {
        struct sockaddr_in client = { };
       
        memset( buffer, 0, sizeof( buffer ) );
       
        printf( "Waiting for connection...\n" );
        if( recvfrom( socket_, buffer, sizeof( buffer ), 0,( struct sockaddr * ) & client, & len ) < 0 )
        {
            perror( "recvfrom() ERROR" );
            exit( 4 );
        }
        printf( "|Message from client|: %s \n", buffer );
       
        char buffer_ip[ 128 ] = { };
        printf( "|Client ip: %s port: %d|\n", inet_ntop( AF_INET, & client.sin_addr, buffer_ip, sizeof( buffer_ip ) ), ntohs( client.sin_port ) );
       //////////////
        fstream uchwyt; 
        uchwyt.open("sine_wave.csv"); 
        string linia;
        do
        {
            getline(uchwyt, linia); 
            const char * liniaChar = linia.c_str(); 
            strncpy( buffer, liniaChar, sizeof( buffer ) );   
            if( sendto( socket_, buffer, strlen( buffer ), 0,( struct sockaddr * ) & client, len ) < 0 )
            {
                perror( "sendto() ERROR" );
                exit( 5 );
            }
        }
        while(linia != ""); 
        uchwyt.close(); 

       //////////////
        
    }
   
    shutdown( socket_, SHUT_RDWR );
}

//gcc main.cpp -lstdc++ -o f
