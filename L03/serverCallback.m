function serverCallback(u, ~)
    % Read the data received from the other udpport instance.
    datagram = read(u, u.NumDatagramsAvailable, "uint8");
            
    % get datagram components
    data = char(datagram.Data);
    senderAdress = datagram.SenderAddress;
    senderPort = datagram.SenderPort;
    
    % Prepare the acknowledgement string.
    dataDisp = "Client message: " + data;
    
    disp(dataDisp);
    write(u, uint8('Hello from [MATLAB] server'), senderAdress, senderPort);
end