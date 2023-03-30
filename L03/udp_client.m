%% UDP CLIENT

%%% File info
%
% ************************************************************************
%
%  @file    udp_client.m
%  @author  Adrian Wojcik    adrian.wojcik@put.poznan.pl
%  @version V1.0
%  @date    29-Mar-2022
%  @brief   Simple UDP client with receive (acknowledge) callback
%
% ************************************************************************

%server_ip = '192.168.1.181'; % MATLAB server [PC]
server_ip = '192.168.1.248'; % C / Python server [RPi]
server_port = 20000;

udp_client_port = udpport("datagram","IPV4");
configureCallback(udp_client_port,"datagram", 1, @clientCallback);

udp_send = @(data)( write(udp_client_port, uint8(data), server_ip, server_port) );

udp_send('Hello form [MATLAB] client.');