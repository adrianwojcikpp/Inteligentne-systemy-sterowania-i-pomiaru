%%% File info 
%
% ************************************************************************
%
%  @file     01 Neural observer/neural_observer_example_03a.m
%  @author   Adrian Wojcik
%  @version  1.0
%  @date     12-Dec-2020 19:59:05
%  @brief    Stworzenie sieci neuronowej z poziomu skryptu
%
% ************************************************************************
%
close all; clear all; clc;
% Wywo�anie skryptu do zbierania danych
neural_observer_example_02
close all; % zamkni�cie wykresu

% Teraz mamy znormalizowane dane ucz�ce X oraz wektor cel�w T zorientowane
% KOLUMNOWO. Nale�y stworzy� za pomoc� konstruktora obiektu network obiekt
% jednokierunkowej, w pe�ni po��czonej sieci neuronowej o 1 warstwie
% ukrytej (12 neuron�w), 6 wej�ciach (rozmiar wektora wej�ciowego) oraz 1
% wyj�ciu (aktualna pr�bka pr�dko�ci).
% Funkcja aktywacji warstwy ukrytej - tansig, warstwy wyj�ciowej - purelin.

% Za pomoc� funkcji train nale�y dokona� treningu sieci na podstawie
% zadanego celu (targetu).

% Wygenerowa� model sieci za pomoc� funkcji gensim. Rozbudowa� KOPI� modelu
% symulacyjnego o bloki wst�nego przetwarzania danych. Por�wna� odpowiedzi
% modelu referencyjnego i obserwatora na zadane sygna�y wej�ciowe (np. skok
% jednostkowy napi�cia do po�owy warto�ci znamionowej). Sprawdzi� tak�e
% zachowanie obserwatora po za��czeniu obci��enia.

net = feedforwardnet(12); % 12 neuron�w w warstwie ukrytej
[net, NetStruct] = train(net, X, T); % uczenie sieci
% view(net); % wy�wietlenie schematu sieci
gensim(net); % wygenerowanie bloczka simulinkowego