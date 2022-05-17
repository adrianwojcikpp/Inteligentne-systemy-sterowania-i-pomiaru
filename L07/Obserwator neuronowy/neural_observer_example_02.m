%%% File info 
%
% ************************************************************************
%
%  @file     01 Neural observer/neural_observer_example_02.m
%  @author   Adrian Wojcik
%  @version  1.0
%  @date     12-Dec-2020 19:59:05
%  @brief    Przygotowanie danych ucz�cych
%
% ************************************************************************
%
close all; clear all; clc;
%% DANE WEJ�CIOWE
% Okres pr�bkowania i czas symulacji
Tp = 1e-3;  % [s]
% Przynajmniej 10x mniejszy od sta�ej elektrycznej L/R = 0.0166.
Tsim = 10;	% [s]
NN = 100;   % zmiana warto�ci napi�cia

% Warto�ci znamionowe
w_N = 157;  % [rad/s]
m_N = 525;  % [Nm]
u_N = 420;  % [V]
i_N = 127;  % [A]

% Parametry modelu
R = 0.472;  % [Om]
L = 7.85e-3;% [H]
kfi = 4.13; % [Vs]
J = 0.32;   % [kg*m^2]

% Dane wej�ciowe
t_load = 0.3;   	% czas za��czenia momentu oporowego
i_z = 0;            % zadana warto�� pr�du p�yn�cego przy za��czeniu momentu oporowego
% WA�NE - do danych ucz�cych warto�� momentu oporowego musi by� zerowa.
m_val = kfi*i_z;	% warto�� momentu oporowego

% Pusty wektor napi�cia steruj�cego
tt_in = 0:Tp:Tsim;
m_load = zeros(1, Tsim/Tp+1);
% Za��czenie momentu oporowego
m_load(t_load/Tp:end) = m_val;
u_in = 200*ones(1, Tsim/Tp+1);
% Wype�nienie ka�dych NN pr�bek wektora warto�ciami losowymi <0, u_N>
for jj = 1:length(u_in)/NN
    u_in(1+(jj-1)*NN : jj*NN) = u_N*rand();
end

%% URUCHOMIENIE SYMULACJI
sim('model_sym_DC');

% Wykresy na podstawie zebranych danych
[hAx,hLine1,hLine2] = plotyy(tout, w_out, tout, i_out);
set(gcf, 'Position', [10, 190, 1000, 620]);
legend('\omega_{wy}', 'i_{wy}');
set(legend, 'FontSize', 11);
xlabel('czas [s]', 'FontSize', 12);
ylabel(hAx(1), 'Pr�dko�� k�towa [rad/s]', 'FontSize', 11);
ylabel(hAx(2), 'Pr�d [A]', 'FontSize', 11);
title('Dzia�anie modelu silnika DC po podaniu na wej�cie wektora ucz�cego', ...
    'Fontsize', 11, 'FontWeight', 'bold');
grid on;

%% ZEBRANIE DANYCH UCZ�CYCH
% SKALOWANIE - DZIELENIE PRZEZ WARTO�CI ZNAMIONOWE!!!
% Wektor cel�w
T = w_out' / w_N;
% Wektor ucz�cy
X = [   u_in/u_N;                       % u(k)
       [0, u_in(1:end-1)/u_N];          % u(k-1)
       [0,  0, u_in(1:end-2)/u_N];      % u(k-2)
        i_out'/i_N;                     % i(k)
       [0, i_out(1:end-1)'/i_N];        % i(k-1)
       [0, 0, i_out(1:end-2)'/i_N]  ];	% i(k-2)