function clientCallback(u, ~)
    % Read the data received from the other udpport instance.
    datagram = read(u, u.NumDatagramsAvailable, "char");
    data = datagram.Data;
    
    % read application data
    app_data = str2double(strsplit(data, ',')); % text -> double

    t = app_data(1) / 1e6; % ms -> s 
    u = app_data(2);
    y = app_data(3);
        
    % print application data on console
    time = datestr(now, 'HH:MM:SS.FFF');
    dataDisp = "[" + time + "] t = " + num2str(t,"%.2f") + " s, u = " + ...
        num2str(u,4) + ", y = " + num2str(y,4);        
    
    disp(dataDisp);
end