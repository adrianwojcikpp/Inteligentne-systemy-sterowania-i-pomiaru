udp_server_port = udpport('LocalHost', '192.168.0.15','LocalPort', 8000);
configureCallback(udp_server_port,"terminator",@sendAcknowledgement);