function clientCallback(u, ~)
    % Read the data received from the other udpport instance.
    datagram = read(u, u.NumDatagramsAvailable, "uint8");
            
    % get datagram components
    data = jsondecode(char(datagram.Data));
    
    % Prepare the acknowledgement string.
    time = datestr(now, 'HH:MM:SS.FFF');
    dataDisp = "Server response [" + time + "]: " + data.angle;
    
    disp(dataDisp);
end