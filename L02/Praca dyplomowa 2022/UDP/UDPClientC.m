clear all
clc

y = [];
n = 200000; % nr of samples to take from server

u = udp('192.168.1.2',6789); %IP of PC
fopen(u);
fwrite(u,'Connection Succeed')
for i = 1:n
A = fread(u,100); 
y(i) = decodeStringData(A);
Processed = y(i) * 10
fwrite(u,num2str(Processed))
end
fclose(u)

%plot(y)
%50ms