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

server_ip = '172.27.229.191'; % C++ / Python server [RPi]
server_port = 20000;

udp_client_port = udpport("datagram","IPV4");
configureCallback(udp_client_port,"datagram", 1, @clientCallback);

udp_send = @(data)( write(udp_client_port, data, server_ip, server_port) );

udp_send("-a -b -c 100");