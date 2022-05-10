%% INVERSE PENDULUM

%%% File info
%
% ************************************************************************
%
%  @file    /L05/LAB05_EX1_2.m
%  @author  Adrian Wojcik
%  @version 2.0
%  @date    02-Apr-2022
%  @brief   inverse pendulum fuzzy controller ex. 1 and 2 
%
% ************************************************************************
clear all; close all; clc;  bdclose all;

    PLOT_ENABLE = 1;
    DISP_ENABLE = 1;

%% System
system_name = 'wahadlo';
system_block_name = [system_name '/' 'Odwrocone wahadlo'];
load_system(system_name);
% System *operating point*
% pendulum angle, pendulum angular velocity, cart position, cart speed
operating_point = [0.0, 0.0, 0.0, 0.0]; 
operating_point_name = 'init_cond';

set_param(system_block_name, operating_point_name, ... 
          ['[' num2str(operating_point) ']']);

% Pendulum length range
p_length = logspace(log10(0.1), log10(8), 15);
%p_length = linspace(0.1, 20, 10);
p_length = unique(round(p_length, 1));       
% System *parameters*
% pendulum length [m], pendulum mass [kg], cart mass [kg], g-force [m/s2]
parameters = [p_length(1), 0.1, 1.0, 9.8]; 
parameters_name = 'specs';  
% Linearization about Operating Point 
model = cell(size(p_length));

for i = 1 : length(p_length)
    
   % change parameters
   parameters(1) = p_length(i);
   set_param(system_block_name, parameters_name, ... 
          ['[' num2str(parameters) ']']); pause(2);
    
   % get model
   [A,B,C,D] = linmod(system_name);
   
   model{i} = ss(A,B,C,D);
   model{i}.Name = ['Cart with Pendulum linearized model at L=' num2str(p_length(i)) ' m']; 
end
save_system(system_name);close_system(system_name);

%% Plot zeros and poles
if PLOT_ENABLE
figure('Name','Linearized model poles');
c = 'rgbcmyk';
subplot(1,2,1);
for i = 1 : length(model)
    h = pzplot(model{i}, c(mod(i,length(c))+1)); hold on;
    if DISP_ENABLE
    disp(model{i}.Name);
    disp('Poles:'); disp(sort(eig(model{i}))');
    end
end

pzo = getoptions(h);
pzo.Grid = 'on';
pzo.FreqUnits = 'Hz';
setoptions(h,pzo);
hold off;

poles = zeros(size(model));
for i = 1 : length(model)
    p = eig(model{i});
    poles(i) =  p(3);
end

subplot(1,2,2);
plot(p_length,poles,'b*-'); hold on;
grid on;
ylabel('Real Axis');
xlabel('Pendulum length');
title('System dynamics as a function of pendulum length');
%axis([0 8 0 13]);
end
%% Poles-placement
    
    % reference close-loop dynamics
        sysRef.wn1 = sqrt(2);          % [rad/s]
        sysRef.zeta1 = sqrt(2)/2;      % [-]
        sysRef.tau1 = 1./(sysRef.zeta1.*sysRef.wn1); % [s]
        sysRef.wn2 = 2.00;             % [rad/s]
        sysRef.zeta2 = 1.00;           % [-]
        sysRef.tau2 = 1./(sysRef.zeta2.*sysRef.wn2); % [s]
        sysRef.kn = 1;                 % [m/N]
        s = tf('s');                   % s-operator
        sysRef.TF = sysRef.kn / ((s^2 / sysRef.wn1^2 + 2*sysRef.zeta1*s / sysRef.wn1 + 1)*...
                                 (s^2 / sysRef.wn2^2 + 2*sysRef.zeta2*s / sysRef.wn2 + 1));                                
    
    poleRef = pole(sysRef.TF); % [-2, -2, -1+1i, -1-1i];  %

    if DISP_ENABLE
    disp('Poles placement - reference poles of closed system: '); disp(sort(poleRef)');
    end
    
    % State feedback gain
    K = cell(size(model));
    % Scale factors vector
    Nbar = zeros(size(p_length));
   
    for i = 1 : length(model)
        K{i} = place(model{i}.a, model{i}.b, poleRef); 
        Nbar(i) = rscale(model{i}.a, model{i}.b, [0 0 1 0], 0, K{i});
        poleResult = eig(model{i}.a-model{i}.b*K{i})';
        zeroResult = zero(ss(model{i}.a-model{i}.b*K{i},model{i}.b*K{i}*[0;0;1;0],[0 0 1 0],0));
        if DISP_ENABLE
        disp(['[' num2str(i) '.P] Closeed system poles (L=' num2str(p_length(i)) '): ']);
        disp(sort(poleResult));
        disp(['[' num2str(i) '.Z] Position control loop zeros (L=' num2str(p_length(i)) '):']);
        disp(sort(zeroResult)');
        end
    end
    
%% Plot feedback gains

    K_plot = reshape(cell2mat(K),[4,length(p_length)]);
    K_plot = abs(K_plot) ./ max(abs(K_plot),[],2);
    if PLOT_ENABLE
    figure('Name','Normalized feedback gain');
    plot(p_length, K_plot); hold on; grid on;
    title('Full state feedback gain values');
    xlabel('Pendulum length [m]');
    ylabel('Normalized gain [-]');
    legend('Angular position fb gain', 'Angular velocity fb gain', ...
           'Linear position fb gain', 'Linear velocity fb gain');
    
    hold off;
    end
    
%% Variable reassignment

    FullStateFeedbackController.Gain = K;
    FullStateFeedbackController.Scale = Nbar;
    FullStateFeedbackController.OpPoint = p_length';
    
    indx_selected = [1 10 13];
    K_selected = cell(size(indx_selected));
    Nbar_selceted = zeros(size(indx_selected));

    for indx = 1 : length(indx_selected)
        K_selected{indx} = K{indx_selected(indx)};
        Nbar_selceted(indx) = Nbar(indx_selected(indx));
    end

%% Run simulation

  system_name = 'wahadlo_stabil_noanim';
  load_system(system_name);
  pos = cell(size(p_length)); posRef = pos;
  for i = 1 : length(p_length)
     n = i;
     sim(system_name); pause(2);
     pos{i} = position.signals(1).values(:,2);
     posRef{i} = position.signals(1).values(:,1);
  end
  save_system(system_name);close_system(system_name);
  
%% Plot results

    figure('Name','Step responses');
    plot(position.time, pos{1},  'g', 'LineWidth',3); hold on;
    plot(position.time, pos{end},'b', 'LineWidth',3); grid on;
    
    for i = 2 : length(p_length)-1
        plot(position.time, pos{i}, 'k');
    end
    plot(position.time, posRef{1},  'r:', 'LineWidth',1); hold on;
      
    xlabel('Time [s]');
    ylabel('Position [m]');
    title('Position - step respone as a function of pendulum length');
    legend('L=0.1','L=8');