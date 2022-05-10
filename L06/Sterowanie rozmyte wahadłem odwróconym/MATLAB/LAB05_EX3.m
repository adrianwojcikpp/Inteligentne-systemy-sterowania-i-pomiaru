%% INVERSE PENDULUM

%%% File info
%
% ************************************************************************
%
%  @file    /L05/LAB05_EX3.m
%  @author  Adrian Wojcik
%  @version V1.0
%  @date    10-MAr-2018
%  @brief   inverse pendulum fuzzy controller ex. 2 
%
% ************************************************************************

%% Create FIS structure

    fis_name = 'Inverse Pendulum Full State Controller';
    InvPendulumController = sugfis('Name', fis_name);
   
    InvPendulumController.andMethod = 'min';
    InvPendulumController.orMethod = 'max';
    InvPendulumController.defuzzMethod = 'wtaver';
    InvPendulumController.impMethod = 'prod';
    InvPendulumController.aggMethod = 'sum';
    
%% Add inputs

    m = 6; % number of inputs

    % Input #1: reference linear position
    refPosition.name = 'refPosition';
    refPosition.number = 1;
    refPosition.range = [-5 5]; %[m]
    InvPendulumController = addInput(InvPendulumController, refPosition.range, 'Name', refPosition.name);

    % Input #2: angular position
    angularPosition.name = 'angularPosition';
    angularPosition.number = 2;
    angularPosition.range = [-2*pi 2*pi]; %[rad]
    InvPendulumController = addInput(InvPendulumController, angularPosition.range, 'Name', angularPosition.name);

    % Input #3: angular velocity
    angularVelocity.name = 'angularVelocity';
    angularVelocity.number = 3;
    angularVelocity.range = [-5 5]; %[rad/s]
    InvPendulumController = addInput(InvPendulumController, angularVelocity.range, 'Name', angularVelocity.name);
    
    % Input #4: linear position
    linearPosition.name = 'linearPosition';
    linearPosition.number = 4;
    linearPosition.range = [-5 5]; %[m]
    InvPendulumController = addInput(InvPendulumController, linearPosition.range, 'Name', linearPosition.name);
    
    % Input #5: linear velocity
    linearVelocity.name = 'linearVelocity';
    linearVelocity.number = 5;
    linearVelocity.range = [-20 20]; %[m/s]
    InvPendulumController = addInput(InvPendulumController, linearVelocity.range, 'Name', linearVelocity.name);
                
    % Input #6: pendulum length
    pendulumLength.name = 'pendulumLength';
    pendulumLength.number = 6;
    pendulumLength.range = [0.1 8.1];

    InvPendulumController = addInput(InvPendulumController, pendulumLength.range, 'Name', pendulumLength.name);
                     
    % Pendulum length - short
    InvPendulumController = addMF(InvPendulumController, pendulumLength.name, ...
                    @trimf, [0.1 0.1 3.1], 'Name', 'short');
    
    % Pendulum length - medium
    InvPendulumController = addMF(InvPendulumController, pendulumLength.name, ...
                    @trimf, [0.1 3.1 8.1], 'Name', 'medium');
    
    % Pendulum length - long
    InvPendulumController = addMF(InvPendulumController, pendulumLength.name, ...
                    @trimf, [3.1 8.1 8.1], 'Name', 'long');
    
    if PLOT_ENABLE    
    figure('Name','Input functions');
    plotmf(InvPendulumController, 'input', pendulumLength.number, 1001);
    end
    
%% Add outputs

    n = 1; % number of outputs
    
    % Output #1: hot water
    force.name = 'force';
    force.number = 1;
    force.range = [-50 50];
    
    force.mfName = {'K1', 'K2', 'K3'};
    
    InvPendulumController = addOutput(InvPendulumController, force.range, 'Name', force.name);
    
    for i = 1 : length(force.mfName)
        InvPendulumController = addMF(InvPendulumController, force.name, ...
                          @linear, [Nbar_selceted(i) -K_selected{i} 0 0], 'Name', force.mfName{i});
    end
        
%% Add rules

    rule1 = "If pendulumLength is short then force is K1";
    rule2 = "If pendulumLength is medium then force is K2";
    rule3 = "If pendulumLength is long then force is K3";
    rules = [rule1 rule2 rule3];
         
    InvPendulumController = addRule(InvPendulumController,rules);
        
%% Run simulation

     system_name = 'wahadlo_fuzzy_noanim';
     load_system(system_name);
     sim(system_name); pause(2);
     posFuzzy = position2.signals(1).values(:,2);
     posRefFuzzy = position2.signals(1).values(:,1);
     posLength = position2.signals(1).values(:,3);
     posLength = 2*(posLength-min(posLength))/(max(posLength)-min(posLength))-1;
     save_system(system_name);close_system(system_name);
  
%% Plot results

    figure('Name','Fuzzy system');
    plot(position2.time, posFuzzy,  'k', 'LineWidth',3); hold on;
    plot(position2.time, posRefFuzzy,  'r', 'LineWidth',1); grid on;
    plot(position2.time, posLength,  'b:', 'LineWidth',1); 
    xlabel('Time [s]');
    ylabel('Position [m]');
    legend({'Position','Reference value', 'Pendulum length (normalized)'});
    
%% Clear variables

    %clearvars -except n FullStateFeedbackController InvPendulumController sysRef 