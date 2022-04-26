s = tf('s'); % complex number frequency parameter

%% First order system

    % Time constant
    T = 0.1; % [s]
    
    % Gain
    K = 0.5; % [-]
    
    % Transfer function
    G = K / (s*T + 1); % [-]
    
    K_org = K;
    T_org = T;

%% System step response

    % Sample time
    ts = 0.001; % [s]
    
    % Time vector
    t = (0 : ts : 1 - ts)'; % [s]
    
    % Input signal: step function
    u = [0; 0.5; ones(length(t)-2,1)];
    
    % Input signal: white noise
    u = wgn(length(t), 1, 1);
    %u = 10*randn(length(t),1);
    
    % Output signal: system response
    y = lsim(G, u, t);
    
    % Plot result
    stairs(t,y); grid on;
    xlabel('Time [s]');
    ylabel('Output signal [-]');
    title('System step response');
    
%% System identification
    
    data = iddata(y,u,ts);
    
    G_ident = tfest(data, 1);
    [num, den] = tfdata(G_ident);

    K_ident = num{1}(end) / den{1}(end);
    T_ident = den{1}(1) / den{1}(end); 
