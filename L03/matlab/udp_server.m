%% UDP SERVER

%%% File info
%
% ************************************************************************
%
%  @file    udp_server.m
%  @author  Adrian Wojcik    adrian.wojcik@put.poznan.pl
%  @version V1.0
%  @date    29-Mar-2022
%  @brief   Simple UDP server with receive callback
%
% ************************************************************************

server_ip = '172.27.224.1'; % MATLAB / Python server [PC]
server_port = 20000;

udp_server_port = udpport("datagram","IPV4", ...
                          "LocalPort", server_port, ...
                          "LocalHost", server_ip);

configureCallback(udp_server_port,"datagram", 1, @serverCallback);

disp("[MATLAB] UDP server up and listening.")

