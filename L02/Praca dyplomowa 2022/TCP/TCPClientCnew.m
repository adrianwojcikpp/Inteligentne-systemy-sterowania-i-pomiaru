t = tcpclient("192.168.0.106",6788)
n = 10000
for i = 1:n


data = read(t,7,"char")
x = str2num(data)*10
write(t,num2str(x))

end
clear t