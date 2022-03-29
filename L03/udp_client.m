udp_client_port = udpport('LocalHost', '192.168.0.15','LocalPort', 9000);
configureCallback(udp_client_port,"terminator",@readAcknowledgement);
udp_send = @(data)( writeline(udp_client_port, data, udp_client_port.LocalHost, 8000));