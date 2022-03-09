
udps = dsp.UDPSender('RemoteIPAddress','192.168.56.102','RemoteIPPort',8881,'SendBufferSize',1024)

u = udp('192.168.56.102','LocalPort',8893);

fopen(u);

array = [];


for i = 1:100
%Send to get number
dataSent = uint8(0.43242);
udps(dataSent)

% get value
A = fread(u,10)
array(i) = A(2)
end

fclose(u)
plot(array)