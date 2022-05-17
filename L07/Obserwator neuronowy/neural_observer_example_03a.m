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
% Wywo³anie skryptu do zbierania danych
neural_observer_example_02
close all; % zamkniêcie wykresu

% Teraz mamy znormalizowane dane ucz¹ce X oraz wektor celów T zorientowane
% KOLUMNOWO. Nale¿y stworzyæ za pomoc¹ konstruktora obiektu network obiekt
% jednokierunkowej, w pe³ni po³¹czonej sieci neuronowej o 1 warstwie
% ukrytej (12 neuronów), 6 wejœciach (rozmiar wektora wejœciowego) oraz 1
% wyjœciu (aktualna próbka prêdkoœci).
% Funkcja aktywacji warstwy ukrytej - tansig, warstwy wyjœciowej - purelin.

% Za pomoc¹ funkcji train nale¿y dokonaæ treningu sieci na podstawie
% zadanego celu (targetu).

% Wygenerowaæ model sieci za pomoc¹ funkcji gensim. Rozbudowaæ KOPIÊ modelu
% symulacyjnego o bloki wstênego przetwarzania danych. Porównaæ odpowiedzi
% modelu referencyjnego i obserwatora na zadane sygna³y wejœciowe (np. skok
% jednostkowy napiêcia do po³owy wartoœci znamionowej). Sprawdziæ tak¿e
% zachowanie obserwatora po za³¹czeniu obci¹¿enia.

net = feedforwardnet(12); % 12 neuronów w warstwie ukrytej
[net, NetStruct] = train(net, X, T); % uczenie sieci
% view(net); % wyœwietlenie schematu sieci
gensim(net); % wygenerowanie bloczka simulinkowego