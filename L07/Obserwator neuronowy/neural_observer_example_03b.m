%%% File info 
%
% ************************************************************************
%
%  @file     01 Neural observer/neural_observer_example_03b.m
%  @author   Adrian Wojcik
%  @version  1.0
%  @date     12-Dec-2020 19:59:05
%  @brief    Dzia³anie uk³adu ze sztuczn¹ sieci¹ neuronow¹
%
% ************************************************************************
%
close all; clear all; clc;
%% DANE WEJŒCIOWE
% Okres próbkowania i czas symulacji
Tp = 1e-3;  % [s]
% Przynajmniej 10x mniejszy od sta³ej elektrycznej L/R = 0.0166.
Tsim = 0.5;	% [s]

% Wartoœci znamionowe
w_N = 157;  % [rad/s]
m_N = 525;  % [Nm]
u_N = 420;  % [V]
i_N = 127;  % [A]

% Parametry modelu
R = 0.472;  % [Om]
L = 7.85e-3;% [H]
kfi = 4.13; % [Vs]
J = 0.32;   % [kg*m^2]

% Dane wejœciowe
t_load = 0.3;   	% czas za³¹czenia momentu oporowego
i_z = 20;           % zadana wartoœæ pr¹du p³yn¹cego przy za³¹czeniu momentu oporowego
m_load = kfi*i_z;	% wartoœæ momentu oporowego
u_in = 200;         % napiêcie zasilaj¹ce

%% URUCHOMIENIE SYMULACJI

%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Wymuszenie skokowe %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%
sigSelect = 1;
sim('neural_observer_DC');

% Wykresy na podstawie zebranych danych
figure;
plot(tout, w_out, 'r', tout, w_est, 'b');
set(gcf, 'Position', [10, 190, 1000, 620]);
legend('\omega_{wy}', '\omega_{est}');
set(legend, 'FontSize', 11, 'Location', 'best');
xlabel('czas [s]', 'FontSize', 12);
ylabel('Prêdkoœæ k¹towa [rad/s]', 'FontSize', 11);
title(['Dzia³anie modelu silnika obcowzbudnego pr¹du sta³ego z neuronowym obserwatorem stanu', ...
    ' - wymuszenie skokowe'], 'Fontsize', 11, 'FontWeight', 'bold');
grid on;

% Obliczenie b³êdu ca³kowitego i naniesienie jego wartoœci na wykresie
error_w = sqrt(sum((w_est - w_out).^2) / length(w_est));
Bounds = get(gca, 'ylim');
UpperBound = Bounds(2);
rmse_text = text(0.07, UpperBound * 0.22, ...
    ['$E = \sqrt{\frac{1}{M}\sum_{k=1}^{M} \left(\omega_{est}^{(k)} - \omega_{wy}^{(k)}\right)^2} = $', ...
    num2str(error_w)], 'FontSize', 14, 'Interpreter', 'latex');
set(rmse_text, 'BackgroundColor', [1 1 0], 'EdgeColor', 'r');

%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Wymuszenie liniowe %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%
sigSelect = 2;
sim('neural_observer_DC');

% Wykresy na podstawie zebranych danych
figure;
plot(tout, w_out, 'r', tout, w_est, 'b');
set(gcf, 'Position', [10, 190, 1000, 620]);
legend('\omega_{wy}', '\omega_{est}');
set(legend, 'FontSize', 11, 'Location', 'best');
xlabel('czas [s]', 'FontSize', 12);
ylabel('Prêdkoœæ k¹towa [rad/s]', 'FontSize', 11);
title(['Dzia³anie modelu silnika obcowzbudnego pr¹du sta³ego z neuronowym obserwatorem stanu', ...
    ' - wymuszenie liniowe'], 'Fontsize', 11, 'FontWeight', 'bold');
grid on;

% Obliczenie b³êdu ca³kowitego i naniesienie jego wartoœci na wykresie
error_w = sqrt(sum((w_est - w_out).^2) / length(w_est));
rmse_text = text(0.07, 5, ...
    ['$E = \sqrt{\frac{1}{M}\sum_{k=1}^{M} \left(\omega_{est}^{(k)} - \omega_{wy}^{(k)}\right)^2} = $', ...
    num2str(error_w)], 'FontSize', 14, 'Interpreter', 'latex');
set(rmse_text, 'BackgroundColor', [1 1 0], 'EdgeColor', 'r');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Wymuszenie sinusoidalne %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
sigSelect = 3;
sim('neural_observer_DC');

% Wykresy na podstawie zebranych danych
figure;
plot(tout, w_out, 'r', tout, w_est, 'b');
set(gcf, 'Position', [10, 190, 1000, 620]);
legend('\omega_{wy}', '\omega_{est}');
set(legend, 'FontSize', 11, 'Location', 'best');
xlabel('czas [s]', 'FontSize', 12);
ylabel('Prêdkoœæ k¹towa [rad/s]', 'FontSize', 11);
title(['Dzia³anie modelu silnika obcowzbudnego pr¹du sta³ego z neuronowym obserwatorem stanu', ...
    ' - wymuszenie sinusoidalne'], 'Fontsize', 11, 'FontWeight', 'bold');
grid on;

% Obliczenie b³êdu ca³kowitego i naniesienie jego wartoœci na wykresie
error_w = sqrt(sum((w_est - w_out).^2) / length(w_est));
rmse_text = text(0.02, -70, ...
    ['$E = \sqrt{\frac{1}{M}\sum_{k=1}^{M} \left(\omega_{est}^{(k)} - \omega_{wy}^{(k)}\right)^2} = $', ...
    num2str(error_w)], 'FontSize', 14, 'Interpreter', 'latex');
set(rmse_text, 'BackgroundColor', [1 1 0], 'EdgeColor', 'r');