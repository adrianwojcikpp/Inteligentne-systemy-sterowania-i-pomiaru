%% Parameters

    R = 0.472;   % [Ohm]
    L = 7.85e-3; % [H]
    k = 4.13;    % [V*s | Nm/A]
    J = 0.32;    % [kg*m^2]
    
    r = 100;
    ts = floor(r*L/R)/r / 10; % [s]
    
    wN = 157;    % [rad/s]
    mN = 525;    % [Nm]
    uN = 420;    % [V]
    iN = 127;    % [A]
    
%% State-space model

    A = [-R/L -k/L; k/J    0];
    B = [1/L     0;   0 -1/J]; 
    C = [0 1];
    D = [0 0];
    
    DCmotor = ss(A,B,C,D);
    DCmotorSISO = ss(A,B(:,1),C,D(:,1));
    
    discretization_method = {'zoh', 'foh','impulse','tustin','matched'};
    
    DCmotorSISOdiscrete = c2d(DCmotorSISO, ts, discretization_method{1});
    
    [DCmotorA, DCmotorB] = ss2tf( DCmotorSISOdiscrete.A, ...
                                  DCmotorSISOdiscrete.B, ...
                                  DCmotorSISOdiscrete.C, ...
                                  DCmotorSISOdiscrete.D  );
                              
    DCmotorModel = tf(DCmotorA, DCmotorB, ts);

%% Reference model

    T1 = 10e-3; % [s]
    T2 =  5e-3; % [s]
    
    s = tf('s'); % s operator
    
    CloseLoopRef = 1 / (T1*s + 1)*(T2*s + 1);
    
%% Clear memory

    clearvars -except DCmotor DCmotorModel DCmotorSISO CloseLoopRef