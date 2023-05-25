%% MRAC SYSTEM DESIGN

%%% File info 
%
% ************************************************************************
%
%  @file     LAB05_Design_MRAC_system.m
%  @author   Adrian Wojcik
%  @version  1.0
%  @date     31-May-2019 10:54:57
%  @brief    Design Model-Reference Neural Controller in MATLAB
%            Based on: https://www.mathworks.com/help/deeplearning/ug/
%             create-reference-model-controller-with-matlab-script.html
% ************************************************************************
%
clear all; close all; clc;

%% System sample time

Ts = 0.05; % [s]

%% Load training data
    
    % TODO: CHANGE PLANT IDENTIFICATION DATA
    [u,y] = robotarm_dataset;

%% Create NARX network - MODEL
d1 = 0:1; % input delay 1 
d2 = 1:2; % input delay 2
S1 = 5;   % hidden layer size
narx_net = narxnet(d1,d2,S1);
nart_net.sampletime = Ts;
narx_net.divideFcn = '';
narx_net.inputs{1}.processFcns = {};
narx_net.inputs{2}.processFcns = {};
narx_net.outputs{2}.processFcns = {};

%% Model training
narx_net.trainParam.epochs = 5000;
narx_net.trainParam.min_grad = 1e-10;

[p,Pi,Ai,t] = preparets(narx_net,u,{},y);

narx_net = train(narx_net,p,t,Pi);

narx_net_closed = closeloop(narx_net);
view(narx_net_closed)

%% Create NARX network - MRAC system
S2 = 5;
mrac_net = feedforwardnet([S2 1 S1]);
mrac_net.sampletime = Ts;
mrac_net.layerConnect = [0 1 0 1;1 0 0 0;0 1 0 1;0 0 1 0];
mrac_net.outputs{4}.feedbackMode = 'closed';
mrac_net.layers{2}.transferFcn = 'purelin';

mrac_net.layerWeights{3,4}.delays = 1:2;
mrac_net.layerWeights{3,2}.delays = 1:2;

mrac_net.layerWeights{3,2}.learn = 0;
mrac_net.layerWeights{3,4}.learn = 0;
mrac_net.layerWeights{4,3}.learn = 0;
mrac_net.biases{3}.learn = 0;
mrac_net.biases{4}.learn = 0;

mrac_net.divideFcn = '';
mrac_net.inputs{1}.processFcns = {};
mrac_net.outputs{4}.processFcns = {};
mrac_net.name = 'Model Reference Adaptive Control Network';

mrac_net.layerWeights{1,2}.delays = 1:2;
mrac_net.layerWeights{1,4}.delays = 1:2;
mrac_net.inputWeights{1}.delays = 1:2;

%% Configure NN MODEL

    % TODO: CHANGE CLOSE LOOP TRAINING DATA
    [refin,refout] = refmodel_dataset;

ind = 1:length(refin);
figure('Name', 'Reference model training data');
plot(ind,cell2mat(refin),ind,cell2mat(refout))
    
mrac_net = configure(mrac_net,refin,refout);

%% Put model inside MRAC system
mrac_net.LW{3,2} = narx_net_closed.IW{1};
mrac_net.LW{3,4} = narx_net_closed.LW{1,2};
mrac_net.b{3} = narx_net_closed.b{1};
mrac_net.LW{4,3} = narx_net_closed.LW{2,1};
mrac_net.b{4} = narx_net_closed.b{2};

%% Training plots
mrac_net.plotFcns = { 'plotperform','plottrainstate',...
                      'ploterrhist','plotregression','plotresponse'};
                  
mrac_net.trainFcn = 'trainlm';
view(mrac_net)

%% MRAC training
[x_tot,xi_tot,ai_tot,t_tot] = preparets(mrac_net,refin,{},refout);

mrac_net.trainParam.epochs = 5000;
mrac_net.trainParam.min_grad = 1e-10;

[mrac_net,tr] = train(mrac_net,x_tot,t_tot,xi_tot,ai_tot);

%% Test results
testin = skyline(1000,50,200,-.7,.7);
testinseq = con2seq(testin);
testoutseq = mrac_net(testinseq);
testout = cell2mat(testoutseq);
figure('Name', 'MRAC System Desigin results');
plot([testin' testout'])