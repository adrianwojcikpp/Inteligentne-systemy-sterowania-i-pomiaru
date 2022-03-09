clear all
clc

y = [];
n = 1000000; % nr of samples to take from server
t = tcpip('192.168.0.106',6789); %IP of PC
fopen(t);

%fwrite(u,'Connection Succeed')
for i = 1:n

A = fread(t,7); 
y(i) = decodeStringData(A);
Processed = y(i) *10
fwrite(t,num2str(Processed))

end
fclose(t)
