s = tf('s'); % complex number frequency parameter

%% First order system

    % Time constant
    T = 0.1; % [s]
    
    % Gain
    K = 0.5; % [-]
    
    % Transfer function
    G = K / (s*T + 1); % [-]
    
%% System step response

    % Sample time
    ts = 0.001; % [s]
    
    % Time vector
    t = (0 : ts : 1 - ts)'; % [s]
    
    % Input signal: step function
    u = [0; 0.5; ones(length(t)-2,1)];
    
    % Input signal: white noise
    %u = wgn(length(t), 1, 1);
    %u = 10*randn(length(t),1);
    
    % Output signal: system response
    y = lsim(G, u, t);
    
    % Plot result
    stairs(t,y); grid on;
    xlabel('Time [s]');
    ylabel('Output signal [-]');
    title('System step response');
    
%% System discretization

    H = c2d(G, ts, 'tustin');
    
    a1_org = -H.den{1,1}(2);
    b0_org = H.num{1,1}(1);
    b1_org = H.num{1,1}(2);
    
%% System identification
    
    yd1 = [0; y(1:end-1)]; % y(k-1)
    ud1 = [0; u(1:end-1)]; % u(k-1)
    %ud2 = [0; 0; u(1:end-2)]; % u(k-2)
    
    % Regressor matrix
    phi = [yd1 u ud1]; 
    
    % Least squares method
    p_ident = (phi.' * phi)^(-1) * phi.' * y;
    a1_ident = p_ident(1);
    b0_ident = p_ident(2);
    b1_ident = p_ident(3);
