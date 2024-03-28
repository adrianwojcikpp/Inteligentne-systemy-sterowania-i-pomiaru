function serverCallback(u, ~)
    % Read the data received from the other udpport instance.
    datagram = read(u, u.NumDatagramsAvailable, "uint8");
            
    % get datagram components
    data = char(datagram.Data);
    assignin('base', 'response', jsondecode(data));
    senderAdress = datagram.SenderAddress;
    senderPort = datagram.SenderPort;
    
    time = datestr(now, 'HH:MM:SS.FFF');
    dataDisp = "Client message: [" + time + "]: " + data;
    disp(dataDisp);

    % Send the acknowledgement string.
    write(u, uint8('ACK from [MATLAB] server'), senderAdress, senderPort);
end