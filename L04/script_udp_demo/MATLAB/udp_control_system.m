%
% ************************************************************************
%
%  @file    udp_control_system.m
%  @author  AW    Adrian.Wojcik@put.poznan.pl
%  @version 1.0
%  @date    13-May-2023
%  @brief   Simple UDP control routine
%
% ************************************************************************
%
%% Plots setup

iteration_max = 1000000;  % number of data points
figure();
subplot(2,1,1);
    hpu = plot(nan(iteration_max,1),nan(iteration_max,1), 'b', 'LineWidth', 2);
    xlabel('Time [s]'); 
    ylabel('Control signal [-]');
    hold on; grid on;
subplot(2,1,2);
    hpy = plot(nan(iteration_max,1),nan(iteration_max,1), 'r', 'LineWidth', 2);
    xlabel('Time [s]');
    ylabel('Measurement signal [-]');
    hold on; grid on;
 hplot = [hpu, hpy];

%% Controller setup 
u_vec = [ones(2500,1); -ones(2500,1); zeros(1000,1)];

%% UDP client setup
%remote_ip = '192.168.1.248';  % C / Python server [RPi]
remote_ip = '172.27.229.191'; % C / Python server [WSL]
remote_port = 20000;

local_port = udpport("datagram","IPV4");

udp_send = @(data)( write(local_port, char(num2str(data)), remote_ip, remote_port) );
udp_receive = @()( read(local_port, local_port.NumDatagramsAvailable, "char") );

%configureCallback(udp_client_port,"datagram", 1, @clientCallback);

udp_send(0); % send first message to get reposonse 

%% Control loop
iteration = 0;
while 1
    if local_port.NumDatagramsAvailable > 0
    
        iteration = iteration + 1;

        % get datagram 
        datagram = udp_receive();
        data = datagram.Data;
                
        % read application data
        app_data = str2double(strsplit(data, ',')); % text -> double

        t = app_data(1) / 1e6; % ms -> s 
        u = app_data(2);
        y = app_data(3);

        % print application data on console
        %console_update(t, u, y);

        % plot application data as time series
        plot_update(hplot, iteration, iteration_max, t, u, y)
        
        % send new control input
        udp_send(u_vec(1+mod(iteration,length(u_vec))));

    end
end

function console_update(t, u, y)
    time = datestr(now, 'HH:MM:SS.FFF');
    dataDisp = "[" + time + "] t = " + num2str(t,"%.2f") ...
        + " s, u = " + num2str(u,4) ...
        + ", y = " + num2str(y,4);        
    disp(dataDisp);
end

function plot_update(hplot, iteration, iteration_max, t, u, y)
    if iteration > iteration_max
        hplot(1).YData = circshift(hplot(1).YData, -1); 
        hplot(1).YData(end) = u; 
        hplot(1).XData = circshift(hplot(1).XData, -1); 
        hplot(1).XData(end) = t; 
        hplot(2).YData = circshift(hplot(2).YData, -1); 
        hplot(2).YData(end) = y; 
        hplot(2).XData = circshift(hplot(2).XData, -1); 
        hplot(2).XData(end) = t;
    else
        hplot(1).YData(iteration) = u; 
        hplot(1).XData(iteration) = t; 
        hplot(2).YData(iteration) = y; 
        hplot(2).XData(iteration) = t; 
    end
end
