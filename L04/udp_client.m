%% UDP CLIENT

%%% File info
%
% ************************************************************************
%
%  @file    udp_client.m
%  @author  Adrian Wojcik    adrian.wojcik@put.poznan.pl
%  @version V1.0
%  @date    29-Mar-2022
%  @brief   Simple UDP client with receive loop in blocking mode
%
% ************************************************************************

%server_ip = '192.168.1.181'; % MATLAB server [PC]
server_ip = '192.168.0.32'; % C / Python server [RPi]
server_port = 20000;

udp_client_port = udpport("datagram","IPV4");

udp_send = @(data)( write(udp_client_port, char(data), server_ip, server_port) );

udp_send(1);

while 1

    if udp_client_port.NumDatagramsAvailable > 0
    
        % Read the data received from the other udpport instance.
        datagram = read(udp_client_port, udp_client_port.NumDatagramsAvailable, "uint8");
                
        % get datagram components
        data = char(datagram.Data);
        
        % Prepare the acknowledgement string.
        time = datestr(now, 'HH:MM:SS.FFF');
        dataDisp = "Server response [" + time + "]: " + data;
        
        disp(dataDisp);

    end

end